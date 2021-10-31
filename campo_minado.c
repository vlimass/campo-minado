#include <stdio.h>
#include <stdlib.h>
#include <time.h>
 
/*Constante para tamanho do tabuleiro */
#define TAM 9

/* Tipo BLOCO: usado para cada casa do tabuleiro, dada por um vetor tabuleiro[linha][coluna] */
typedef struct _BLOCO{  
    int tem_bomba, numero_bombas_ao_redor, aberto_ou_fechado, tem_alerta, foi_verificada;
} BLOCO;

/* Variáveis globais */
int contador_bombas; 
BLOCO tabuleiro[TAM + 1][TAM + 1];
 

/*  Função para posicionar as bombas */
void posicao_bombas() {
    int quant_bombas, i, j;
    i = 0; j = 0;
    srand (time(NULL)); /* semente para o rand () */
 
    for (quant_bombas=0; quant_bombas < (TAM + 1); quant_bombas++) {
        i = rand () % TAM;
        j = rand () % TAM;
 
        if (tabuleiro[i][j].tem_bomba == 1){  /* Para evitar a sobreposição de bomba */
            quant_bombas--;
        }
        else {
            tabuleiro[i][j].tem_bomba = 1; /* Coloca uma bomba nessa posição */
        }
    }
}


/* Função que numera as bombas ao redor de casas no tabuleiro */
void numerar_bombas() {
    int i, j;
 
    for(i=0; i< TAM; i++){
        for(j=0; j < TAM; j++){
            if (tabuleiro[i][j].tem_bomba == 1){
                if (tabuleiro[i][j+1].tem_bomba == 0 && j+1 < TAM) tabuleiro[i][j+1].numero_bombas_ao_redor++;   
                if (tabuleiro[i][j-1].tem_bomba == 0 && j-1 >= 0) tabuleiro[i][j-1].numero_bombas_ao_redor++;
                if (tabuleiro[i+1][j].tem_bomba == 0 && i+1 < TAM) tabuleiro[i+1][j].numero_bombas_ao_redor++;
                if (tabuleiro[i-1][j].tem_bomba == 0 && i-1 >= 0) tabuleiro[i-1][j].numero_bombas_ao_redor++;
                if (tabuleiro[i-1][j-1].tem_bomba == 0 && i-1 >=0 && j-1 >= 0) tabuleiro[i-1][j-1].numero_bombas_ao_redor++;
                if (tabuleiro[i-1][j+1].tem_bomba == 0 && i-1 >= 0 && j+1 < TAM) tabuleiro[i-1][j+1].numero_bombas_ao_redor++;
                if (tabuleiro[i+1][j-1].tem_bomba == 0 && i+1 < TAM && j-1 >= 0) tabuleiro[i+1][j-1].numero_bombas_ao_redor++;
                if (tabuleiro[i+1][j+1].tem_bomba == 0 && i+1 < TAM && j+1 < TAM) tabuleiro[i+1][j+1].numero_bombas_ao_redor++;
            }
        }
    }
}


