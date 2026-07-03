#include <stdio.h>
#define MAX 50
#define ARQUIVO "dados_b.csv"

typedef struct{
    int protocolo;
    char local[100];
    char tipo[50];
    char horario[20];
}Chamada;

Chamada pilha[MAX];
int topo=-1;

int existe(int p){
    for(int i=0;i<=topo;i++) if(pilha[i].protocolo==p) return 1;
    return 0;
}
void carregar_csv(){
    FILE *f=fopen(ARQUIVO,"r");
    if(!f) return;
    topo=-1;
    while(topo<MAX-1 &&
    fscanf(f,"%d;%99[^;];%49[^;];%19[^\n]",
    &pilha[topo+1].protocolo,pilha[topo+1].local,
    pilha[topo+1].tipo,pilha[topo+1].horario)==4){
        topo++;
    }
    fclose(f);
}
void salvar_csv(){
    FILE *f=fopen(ARQUIVO,"w");
    if(!f) return;
    for(int i=0;i<=topo;i++)
      fprintf(f,"%d;%s;%s;%s\n",pilha[i].protocolo,pilha[i].local,pilha[i].tipo,pilha[i].horario);
    fclose(f);
}
void registrar(){
    if(topo==MAX-1){puts("Pilha cheia!");return;}
    Chamada c;
    printf("Protocolo: ");scanf("%d",&c.protocolo);
    if(existe(c.protocolo)){puts("Protocolo ja existe!");return;}
    printf("Local: ");scanf(" %99[^\n]",c.local);
    printf("Tipo: ");scanf(" %49[^\n]",c.tipo);
    printf("Horario: ");scanf(" %19[^\n]",c.horario);
    pilha[++topo]=c;
    salvar_csv();
    puts("Chamada registrada.");
}
void atender(){
    if(topo==-1){puts("Nenhuma chamada.");return;}
    Chamada c=pilha[topo--];
    printf("Atendida:\nProtocolo:%d\nLocal:%s\nTipo:%s\nHorario:%s\n",c.protocolo,c.local,c.tipo,c.horario);
    salvar_csv();
}
void consultar(){
    if(topo==-1){puts("Pilha vazia.");return;}
    Chamada c=pilha[topo];
    printf("Ultima chamada:\nProtocolo:%d\nLocal:%s\nTipo:%s\nHorario:%s\n",c.protocolo,c.local,c.tipo,c.horario);
}
int main(){
 carregar_csv();
 int op;
 do{
  printf("\n1-Registrar\n2-Atender\n3-Consultar ultima\n0-Sair\nOpcao: ");
  scanf("%d",&op);
  switch(op){
   case 1: registrar();break;
   case 2: atender();break;
   case 3: consultar();break;
   case 0: puts("Encerrando...");break;
   default: puts("Opcao invalida!");
  }
 }while(op!=0);
 return 0;
}
