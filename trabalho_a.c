#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define ARQUIVO "dados_a.csv"

typedef struct {
    int id;
    char titulo[50];
    char artista[50];
    char duracao[10];
    char genero[30];
} Musica;

Musica playlist[MAX];
int qtd = 0;

int buscar_indice(int id){
    for(int i=0;i<qtd;i++) if(playlist[i].id==id) return i;
    return -1;
}

void carregar_csv(){
    FILE *f=fopen(ARQUIVO,"r");
    if(!f) return;
    qtd=0;
    while(qtd<MAX &&
          fscanf(f,"%d;%49[^;];%49[^;];%9[^;];%29[^\n]",
          &playlist[qtd].id,
          playlist[qtd].titulo,
          playlist[qtd].artista,
          playlist[qtd].duracao,
          playlist[qtd].genero)==5){
        qtd++;
    }
    fclose(f);
}

void salvar_csv(){
    FILE *f=fopen(ARQUIVO,"w");
    if(!f){ printf("Erro ao salvar!\n"); return; }
    for(int i=0;i<qtd;i++)
        fprintf(f,"%d;%s;%s;%s;%s\n",playlist[i].id,playlist[i].titulo,
                playlist[i].artista,playlist[i].duracao,playlist[i].genero);
    fclose(f);
}

void cadastrar(){
    if(qtd>=MAX){ puts("Playlist cheia!"); return; }
    Musica m;
    printf("ID: "); scanf("%d",&m.id);
    if(buscar_indice(m.id)!=-1){ puts("ID ja existe!"); return; }
    printf("Titulo: "); scanf(" %49[^\n]",m.titulo);
    printf("Artista: "); scanf(" %49[^\n]",m.artista);
    printf("Duracao: "); scanf(" %9[^\n]",m.duracao);
    printf("Genero: "); scanf(" %29[^\n]",m.genero);
    playlist[qtd++]=m;
    salvar_csv();
    puts("Musica cadastrada!");
}

void buscar(){
    int id;
    printf("ID: "); scanf("%d",&id);
    int i=buscar_indice(id);
    if(i==-1){ puts("Nao encontrada!"); return; }
    printf("\nID:%d\nTitulo:%s\nArtista:%s\nDuracao:%s\nGenero:%s\n",
           playlist[i].id,playlist[i].titulo,playlist[i].artista,
           playlist[i].duracao,playlist[i].genero);
}

void editar(){
    int id;
    printf("ID da musica: "); scanf("%d",&id);
    int i=buscar_indice(id);
    if(i==-1){ puts("Nao encontrada!"); return; }
    printf("Novo titulo: "); scanf(" %49[^\n]",playlist[i].titulo);
    printf("Novo artista: "); scanf(" %49[^\n]",playlist[i].artista);
    printf("Nova duracao: "); scanf(" %9[^\n]",playlist[i].duracao);
    printf("Novo genero: "); scanf(" %29[^\n]",playlist[i].genero);
    salvar_csv();
    puts("Musica editada!");
}

void excluir(){
    int id;
    printf("ID: "); scanf("%d",&id);
    int i=buscar_indice(id);
    if(i==-1){ puts("Nao encontrada!"); return; }
    for(;i<qtd-1;i++) playlist[i]=playlist[i+1];
    qtd--;
    salvar_csv();
    puts("Musica excluida!");
}

void listar(){
    if(qtd==0){ puts("Playlist vazia!"); return; }
    for(int i=0;i<qtd;i++)
        printf("[%d] %s - %s (%s) | %s\n",playlist[i].id,playlist[i].titulo,
               playlist[i].artista,playlist[i].duracao,playlist[i].genero);
}

int main(){
    carregar_csv();
    int op;
    do{
        printf("\n--- PLAYLIST ---\n1-Cadastrar\n2-Buscar\n3-Editar\n4-Excluir\n5-Listar\n0-Sair\nOpcao: ");
        scanf("%d",&op);
        switch(op){
            case 1:cadastrar();break;
            case 2:buscar();break;
            case 3:editar();break;
            case 4:excluir();break;
            case 5:listar();break;
            case 0:puts("Encerrando...");break;
            default:puts("Opcao invalida!");
        }
    }while(op!=0);
    return 0;
}
