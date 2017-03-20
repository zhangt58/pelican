N = 1;
i = 1;
n = [];
b = [];
while N < 100001
    N = N * 10;
    psi = linspace(-pi,pi,N) + rand(1,N);
    b(i) = abs(mean(exp(1i*psi*1)));
    n(i) = N;
    i = i + 1;
end

plot(n, b, 'b-o')
