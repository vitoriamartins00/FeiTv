#include <stdio.h>
#include <string.h>
#include "entidades.h"

//funcao para cadastrar um novo usuario, le o nome, email e senha do usuario, verifica se o email ja esta cadastrado 
//lendo o arquivo de usuarios, se nao estiver, escreve os dados do novo usuario no arquivo
void cadastrar_usuarios(){
    Usuarios novo, us_lido;   //declarando nova variavel novo do tipo struct usuarios, para armazenar os dados do usuario a ser cadastrado

    FILE *arquivo;
    int ja_cadastrado = 0;  //contador para verificar se o email ja esta cadastrado

    printf("+------------------------------------------------------------+\n");
    printf("|%33s%27s|\n", "CADASTRO DE USUARIO", " ");
    printf("+------------------------------------------------------------+\n");
    printf("Nome: ");
    scanf(" %[^\n]", novo.nome); //le o nome com espacos
    printf("Email: ");
    scanf(" %s", novo.email);
    printf("Senha: ");
    scanf(" %s", novo.senha);

    arquivo = fopen("usuarios.txt", "r");
    if (arquivo != NULL){
        //checando se o email ja esta cadastrado, lendo o arquivo linha por linha e comparando o email digitado com os emails salvos no arquivo, se encontrar uma correspondencia, define ja_cadastrado como 1 e exibe uma mensagem de erro
        while(fscanf(arquivo, "%[^;];%[^;];%[^\n]\n", us_lido.nome, us_lido.email, us_lido.senha) != EOF){
            if(strcmp(novo.email, us_lido.email) == 0){
                ja_cadastrado = 1;
                printf("\nEmail ja cadastrado. Tente novamente com um email diferente.\n");
                break;
            }
        }
        fclose(arquivo);    //fechando o arquivo apos a leitura para evitar problemas de acesso em outras partes 
    }
    if(ja_cadastrado){
        return;
    }

    arquivo = fopen("usuarios.txt", "a");

    if (arquivo == NULL){
        printf("Erro ao criar o arquivo!\n");
        return;
    }  //verificando se o arquivo foi aberto corretamente, caso contrario exibe uma mensagem de erro e retorna da funcao

    fprintf(arquivo, "%s;%s;%s\n", novo.nome, novo.email, novo.senha); //escreve os dados do usuario no arquivo separando por ponto e virgula

    fclose(arquivo); 
    printf("\nCadastro realizado com sucesso!\n");
    getchar(); 
}

//recebe nomeDestino para preencher com o nome encontrado no arquvo
int fazer_login(char nome_usuario[], char email_logado []){
    char emailBusca[80], senhaBusca[10];
    char nomeSalvo[50], emailSalvo[80], senhaSalvo[10];

    int email_encontrado = 0;
    int login_sucesso = 0;

    FILE *arquivo;

    printf("+------------------------------------------------------------+\n");
    printf("|%33s%27s|\n", "LOGIN", " ");
    printf("+------------------------------------------------------------+\n");
    printf("Email: ");
    scanf(" %s", emailBusca);
    printf("Senha: ");
    scanf(" %s", senhaBusca);
    getchar(); //limpa o buffer do teclado para evitar problemas com fgets em outras partes do programa

    arquivo = fopen("usuarios.txt", "r");

    if (arquivo == NULL){

        printf("\nUsuario nao cadastrado. Acesse a opcao 2 no menu inicial para criar uma conta.\n");
        return 0;
    }

    //lendo o arquivo linha por linha, comparando o email e senha digitados com os dados salvos no arquivo, se encontrar uma correspondencia, define encontrado como 1, caso contrario exibe uma msg de erro
    while (fscanf(arquivo, "%[^;];%[^;];%[^\n]\n", nomeSalvo, emailSalvo, senhaSalvo) != EOF){
        if(strcmp(emailBusca, emailSalvo) == 0){
            email_encontrado = 1;

            if(strcmp(senhaBusca, senhaSalvo) == 0){
                login_sucesso = 1;
                strcpy(nome_usuario, nomeSalvo);    //preenche a variavel nome_usuario com o nome encontrado no arquivo para usar posteriormente
                strcpy(email_logado, emailSalvo);
                break;
            }
            
        }
    }
    fclose(arquivo);

    //validacao de acesso 
    if (login_sucesso){
        return 1;
    }

    if (email_encontrado){
        printf("\nSenha incorreta. Tente novamente.\n");
    } else {
        printf("\nUsuario nao cadastrado. Acesse a opcao 2 no menu inicial para criar uma conta.\n");
    }
    return 0;
}