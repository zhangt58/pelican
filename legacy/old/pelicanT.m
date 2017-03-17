function [fieldArray,pardis] = pelicanT (inputPanel)
% pelicanT Time-dependent mode wrap of pelican
% Usage: [fieldArray,pardis] = pelicanT (inputPanel)
% 	Input parameters:
% 		inputPanel: cell array, from which parameters can be read as
% 			bundis   = inputPanel{1}; bunch pos, s, [m]
%			curdis   = inputPanel{2}; current along bunch, I0, [A]
%			bmsdis   = inputPanel{3}; beam size, sigmax, [m]
%			pardis   = inputPanel{4}; longitudinal phase space
%			lambdas  = inputPanel{5}; FEL central wavelength, [m]
%			zsep   	 = inputPanel{6}; slice seperation in lambdas
%			lambdau  = inputPanel{7}; undulator period length, [m]
%			K0       = inputPanel{8}; undulator parameter, [Kx,Ky]
%			iutype   = inputPanel{9}; undulator type,'helical' or 'planar'
%			Nutot    = inputPanel{10}; total undulator periods
%			nstep    = inputPanel{11}; integration steps
%			nharm    = inputPanel{12}; max harminic for calc bf
%			iSave    = inputPanel{13}; if save every integration step
%			iParal   = inputPanel{14}; if parallel runnning enable
%			fieldiniX= inputPanel{15}; initial field in x
%			fieldiniY= inputPanel{16}; initial field in y
%           errArray = inputPanel{17}: field error, [flag,kx(%),ky(%)]
% 	Output parameters:
% 		fieldArray : {zpos,fieldOut,powerOut,bunfOut};
% 		pardis: particle distribution;
%
%   Program version number: 1.0
%   Author: Tong Zhang <tzhang@sinap.ac.cn>
%   Modified: 14:39, Dec. 12, 2012 (v1.0)
%   Modified: 22:19, Dec. 12, 2012 (v1.1)
%
% update log:
% 1.0: TDP wrap of pelican, named to be pelicanT
% 1.1: pelican updated with field error concluded

% load parameters
bundis   = inputPanel{1};
curdis   = inputPanel{2};
bmsdis   = inputPanel{3};
pardis   = inputPanel{4};
lambdas  = inputPanel{5};
zsep   	 = inputPanel{6};
lambdau  = inputPanel{7};
K0Array  = inputPanel{8};
iutype   = inputPanel{9};
Nutot    = inputPanel{10};
nstep    = inputPanel{11};
nharm    = inputPanel{12};
iSave    = inputPanel{13};
iParal   = inputPanel{14};
fieldiniX= inputPanel{15};
fieldiniY= inputPanel{16};
errArray = inputPanel{17};
%iTDP     = inputPanel{18};

nslice     = length(bundis);
paramArray = cell(nslice,1);
fieldOut   = zeros(nslice,2);
powerOut   = zeros(nslice,2);
bunfOut    = zeros(nslice,nharm);
zEntry     = floor(Nutot/zsep);
fieldArray = cell(zEntry,1);
field0     = [fieldiniX,fieldiniY];

for i = 1:nslice
    paramArray{i} = {K0Array,lambdau,iutype,lambdas,bmsdis(i),nstep,iSave,nharm,errArray};
end

if iParal ~= 1 % not parallel running
	%% first one zsep periods
	for i = 1:nslice
		[pardis{i},fieldOut(i,:),powerOut(i,:),bunfOut(i,:)] ...
			= pelican(pardis{i},field0,curdis(i),paramArray{i},zsep);
	end
	%
	% should re-binning
	%
	fieldArray{1} = {1*zsep*lambdau,fieldOut,powerOut,bunfOut}; 
	% #1: zpos (unit: m), #2: fld, #3: power, #4: bf

	%% all slippages total length ~ zentri*zsep
    for ii = 2:zEntry
        for i = 1:nslice-1
            [pardis{i},fieldOut(i,:),powerOut(i,:),bunfOut(i,:)] = ...
                pelican(pardis{i},fieldOut(i+1,:),curdis(i),paramArray{i},zsep);
        end
        [pardis{nslice},fieldOut(nslice,:),powerOut(nslice,:),bunfOut(nslice,:)] =...
            pelican(pardis{nslice},field0,curdis(nslice),paramArray{nslice},zsep);
        fieldArray{ii} = {ii*zsep*lambdau,fieldOut,powerOut,bunfOut};
    end
