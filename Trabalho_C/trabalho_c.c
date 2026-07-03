
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 30
#define ARQUIVO "dados_c.csv"

typedef struct{
    int id;
    char nome_arquivo[100];
    int qtd_paginas;
    char tipo;
}Trabalho;

Trabalho fila_n[MAX];
int ini_n=0,fim_n=0;

Trabalho fila_p[MAX];
int ini_p=0,fim_p=0,qtd_p=0;

int id_existe(int id){
    for(int i=ini_n;i<fim_n;i++) if(fila_n[i].id==id) return 1;
    int a=ini_p;
    for(int i=0;i<qtd_p;i++){ if(fila_p[a].id==id) return 1; a=(a+1)%MAX; }
    return 0;
}

void carregar_csv(){
    FILE *f=fopen(ARQUIVO,"r");
    if(!f) return;
    Trabalho t;
    while(fscanf(f,"%d;%99[^;];%d;%c\n",&t.id,t.nome_arquivo,&t.qtd_paginas,&t.tipo)!=EOF){
        if(t.tipo=='N'){ fila_n[fim_n++]=t; }
        else{ fila_p[fim_p]=t; fim_p=(fim_p+1)%MAX; qtd_p++; }
    }
    fclose(f);
}

void salvar_csv(){
    FILE *f=fopen(ARQUIVO,"w");
    if(!f) return;
    for(int i=ini_n;i<fim_n;i++)
        fprintf(f,"%d;%s;%d;%c\n",fila_n[i].id,fila_n[i].nome_arquivo,fila_n[i].qtd_paginas,fila_n[i].tipo);
    int a=ini_p;
    for(int i=0;i<qtd_p;i++){
        fprintf(f,"%d;%s;%d;%c\n",fila_p[a].id,fila_p[a].nome_arquivo,fila_p[a].qtd_paginas,fila_p[a].tipo);
        a=(a+1)%MAX;
    }
    fclose(f);
}

void inserir(){
    Trabalho t;
    printf("ID: "); scanf("%d",&t.id);
    if(id_existe(t.id)){ printf("ID ja existe!\n"); return; }
    printf("Arquivo: "); scanf(" %[^\n]",t.nome_arquivo);
    printf("Paginas: "); scanf("%d",&t.qtd_paginas);
    printf("Tipo (N/P): "); scanf(" %c",&t.tipo);

    if(t.tipo=='N'||t.tipo=='n'){
        t.tipo='N'; if(fim_n>=MAX){puts("Fila normal cheia!");return;}
        fila_n[fim_n++]=t;
    }else if(t.tipo=='P'||t.tipo=='p'){
        t.tipo='P'; if(qtd_p>=MAX){puts("Fila prioritaria cheia!");return;}
        fila_p[fim_p]=t; fim_p=(fim_p+1)%MAX; qtd_p++;
    }else{ puts("Tipo invalido!"); return; }
    salvar_csv();
}

void processar(){
    if(qtd_p){
        Trabalho t=fila_p[ini_p]; ini_p=(ini_p+1)%MAX; qtd_p--;
        printf("Imprimindo [P]: %s (%d paginas)\n",t.nome_arquivo,t.qtd_paginas);
    }else if(ini_n<fim_n){
        Trabalho t=fila_n[ini_n++];
        printf("Imprimindo [N]: %s (%d paginas)\n",t.nome_arquivo,t.qtd_paginas);
    }else puts("Fila vazia!");
    salvar_csv();
}

void listar(){
    int a=ini_p;
    puts("\nPrioritarios:");
    for(int i=0;i<qtd_p;i++){ printf("%d - %s\n",fila_p[a].id,fila_p[a].nome_arquivo); a=(a+1)%MAX; }
    if(!qtd_p) puts("Vazio");
    puts("\nNormais:");
    for(int i=ini_n;i<fim_n;i++) printf("%d - %s\n",fila_n[i].id,fila_n[i].nome_arquivo);
    if(ini_n==fim_n) puts("Vazio");
}

void buscar(){
    int id,a;
    printf("ID: "); scanf("%d",&id);
    a=ini_p;
    for(int i=0;i<qtd_p;i++){
        if(fila_p[a].id==id){ printf("Encontrado: %s %d pags Prioritario\n",fila_p[a].nome_arquivo,fila_p[a].qtd_paginas); return; }
        a=(a+1)%MAX;
    }
    for(int i=ini_n;i<fim_n;i++)
        if(fila_n[i].id==id){ printf("Encontrado: %s %d pags Normal\n",fila_n[i].nome_arquivo,fila_n[i].qtd_paginas); return; }
    puts("Nao encontrado.");
}

void cancelar(){
    int id; printf("ID: "); scanf("%d",&id);
    for(int i=ini_n;i<fim_n;i++) if(fila_n[i].id==id){
        for(int j=i;j<fim_n-1;j++) fila_n[j]=fila_n[j+1];
        fim_n--; salvar_csv(); puts("Cancelado."); return;
    }
    Trabalho aux[MAX]; int c=0,a=ini_p,ok=0;
    for(int i=0;i<qtd_p;i++){ if(fila_p[a].id!=id) aux[c++]=fila_p[a]; else ok=1; a=(a+1)%MAX; }
    if(ok){
        ini_p=fim_p=qtd_p=0;
        for(int i=0;i<c;i++){ fila_p[fim_p]=aux[i]; fim_p=(fim_p+1)%MAX; qtd_p++; }
        salvar_csv(); puts("Cancelado."); return;
    }
    puts("ID nao encontrado.");
}

int main(){
    carregar_csv();
    int op;
    do{
        printf("\n1 Inserir\n2 Processar\n3 Listar\n4 Buscar\n5 Cancelar\n0 Sair\nOpcao: ");
        scanf("%d",&op);
        switch(op){
            case 1: inserir(); break;
            case 2: processar(); break;
            case 3: listar(); break;
            case 4: buscar(); break;
            case 5: cancelar(); break;
        }
    }while(op!=0);
    return 0;
}
