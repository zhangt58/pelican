%% interface between Pelican and Genesis
% jobs: 
%   Genesis: prepare initial particle distribution for Pelican simulation
%   Pelican: simulation in radiator
% Author: Tong Zhang (tzhang@sinap.ac.cn)
% Created: 21:55, Dec. 9, 2012

%% run genesis simulation to generate dpa and current profile
clear all
cd ../Genesis
scur = load('curfile');
s    = scur(:,1); % m
cur  = scur(:,2); % A
%% read phase space data from GENESIS output
npart = 8192;
nslice = 3360;
fid = fopen('mod.out.dpa');
a = fread(fid,'double');
a = reshape(a, [npart,6,nslice]);
slice = cell(nslice,1);
for i = 1:nslice
    slice{i}=a(:,:,i);
end
fclose(fid);
clear a fid i
%% show phase space
%figure(1);
%hold on
for i = 1:nslice
    slice{i}(:,2) = slice{i}(:,2)+2*pi*(i-1);
%     plot(slice{i}(:,2),slice{i}(:,1),'.','MarkerSize',1);
end

%% pass chicane
c0 = 299792458.0;
e0 = 1.60218e-19;
m0 = 9.10938e-31;
ibfield = 0.1449;
imagl   = 0.15;
idril   = 0.285;
convharm= 5;
kseed = 2*pi/250e-9;
ks    = convharm*kseed;
slicenew = slice;
R56 = zeros(nslice,1);
gam = zeros(nslice,1); % mean energy (gamma)
sigmag = zeros(nslice,1); % rms energy spread
rmssize = zeros(nslice,1); % rms transverse size
bf  = zeros(nslice,1);
%figure(2);
%clf
%subplot(2,1,1)
%hold on
for i = 1:nslice
    gam(i) = mean(slice{i}(:,1));
end
g0 = mean(gam);
for i = 1:nslice
    sigmag(i)  = std(slice{i}(:,1));
    rmssize(i) = sqrt(std(slice{i}(:,3)).^2+std(slice{i}(:,4)).^2);
    R56(i) = (asin(imagl/(sqrt(g0^2-1)*m0*c0)*ibfield*e0))^2 ...
             *(2/3*imagl+idril)*2;
    slicenew{i}(:,2) = convharm*slice{i}(:,2) + ...
                    ks*(slice{i}(:,1)/g0-1)*R56(i);
    bf(i) = abs(mean(exp(-1i*slicenew{i}(:,2))));
%    plot(slicenew{i}(:,2),slicenew{i}(:,1),'r.','MarkerSize',1);
end
grid

%figure(2);
%subplot(2,1,2)
%plotyy(s,bf,s,gam)
%grid
%% save particle distribution for Pelican
cd ../Pelican
save('interWithG_data','slicenew','nslice','gam','bf','s','cur','sigmag','rmssize')