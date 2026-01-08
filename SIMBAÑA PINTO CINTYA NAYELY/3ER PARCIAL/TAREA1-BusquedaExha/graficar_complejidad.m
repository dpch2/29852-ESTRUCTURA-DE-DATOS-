% Script para graficar complejidad temporal
clear; clc;

% Leer datos del archivo
datos = load('complejidad_datos.txt');
n = datos(:, 1);
operaciones = datos(:, 2);

% Crear figura
figure('Position', [100, 100, 800, 600]);

% Graficar datos reales
plot(n, operaciones, 'bo-', 'LineWidth', 2, 'MarkerSize', 8, 'MarkerFaceColor', 'b');
hold on;

% Graficar curva teorica O(n^2)
n_teorico = linspace(min(n), max(n), 100);
operaciones_teoricas = (n_teorico .* (n_teorico - 1)) / 2;
plot(n_teorico, operaciones_teoricas, 'r--', 'LineWidth', 1.5);

% Configurar grafica
xlabel('Tamaño del Problema (N)', 'FontSize', 12, 'FontWeight', 'bold');
ylabel('Numero de Operaciones', 'FontSize', 12, 'FontWeight', 'bold');
title('Complejidad Temporal - Busqueda Exhaustiva de Pares', 'FontSize', 14, 'FontWeight', 'bold');
legend('Datos Reales', 'Complejidad Teorica O(n^2)', 'Location', 'northwest');
grid on;
hold off;

% Guardar grafica
saveas(gcf, 'complejidad_temporal.png');
disp('Grafica generada exitosamente: complejidad_temporal.png');