/* Função que imprime o display do tabuleiro na tela */
void desenhar_tabuleiro(){ 
    int i, j, r;

    /* Contador de bombas */
    printf("\nBOMBAS RESTANTES ( * ): ");
    printf("\033[0;31m"); /* Set color = Vermelho */ 
    printf("%d\n", contador_bombas);
    printf("\033[0m"); /* Set color = default */

    /* Display do tabuleiro */
    for (i = 0; i < TAM; i++) {
        if (i==0){    
            printf ("\n   ");
            for (r=0; r < TAM ; r++){ /*coordenadas superiores*/
                printf("    %d ", r + 1);
            }  
        }
        printf ("\n     ");
            
        for (r=0; r < TAM; r++){
            printf("------");
        }

        printf("-\n");
        
        printf("  ");
        printf ("%d ", i + 1); /*coordenadas da lateral esquerda*/

        for (j=0; j < TAM; j++){
            if(tabuleiro[i][j].tem_alerta == 1){ /* Imprimir a "bandeira", bloco de alerta */
                printf("|"); 
                printf("\033[0;33m"); 
                printf ("  !  ");
                printf("\033[0m"); 

            } else if (tabuleiro[i][j].aberto_ou_fechado == 0){ 
                printf ("|     ");  

            } else if(tabuleiro[i][j].aberto_ou_fechado == 1){
                if(tabuleiro[i][j].tem_bomba == 0){
                    printf("|"); 
                    switch (tabuleiro[i][j].numero_bombas_ao_redor){
                    case 1:
                        printf("\033[0;34m"); /* Azul */
                        printf ("  %d  ", tabuleiro[i][j].numero_bombas_ao_redor); 
                        printf("\033[0m");
                        break;
                    case 2:
                        printf("\033[0;32m"); /* Verde */
                        printf ("  %d  ", tabuleiro[i][j].numero_bombas_ao_redor); 
                        printf("\033[0m");
                        break;
                    case 3:
                        printf("\033[0;35m"); /* Roxo */
                        printf ("  %d  ", tabuleiro[i][j].numero_bombas_ao_redor); 
                        printf("\033[0m");
                        break;
                    case 4: 
                        printf("\033[0;36m"); /* Ciano */
                        printf ("  %d  ", tabuleiro[i][j].numero_bombas_ao_redor); 
                        printf("\033[0m");
                        break;
                    default:
                        printf ("  %d  ", tabuleiro[i][j].numero_bombas_ao_redor); 
                        break;
                    }
                }   
                else{ 
                    printf("|"); 
                    printf("\033[0;31m"); /* Vermelho */ 
                    printf ("  *  "); 
                    printf("\033[0m");
                }

            }       
        }
        printf ("|"); 
    }

    printf ("\n    ");
    for (r=0; r < TAM; r++){
        printf("------");
    }
    printf("-\n");
    printf(" =============================================================\n\n");

}


/* Imprime o tabuleiro gabarito */
void imprimir_gabarito(){
    int i, j, r;
    for (i = 0; i < TAM; i++) {
        if (i==0){    
            printf ("\n   ");
            for (r=0; r < TAM ; r++){ /*coordenadas superiores*/
                printf("    %d ", r + 1);
            }  
        }
        printf ("\n     ");
            
        for (r=0; r < TAM; r++){
            printf("------");
        }

        printf("-\n");
        printf("  ");
        printf ("%d ", i + 1); /*coordenadas da lateral esquerda*/

        for (j=0; j < TAM; j++){
            if (tabuleiro[i][j].tem_bomba == 1) { 
                printf ("|  *  ");    
            } else {
                printf ("|  %d  ", tabuleiro[i][j].numero_bombas_ao_redor); 
            }
        }
        printf ("|"); 
    }

    printf ("\n    ");
    for (r=0; r < TAM; r++){
        printf("------");
    }
    printf("-\n");
    printf(" =============================================================\n\n");
}   


