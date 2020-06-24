function y = grd(r,theta,omega)
    y = (r^2-r*cos(omega-theta))./(1+r^2-2*r*cos(omega-theta));
end

