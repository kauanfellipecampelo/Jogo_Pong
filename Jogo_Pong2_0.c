#include <stdio.h>   // Biblioteca padrão de entrada e saída, usada para funções como printf() e scanf()
#include <stdlib.h>  // Biblioteca que fornece funções de gerenciamento de memória e controle de execução, como malloc(), free(), exit(), etc.
#include <conio.h>   // Biblioteca usada para controle de entrada de teclado, como _getch() e _kbhit() (geralmente usada em programas de console para detectar teclas pressionadas)
#include <windows.h> // Biblioteca para interagir com recursos do sistema operacional Windows, como manipulação de cores no console e controle de tempo (Sleep())
#include <locale.h>  // Biblioteca para definir e manipular configurações de localidade (usada aqui para definir o idioma para português)


// Definições de constantes do jogo
#define LARGURA 40  
#define ALTURA 20  
#define TAMANHO_RAQUETE 4 
#define NOME_ARQUIVO "estatisticas.dat" 

// Estrutura que mantém as estatísticas do jogo
typedef struct {
    int pontos_jogador1;
    int pontos_jogador2;
    int fase_atual;
    int pontos_totais;
} EstatisticasJogo;

// Estrutura para armazenar a posição (x, y) de um ponto
typedef struct {
    int x, y; 
} Posicao;

// Função para configurar as cores do texto e fundo no console
void configurar_cor(int cor_texto, int cor_fundo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // Obtém o manipulador de saída do console
    SetConsoleTextAttribute(hConsole, (cor_fundo << 4) | cor_texto);  // Define a cor do texto e fundo
}

// Função para resetar as cores para o padrão
void resetar_cor() {
    configurar_cor(7, 0);  // Configura o texto como branco (7) no fundo preto (0)
}

// Função para desenhar a borda superior do campo de jogo
void desenhar_borda() {
    int i;
    configurar_cor(1, 1);  // Configura a cor para o texto com cor 1 (vermelho) e fundo 1 (azul)
    for (i = 0; i <= LARGURA; i++) printf(" ");  // Imprime a borda
    printf("\n");
    resetar_cor();  // Reseta a cor para o padrão
}

// Função que desenha o campo de jogo, raquetes, bola e pontuação
void desenhar_jogo(Posicao bola, int raquete1_y, int raquete2_y, int pontos_jogador1, int pontos_jogador2, int fase_atual) {
    int y, x;
    system("cls");  // Limpa a tela do console

    desenhar_borda();  // Desenha a borda superior

    // Loop para desenhar o campo de jogo linha por linha
    for (y = 0; y < ALTURA; y++) {
        for (x = 0; x <= LARGURA; x++) {
            if (x == 0 || x == LARGURA) {
                configurar_cor(1, 1);  // Cor para as bordas (azul com fundo azul)
                printf(" ");  // Desenha a borda
                resetar_cor();  // Reseta a cor
            } else if (x == bola.x && y == bola.y) {
                printf("O");  // Desenha a bola
                resetar_cor();  // Reseta a cor
            } else if (x == 2 && y >= raquete1_y && y < raquete1_y + TAMANHO_RAQUETE) {
                configurar_cor(2, 2);  // Configura a cor para a raquete do jogador 1 (verde)
                printf("|");  // Desenha a raquete do jogador 1
                resetar_cor();  // Reseta a cor
            } else if (x == LARGURA - 3 && y >= raquete2_y && y < raquete2_y + TAMANHO_RAQUETE) {
                configurar_cor(6, 6);  // Configura a cor para a raquete do jogador 2 (amarelo)
                printf("|");  // Desenha a raquete do jogador 2
                resetar_cor();  // Reseta a cor
            } else {
                printf(" ");  // Preenche o restante do campo com espaços vazios
            }
        }
        printf("\n");
    }

    desenhar_borda();  // Desenha a borda inferior
    printf("Jogador 1: %d    Jogador 2: %d    Fase: %d\n", pontos_jogador1, pontos_jogador2, fase_atual);  // Exibe a pontuação e fase
}

