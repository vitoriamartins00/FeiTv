#include <stdio.h>
#include <string.h>
#include "entidades.h"

//funcao para verificar se um video ja esta na playlist de favoritos do usuario, 
//lendo o arquivo de favoritos do usuario e comparando o id procurado com os ids dos videos salvos, 
//se encontrar uma correspondencia, retorna 1 para indicar que o video ja esta na playlist, caso contrario retorna 0
int verificacao_playlist(char email_log[], int id_procurado){
    char nome_arquivo[80];
    int id_lido, ano;
    char titulo [50];
    char genero [30];

    sprintf(nome_arquivo, "fav_%s.txt", email_log); //monta o nome do arquivo de favs do usuario logado
    FILE *arquivo = fopen(nome_arquivo, "r");

    if (arquivo == NULL){
        return 0; //indica que a playlist nao existe ou esta vazia
    }

    while(fscanf(arquivo, "%d;%[^;];%[^;];%d\n", &id_lido, titulo, genero, &ano) != EOF){
        if(id_lido == id_procurado){
            fclose(arquivo);
            return 1;
        }
    }

    fclose(arquivo);
    return 0;   //passou e nao encontrou o id
}

//funcao para criar uma nova playlist de favoritos, exibe o catalogo de videos e permite o usuario escolher 
//um video para adicionar a sua playlist
void criar_lista(char email_log[]){
    char nome_arquivo[80];
    int id_escolhido;
    int valido = 0;
    Videos v;

    FILE *arq_videos, *arq_favs;

    arq_videos = fopen("videos.txt", "r");
    if(arq_videos == NULL){
        printf("\nErro: O catalogo esta vazio ou nao existe.\n");
        return;
    }

    printf("+------------------------------------------------------------+\n");
    printf("|%30s %-29s|\n", "FEItv - CATALOGO DE VIDEOS", "");
    printf("+------------------------------------------------------------+\n");

    while(fscanf(arq_videos, "%d;%[^;];%[^;];%d;%d;%[^\n]\n", &v.id, v.titulo, v.genero, &v.ano, &v.curtidas, v.sinopse) != EOF){
        printf("ID: %d  | %-20s (%d) | Curtidas: %d\n", v.id, v.titulo, v.ano, v.curtidas);
    }
    fclose(arq_videos);
    printf("\n==============================================================\n");

    do {
        printf("\nDigite o ID do video para favoritar (ou 0 para voltar): ");
        if (scanf("%d", &id_escolhido) != 1){
            printf("\n>>>AVISO: Digite apenas numeros para o ID! <<<\n");
            while (getchar() != '\n');
            continue;

        }
        while (getchar() != '\n');

        if (id_escolhido == 0) {
            return;
        }

        if(verificacao_playlist(email_log, id_escolhido)){
            printf(">>> AVISO: Este video já foi adicionado a sua lista de favoritos! <<<\n");
            continue;
        }

        if(id_existente(id_escolhido)) {
            valido = 1;
        }
        else {
            printf("\n============================================================\n");
            printf("ID %d nao encontrado.\n", id_escolhido);
            printf("\n============================================================\n");
        }
    } while(!valido);

    // busca os dados do vídeo escolhido para salvar o titulo e ano
    arq_videos = fopen("videos.txt", "r");
    while(fscanf(arq_videos, "%d;%[^;];%[^;];%d;%d;%[^\n]\n", &v.id, v.titulo, v.genero, &v.ano, &v.curtidas, v.sinopse) != EOF){
        if (v.id == id_escolhido) break;
    }
    fclose(arq_videos);

    sprintf(nome_arquivo, "fav_%s.txt", email_log);
    arq_favs = fopen(nome_arquivo, "a");

    if (arq_favs != NULL){
        // agora salva apenas os tres dados id, titulo e ano
        fprintf(arq_favs, "%d;%s;%s;%d\n", v.id, v.titulo, v.genero, v.ano); 
        fclose(arq_favs);
        printf("\n'%s' adicionado com sucesso!\n", v.titulo);
    }
}