else % parallel running
    if ~ matlabpool('size') > 0
        matlabpool local
    end
    temppar = cell(nslice,1);
	parfor i = 1:nslice
		[temppar{i},fieldOut(i,:),powerOut(i,:),bunfOut(i,:)] ...
			= pelican(pardis{i},field0,curdis(i),paramArray{i},zsep);
	end
	pardis = temppar;
	fieldArray{1} = {1*zsep*lambdau,fieldOut,powerOut,bunfOut}; 
	% slippage
    tempfld = zeros(nslice,2);
    temppar = cell(nslice,1);
    for ii = 2:zEntry
        parfor i = 1:nslice-1
            [temppar{i},tempfld(i,:),powerOut(i,:),bunfOut(i,:)] = ...
                pelican(pardis{i},fieldOut(i+1,:),curdis(i),paramArray{i},zsep);
        end
        [temppar{nslice},tempfld(nslice,:),powerOut(nslice,:),bunfOut(nslice,:)] ...
            = pelican(pardis{nslice},field0,curdis(nslice),paramArray{nslice},zsep);
        pardis   = temppar;
        fieldOut = tempfld;
        fieldArray{ii} = {ii*zsep*lambdau,fieldOut,powerOut,bunfOut};
    end
end
end


%% function pelican 
function [parout, fldout, pout, bfout] = pelican (parin, fldin, I0in, paramArray, Nwig)
% pelican A one-dimensional free-electron laser simulation code
% Usage: [parout, fldout, pout] = pelican (parin, fldin, I0in, paramArray, Nwig)
%   input parameters:
%     parin = [gamin,psiin]: double array (npart x 1), input longitudinal phase space;
%     fldin = [Exin, Eyin]:   complex, input seed field, [v/m];
%     I0in: double, input current value, [A];
%     paramArray = {K0Array,lambdau,iutype,lambdas,sigmax,nstep,isave,nharm,errArray}; 
%                   cell, required parameters
%       K0:      double, undulator parameter; [Kx,Ky]
%       lambdau: double, undulator period length, [m];
%       iutype:  string, undulator type, 'planar' or 'helical';
%       lambdas: double, FEL central wavelength, [nm];
%       sigmax:  double, transverse rms beam size, [m];
%       nstep:   integer, integration steps for each period;
%       isave:   bool, 1 for save all results, fldout = [z, fld],
%                      0 only save the last one, fldout = fld;
%       nharm:   max harmonic for bunching factor calculation;
%       errArray: field error definition, [ierrer, rmskx(%), rmsky(%)]
%                          
%   output parameters:
%     parout = [gamout,psiout]:   output longitudinal phase space;
%     fldout = [Exout, Eyout]:    output seed field, if isave = 1, zpos is 1st col
%     pout   = [pxout, pyout]:    output power, if isave = 1, zpos is 1st col
% 	  bfout  = [bf(1)..bf(nharm)]:bunching factor,if isave = 1, zpos is 1st col
%
%   Program version number: 1.1
%   Author: Tong Zhang <tzhang@sinap.ac.cn>
%   Created:  21:12, Dec. 06, 2012 (1.0)
%   Modified: 10:56, Dec. 08, 2012 (1.1)
%   Modified: 22:14, Dec. 12, 2012 (1.2)
%   
%   update log:
%   1.0: complete main program of Pelican
%   1.1: output control flag, isave controls output gaincurve or not
% 		 add bunching factor output, nharm input parameter
%   1.2: include field error

%% constants
c0  = 299792458.0;    % speed of light, [m/s]
e0  = 1.60218e-19;  % electron charge, [Coulomb]
m0  = 9.10938e-31;  % electron mass, [kilogram]
u0  = pi*4.0e-7;    % vacuum permeability, [sec.volt/Amp.meter]
ep0 = 8.8542e-12;   % vacuum permittivity, [Amp.sec/meter.volt]

%%
% read input parameters
psi = parin(:,2); 	% phase
gam = parin(:,1); 	% lorentz factor
g0  = mean(gam);  	% central energy
eta = gam/g0-1;   	% relative energy spread

Ex    = fldin(1,1); % input Ex field
Ey    = fldin(1,2); % input Ey field
I0    = I0in;       % peak current, [Amp]

K0Array = paramArray{1}; % undulator parameter, central value,
lambdau = paramArray{2}; % undulator period, [m]
iutype  = paramArray{3}; % undulator type
lambdas = paramArray{4}; % FEL wavelength, [m]
sigmax  = paramArray{5}; % transverse rms beam size, [m]
nstep   = paramArray{6}; % total integration steps for each period length
isave   = paramArray{7}; % sign for saving gaincurve or not
nharm   = paramArray{8}; % maximum harmonic number of bunching factor for output
errArray= paramArray{9}; % field error defined array
Nu      = Nwig;          % forward length in unit of undulator period

ierror   = errArray(1); % flag for error enabled (1) or not
sigerrkx = errArray(2); % rms error in Kx (%)
sigerrky = errArray(3); % rms error in Ky (%)

Ab = pi*sigmax.^2; 		 % transverse beam area, [m^2]
j0 = I0./Ab;       		 % current density, [Amp/m^2]
ku = 2*pi/lambdau;    	 % undulator wavenumber [1/m]
ws = 2*pi*c0/lambdas; 	 % FEL angular frequency [1/m]
ndelz = lambdau/nstep; 	 % integration step size, [m]
coef1 = e0/m0/c0/c0/g0;
coef2 = u0*c0*c0/ws;
coef3 = u0*c0/4/g0;
totalstep = nstep*Nu; 	 % total integration step

