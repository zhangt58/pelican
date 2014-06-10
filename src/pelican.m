function [parout, fldout, pout, bfout] = pelican (parin, fldin, I0in, paramArray, Nwig)
% pelican A one-dimensional free-electron laser simulation code
% Usage: [parout, fldout, pout] = pelican (parin, fldin, I0in, paramArray, Nwig)
%   input parameters:
%     parin: double array (npart x 2), [gamin,psiin], input longitudinal phase space;
%     fldin: complex, [Exin, Eyin], input seed fields (in x and y), [v/m];
%     I0in : double, input current value, [Amp];
%     paramArray: cell, {K0Array, lambdau, iutype, lambdas, sigmax, nstep, isave, nharm, errArray}, 
%                 required input parameters;
%       K0Array : double, undulator parameter in x and y, [Kx,Ky];
%       lambdau : double, undulator period length, [m];
%       iutype  : string, undulator type, 'planar' or 'helical';
%       lambdas : double, FEL central wavelength, [nm];
%       sigmax  : double, transverse rms beam size, [m];
%       nstep   : integer, integration steps for each undulator period;
%       isave   : bool, 1 for saving all results, fldout = [z, fld],
%                       0 only saves the last record, fldout = fld;
%       nharm   : integer, max harmonic for bunching factor calculation;
%       errArray: double array, field error definition, [ierrer, rmskx(%), rmsky(%)].
%                          
%   output parameters:
%     parout = [gamout,psiout]   : output longitudinal phase space;
%     fldout = [Exout, Eyout]    : output seed field, if isave = 1, zpos is 1st col
%     pout   = [pxout, pyout]    : output power, if isave = 1, zpos is 1st col
% 	  bfout  = [bf(1)..bf(nharm)]: bunching factor,if isave = 1, zpos is 1st col
%
%   Program version number: 1.2
%   Author  : Tong Zhang <tzhang@sinap.ac.cn>
%   Created : 21:12, Dec. 06, 2012 (1.0)
%   Modified: 10:56, Dec. 08, 2012 (1.1)
%   Modified: 22:14, Dec. 12, 2012 (1.2)
%   
%   update log:
%   1.0: complete main program of pelican
%   1.1: output control flag, isave controls output gaincurve or not
% 		 add bunching factor output, nharm input parameter
%   1.2: include field error

%% constants
c0  = 299792458.0;  % speed of light, [m/s]
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

Ex  = fldin(1,1);   % input Ex field
Ey  = fldin(1,2);   % input Ey field
I0  = I0in;         % peak current, [Amp]

K0Array = paramArray{1}; % undulator parameter
lambdau = paramArray{2}; % undulator period, [m]
iutype  = paramArray{3}; % undulator type
lambdas = paramArray{4}; % FEL wavelength, [m]
sigmax  = paramArray{5}; % transverse rms beam size, [m]
nstep   = paramArray{6}; % total integration steps for each period length
isave   = paramArray{7}; % sign for saving gaincurve or not
nharm   = paramArray{8}; % maximum harmonic number of bunching factor for output
errArray= paramArray{9}; % field error defined array
Nu      = Nwig;          % forward length in unit of undulator period

ierror   = errArray(1);  % flag for error enabled (1) or not (0)
sigerrkx = errArray(2);  % rms error in Kx (%)
sigerrky = errArray(3);  % rms error in Ky (%)

Ab    = pi*sigmax.^2;    % transverse beam area, [m^2]
j0    = I0./Ab;       	 % transverse current density, [Amp/m^2]
ku    = 2*pi/lambdau;    % undulator wavenumber, [1/m]
ws    = 2*pi*c0/lambdas; % FEL angular frequency, [1/m]
ndelz = lambdau/nstep; 	 % integration step size, [m]
coef1 = e0/m0/c0/c0/g0;
coef2 = u0*c0*c0/ws;
coef3 = u0*c0/4/g0;
totalstep = nstep*Nu; 	 % total integration step


if strcmp(iutype,'planar') % generate undulator parameter values for all integration steps
    K0 = K0Array(1);
    if ierror == 1 % field error defined
        KK0 = normrnd(K0, sigerrkx*K0, [totalstep, 1]);
    else
        KK0 = K0*ones(totalstep, 1);
    end
    if isave == 1 % save results after every integration step
		zzArray = zeros(totalstep, 1); 	   % z-pos, [m]
		bfArray = zeros(totalstep, nharm); % bunching factor, bf{n} -> nth col
		ExArray = zeros(totalstep, 1); 	   % Ex field, [v/m]
		EyArray = zeros(totalstep, 1); 	   % Ey field, [v/m]
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
        Kx = normrnd(K0x, sigerrkx*K0x, [totalstep, 1]);
        Ky = normrnd(K0y, sigerrky*K0y, [totalstep, 1]);
    else
        Kx = K0x*ones(totalstep, 1);
        Ky = K0y*ones(totalstep, 1);
    end
	if isave == 1
		zzArray = zeros(totalstep, 1); 	   % z-pos, [m]
		bfArray = zeros(totalstep, nharm); % bunching factor, bf{n} -> nth col
		ExArray = zeros(totalstep, 1);     % Ex field, [v/m]
		EyArray = zeros(totalstep, 1);     % Ex field, [v/m]
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
if isave == 1 % save gaincurve
	fldout = [zzArray, ExArray, EyArray];
	pout   = [zzArray, abs([ExArray, EyArray]).^2*1/2*ep0*c0.*Ab];
	bfout  = [zzArray, bfArray];
else % just output the last record
	fldout = [Ex, Ey];
	pout   = abs(fldout).^2*1/2*ep0*c0.*Ab;
	bfout  = bfArray;
end
