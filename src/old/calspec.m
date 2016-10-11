function [specout] = calspec (s, efield, lambdas)
% calspec.m: Calculate the spectrum of a light field
% Usage: specout = calspec(s,efield,lambdas)
%   Input parameters:
%    s: x-axis of field, [m] 
%    efield: field along s, [V/m]
%    lambdas: central wavelngth, [m]
%   Output results:
%    specout: calculated spectra with [lambda (nm),plambda]
% 
%   Author: Tong Zhang (tzhang@sinap.ac.cn)
%   Created: 10:49, Dec. 7, 2012

c0     = 299.792458;    % light speed, [nm/fs]
eAmp   = abs(efield);   % field amplitude, [V/m]
N      = length(efield);
w0     = 2*pi*c0/(lambdas*1e9);
dt     = (s(end)-s(1))*1e9/c0/N;
dw     = 2*pi/N/dt;
w      = (-N/2:N/2-1)*dw;
absw   = w + w0;
ew     = fftshift(fft(eAmp,N));
pw     = abs(ew).^2;
temp   = find(absw>0);
zp     = temp(1);
lambda = 2*pi*c0./absw(end:-1:zp); % [nm]
plambda= pw(end:-1:zp);
specout= [lambda',plambda]; 