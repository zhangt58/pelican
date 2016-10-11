%% plot figures from crossed approach results
%%
%clear all
load crossed.mat
%% get Ex(Ey) field and calculated polarization curve
% total slippage: N1(rad1)+N2(phase-shifter: free drift)
%driftlength=0.5;
Ndrif = driftlength/lambdau;
Nslip = Nutot/zsep + Ndrif/zsep/(1+K0(1)^2/2);
Ndslice = ceil(Nslip);
poldeg = crossPolar(fieldArray1,fieldyPs,Ndslice);
% polar show
figure;
plot(poldeg(:,1),poldeg(:,2)*100,'sq-b',poldeg(:,1),poldeg(:,3)*100,'o-r',...
    'linewidth',2)
xlabel('\Delta\phi [rad]')
ylabel('Polarization degree [%]')
ylim([0,105])
xlim([0,2*pi])
grid
legend('P_{tot}','P_{cir}')
%% show slippage effect
% displacement between the two undulators from 0.1 to 0.5 m
%ips = 1;
delphi      = fieldyPs{ips}{1};
fieldArray2 = fieldyPs{ips}{2};
Exfield = fieldArray1{end}{2}(:,1);
Eyfield = fieldArray2{end}{2}(:,1);
disArray = linspace(0,2,10);
dslice = ceil(Nutot/zsep + disArray./lambdau./zsep./(1+K0(1)^2/2));
disPol = zeros(length(disArray),2);
for i = 1:length(disArray)
    extemp = Exfield(1:end-dslice(i));
    eytemp = [Eyfield(dslice(i):end-dslice(i)-1);zeros(dslice(i),1)];
    disPol(i,:) = calpolar(extemp,eytemp);
end

figure;
plot(disArray,disPol(:,1)*100,'ro-','linewidth',2)
xlabel('Displacement [m]')
ylabel('Total Polarization degree [%]')
legend(['\delta\phi = ',num2str(delphi)])
grid

%% show polarization deg v.s. z-pos
%ips         = 1;
delphi      = fieldyPs{ips}{1};
fieldArray2 = fieldyPs{ips}{2};
zentri      = length(fieldArray1);
deltslice   = Ndslice;
poliz       = zeros(zentri,3);
for i = 1:zentri  
    Exfield = fieldArray1{i}{2}(:,1);
    Eyfield = fieldArray2{i}{2}(:,1);
    extemp = Exfield(1:end-deltslice);
    eytemp = [Eyfield(deltslice:end-deltslice-1);zeros(deltslice,1)];
    poliz(i,:) = [fieldArray1{i}{1},calpolar(extemp,eytemp)];
end
figure;
plot(poliz(:,1),poliz(:,2)*100,'ro-',...
     poliz(:,1),poliz(:,3)*100,'bsq-','linewidth',2)
xlabel('z [m]')
ylabel('Polarization degree [%]')
legend('P_{tot}','P_{cir}')
title(['\delta\phi = ',num2str(delphi)])
grid
%% show current and power profile
figure
%subplot(2,2,1) % left -> right: tail -> head
plot(s*1e6, cur, 'm-', 'linewidth', 2)
grid
xlabel('s [\mum]')
ylabel('Current [A]')

izstart = length(fieldArray1); % izstart <= zentri
figure
%subplot(2,2,2)
for izstep = izstart;
    pxend = fieldArray1{izstep}{3}(:,1);
    pyend = fieldArray2{izstep}{3}(:,1);
    px = pxend(1:end-deltslice);
    py = [pyend(deltslice:end-deltslice-1);zeros(deltslice,1)];
    plot(s(1:end-deltslice)*1e6, px, 'b-',...
         s(1:end-deltslice)*1e6, py, 'r-',...
         'linewidth', 2)
end
grid
xlabel('s [\mum]')
ylabel('FEL power [W]')
legend('P_x','P_y',2)

figure
%subplot(2,2,3)
phasexend = mod(phase(fieldArray1{izstep}{2}(:,1)),2*pi);
phaseyend = mod(phase(fieldArray2{izstep}{2}(:,1)),2*pi);
phasex = phasexend(1:end-deltslice);
phasey = [phaseyend(deltslice:end-deltslice-1);zeros(deltslice,1)];
for izstep = izstart;
    plot(s(1:end-deltslice)*1e6, phasex,'b-',...
         s(1:end-deltslice)*1e6, phasey,'r-',...
         'linewidth', 2)
end
grid
xlabel('s [\mum]')
ylabel('FEL phase [rad]')
legend('E_x','E_y',0)

%% Spectra calulation
exfield = fieldArray1{izstart}{2}(:,1);
lplx = calspec(s, exfield, lambdas);

eyfield = fieldArray2{izstart}{2}(:,1);
lply = calspec(s, eyfield, lambdas);

figure
%subplot(2,2,4)
plot(lplx(:,1),lplx(:,2),'bo-',...
     lply(:,1),lply(:,2),'r-',...
    'linewidth',2)
xlabel('\lambda_s [nm]')
ylabel('P[\lambda] (a.u.)')
xlim([149.,151])
legend('E_x','E_y',2)
grid

%% gain curve
figure
zentri  = length(fieldArray1);
iz      = zeros(zentri,1);
avgPx   = zeros(zentri,1);
avgphix = zeros(zentri,1);
maxPx   = zeros(zentri,1);
avgPy   = zeros(zentri,1);
avgphiy = zeros(zentri,1);
maxPy   = zeros(zentri,1);
for i = 1:zentri
    iz(i)      = fieldArray1{i}{1};
    avgPx(i)   = mean(fieldArray1{i}{3}(:,1));
    avgphix(i) = phase(mean(fieldArray1{i}{2}(:,1)));
    maxPx(i)   = max(fieldArray1{i}{3}(:,1));
    
    avgPy(i)   = mean(fieldArray2{i}{3}(:,1));
    avgphiy(i) = phase(mean(fieldArray2{i}{2}(:,1)));
    maxPy(i)   = max(fieldArray2{i}{3}(:,1));
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
