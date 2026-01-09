% Script generado por C++
if exist('datos_complejidad.txt', 'file')
    data = load('datos_complejidad.txt');
    N = data(:,1);
    Tiempo = data(:,2);
    figure('Name', 'Complejidad N-Reinas');
    plot(N, Tiempo, '-s', 'LineWidth', 2, 'MarkerFaceColor', 'r');
    title('Analisis de Tiempos: Primera Solucion');
    xlabel('N (Numero de Reinas)');
    ylabel('Tiempo (Microsegundos)');
    grid on;
else
    disp('No se encontro el archivo datos_complejidad.txt');
end
