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
    carta->estado[strcspn(carta->estado, "\n")] = 0;

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

float obterValorAtributo(CartaCidade carta, int atributo) {
    switch(atributo) {
        case 1: return (float)carta.populacao;
        case 2: return carta.area;
        case 3: return carta.pib;
        case 4: return (float)carta.pontos_turisticos;
        case 5: return carta.populacao / carta.area; // densidade
        default: return 0;
    }
}

const char* nomeAtributo(int atributo) {
    switch(atributo) {
        case 1: return "População";
        case 2: return "Área";
        case 3: return "PIB";
        case 4: return "Pontos Turísticos";
        case 5: return "Densidade Populacional";
        default: return "Desconhecido";
    }
}

int compararValores(float v1, float v2, int atributo) {
    if(atributo == 5) // Densidade: menor vence
        return (v1 < v2) ? 1 : (v1 > v2) ? 2 : 0;
    else // Demais: maior vence
        return (v1 > v2) ? 1 : (v1 < v2) ? 2 : 0;
}

void compararCartasMestre(CartaCidade c1, CartaCidade c2, int atributo1, int atributo2) {
    float v1_1 = obterValorAtributo(c1, atributo1);
    float v2_1 = obterValorAtributo(c2, atributo1);
    float v1_2 = obterValorAtributo(c1, atributo2);
    float v2_2 = obterValorAtributo(c2, atributo2);

    int res1 = compararValores(v1_1, v2_1, atributo1);

    printf("\nComparando atributo principal: %s\n", nomeAtributo(atributo1));
    printf("%s: %.2f x %s: %.2f\n", c1.nome, v1_1, c2.nome, v2_1);

    if (res1 == 1)
        printf("Vencedora: %s (%s maior)\n", c1.nome, nomeAtributo(atributo1));
    else if (res1 == 2)
        printf("Vencedora: %s (%s maior)\n", c2.nome, nomeAtributo(atributo1));
    else {
        printf("Empate em %s!\n", nomeAtributo(atributo1));
        printf("Comparando atributo de desempate: %s\n", nomeAtributo(atributo2));
        printf("%s: %.2f x %s: %.2f\n", c1.nome, v1_2, c2.nome, v2_2);
        int res2 = compararValores(v1_2, v2_2, atributo2);
        res2 == 1 ? printf("Vencedora: %s (%s maior)\n", c1.nome, nomeAtributo(atributo2)) :
        res2 == 2 ? printf("Vencedora: %s (%s maior)\n", c2.nome, nomeAtributo(atributo2)) :
        printf("Empate absoluto!\n");
    }
}

int menuAtributo(const char* mensagem) {
    int op;
    printf("\n%s\n", mensagem);
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Pontos Turísticos\n");
    printf("5 - Densidade Populacional (MENOR vence)\n");
    printf("Escolha o número: ");
    scanf("%d", &op); getchar();
    return op;
}

int main() {
    CartaCidade carta1, carta2;
    int continuar = 1;

    // Cadastro das cartas
    cadastrarCarta(&carta1, 1);
    cadastrarCarta(&carta2, 2);

    // Exibição das cartas
    exibirCarta(&carta1, 1);
    exibirCarta(&carta2, 2);

    while (continuar) {
        printf("\n=== MENU DE COMPARAÇÃO ===\n");
        int atributo1 = menuAtributo("Escolha o atributo PRINCIPAL para comparação:");
        int atributo2 = menuAtributo("Escolha o atributo de DESEMPATE (diferente do principal):");

        if (atributo1 < 1 || atributo1 > 5 || atributo2 < 1 || atributo2 > 5 || atributo1 == atributo2) {
            printf("Atributos inválidos! Tente novamente.\n");
            continue;
        }

        compararCartasMestre(carta1, carta2, atributo1, atributo2);

        printf("\nDeseja fazer uma nova comparação? (1=Sim, 0=Não): ");
        scanf("%d", &continuar); getchar();
    }

    printf("Programa encerrado!\n");
    return 0;
}