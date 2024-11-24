#include <stdio.h>   // Biblioteca padr�o de entrada e sa�da, usada para fun��es como printf() e scanf()
#include <stdlib.h>  // Biblioteca que fornece fun��es de gerenciamento de mem�ria e controle de execu��o, como malloc(), free(), exit(), etc.
#include <conio.h>   // Biblioteca usada para controle de entrada de teclado, como _getch() e _kbhit() (geralmente usada em programas de console para detectar teclas pressionadas)
#include <windows.h> // Biblioteca para interagir com recursos do sistema operacional Windows, como manipula��o de cores no console e controle de tempo (Sleep())
#include <locale.h>  // Biblioteca para definir e manipular configura��es de localidade (usada aqui para definir o idioma para portugu�s)


// Defini��es de constantes do jogo
#define LARGURA 40  
#define ALTURA 20  
#define TAMANHO_RAQUETE 4 
#define NOME_ARQUIVO "estatisticas.dat" 

// Estrutura que mant�m as estat�sticas do jogo
typedef struct {
    int pontos_jogador1;
    int pontos_jogador2;
    int fase_atual;
    int pontos_totais;
} EstatisticasJogo;

// Estrutura para armazenar a posi��o (x, y) de um ponto
typedef struct {
    int x, y; 
} Posicao;

// Fun��o para configurar as cores do texto e fundo no console
void configurar_cor(int cor_texto, int cor_fundo) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // Obt�m o manipulador de sa�da do console
    SetConsoleTextAttribute(hConsole, (cor_fundo << 4) | cor_texto);  // Define a cor do texto e fundo
}

// Fun��o para resetar as cores para o padr�o
void resetar_cor() {
    configurar_cor(7, 0);  // Configura o texto como branco (7) no fundo preto (0)
}

// Fun��o para desenhar a borda superior do campo de jogo
void desenhar_borda() {
    int i;
    configurar_cor(1, 1);  // Configura a cor para o texto com cor 1 (vermelho) e fundo 1 (azul)
    for (i = 0; i <= LARGURA; i++) printf(" ");  // Imprime a borda
    printf("\n");
    resetar_cor();  // Reseta a cor para o padr�o
}

// Fun��o que desenha o campo de jogo, raquetes, bola e pontua��o
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
                printf(" ");  // Preenche o restante do campo com espa�os vazios
            }
        }
        printf("\n");
    }

    desenhar_borda();  // Desenha a borda inferior
    printf("Jogador 1: %d    Jogador 2: %d    Fase: %d\n", pontos_jogador1, pontos_jogador2, fase_atual);  // Exibe a pontua��o e fase
}

// Fun��o para desenhar o menu principal
void desenhar_menu_principal() {
    system("cls");  // Limpa a tela do console
    configurar_cor(10, 0);  // Configura a cor para texto verde (10) com fundo preto (0)

    printf("========================================\n");
    printf("|              JOGO PONG               |\n");
    printf("|                                      |\n");
    printf("|     [1] Iniciar Jogo                 |\n");
    printf("|     [2] Estat�sticas                 |\n");
    printf("========================================\n");

    resetar_cor();  // Reseta a cor para o padr�o
}

// Fun��o para exibir o menu final ap�s o jogo
void exibir_menu_final() {
    system("cls");  // Limpa a tela do console
    configurar_cor(10, 0);  // Configura a cor para texto verde (10) com fundo preto (0)

    printf("========================================\n");
    printf("|              FIM DE JOGO             |\n");
    printf("|                                      |\n");
    printf("|     [1] Ver Estat�sticas             |\n");
    printf("|     [2] Jogar Novamente              |\n");
    printf("========================================\n");

    resetar_cor();  // Reseta a cor para o padr�o
}

// Fun��o para exibir as estat�sticas do jogo
void exibir_estatisticas(EstatisticasJogo *estatisticas) {
    system("cls");  // Limpa a tela do console
    configurar_cor(7, 0);  // Configura a cor para texto branco (7) com fundo preto (0)

    printf("============================================\n");
    printf("|                FIM DE JOGO               |\n");
    printf("============================================\n");
    printf("Jogador 1: %d pontos\n", estatisticas->pontos_jogador1);  // Exibe a pontua��o do jogador 1
    printf("Jogador 2: %d pontos\n", estatisticas->pontos_jogador2);  // Exibe a pontua��o do jogador 2
    printf("Fase alcan�ada: %d\n", estatisticas->fase_atual - 1);  // Exibe a fase alcan�ada
    printf("Pontos totais: %d\n", estatisticas->pontos_totais);  // Exibe os pontos totais
    printf("\nPressione qualquer tecla para voltar ao menu...\n");

    _getch();  // Aguarda o pressionamento de uma tecla
}

// Fun��o para salvar as estat�sticas no arquivo
void salvar_estatisticas(EstatisticasJogo *estatisticas) {
    FILE *arquivo = fopen(NOME_ARQUIVO, "wb");  // Abre o arquivo em modo bin�rio para escrita
    if (arquivo == NULL) {
        printf("Erro ao salvar as estat�sticas!\n");
        return;
    }

    fwrite(estatisticas, sizeof(EstatisticasJogo), 1, arquivo);  // Escreve as estat�sticas no arquivo
    fclose(arquivo);  // Fecha o arquivo
}

