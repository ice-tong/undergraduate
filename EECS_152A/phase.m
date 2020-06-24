function y = phase(r, theta, omega)
    y = atan((r*sin(omega-theta))./(1-r*cos(omega-theta)));
end

