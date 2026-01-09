datos = readtable('datos.txt');

n = datos.n;
ops = datos.ops;

figure
plot(n, ops, 'o-')
xlabel('n')
ylabel('Operaciones')
title('Complejidad Experimental O(n^2)')
grid on