/* Atualiza as casas abertas do tabuleiro */
void atualizar_tabuleiro(int linha, int coluna){
    int i, j;
 
    tabuleiro[linha][coluna].foi_verificada = 1; /* Casa já verificada pela função atualizar_tabuleiro() */
    tabuleiro[linha][coluna].aberto_ou_fechado = 1; /* A própria posição escolhida é mostrada ao usuário*/
 
    if(tabuleiro[linha][coluna].tem_bomba == 0){ /* Usuário não escolheu uma BOMBA */

        if(tabuleiro[linha][coluna].numero_bombas_ao_redor == 0){

            /* Casa à direita */
            if (coluna < (TAM - 1) && tabuleiro[linha][coluna+1].tem_bomba == 0 && tabuleiro[linha][coluna+1].foi_verificada == 0){
                atualizar_tabuleiro(linha, (coluna+1));
            }
            /* Casa à esquerda */
            if (coluna > 0 && tabuleiro[linha][coluna-1].tem_bomba == 0 && tabuleiro[linha][coluna-1].foi_verificada == 0){ 
                atualizar_tabuleiro(linha, (coluna-1));
            }
            /* Casa acima */
            if (linha < (TAM - 1) && tabuleiro[linha+1][coluna].tem_bomba == 0 && tabuleiro[linha+1][coluna].foi_verificada == 0){ 
                atualizar_tabuleiro((linha+1), coluna);
            }
            /* Casa abaixo */
            if (linha > 0 && tabuleiro[linha-1][coluna].tem_bomba == 0  && tabuleiro[linha-1][coluna].foi_verificada == 0){ 
                atualizar_tabuleiro((linha-1), coluna);
            }
            /* Casa na diagonal superior esquerda */
            if (linha > 0 && coluna > 0 && tabuleiro[linha-1][coluna-1].tem_bomba == 0 && tabuleiro[linha-1][coluna-1].foi_verificada == 0){ 
                atualizar_tabuleiro((linha-1),(coluna-1));
            }
            /* Casa na diagonal superior direita */
            if (linha > 0 && coluna < (TAM - 1) && tabuleiro[linha-1][coluna+1].tem_bomba == 0 && tabuleiro[linha-1][coluna+1].foi_verificada == 0){ 
                atualizar_tabuleiro((linha-1), (coluna+1));
            }
            /* Casa na diagonal inferior esquerda */
            if (linha < (TAM - 1) && coluna > 0 && tabuleiro[linha+1][coluna-1].tem_bomba == 0 && tabuleiro[linha+1][coluna-1].foi_verificada == 0){
                atualizar_tabuleiro((linha+1), (coluna-1));
            }
            /* Casa na diagonal inferior direita */
            if (linha < (TAM - 1) && coluna < (TAM - 1) && tabuleiro[linha+1][coluna+1].tem_bomba == 0 && tabuleiro[linha+1][coluna+1].foi_verificada == 0){
                atualizar_tabuleiro((linha+1), (coluna+1));   
            }
        }

 
    } else if (tabuleiro[linha][coluna].tem_bomba == 1){ /* Usuário escolheu uma BOMBA */
        for (i = 0; i < TAM; i++){
            for (j = 0; j < TAM; j++){
                if(tabuleiro[i][j].tem_bomba == 1) tabuleiro[i][j].aberto_ou_fechado = 1;
            }
        }
        desenhar_tabuleiro(); /* Imprime o tabuleiro da derrota */
        
        printf("\033[0;31m"); /* Vermelho */ 
        printf("\n    _ ._  _ , _ ._\n  (_ ' ( `  )_  .__)\n ( (  (    )   `)  ) _)\n(__ (_   (_ . _) _) ,__)\n     `~~` ' . /`~~\n         ;   ;\n        /   |   BUUMMM!\n_______/_ __ |_______\n\n");
        printf("\033[0m");
        printf ("PERDEU! Voce explodiu! Tente novamente...\n");

        exit(0);
    }
}


/* Coloca ou retira um campo de alerta */
void mexer_bloco_alerta(int linha, int coluna){
    if(tabuleiro[linha][coluna].tem_alerta == 0){tabuleiro[linha][coluna].tem_alerta = 1; contador_bombas--;}
    else {tabuleiro[linha][coluna].tem_alerta = 0; contador_bombas++;}
}


