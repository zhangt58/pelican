%% script for run crossed undulator FEL simulation

clear all
load interWithG_data.mat

iParal  =  1;       % enable parallel running
zsep    =  2;       % slices sepration in unit of lambdas
Nutot   =  50;      % total undulator period
lambdas =  150e-9;   % FEL central wavelength, [m]
lambdau =  0.03;    % undulator period length, [m]
K0      =  [1.564*sqrt(2),1.564*sqrt(2)];   % planar
iutype  = 'planar';  % undulator type
errArray= [0,0.2,0.2];
nstep   = 1;         % integration steps for each undulator period
iSave   = 0;         % only need the last result 
nharm   = 1;         % only calculate fundamental bunching factor
fldx0   = 0;
fldy0   = 0;

inputpanel1 = {s,cur,rmssize,slicenew,lambdas,zsep,...
              lambdau,K0,iutype,Nutot,nstep,nharm,...
              iSave,iParal,fldx0,fldy0,errArray};         
[fieldArray1,pardis1] = pelicanT(inputpanel1);
%% tuning phase-shifter
nPs = 50;
psPhi = linspace(0,2*pi,nPs);
poldeg  = zeros(nPs,2);
fieldyPs = cell(nPs,1);
for k = 1:nPs
    parNew = phaseshift(pardis1,psPhi(k));
    inputpanel2 = {s,cur,rmssize,parNew,lambdas,zsep,...
                    lambdau,K0,iutype,Nutot,nstep,nharm,...
                    iSave,iParal,fldx0,fldy0,errArray};
    [fieldArray2,pardis2] = pelicanT(inputpanel2);
    fieldyPs{k} = {psPhi(k),fieldArray2};
end
%%
save ('crossed.mat','fieldArray1','fieldyPs','s','cur','lambdau','lambdas','Nutot','zsep','K0');
%% plot figures
ishowfigs = 1;
if ishowfigs == 1
    %clear all
    driftlength = 0.5;
    ips = 20;
    showfigs
end