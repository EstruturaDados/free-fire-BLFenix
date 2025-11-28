#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_ITENS 10

typedef struct {
    char nome[50];
    char tipo[30];
    int quantidade;
    int prioridade; // NOVO
} Item;

typedef enum {
    ORDENAR_NOME = 1,
    ORDENAR_TIPO = 2,
    ORDENAR_PRIORIDADE = 3
} Criterio;

// Funções auxiliares
int comparar(Item a, Item b, Criterio c) {
    switch(c) {
        case ORDENAR_NOME:
            return strcmp(a.nome, b.nome);
        case ORDENAR_TIPO:
            return strcmp(a.tipo, b.tipo);
        case ORDENAR_PRIORIDADE:
            return a.prioridade - b.prioridade;
    }
    return 0;
}

int insertionSort(Item v[], int n, Criterio crit) {
    int comparacoes = 0;

    for (int i = 1; i < n; i++) {
        Item chave = v[i];
        int j = i - 1;

        while (j >= 0 && comparar(v[j], chave, crit) > 0) {
            comparacoes++;
            v[j+1] = v[j];
            j--;
        }
        v[j+1] = chave;
    }
    return comparacoes;
}

int buscaBinaria(Item v[], int n, char alvo[]) {
    int inicio = 0, fim = n - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int cmp = strcmp(alvo, v[meio].nome);

        if (cmp == 0) return meio;
        else if (cmp > 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

int main() {
    Item mochila[MAX_ITENS];
    int total = 0;
    int opcao;
    bool ordenadoPorNome = false;

    do {
        printf("\n===== MOCHILA - NIVEL MESTRE =====\n");
        printf("1 - Adicionar item\n");
        printf("2 - Remover item\n");
        printf("3 - Listar itens\n");
        printf("4 - Ordenar mochila\n");
        printf("5 - Busca binaria por nome\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        getchar();

        switch(opcao) {

            case 1:
                if (total == MAX_ITENS) {
                    printf("Mochila cheia!\n");
                    break;
                }

                printf("Nome: ");
                fgets(mochila[total].nome, 50, stdin);
                mochila[total].nome[strcspn(mochila[total].nome, "\n")] = '\0';

                printf("Tipo: ");
                fgets(mochila[total].tipo, 30, stdin);
                mochila[total].tipo[strcspn(mochila[total].tipo, "\n")] = '\0';

                printf("Quantidade: ");
                scanf("%d", &mochila[total].quantidade);
                getchar();

                printf("Prioridade (1 a 5): ");
                scanf("%d", &mochila[total].prioridade);
                getchar();

                total++;
                ordenadoPorNome = false;
                break;

            case 2: {
                char nomeBuscado[50];
                printf("Nome do item para remover: ");
                fgets(nomeBuscado, 50, stdin);
                nomeBuscado[strcspn(nomeBuscado, "\n")] = '\0';

                int encontrado = 0;

                for (int i = 0; i < total; i++) {
                    if (strcmp(nomeBuscado, mochila[i].nome) == 0) {
                        encontrado = 1;
                        for (int j = i; j < total - 1; j++) mochila[j] = mochila[j+1];
                        total--;
                        break;
                    }
                }

                if (!encontrado) printf("Item nao encontrado!\n");
                break;
            }

            case 3:
                printf("\n--- ITENS NA MOCHILA ---\n");
                for (int i = 0; i < total; i++) {
                    printf("%s | Tipo: %s | Qtd: %d | Prioridade: %d\n",
                        mochila[i].nome,
                        mochila[i].tipo,
                        mochila[i].quantidade,
                        mochila[i].prioridade);
                }
                break;

            case 4: {
                printf("Ordenar por:\n1 - Nome\n2 - Tipo\n3 - Prioridade\nEscolha: ");
                int c;
                scanf("%d", &c);
                getchar();

                int comparacoes = insertionSort(mochila, total, c);

                printf("Mochila ordenada!\n");
                printf("Comparacoes realizadas: %d\n", comparacoes);

                ordenadoPorNome = (c == ORDENAR_NOME);
                break;
            }

            case 5: {
                if (!ordenadoPorNome) {
                    printf("A mochila nao esta ordenada por nome!\n");
                    break;
                }

                char alvo[50];
                printf("Nome do item: ");
                fgets(alvo, 50, stdin);
                alvo[strcspn(alvo, "\n")] = '\0';

                int pos = buscaBinaria(mochila, total, alvo);

                if (pos == -1) printf("Item nao encontrado!\n");
                else {
                    printf("Item encontrado!\n");
                    printf("Nome: %s\n", mochila[pos].nome);
                    printf("Tipo: %s\n", mochila[pos].tipo);
                    printf("Quantidade: %d\n", mochila[pos].quantidade);
                    printf("Prioridade: %d\n", mochila[pos].prioridade);
                }

                break;
            }

        }

    } while(opcao != 0);

    return 0;
}
