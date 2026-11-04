#ifndef ENTIDADES_H //verifica se a macro ENTIDADES_H ja foi definida
#define ENTIDADES_H //reconhece que ENTIDADES_H esta definida

//definicao das classes de usuario
typedef struct {
    char nome[50];
    char email[80];
    char senha[10];
}Usuarios;

//definicao das classes de videos
typedef struct {
    int id;
    char titulo[100];
    char genero[30];
    int ano;
    int curtidas;
    char sinopse[500];
} Videos;

//definicao das classes de playlist
typedef struct {
    char nomeplaylist[50];
    char email_usuario[80];
    int id_video[20];

}Playlist;

//funcoes de usuarios
void cadastrar_usuarios();  
int fazer_login(char nome_usuario[], char email_logado[]); 
void menu_home(char nome_usuario[], char email_logado[]);
int ler_opcao();

//funcoes videos e curtidas
void buscar_video(char email_log[]);
void atualizar_curtidas(int id_video, int op_acao);
void att_log_curtida(char email_log[], int id_video, char titulo_video[], int op_acao);
int id_existente(int id_procurado);
int login_curtida(char email_log[], int id_video);

//funcoes favoritos
int verificacao_playlist(char email_log[], int id_procurado);
void criar_lista(char email_log []);
void listar_fav(char email_log[]);
void remover_fav(char email_log[]);
void add_video (char email_log [], int id_video, char titulo[], char genero[], int ano);
void editar_lista(char email_log[]);
void gerenciar_favs(char email_log []);



#endif //finaliza o bloco de protecao