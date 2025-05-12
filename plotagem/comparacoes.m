% Carregar os dados do arquivo CSV
dados = readtable('comparacoes.csv');

% 1. Gráfico de comparações por inserção
figure(1);
scatter(1:height(dados), dados.Comparacoes_Heap, 10, 'b', 'filled');
hold on;
scatter(1:height(dados), dados.Comparacoes_Lista, 10, 'r', 'filled');
hold off;

title('Comparações por Inserção');
xlabel('Número de inserções');
ylabel('Número de comparações');
legend('Com Heap (O(log n))', 'Sem Heap (O(n))', 'Location', 'northwest');
grid on;

% 2. Gráfico de tendências (média móvel)
janela = 50; % Tamanho da janela para suavização
heap_suavizado = movmean(dados.Comparacoes_Heap, janela);
lista_suavizado = movmean(dados.Comparacoes_Lista, janela);

figure(2);
plot(heap_suavizado, 'b-', 'LineWidth', 1.5);
hold on;
plot(lista_suavizado, 'r-', 'LineWidth', 1.5);
hold off;

title('Tendência das Comparações (Média Móvel)');
xlabel('Número de inserções');
ylabel('Comparações (suavizadas)');
legend('Com Heap', 'Sem Heap');
grid on;
