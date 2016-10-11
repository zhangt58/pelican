clear all;

% read data distribution
filename1 = '0.out.dpa';
fid   = fopen(filename1, 'r');
finfo = dir(filename1);
np    = finfo.bytes/48;
data  = fread(fid, [np 6], 'double');
psi   = data(:,2);
gam   = data(:,1);
g0      = 265;  % beam energy [MeV], Lorentz factor
% contants
c0  = 299792458;    % speed of light, [m/s]
e0  = 1.60218e-19;  % electron charge, [Coulomb]
m0  = 9.10938e-31;  % electron mass, [kilogram]
u0  = pi*4.0e-7;    % vacuum permeability, [sec.volt/Amp.meter]
ep0 = 8.8542e-12;   % vacuum permittivity, [Amp.sec/meter.volt]
IA  = 17045;        % Alfven current, [A]

I0      = 300;          % peak current, [Amp]
sigmax  = 300e-6;       % transverse rms beam size, [m]
Ab      = pi*sigmax^2;  % transverse beam area, [m^2]
j0      = I0/Ab;        % current density, [Amp/m^2]
lambdau = 0.025;        % undulator period, [m]
ku      = 2*pi/lambdau; % undulator wave number, [1/m]
au      = 0.7025;       % undulator parameter
KJJ     = besselj(0,au^2/2/(1+au^2))-besselj(1,au^2/2/(1+au^2)); % coupled undulator parameter for planar type
eta0    = 1.0e-4;       % relative energy spread
lambdas = 266e-9; %lambdau/2/g0^2*(1+au^2); % FEL wavelength, [m]
omegas  = 2*pi*c0/lambdas;  % FEL angular frequency, [Hz]
Ein     = 5e5;            % input seed field, [Volt/m]
rho     = (I0/IA*(lambdau*au*KJJ/2/pi/sigmax)^2)^(1/3)/2/g0;
Lg0     = lambdau/4/pi/sqrt(3)/rho;
%%
%parin = [gam, psi];
parin = gendis0(1e4,g0,eta0);
fldin = [Ein, 0];
I0in  = I0;
K0Array = ones(2,1)*sqrt(2)*au;
iutype = 'planar';
nstep = 1;
isave = 1;
nharm = 1;
errArray = [0,0,0];
paramArray = {K0Array, lambdau, iutype, lambdas, sigmax, nstep, isave, nharm, errArray};
Ng = 20;
Nwig  = floor(Ng*Lg0/lambdau);
[parout,fldout,pout,bfout] = pelican(parin, fldin, I0in, paramArray, Nwig);
%%
figure(1)
semilogy(pout(:,1)/Lg0, pout(:,2),'r', 'linewidth', 2)
grid
xlabel('z/z_g^0')
ylabel('FEL Power [W]')
%%
figure(2)
plot(parout(:,2), parout(:,1), 'r.','MarkerSize',1);

%% scan central wavelength
gamma0 = linspace(260,270,100);
pgout  = zeros(length(gamma0), 1);
eta0   = 1e-04;
np     = 1e+04;
paramArray = {K0Array, lambdau, iutype, lambdas, sigmax, nstep, 0, nharm, errArray};
for idx = 1:length(gamma0)
    parin = gendis0(np,gamma0(idx),eta0);
    [parout,fldout,pout,bfout] = pelican(parin, fldin, I0in, paramArray, 300);
    pgout(idx) = pout(1);
end
