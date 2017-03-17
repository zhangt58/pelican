function poldeg = crossPolar (fieldArray1,fieldyPs,dslice)
% crossPolar calculate the polarization degree for crossed undulator 
% Usage: poldeg = crossPolar (fieldArray1,fieldyPs,dslice)
%   Input parameters:
%     fieldArray1: fieldArray for Ex field, cell
%     fieldyPs:    cell array of the Ex field fieldArray
%     dslice:      slippage contribution
%   Output parameters:
%     poldeg: #1|#2|#3|: #1: delphase, #2: Ptot, #3: Pcir
%
% Author: Tong Zhang (tzhang@sinap.ac.cn)
% Created: 14:30, Dec. 13, 2012

Exfield = fieldArray1{end}{2}(:,1);
extemp  = Exfield(1:end-dslice);
poldeg  = zeros(length(fieldyPs),3);
for k = 1:length(fieldyPs)
    Eyfield = fieldyPs{k}{2}{end}{2}(:,1);
    eytemp = [Eyfield(dslice:end-dslice-1);zeros(dslice,1)];
    poldeg(k,:) = [fieldyPs{k}{1},calpolar(extemp, eytemp)];
end