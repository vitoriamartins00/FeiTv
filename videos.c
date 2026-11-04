#include <stdio.h>
#include <string.h>
#include "entidades.h"

//funcao de validacao de curtida, verifica se o usuario ja curtiu o video, lendo um arquivo de curtidas onde cada linha tem o formato "email;id_video", se encontrar uma correspondencia, retorna 1 para indicar que o usuario ja curtiu o video, caso contrario retorna 0
int login_curtida(char email_log[], int id_video){
    FILE *arquivo = fopen("curtidas.txt", "r");
    if(arquivo == NULL) return 0;

    char email_lido[80];
    char titulo_lido[50];
    int id_lido;
    int curtida_encontrada = 0;

    while(fscanf(arquivo, "%[^;];%d;%[^\n]\n", email_lido, &id_lido, titulo_lido) != EOF){
        if (strcmp(email_log, email_lido) == 0 && id_lido == id_video){
            curtida_encontrada = 1;
            break;
        }
    }
    fclose(arquivo);
    return curtida_encontrada;
}

//funcao para atualizar o numero de curtidas do video e manter um log das curtidas para cada usuario, 
//recebe o email do usuario, o id do video e a acao (1 para curtir, -1 para descurtir), se for curtir, 
//adiciona uma linha no arquivo de curtidas com o formato "email;id_video;titulo_video", se for descurtir, remove a linha correspondente do arquivo de curtidas
void att_log_curtida(char email_log[], int id_video, char titulo_video[], int op_acao){
    if(op_acao == 1){
        FILE *arquivo = fopen("curtidas.txt", "a");
        if(arquivo){
            fprintf(arquivo, "%s;%d;%s\n", email_log, id_video, titulo_video);
            fclose(arquivo);
        }
    } else if (op_acao == -1){  //remove curtida (descurtir)
        FILE *arquivo = fopen("curtidas.txt", "r");
        FILE *temp = fopen("temp_curtidas.txt", "w");

        char email_lido[80];
        char titulo_lido[50];
        int id_lido;

        if(arquivo && temp){
            while(fscanf(arquivo, "%[^;];%d;%[^\n]\n", email_lido, &id_lido, titulo_lido) != EOF){
                //so escreve no temporario se nao for a curtida que quero remover
                if (!(strcmp(email_log, email_lido) == 0 && id_lido == id_video)){
                    fprintf(temp, "%s;%d;%s\n", email_lido, id_lido, titulo_lido);
                }
            }
            fclose(arquivo);
            fclose(temp);

            remove("curtidas.txt");
            rename("temp_curtidas.txt", "curtidas.txt");
        }

    }
}


