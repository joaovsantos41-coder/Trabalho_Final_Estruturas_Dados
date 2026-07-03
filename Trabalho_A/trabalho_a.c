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

void carregar_csv() {
    FILE *f = fopen(ARQUIVO, "r");
    if (!f) return;
    while (fscanf(f, "%d;%[^;];%[^;];%[^;];%[^\n]\n", 
           &playlist[qtd].id, playlist[qtd].titulo, playlist[qtd].artista, 
           playlist[qtd].duracao, playlist[qtd].genero) != EOF) {
        qtd++;
    }
    fclose(f);
}

void salvar_csv() {
    FILE *f = fopen(ARQUIVO, "w");
    if (!f) { printf("Erro ao salvar!\n"); return; }
    for (int i = 0; i < qtd; i++) {
        fprintf(f, "%d;%s;%s;%s;%s\n", playlist[i].id, playlist[i].titulo, 
                playlist[i].artista, playlist[i].duracao, playlist[i].genero);
    }
    fclose(f);
}

int buscar_indice(int id) {
    for (int i = 0; i < qtd; i++) {
        if (playlist[i].id == id) return i;
    }
    return -1;
}

void cadastrar() {
    if (qtd >= MAX) { printf("Playlist cheia!\n"); return; }
    
    Musica m;
    printf("ID: "); scanf("%d", &m.id);
    if (buscar_indice(m.id) != -1) { printf("ID ja existe!\n"); return; }
    
    printf("Titulo: "); scanf(" %[^\n]", m.titulo);
    printf("Artista: "); scanf(" %[^\n]", m.artista);
    printf("Duracao (MM:SS): "); scanf(" %[^\n]", m.duracao);
    printf("Genero: "); scanf(" %[^\n]", m.genero);
    
    playlist[qtd++] = m;
    salvar_csv();
    printf("Cadastrada com sucesso!\n");
}

void listar() {
    if (qtd == 0) { printf("Playlist vazia!\n"); return; }
    for (int i = 0; i < qtd; i++) {
        printf("[%d] %s - %s (%s) | %s\n", playlist[i].id, playlist[i].titulo, 
               playlist[i].artista, playlist[i].duracao, playlist[i].genero);
    }
}

void excluir() {
    int id;
    printf("ID para excluir: "); scanf("%d", &id);
    int idx = buscar_indice(id);
    if (idx == -1) { printf("Musica nao encontrada!\n"); return; }
    
    for (int i = idx; i < qtd - 1; i++) {
        playlist[i] = playlist[i + 1];
    }
    qtd--;
    salvar_csv();
    printf("Excluida com sucesso!\n");
}

int main() {
    int op;
    carregar_csv();
    do {
        printf("\n--- Playlist ---\n1. Cadastrar\n2. Listar\n3. Excluir\n0. Sair\nEscolha: ");
        scanf("%d", &op);
        switch(op) {
            case 1: cadastrar(); break;
            case 2: listar(); break;
            case 3: excluir(); break;
            case 0: break;
            default: printf("Invalido!\n");
        }
    } while(op != 0);
    return 0;
}
