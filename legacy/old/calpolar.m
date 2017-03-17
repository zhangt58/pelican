function polardeg = calpolar (Exfield, Eyfield)
% calpolar.m: Calulate the polarization degree of the light fields
% Usage: polardeg = calpolar(Exfield, Eyfield)
%   Input parameters:
%    Exfield: Ex;
%    Eyfield: Ey;
%   Output results:
%    polardeg = [ptot, pcir], 
%               ptot: total polarization degree
%               pcir: circular polarization degree
%   Author: Tong Zhang (tzhang@sinap.ac.cn)
%   Created: 14:02, Dec. 7, 2012

phix = phase(Exfield);
phiy = phase(Eyfield);
dphi = phix-phiy;
ExAmp= abs(Exfield);
EyAmp= abs(Eyfield);
s0   = mean(ExAmp.^2) + mean(EyAmp.^2);
s1   = mean(ExAmp.^2) - mean(EyAmp.^2);
s2   = 2*mean(ExAmp.*EyAmp.*cos(dphi));
s3   = 2*mean(ExAmp.*EyAmp.*sin(dphi));
pt   = sqrt(s1.^2+s2.^2+s3.^2)./s0;
pc   = abs(s3)./s0;
polardeg = [pt, pc];