if strcmp(iutype,'planar')
    K0 = K0Array(1);
    if ierror == 1 % field error defined
        KK0 = normrnd(K0,sigerrkx*K0, [1,totalstep]);
    else
        KK0 = K0*ones(1,totalstep);
    end
    if isave == 1 % save results after every integration step
		zzArray = zeros(totalstep,1); 	  % z-pos, [m]
		bfArray = zeros(totalstep,nharm); % bunching factor, bf{n} -> nth col
		ExArray = zeros(totalstep,1); 	  % Ex field
		EyArray = zeros(totalstep,1); 	  % Ey field
		b  = KK0.^2./(4+2*KK0.^2);
		JJ = besselj(0,b)-besselj(1,b);   % coupled bessel factor for planar undulator
 		for iz = 1:1:totalstep
			j1  = 2*j0*mean(exp(-1i*psi));
			eta = eta-coef1*real((KK0(iz)*JJ(iz)*Ex/2/g0-1i*coef2*j1)*exp(1i*psi))*ndelz;
			psi = psi+2*ku*eta*ndelz;   
			Ex  = Ex-coef3*KK0(iz)*JJ(iz)*j1*ndelz;
			zzArray(iz) = iz*ndelz;
			ExArray(iz) = Ex;
			for iharm = 1:nharm
				bfArray(iz,iharm) = mean(exp(-1i*iharm*psi));
			end
		end
	else % only save results after the last integration step
		bfArray = zeros(1,nharm); 
		b  = KK0.^2./(4+2*KK0.^2);
		JJ = besselj(0,b)-besselj(1,b); % coupled bessel factor for planar undulator
		for iz = 1:1:totalstep
			j1  = 2*j0*mean(exp(-1i*psi));
			eta = eta-coef1*real((KK0(iz)*JJ(iz)*Ex/2/g0-1i*coef2*j1)*exp(1i*psi))*ndelz;
			psi = psi+2*ku*eta*ndelz;   
			Ex  = Ex-coef3*KK0(iz)*JJ(iz)*j1*ndelz; 
		end
		for iharm = 1:nharm
			bfArray(iharm) = mean(exp(-1i*iharm*psi));
		end
	end
else % helical
    K0x = K0Array(1);
    K0y = K0Array(2);
    if ierror == 1 % field error defined
        Kx = normrnd(K0x,sigerrkx*K0x, [1,totalstep]);
        Ky = normrnd(K0y,sigerrky*K0y, [1,totalstep]);
    else
        Kx = K0x*ones(1,totalstep);
        Ky = K0y*ones(1,totalstep);
    end
	if isave == 1
		zzArray = zeros(totalstep,1); 	  % z-pos, [m]
		bfArray = zeros(totalstep,nharm);
		ExArray = zeros(totalstep,1);     % Ex field
		EyArray = zeros(totalstep,1);     % Ex field
		for iz = 1:1:totalstep
			j1  = 2*j0*mean(exp(-1i*psi));
			eta = eta-coef1*real(((Kx(iz)*Ex-1i*Ky(iz)*Ey)/2/g0-1i*coef2*j1)*exp(1i*psi))*ndelz;
			psi = psi+2*ku*eta*ndelz;
			Ex  = Ex-coef3*Kx(iz)*j1*ndelz;
			Ey  = Ey-coef3*Ky(iz)*j1*ndelz*1i; 
			zzArray(iz) = iz*ndelz;
			ExArray(iz) = Ex;
			EyArray(iz) = Ey;
			for iharm = 1:nharm
				bfArray(iz,iharm) = mean(exp(-1i*iharm*psi));
			end
		end
	else
		bfArray = zeros(1,nharm); 
		for iz = 1:1:totalstep
			j1  = 2*j0*mean(exp(-1i*psi));
			eta = eta-coef1*real(((Kx(iz)*Ex-1i*Ky(iz)*Ey)/2/g0-1i*coef2*j1)*exp(1i*psi))*ndelz;
			psi = psi+2*ku*eta*ndelz;
			Ex  = Ex-coef3*Kx(iz)*j1*ndelz;
			Ey  = Ey-coef3*Ky(iz)*j1*ndelz*1i; 
		end
		for iharm = 1:nharm
			bfArray(iharm) = mean(exp(-1i*iharm*psi));
		end
	end
end

% return values
parout = [(1+eta)*g0, psi];
if isave == 1
	fldout = [zzArray, ExArray, EyArray];
	pout   = [zzArray, abs([ExArray, EyArray]).^2*1/2*ep0*c0.*Ab];
	bfout  = [zzArray, bfArray];
else
	fldout = [Ex, Ey];
	pout   = abs(fldout).^2*1/2*ep0*c0.*Ab;
	bfout  = bfArray;
end

end