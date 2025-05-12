% Charger les données
data = readtable('comparacoes.csv');

% 1. Graphique des comparaisons pour chaque insertion
figure(1);
scatter(1:height(data), data.Comparacoes_Heap, 10, 'b', 'filled');
hold on;
scatter(1:height(data), data.Comparacoes_Lista, 10, 'r', 'filled');
hold off;

title('Comparaisons par Insertion');
xlabel('Nombre d''insertions');
ylabel('Nombre de comparaisons');
legend('Avec Heap (O(log n))', 'Sans Heap (O(n))', 'Location', 'northwest');
grid on;

% 2. Graphique des tendances (moyenne mobile)
window_size = 50; % Ajustez pour lisser plus ou moins
heap_smooth = movmean(data.Comparacoes_Heap, window_size);
list_smooth = movmean(data.Comparacoes_Lista, window_size);

figure(2);
plot(heap_smooth, 'b-', 'LineWidth', 1.5);
hold on;
plot(list_smooth, 'r-', 'LineWidth', 1.5);
hold off;

title('Tendance des Comparaisons (Moyenne Mobile)');
xlabel('Nombre d''insertions');
ylabel('Comparaisons (lissées)');
legend('Avec Heap', 'Sans Heap');
grid on;

% 3. Histogramme des comparaisons
figure(3);
subplot(2,1,1);
histogram(data.Comparacoes_Heap, 'FaceColor', 'b');
title('Distribution des comparaisons (Heap)');
xlabel('Comparaisons');
ylabel('Fréquence');

subplot(2,1,2);
histogram(data.Comparacoes_Lista, 'FaceColor', 'r');
title('Distribution des comparaisons (Liste)');
xlabel('Comparaisons');
ylabel('Fréquence');

% 4. Comparaison des maxima
fprintf('Comparaisons maximales:\n');
fprintf('  - Heap: %d (attendu ~log2(1000)=10)\n', max(data.Comparacoes_Heap));
fprintf('  - Liste: %d (attendu ~n/2=%d)\n', max(data.Comparacoes_Lista), height(data)/2);