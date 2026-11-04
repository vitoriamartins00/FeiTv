#include <stdio.h>
#include "entidades.h"

//funcao para exibir o menu home do usuario logado, recebe o nome e email do usuario logado para 
//personalizar, exibe as opcoes de buscar video, gerenciar favoritos e logout, lendo a opcao do usuario 
//e chamando as funcoes correspondentes para cada opcao
void menu_home(char nome[], char email_logado[]){
    int op_home;

    do{
        printf("+------------------------------------------------------------+\n");
        printf("|%30s %-29s|\n", "FEItv - HOME,", nome);
        printf("+------------------------------------------------------------+\n");
        printf("1: Buscar Video\n2: Gerenciar Favoritos\n0: Logout");
        printf("\n==============================================================\n");
        printf("Escolha: ");
        
        op_home = ler_opcao(); 

        switch (op_home) {
            case 0:
                printf("Encerrando seu acesso... Ate logo, %s!\n", nome);
                break;
            case 1:
                buscar_video(email_logado); //chama a funcao de busca de video
                break;
            case 2:
                gerenciar_favs(email_logado); //chama a funcao de gerenciamento de favoritos
                break;
            default:
                printf("\nOpcao invalida!\n");
                printf("\n\n>>> AVISO: Escolha apenas entre as opcoes 0, 1 ou 2. <<<\n\n");
                printf("\nPressione ENTER para continuar...");
                getchar();
                break;
        }

    } while (op_home != 0);
}