// Função para desenhar o menu principal
void desenhar_menu_principal() {
    system("cls");  // Limpa a tela do console
    configurar_cor(10, 0);  // Configura a cor para texto verde (10) com fundo preto (0)

    printf("========================================\n");
    printf("|              JOGO PONG               |\n");
    printf("|                                      |\n");
    printf("|     [1] Iniciar Jogo                 |\n");
    printf("|     [2] Estatísticas                 |\n");
    printf("========================================\n");

    resetar_cor();  // Reseta a cor para o padrão
}

// Função para exibir o menu final após o jogo
void exibir_menu_final() {
    system("cls");  // Limpa a tela do console
    configurar_cor(10, 0);  // Configura a cor para texto verde (10) com fundo preto (0)

    printf("========================================\n");
    printf("|              FIM DE JOGO             |\n");
    printf("|                                      |\n");
    printf("|     [1] Ver Estatísticas             |\n");
    printf("|     [2] Jogar Novamente              |\n");
    printf("========================================\n");

    resetar_cor();  // Reseta a cor para o padrão
}

// Função para exibir as estatísticas do jogo
void exibir_estatisticas(EstatisticasJogo *estatisticas) {
    system("cls");  // Limpa a tela do console
    configurar_cor(7, 0);  // Configura a cor para texto branco (7) com fundo preto (0)

    printf("============================================\n");
    printf("|                FIM DE JOGO               |\n");
    printf("============================================\n");
    printf("Jogador 1: %d pontos\n", estatisticas->pontos_jogador1);  // Exibe a pontuação do jogador 1
    printf("Jogador 2: %d pontos\n", estatisticas->pontos_jogador2);  // Exibe a pontuação do jogador 2
    printf("Fase alcançada: %d\n", estatisticas->fase_atual - 1);  // Exibe a fase alcançada
    printf("Pontos totais: %d\n", estatisticas->pontos_totais);  // Exibe os pontos totais
    printf("\nPressione qualquer tecla para voltar ao menu...\n");

    _getch();  // Aguarda o pressionamento de uma tecla
}

// Função para salvar as estatísticas no arquivo
void salvar_estatisticas(EstatisticasJogo *estatisticas) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "wb");  // Abre o arquivo em modo binário para escrita
    if (arquivo == NULL) {
        printf("Erro ao salvar as estatísticas!\n");
        return;
    }

    fwrite(estatisticas, sizeof(EstatisticasJogo), 1, arquivo);  // Escreve as estatísticas no arquivo
    fclose(arquivo);  // Fecha o arquivo
}

// Função para carregar as estatísticas do arquivo
EstatisticasJogo* carregar_estatisticas() {
    EstatisticasJogo *estatisticas = (EstatisticasJogo *)malloc(sizeof(EstatisticasJogo));  // Aloca memória para as estatísticas
    if (estatisticas == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(1);
    }

    FILE *arquivo = fopen(NOME_ARQUIVO, "rb");  // Abre o arquivo em modo binário para leitura

    if (arquivo != NULL) {
        fread(estatisticas, sizeof(EstatisticasJogo), 1, arquivo);  // Lê as estatísticas do arquivo
        fclose(arquivo);  // Fecha o arquivo
    } else {
        estatisticas->pontos_jogador1 = 0;
        estatisticas->pontos_jogador2 = 0;
        estatisticas->fase_atual = 0;
        estatisticas->pontos_totais = 0;  // Se não existir o arquivo, inicializa as estatísticas com zero
    }

    return estatisticas;  // Retorna o ponteiro para as estatísticas
}

