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
