function [pardis] = gendis0(np0, gam0, eta0)
    
psidis0 = linspace(-1*pi,1*pi,np0);
gamdis0 = normrnd(gam0, eta0*gam0, [1, np0]);
pardis  = [gamdis0',psidis0'];