#include <stdio.h>
#include <string.h>

#define MAX_NOME 50
#define MAX_ESTADO 30

typedef struct {
    char estado[MAX_ESTADO];
    int codigo;
    char nome[MAX_NOME];
    int populacao;
    float area;
    float pib;
    int pontos_turisticos;
} CartaCidade;

void cadastrarCarta(CartaCidade *carta, int numero) {
    printf("\n--- Cadastro da Carta %d ---\n", numero);
    printf("Nome do Estado: ");
    fgets(carta->estado, MAX_ESTADO, stdin);
    carta->estado[strcspn(carta->estado, "\n")] = 0; // Remove \n

    printf("Código da Carta: ");
    scanf("%d", &carta->codigo); getchar();

    printf("Nome da Cidade: ");
    fgets(carta->nome, MAX_NOME, stdin);
    carta->nome[strcspn(carta->nome, "\n")] = 0;

    printf("População: ");
    scanf("%d", &carta->populacao); getchar();

    printf("Área (km2): ");
    scanf("%f", &carta->area); getchar();

    printf("PIB (em bilhões): ");
    scanf("%f", &carta->pib); getchar();

    printf("Número de Pontos Turísticos: ");
    scanf("%d", &carta->pontos_turisticos); getchar();
}

void exibirCarta(const CartaCidade *carta, int numero) {
    printf("\n--- Carta %d ---\n", numero);
    printf("Estado: %s\n", carta->estado);
    printf("Código: %d\n", carta->codigo);
    printf("Cidade: %s\n", carta->nome);
    printf("População: %d\n", carta->populacao);
    printf("Área: %.2f km2\n", carta->area);
    printf("PIB: %.2f bilhões\n", carta->pib);
    printf("Pontos Turísticos: %d\n", carta->pontos_turisticos);
    printf("---------------------\n");
}

void compararCartas(CartaCidade c1, CartaCidade c2, int atributo) {
    printf("\nComparação baseada em ");
    switch(atributo) {
        case 1: printf("População\n");
                if (c1.populacao > c2.populacao)
                    printf("Vencedora: %s (População maior)\n", c1.nome);
                else if (c1.populacao < c2.populacao)
                    printf("Vencedora: %s (População maior)\n", c2.nome);
                else
                    printf("Empate (População igual)\n");
                break;
        case 2: printf("Área\n");
                if (c1.area > c2.area)
                    printf("Vencedora: %s (Área maior)\n", c1.nome);
                else if (c1.area < c2.area)
                    printf("Vencedora: %s (Área maior)\n", c2.nome);
                else
                    printf("Empate (Área igual)\n");
                break;
        case 3: printf("PIB\n");
                if (c1.pib > c2.pib)
                    printf("Vencedora: %s (PIB maior)\n", c1.nome);
                else if (c1.pib < c2.pib)
                    printf("Vencedora: %s (PIB maior)\n", c2.nome);
                else
                    printf("Empate (PIB igual)\n");
                break;
        case 4: printf("Pontos Turísticos\n");
                if (c1.pontos_turisticos > c2.pontos_turisticos)
                    printf("Vencedora: %s (Mais pontos turísticos)\n", c1.nome);
                else if (c1.pontos_turisticos < c2.pontos_turisticos)
                    printf("Vencedora: %s (Mais pontos turísticos)\n", c2.nome);
                else
                    printf("Empate (Número de pontos turísticos igual)\n");
                break;
        case 5: printf("Densidade Populacional\n");
                {
                    float dens1 = c1.populacao / c1.area;
                    float dens2 = c2.populacao / c2.area;
                    if (dens1 < dens2)
                        printf("Vencedora: %s (Menor densidade)\n", c1.nome);
                    else if (dens1 > dens2)
                        printf("Vencedora: %s (Menor densidade)\n", c2.nome);
                    else
                        printf("Empate (Densidade igual)\n");
                }
                break;
        default: printf("Atributo inválido!\n");
    }
}

int main() {
    CartaCidade carta1, carta2;
    int atributo;

    cadastrarCarta(&carta1, 1);
    cadastrarCarta(&carta2, 2);

    exibirCarta(&carta1, 1);
    exibirCarta(&carta2, 2);

    printf("\nEscolha o atributo para comparar:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turísticos\n");
    printf("5 - Densidade Populacional (MENOR vence)\n");
    printf("Digite o número do atributo: ");
    scanf("%d", &atributo);

    compararCartas(carta1, carta2, atributo);

    return 0;
}