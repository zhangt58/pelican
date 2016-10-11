#!/usr/bin/octave -qf

args = argv();
beamfile = args{1};

a  = load(beamfile);
ga = smooth(a(:,1),a(:,2),0.1,'loess');
a(:,2) = ga;
dlmwrite(beamfile,a,'precision','%.6e','delimiter',' ');
