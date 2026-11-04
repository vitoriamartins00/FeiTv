#include <stdio.h>
#include <string.h>
#include "entidades.h"

#define LARGURA 60 //definindo o espaco para centralizacao do menu inicial 

//funcao para exibir o cabecalho do menu, centralizando o titulo "FEItv" 
void cabecalho(){
    printf("+------------------------------------------------------------+\n");
    printf("|%33s%27s|\n", "FEItv", " ");
    printf("+------------------------------------------------------------+\n");
}

//funcao para ler a opcao do usuario, garantindo que seja um numero valido, caso contrario 
//retorna -1 para indicar uma opcao invalida
int ler_opcao(){
    int op;
    //lendo a opcao do usuario, verificando se a entrada e um numero valido, caso contrario retorna -1 para indicar uma opcao invalida
    if(scanf("%d", &op) != 1){
        while (getchar() != '\n');
        return -1;
    }   
    while (getchar() != '\n'); //limpa o buffer do teclado para evitar problemas com fgets em outras partes do programa
    return op;  
    
}

//funcao principal do programa, exibe o menu inicial com as opcoes de login, cadastro e sair, lendo a 
//opcao do usuario e chamando as funcoes correspondentes para cada opcao, caso escolha login, chama a 
//funcao de fazer login, se o login for bem sucedido, chama a funcao de menu home passando o nome e email do usuario logado,
// caso escolha cadastro, chama a funcao de cadastrar usuarios
int main (){
    int opcao;

    do{
        cabecalho();
        printf("1: Login\n");
        printf("2: Cadastro\n");
        printf("0: Sair\n");
        printf("--------------------------------------------------------------\n");
        printf("Escolha uma opcao: ");
        opcao = ler_opcao(); //chama a funcao para ler a opcao do usuario, garantindo que seja um numero valido

        switch(opcao){
            case 0:
                printf("Saindo da FEItv. Ate mais!\n");
                break;
            case 1:{
                char nome_usuario[50];
                char email_usuario[80];
                //se retornar 1 o usuario foi encontrado
                if (fazer_login(nome_usuario, email_usuario)){
                    menu_home(nome_usuario, email_usuario);
                }
                break;
            }
            case 2:
                cadastrar_usuarios();
                break;
            default:
                printf("\nOpcao invalida!");
                printf("\n\n>>>AVISO: Escolha apenas entre as opcoes 0, 1 ou 2.<<<\n\n");
                break;
        }

    } while (opcao != 0);

    return 0;
};