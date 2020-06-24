function y = dBgain(r, theta, omega)
    y = 10*log10(1+r^2-2*r*cos(omega-theta));
end