//funcao para listar os videos salvos na playlist de favoritos do usuario, l
//e o arquivo de favoritos do usuario e exibe os videos salvos, se a playlist estiver vazia ou nao existir, 
//exibe uma mensagem informando que a lista esta vazia
void listar_fav(char email_log[]){
    char nome_arq[80];
    int id_fav, ano;
    char titulo [50];
    char genero [30];
    int encontrou_v = 0;

    sprintf(nome_arq, "fav_%s.txt", email_log);
    FILE *arq_favs = fopen(nome_arq, "r");

    if (arq_favs == NULL){
        printf("\n+------------------------------------------------------------+\n");
        printf("|%30s %-29s|\n", "SUA LISTA ESTA VAZIA", "");
        printf("\n|%30s %1s|\n", "Escolha a opcao 1 abaixo para adicionar seu primeiro video", "");
        printf("+------------------------------------------------------------+\n");
        return; 
    }

    printf("+------------------------------------------------------------+\n");
    printf("|%30s %-29s|\n", "FEItv - LISTA DE FAVORITOS", "");
    printf("+------------------------------------------------------------+\n");

    
    while (fscanf(arq_favs, "%d;%[^;];%[^;];%d\n", &id_fav, titulo, genero, &ano) != EOF) {
        printf("ID: %d | %-20s | %-12s (%d)\n", id_fav, titulo, genero, ano);
        encontrou_v = 1;
    }
    fclose(arq_favs);

    if(!encontrou_v){
        printf("|%30s %-29s|\n", "Nenhum video salvo encontrado", "");
        printf("+------------------------------------------------------------+\n");
    }else{
        printf("+------------------------------------------------------------+\n");
    }
}

//funcao para remover um video da playlist de favoritos do usuario,
//exibe a lista de favoritos do usuario e pede para digitar o ID do video que deseja remover,
//lendo o arquivo de favoritos do usuario e copiando para um arquivo temporario
void remover_fav(char email_log []){
    char nome_orig[80], nome_temp[80];
    int id_remover, id_lido, ano;
    char titulo [50];
    char genero [30];
    int encontrado = 0;
    FILE *arq_orig, *arq_temp;

    sprintf(nome_orig, "fav_%s.txt", email_log);
    sprintf(nome_temp, "temp_fav_%s.txt", email_log);

    arq_orig = fopen(nome_orig, "r");

    if(arq_orig == NULL) {
        printf("\n============================================================\n");
        printf(">>> AVISO: Voce nao possui uma lista de favoritos criada! <<<\n");
        printf("\n============================================================\n");
        printf("Pressiona ENTER para retornar ao menu...");
        getchar();
        return;
    }

    listar_fav(email_log);
    printf("\n==============================================================\n");

    while(1) {
        printf("\nDigite o ID para remover (0 para cancelar): ");
        if(scanf("%d", &id_remover) != 1){
            printf("\n>>> AVISO: Digite apenas numeros para o ID! <<<\n");
            while (getchar() != '\n'); //limpa o buffer do teclado
            continue;
        }

        while(getchar() != '\n');
        break;
    }

    if(id_remover == 0) { fclose(arq_orig); return; }

    arq_temp = fopen(nome_temp, "w");
    
    //lendo o arquivo orig. e copiando para o temporario
    while(fscanf(arq_orig, "%d;%[^;];%[^;];%d\n", &id_lido, titulo, genero, &ano) != EOF){
        if(id_lido != id_remover) 
            fprintf(arq_temp, "%d;%s;%s;%d\n", id_lido, titulo, genero, ano);
        else 
            encontrado = 1;
    }

    fclose(arq_orig); 
    fclose(arq_temp);

    if(encontrado){
        remove(nome_orig);
        rename(nome_temp, nome_orig);
        printf("Video removido com sucesso!\n");
    } else {
        remove(nome_temp);
        printf("ID nao encontrado na sua lista de favoritos.\n");
    }
}

//funcao para adicionar um video a playlist de favoritos do usuario, recebe o email do usuario logado, id do video, titulo, genero e ano,
//monta o nome do arquivo de favoritos do usuario e escreve os dados do video no arquivo de favoritos do usuario, se o arquivo nao existir, ele sera criado
void add_video (char email_log [], int id_video, char titulo[], char genero[], int ano){
    char nome_arquivo[50];
    sprintf(nome_arquivo, "fav_%s.txt", email_log);

    FILE *arquivo = fopen(nome_arquivo, "a");
    if(arquivo == NULL){
        printf("Erro ao acessar lista de favoritos.");
        return;
    }

    fprintf(arquivo, "%d;%s;%s;%d\n", id_video, titulo, genero, ano);
    fclose(arquivo);

    printf("\n'%s' adicionado ao seus favoritos\n", titulo);
}

