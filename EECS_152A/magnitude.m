function y = magnitude(r,theta,omega)
    y = sqrt(1+r^2-2*r*cos(omega-theta));
end