/*  Função principal */
int main (void) {
    int i, j, linha_usuario, coluna_usuario, aux, valid, opcao_usuario;
    contador_bombas = 10;

    /* O cronômetro é iniciado */
    float tempo_do_jogo_s, tempo_do_jogo_min = 0;
    time_t tempo_inicio, tempo_fim;
    tempo_inicio = time(NULL);
 
    /* Inicializa o vetor tabuleiro com 0 */
    for (i = 0; i < TAM; i++) {
        for (j=0; j < TAM; j++){
            tabuleiro[i][j].numero_bombas_ao_redor = 0;  
            tabuleiro[i][j].aberto_ou_fechado = 0;
            tabuleiro[i][j].foi_verificada = 0;
        }
    }
 
    /* Chamada da função para posicionar as bombas */
    posicao_bombas();
 
    /* Impressão do tabuleiro vazio */
    system("cls"); 
    desenhar_tabuleiro();
 
    /* Numerar as bombas ao redor dos blocos sem bombas no tabuleiro */
    numerar_bombas();
 
    /* Caso queiramos ver o gabarito */
    /* imprimir_gabarito(); */

    /* Loop das jogadas */
    while(1){
        /* Loop para a validação incorreta */
        valid = 0;
        while(!valid){ 
            /* Input do usuário */
            printf("O que quer fazer?\n");
            printf("(1) Selecionar campo para pisar\n(2) Ajustar campo de alerta\n=> ");

            /* Validação */
            valid = scanf("%d", &opcao_usuario); 
            while(getchar() != '\n');
            if(valid == 0 || opcao_usuario <= 0 || opcao_usuario >= 3) {printf("[ERRO] Por favor, insira uma das opcoes acima\n\n"); valid=0;}
        }

        printf("\nInsira a coordenada que deseja: \n");
        /* Validação da linha */
        valid = 0; 
        while(!valid){
            printf("-> Linha: ");
            valid = scanf("%d", &linha_usuario);
            while(getchar() != '\n');
            if(valid == 0 || linha_usuario <= 0 || linha_usuario >= 10) {printf("[ERRO] Por favor, insira uma linha valida\n\n"); valid=0;}
        }
        /* Validação da coluna */
        valid = 0;
        while(!valid){
            printf("-> Coluna: ");
            valid = scanf("%d", &coluna_usuario);
            while(getchar() != '\n');
            if(valid == 0 || coluna_usuario <= 0 || coluna_usuario >= 10) {printf("[ERRO] Por favor, insira uma coluna valida\n\n"); valid=0;}
        }
        
        /* Ajuste da linha e coluna para a posição ZERO */
        linha_usuario--;
        coluna_usuario--;

        /* Limpar o tabuleiro antigo  */
        system("cls"); 
        
        /* Verificação da opção do usuário */
        switch (opcao_usuario){
        case 1:
            atualizar_tabuleiro(linha_usuario, coluna_usuario); /* Caso o usuário desejar selecionar um campo para pisar */
            break;
        case 2:
            mexer_bloco_alerta(linha_usuario, coluna_usuario); /* Caso o usuário desejar mexer com um campo de alerta */
            break;
        }

        /* Imprime um novo tabuleiro */
        desenhar_tabuleiro();

        /* Verifica se o usuário venceu */
        aux = 0;
        for(i = 0; i < TAM; i++){
            for(j = 0; j < TAM; j++){
                if(tabuleiro[i][j].tem_bomba == 0 && tabuleiro[i][j].aberto_ou_fechado == 1) aux++;
            }
        }

        /* aux = 71;   */  /* Forçar uma vitória */ 

        if(aux == (TAM*TAM) - (TAM + 1)){
            /* O cronômetro é finalizado*/
            tempo_fim = time(NULL);

            /* Cálculo do tempo de jogo */
            tempo_do_jogo_s = difftime(tempo_fim, tempo_inicio);
            while(tempo_do_jogo_s >= 60){ tempo_do_jogo_min++; tempo_do_jogo_s -= 60;}

            /* Mostra o display do tempo ao usuário */
            printf("TEMPO JOGADO: ");
            printf("\033[0;33m"); /* Amarelo */ 
            if(tempo_do_jogo_min < 10 && tempo_do_jogo_s < 10) printf("0%.0f : 0%.0f \n\n", tempo_do_jogo_min, tempo_do_jogo_s);   
            else if(tempo_do_jogo_min > 10 && tempo_do_jogo_s < 10) printf("%.0f : 0%.0f \n\n", tempo_do_jogo_min, tempo_do_jogo_s);
            else if(tempo_do_jogo_min < 10 && tempo_do_jogo_s > 10) printf("0%.0f : %.0f \n\n", tempo_do_jogo_min, tempo_do_jogo_s);
            else if(tempo_do_jogo_min > 10 && tempo_do_jogo_s > 10) printf("%.0f : %.0f \n\n", tempo_do_jogo_min, tempo_do_jogo_s);
            printf("\033[0m");

            /* Mostra o display da vitória */
            printf("\033[0;33m"); /* Amarelo */ 
            printf ("        ___________\n   .--- .::.        `---.\n   (::::::'              )\n   |`-----._______.-----'|\n   |              :::::::|\n  .|               ::::::!-.\n");
            printf ("  :|               :::::/|/\n   |               ::::::|\n   |     PARABENS!      :|\n   |   VOCE VENCEU!  ::::|\n   | Aqui seu trofeu!::::|\n");
            printf ("   |              .::::::|\n   J              :::::::F\n    .            :::::::/\n     `.        .:::::::.\n       `-._  .::::::-'\n");
            printf ("___________|  ...|.__________\n	   |  :::|\n           F   ::J\n          /     ::|\n     __.-'      :::`-.__\n       `  ---------  `\n");
            printf("\033[0m");
            printf ("\nVENCEU! Voce evitou todas as bombas!\n");

            exit(0);
        }
    }
    return 0;   
}