//funcao para atualizar o numero de curtidas do video, recebe o id do video e a acao (1 para curtir, -1 
//para descurtir), le o arquivo de videos e escreve em um arquivo temporario, atualizando o numero de curtidas 
//do video correspondente, apos a leitura completa, substitui o arquivo original pelo temporario
void atualizar_curtidas(int id_video, int op_acao){
    FILE *arquivo = fopen("videos.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    Videos v;
    int cont_curtidas = 0;

    if (arquivo == NULL || temp == NULL) return;

    while(fscanf(arquivo, "%d;%[^;];%[^;];%d;%d;%[^\n]\n", &v.id, v.titulo, v.genero, &v.ano, &v.curtidas, v.sinopse) != EOF){
        if (v.id == id_video){
            if(op_acao == -1 && v.curtidas > 0){
                v.curtidas--;
            }else if (op_acao == 1){
                v.curtidas++;
            }
            cont_curtidas = 1;
        }
        fprintf(temp, "%d;%s;%s;%d;%d;%s\n", v.id, v.titulo,v.genero, v.ano, v.curtidas, v.sinopse);
    }

    fclose(arquivo);
    fclose(temp);

    if(cont_curtidas > 0){
        remove("videos.txt");
        rename("temp.txt", "videos.txt");
        printf("\nRegistrado com sucesso!\n");
        return;     
    }else{
        remove("temp.txt");     //apaga o arquivo temporario
        printf("Erro: Nenhum dado foi lido.Operacao cancelada para protecao do arquivo\n");
    }
}

//funcao de busca de video, exibe o catalogo de videos e permite ao usuario digitar um titulo para buscar, 
//se encontrar um video cujo titulo contenha a chave de busca, exibe os detalhes do video e da a opcao de curtir ou descurtir o video, 
//validando a entrada do usuario e garantindo que ele so possa curtir ou descurtir um video uma unica vez, se o usuario escolher curtir 
//ou descurtir, chama as funcoes de atualizar curtidas e atualizar log de curtidas
void buscar_video(char email_log[]){
    Videos v;
    char p_chave[50];
    int localizado = 0;
    FILE *arquivo = fopen("videos.txt", "r");

    if (arquivo == NULL){
        printf("Erro ao carregar a lista de videos.\n");
        return;
    }

    printf("+------------------------------------------------------------+\n");
    printf("|%30s %-29s|\n", "FEItv - CATALOGO DE VIDEOS", "");
    printf("+------------------------------------------------------------+\n");

    while(fscanf(arquivo, "%d;%[^;];%[^;];%d;%d;%[^\n]\n", &v.id, v.titulo, v.genero, &v.ano, &v.curtidas, v.sinopse) != EOF){
        printf("ID: %d  | %-20s (%d) | Curtidas: %d\n", v.id, v.titulo, v.ano, v.curtidas);
    }
    fclose(arquivo);
    
    printf("+------------------------------------------------------------+\n");
    printf("Digite o titulo do filme desejado (ATENCAO: Diferencie Maiuscula/Minuscula para a busca):\n");
    scanf(" %[^\n]", p_chave);
    while (getchar() != '\n');

    arquivo = fopen("videos.txt", "r");
    if (arquivo == NULL){
        printf("Erro ao reabrir a lista de videos.\n");
        return;
    }

    while(fscanf(arquivo, "%d;%[^;];%[^;];%d;%d;%[^\n]\n", &v.id, v.titulo, v.genero, &v.ano, &v.curtidas, v.sinopse) != EOF){
        if(strstr(v.titulo, p_chave) != NULL){
            printf("\n==================================================================================\n");
            printf("\nID: %d  | %s (%d)| Curtidas: %d", v.id, v.titulo, v.ano, v.curtidas);
            printf("\nGenero: %s", v.genero);
            printf("\n");
            printf("\nSinopse: %.90s", v.sinopse); 
            if (strlen(v.sinopse) > 90){
                printf("\n         %.90s", v.sinopse + 90);
            }
            if (strlen(v.sinopse) > 180) {
                printf("\n         %.90s", v.sinopse + 180);
            }
            printf("\n");
            printf("\n==================================================================================\n");
            localizado = 1;
        }
    }
    fclose(arquivo);

    if(localizado){
        int id_reacao,acao;
        int id_valido = 0;

        while(1) {
            printf("\n[1] Curtir 👍| [2] Descurtir 👎| [0] Voltar: ");
            if(scanf("%d", &acao) != 1){
                printf("\n>>> AVISO: Digite apenas numeros para a opcao! <<<\n");
                while(getchar() != '\n');
                continue;
            }
            while(getchar() != '\n');

            if(acao == 0 || acao == 1 || acao == 2) break;
            printf("\n>>> AVISO: Opcao invalida! Escolha 0, 1 ou 2. <<<\n");
        }

        if (acao == 0){
            printf("Retornando ao menu anterior...\n");
            return;
        }

        
        do{
            printf("Informe o ID do video: ");

            if(scanf("%d", &id_reacao) != 1){
                while (getchar() != '\n');
                printf("\n>>> Erro: Digite um numero valido! <<<\n");
                continue;
            }
            while (getchar() != '\n');

                
            if(id_existente(id_reacao)){
                id_valido = 1;
            }else{
                printf("\n[!] Erro: O ID %d nao existe no catalogo de videos.\n", id_reacao);
            }
        } while(!id_valido);    

        char titulo_v_escolhido[50]= "";
        arquivo = fopen("videos.txt", "r");
        while(fscanf(arquivo, "%d;%[^;];%[^;];%d;%d;%[^\n]\n", &v.id, v.titulo, v.genero, &v.ano, &v.curtidas, v.sinopse) != EOF){
            if(v.id == id_reacao){
                strcpy(titulo_v_escolhido, v.titulo);
                break;
            }
        }
        fclose(arquivo);

        int ja_curtido = login_curtida(email_log, id_reacao);
        if(acao == 1){
            if (ja_curtido){
                printf("\nVoce ja curtiu este video.\n");
            }else{
                atualizar_curtidas(id_reacao, 1);
                att_log_curtida(email_log, id_reacao, titulo_v_escolhido, 1);
            }
        }else if(acao == 2){
            if(!ja_curtido){
                printf("\nVoce ainda nao curtiu este video.\n");
            }else{
                atualizar_curtidas(id_reacao, -1);  //descurtir
                att_log_curtida(email_log, id_reacao,"", -1); //remove do log de curtidas
            }
        }

        printf("Pressione ENTER para continuar...");
        getchar();

    }else{
        printf("\nVideo nao encontrado.\n");
        printf("Pressione ENTER para continuar...");
        getchar();
    }
}

//funcao para validar se o ID do video existe no catalogo, lendo o arquivo de videos e comparando o id procurado 
//com os ids dos videos, se encontrar uma correspondencia, retorna 1 para indicar que o id existe, 
//caso contrario retorna 0
int id_existente(int id_procurado){
    FILE *arquivo = fopen("videos.txt", "r");
    Videos v;
    int id_encontrado = 0;

    if (arquivo == NULL) return 0;

    while(fscanf(arquivo, "%d;%[^;];%[^;];%d;%d;%[^\n]\n", &v.id, v.titulo, v.genero, &v.ano, &v.curtidas, v.sinopse) != EOF){
        if(v.id == id_procurado){
            id_encontrado = 1;
            break;
        }
    }

    fclose(arquivo);
    return id_encontrado;
}