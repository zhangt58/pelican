%% script for run EPU FEL simulation

clear all
load interWithG_data.mat

iParal  =  1;       % enable parallel running
zsep    =  2;       % slices sepration in unit of lambdas
Nutot   =  100;      % total undulator period
lambdas =  150e-9;   % FEL central wavelength, [m]
lambdau =  0.03;    % undulator period length, [m]
K0 = [1.564,1.564];  % helical
iutype = 'helical';    % undulator type
errArray = [1,0.15,0.1];
nstep  = 2;         % integration steps for each undulator period
iSave  = 0;         % only need the last result 
nharm  = 1;         % only calculate fundamental bunching factor
fieldiniX = 0;
fieldiniY = 0;

inputpanel = {s,cur,rmssize,slicenew,lambdas,zsep,...
              lambdau,K0,iutype,Nutot,nstep,nharm,...
              iSave,iParal,fieldiniX,fieldiniY,errArray};
[fieldArray,pardis] = pelicanT(inputpanel);

%% polarization calculation (for helical)
zentri = length(fieldArray);
poldeg = zeros(zentri,2);
zz     = zeros(zentri,1);
for i = 1:zentri
    zz(i)   = fieldArray{i}{1};
    Exfield = fieldArray{i}{2}(:,1);
    Eyfield = fieldArray{i}{2}(:,2);
    poldeg(i,:)= calpolar(Exfield, Eyfield);
end
figure
plot(zz,poldeg(:,1)*100,'rsq-',zz,poldeg(:,2)*100,'bo-','linewidth',2)
xlabel('z [m]')
ylabel('Polarization degree [%]')
legend('P_{tot}','P_{cir}')
grid
%% show current and power profile
ishowfigs = 0;
if ishowfigs == 1
figure
%subplot(2,2,1) % left -> right: tail -> head
plot(s*1e6, cur, 'm-', 'linewidth', 2)
grid
xlabel('s [\mum]')
ylabel('Current [A]')

izstart = length(fieldArray); % izstart <= zentri
figure
%subplot(2,2,2)
for izstep = izstart;
    pxend = fieldArray{izstep}{3}(:,1);
    pyend = fieldArray{izstep}{3}(:,2);
    plot(s*1e6, pxend, 'b-',...
         s*1e6, pyend, 'r-',...
         'linewidth', 2)
end
grid
xlabel('s [\mum]')
ylabel('FEL power [W]')
legend('P_x','P_y',2)

figure
%subplot(2,2,3)
phasexend = mod(phase(fieldArray{izstep}{2}(:,1)),2*pi);
phaseyend = mod(phase(fieldArray{izstep}{2}(:,2)),2*pi);
for izstep = izstart;
    plot(s*1e6, phasexend,'b-',...
         s*1e6, phaseyend,'r-',...
         'linewidth', 2)
end
grid
xlabel('s [\mum]')
ylabel('FEL phase [rad]')
legend('E_x','E_y',0)

%% Spectra calulation
exfield = fieldArray{izstart}{2}(:,1);
lplx = calspec(s, exfield, lambdas);

eyfield = fieldArray{izstart}{2}(:,2);
lply = calspec(s, eyfield, lambdas);

figure
%subplot(2,2,4)
plot(lplx(:,1),lplx(:,2),'b-',...
     lply(:,1),lply(:,2),'r-',...
    'linewidth',2)
xlabel('\lambda_s [nm]')
ylabel('P[\lambda] (a.u.)')
xlim([149.8,150.2])
legend('E_x','E_y',2)
grid

%% gain curve
figure
zentri  = length(fieldArray);
iz      = zeros(zentri,1);
avgPx   = zeros(zentri,1);
avgphix = zeros(zentri,1);
maxPx   = zeros(zentri,1);
avgPy   = zeros(zentri,1);
avgphiy = zeros(zentri,1);
maxPy   = zeros(zentri,1);
for i = 1:zentri
    iz(i)      = fieldArray{i}{1};
    avgPx(i)   = mean(fieldArray{i}{3}(:,1));
    avgphix(i) = phase(mean(fieldArray{i}{2}(:,1)));
    maxPx(i)   = max(fieldArray{i}{3}(:,1));
    
    avgPy(i)   = mean(fieldArray{i}{3}(:,2));
    avgphiy(i) = phase(mean(fieldArray{i}{2}(:,2)));
    maxPy(i)   = max(fieldArray{i}{3}(:,2));
end
plot(iz,avgPx,'r-',...
     iz,maxPx,'b-',...
     iz,avgPy,'g-',...
     iz,maxPy,'m-',...
     'linewidth', 2)
xlabel('z [m]')
ylabel('FEL power [W]')
legend('Avg(x)','Max(x)','Avg(y)','Max(y)',2)
grid

end
%%
save ('EPU.mat','fieldArray')