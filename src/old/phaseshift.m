function [parcellout] = phaseshift (parcellin, dphi)
% phaseshift Simulate phaseshifter between the crossed planar undulators
% Usage: parcellout = phaseshift(parcellin, dphi)
%   Input parameter:
%     parcellin: cell array of particle distribution;
%     dphi:      additional phase shift to phi;
%   Output results:
%     parcellout: shifted particle distribution
%   
%   Author: Tong Zhang (tzhang@sinap.ac.cn)
%   Created: 20:38, Dec. 10, 2012

nslice = length(parcellin);
parcellout = cell(nslice,1);
for i = 1:nslice
    parcellout{i} = [parcellin{i}(:,1),parcellin{i}(:,2)-dphi];
end