int main() {
    setlocale(LC_ALL, "Portuguese");  // Configura a localidade para português
    int escolha;
    EstatisticasJogo *estatisticas = carregar_estatisticas();  // Carrega as estatísticas do arquivo

    // Loop do menu principal
    while (1) {
        desenhar_menu_principal();  // Desenha o menu principal
        if (_kbhit()) {  // Se uma tecla foi pressionada
            char tecla = _getch();  // Captura a tecla pressionada
            if (tecla == '1') {  // Se a tecla for '1', inicia o jogo
                break;
            } else if (tecla == '2') {  // Se a tecla for '2', exibe as estatísticas
                exibir_estatisticas(estatisticas);
            }
        }
    }

    // Inicializa a posição da bola, raquetes e pontuação
    Posicao bola = {LARGURA / 2, ALTURA / 2};
    int bola_dx = 1, bola_dy = 1;
    int raquete1_y = ALTURA / 2 - TAMANHO_RAQUETE / 2;
    int raquete2_y = ALTURA / 2 - TAMANHO_RAQUETE / 2;
    int pontos_jogador1 = 0, pontos_jogador2 = 0;
    int pontos_totais = 0;
    int fase_atual = 1;
    int velocidade = 100;

    // Loop principal do jogo
    while (pontos_jogador1 < 10 && pontos_jogador2 < 10) {
        bola.x += bola_dx;
        bola.y += bola_dy;

        // Verifica colisões com as bordas superior e inferior
        if (bola.y == 0 || bola.y == ALTURA - 1) {
            bola_dy *= -1;  // Inverte a direção vertical da bola
        }

        // Verifica colisões com as raquetes
        if (bola.x == 3 && bola.y >= raquete1_y && bola.y < raquete1_y + TAMANHO_RAQUETE) {
            bola_dx *= -1;  // Inverte a direção horizontal da bola
        }

        if (bola.x == LARGURA - 4 && bola.y >= raquete2_y && bola.y < raquete2_y + TAMANHO_RAQUETE) {
            bola_dx *= -1;  // Inverte a direção horizontal da bola
        }

        // Se a bola passa para o lado esquerdo, o jogador 2 ganha ponto
        if (bola.x <= 0) {
            pontos_jogador2++;
            pontos_totais++;
            bola = (Posicao){LARGURA / 2, ALTURA / 2};  // Reinicia a bola no centro
            bola_dx = 1;  // Define a direção da bola
            bola_dy = (rand() % 2 == 0) ? 1 : -1;  // Define a direção aleatória vertical
        } else if (bola.x >= LARGURA) {  // Se a bola passa para o lado direito, o jogador 1 ganha ponto
            pontos_jogador1++;
            pontos_totais++;
            bola = (Posicao){LARGURA / 2, ALTURA / 2};  // Reinicia a bola no centro
            bola_dx = -1;  // Define a direção da bola
            bola_dy = (rand() % 2 == 0) ? 1 : -1;  // Define a direção aleatória vertical
        }

        // Verifica as teclas para movimentar as raquetes
        if (_kbhit()) {  // Verifica se uma tecla foi pressionada
            char tecla = _getch();  // Captura a tecla pressionada
            if (tecla == 'w' && raquete1_y > 0) raquete1_y--;  // Movimenta a raquete do jogador 1 para cima
            if (tecla == 's' && raquete1_y < ALTURA - TAMANHO_RAQUETE) raquete1_y++;  // Movimenta a raquete do jogador 1 para baixo
            if (tecla == 'i' && raquete2_y > 0) raquete2_y--;  // Movimenta a raquete do jogador 2 para cima
            if (tecla == 'k' && raquete2_y < ALTURA - TAMANHO_RAQUETE) raquete2_y++;  // Movimenta a raquete do jogador 2 para baixo
        }

        desenhar_jogo(bola, raquete1_y, raquete2_y, pontos_jogador1, pontos_jogador2, fase_atual);  // Desenha o campo de jogo

        // Verifica se é hora de avançar para a próxima fase
        if (pontos_totais >= fase_atual * 2) {
            fase_atual++;  // Avança para a próxima fase
            if (fase_atual <= 5) velocidade -= 15;  // Aumenta a velocidade do jogo
        }

        Sleep(velocidade);  // Faz uma pausa para controlar a velocidade do jogo
    }

    // Salva as estatísticas do jogo
    estatisticas->pontos_jogador1 = pontos_jogador1;
    estatisticas->pontos_jogador2 = pontos_jogador2;
    estatisticas->fase_atual = fase_atual;
    estatisticas->pontos_totais = pontos_totais;
    salvar_estatisticas(estatisticas);

    // Exibe o menu final após o término do jogo
    while (1) {
        exibir_menu_final();  // Exibe o menu final
        if (_kbhit()) {  // Verifica se uma tecla foi pressionada
            char tecla = _getch();  // Captura a tecla pressionada
            if (tecla == '1') {  // Se for '1', exibe as estatísticas
                exibir_estatisticas(estatisticas);
            } else if (tecla == '2') {  // Se for '2', reinicia o jogo
                main();  // Chama a função main novamente para reiniciar
            }
        }
    }

    free(estatisticas);  // Libera a memória alocada para as estatísticas
    return 0;  // Encerra o programa
}