// Fun��o para carregar as estat�sticas do arquivo
EstatisticasJogo* carregar_estatisticas() {
    EstatisticasJogo *estatisticas = (EstatisticasJogo *)malloc(sizeof(EstatisticasJogo));  // Aloca mem�ria para as estat�sticas
    if (estatisticas == NULL) {
        printf("Erro de aloca��o de mem�ria!\n");
        exit(1);
    }

    FILE *arquivo = fopen(NOME_ARQUIVO, "rb");  // Abre o arquivo em modo bin�rio para leitura

    if (arquivo != NULL) {
        fread(estatisticas, sizeof(EstatisticasJogo), 1, arquivo);  // L� as estat�sticas do arquivo
        fclose(arquivo);  // Fecha o arquivo
    } else {
        estatisticas->pontos_jogador1 = 0;
        estatisticas->pontos_jogador2 = 0;
        estatisticas->fase_atual = 0;
        estatisticas->pontos_totais = 0;  // Se n�o existir o arquivo, inicializa as estat�sticas com zero
    }

    return estatisticas;  // Retorna o ponteiro para as estat�sticas
}

int main() {
    setlocale(LC_ALL, "Portuguese");  // Configura a localidade para portugu�s
    int escolha;
    EstatisticasJogo *estatisticas = carregar_estatisticas();  // Carrega as estat�sticas do arquivo

    // Loop do menu principal
    while (1) {
        desenhar_menu_principal();  // Desenha o menu principal
        if (_kbhit()) {  // Se uma tecla foi pressionada
            char tecla = _getch();  // Captura a tecla pressionada
            if (tecla == '1') {  // Se a tecla for '1', inicia o jogo
                break;
            } else if (tecla == '2') {  // Se a tecla for '2', exibe as estat�sticas
                exibir_estatisticas(estatisticas);
            }
        }
    }

    // Inicializa a posi��o da bola, raquetes e pontua��o
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

        // Verifica colis�es com as bordas superior e inferior
        if (bola.y == 0 || bola.y == ALTURA - 1) {
            bola_dy *= -1;  // Inverte a dire��o vertical da bola
        }

        // Verifica colis�es com as raquetes
        if (bola.x == 3 && bola.y >= raquete1_y && bola.y < raquete1_y + TAMANHO_RAQUETE) {
            bola_dx *= -1;  // Inverte a dire��o horizontal da bola
        }

        if (bola.x == LARGURA - 4 && bola.y >= raquete2_y && bola.y < raquete2_y + TAMANHO_RAQUETE) {
            bola_dx *= -1;  // Inverte a dire��o horizontal da bola
        }

        // Se a bola passa para o lado esquerdo, o jogador 2 ganha ponto
        if (bola.x <= 0) {
            pontos_jogador2++;
            pontos_totais++;
            bola = (Posicao){LARGURA / 2, ALTURA / 2};  // Reinicia a bola no centro
            bola_dx = 1;  // Define a dire��o da bola
            bola_dy = (rand() % 2 == 0) ? 1 : -1;  // Define a dire��o aleat�ria vertical
        } else if (bola.x >= LARGURA) {  // Se a bola passa para o lado direito, o jogador 1 ganha ponto
            pontos_jogador1++;
            pontos_totais++;
            bola = (Posicao){LARGURA / 2, ALTURA / 2};  // Reinicia a bola no centro
            bola_dx = -1;  // Define a dire��o da bola
            bola_dy = (rand() % 2 == 0) ? 1 : -1;  // Define a dire��o aleat�ria vertical
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

        // Verifica se � hora de avan�ar para a pr�xima fase
        if (pontos_totais >= fase_atual * 2) {
            fase_atual++;  // Avan�a para a pr�xima fase
            if (fase_atual <= 5) velocidade -= 15;  // Aumenta a velocidade do jogo
        }

        Sleep(velocidade);  // Faz uma pausa para controlar a velocidade do jogo
    }

    // Salva as estat�sticas do jogo
    estatisticas->pontos_jogador1 = pontos_jogador1;
    estatisticas->pontos_jogador2 = pontos_jogador2;
    estatisticas->fase_atual = fase_atual;
    estatisticas->pontos_totais = pontos_totais;
    salvar_estatisticas(estatisticas);

    // Exibe o menu final ap�s o t�rmino do jogo
    while (1) {
        exibir_menu_final();  // Exibe o menu final
        if (_kbhit()) {  // Verifica se uma tecla foi pressionada
            char tecla = _getch();  // Captura a tecla pressionada
            if (tecla == '1') {  // Se for '1', exibe as estat�sticas
                exibir_estatisticas(estatisticas);
            } else if (tecla == '2') {  // Se for '2', reinicia o jogo
                main();  // Chama a fun��o main novamente para reiniciar
            }
        }
    }

    free(estatisticas);  // Libera a mem�ria alocada para as estat�sticas
    return 0;  // Encerra o programa
}