//funcao para editar a lista de favoritos do usuario, exibe a lista de favoritos do usuario e da a opcao de 
//adicionar ou remover videos da lista, caso escolha adicionar, exibe o catalogo de videos para escolher um video para adicionar a lista, caso escolha remover, chama a funcao de remover video da lista
void editar_lista(char email_log[]){
    int op_ed, id_escolhido;
    int valido_id;
    Videos v;
    FILE *arq_catalogo;

    do{
        listar_fav(email_log);

        printf("\n1:Adicionar video\n2:Remover video\n0:Voltar\n");
        printf("==============================================================\n");
        printf("Escolha: ");
        op_ed = ler_opcao();

        if(op_ed == 1){
            arq_catalogo = fopen("videos.txt", "r");
            if (arq_catalogo == NULL){
                printf("\nErro: Arquivo videos.txt nao encontrado.\n");
                continue;
            }

            printf("+------------------------------------------------------------+\n");
            printf("|%30s %-29s|\n", "FEItv - CATALOGO DE VIDEOS", "");
            printf("+------------------------------------------------------------+\n");
            while (fscanf(arq_catalogo, "%d;%[^;];%[^;];%d;%d;%[^\n]\n", &v.id, v.titulo, v.genero, &v.ano, &v.curtidas, v.sinopse) != EOF) {
                printf("ID: %-3d | %-20s | %-15s (%d)\n", v.id, v.titulo, v.genero, v.ano);
            }

            fclose(arq_catalogo);
            printf("+------------------------------------------------------------+\n");

            while(1){
                printf("\nDigite o ID do video que deseja adicionar ou 0 para cancelar: ");
                //validacao para garantir que o ID digitado seja um numero inteiro
                if(scanf("%d", &id_escolhido) != 1) {
                    printf("\n >>>AVISO: Digite apenas numeros para o ID! <<<\n");
                    while (getchar() != '\n'); //limpa a string/letras do buffer
                    continue; //reinicia o loop do menu
                }
                while (getchar() != '\n');  //limpa o enter do buffer

                if (id_escolhido == 0) {
                    printf("Operacao cancelada.\n");
                    break;      //sai do loop do do-while e volta ao menu anterior
                }

                if(verificacao_playlist(email_log, id_escolhido)){
                printf("\n>>> AVISO: Este video ja esta na sua lista de favoritos! <<<\n");
                continue;
                }

                //validacao de existencia
                if(id_existente(id_escolhido)){
                    break;
                } else{
                    printf("\n==============================================================\n");
                    printf("\n>>> AVISO: ID %d nao localizado no catalogo. Tente novamente! <<<\n", id_escolhido);
                    printf("\n==============================================================\n");
                }
            }

            if(id_escolhido == 0){
                continue;
            }

            //insere o video apos a validacao
            arq_catalogo = fopen("videos.txt", "r");
                
            while (fscanf(arq_catalogo, "%d;%[^;];%[^;];%d;%d;%[^\n]\n", &v.id, v.titulo, v.genero, &v.ano, &v.curtidas, v.sinopse) != EOF){
                if (v.id == id_escolhido){
                    add_video(email_log, v.id, v.titulo, v.genero, v.ano);
                        break;
                }
            }
            fclose(arq_catalogo);

        }
        else if (op_ed == 2){
            remover_fav(email_log);
        } else if (op_ed != 0){
            printf("\nOpcao invalida!\n");
            printf("\n>>>AVISO: A opcao %d nao existe! Escolha 0, 1 ou 2.<<<\n", op_ed);    
        }else if (op_ed == 0){
            printf("\nRetornando ao menu anterior...\n");
        }
    } while(op_ed != 0);
}

//funcao para gerenciar os favoritos do usuario, exibe um menu com as opcoes de criar lista, ver lista e excluir lista,
//chamando as funcoes correspondentes para cada opcao, caso escolha excluir lista, verifica se a lista existe antes de 
//tentar excluir, caso escolha ver lista, chama a funcao de listar favoritos, caso escolha criar lista, chama a funcao de criar lista
void gerenciar_favs(char email_log[]){
    int op;

    do{
        printf("\n+------------------------------------------------------------+\n");
        printf("|%30s %-29s|\n", "FEItv - GERENCIAR FAVORITOS", "");
        printf("+------------------------------------------------------------+\n");
        printf("1:Criar Lista\n2:Ver Lista\n3:Excluir Lista\n0:Voltar\n");
        printf("==============================================================\n");
        printf("Escolha: ");
        op = ler_opcao();

        switch(op){
            case 0:
                printf("\nRetornando ao menu anterior...\n");
                break;
            case 1:
                criar_lista(email_log);
                break;
            case 2: 
                editar_lista(email_log);
                break;
            case 3:{
                char nome_arquivo[80];
                sprintf(nome_arquivo, "fav_%s.txt", email_log);
                FILE *checar_arq = fopen(nome_arquivo, "r");

                if(checar_arq == NULL){
                    printf(">>> AVISO: Voce nao possui uma lista de favoritos para excluir! <<<\n");
                }else{
                    fclose(checar_arq);
                    remove(nome_arquivo);
                    printf("Lista excluida com sucesso!\n");
                }
                printf("\nPressione ENTER para continuar...");
                getchar();
                break;  
            }
            default:
                printf("\nOpcao invalida!");
                printf("\n\n>>>AVISO: Escolha apenas entre as opcoes 0, 1 ou 2.<<<\n");
                printf("\nPressione ENTER para continuar...");
                getchar();
                break;
        }
    } while(op != 0);
}