#include "pilhaDinamica.h"

#include <stdio.h>
struct elemento {
  struct peca pc;
  struct elemento *prox;
  int tmh;
  int ocupado;
};
typedef struct {
    int x;
    int y;
} Par;

typedef struct elemento Elemento;
//7 8 9
//4   6
//1 2 3

int colocaremcima(Pilha a,Pilha b){
  printf("\nsdluhdaui\n");
  if ((*a).tmh>=(*b).tmh){
    printf("\nsdluhdaui\n");
    Pilha aux=a;
    for(int i=0;i<(*a).tmh;i++){
      inserir(&b,(*aux).pc);
      if ((*aux).prox!=NULL)
        aux=(*aux).prox;
    }
    printaMonte(&b);
    (*a).ocupado=0;
    return 1;
  }
  return 0;
}
Par comer(Elemento**matriz,Par s,char p){
  Par dst=s;
  int sentido;
  int primeiraexec=1;
  do{
    if(!primeiraexec){
      printf("\nLocalização inválida tente novamente: ");
    }else{
      printf("\nDigite a pilha que vai comer(com base no numpad): ");
    }
    scanf("%d",&sentido);
    switch (sentido){
      case 1:
        dst.x++;dst.y--;break;
      case 2:
        dst.x++;break;
      case 3:
        dst.x++;dst.y++;break;


      case 4:
        dst.y--;break;
      case 6:
        dst.y++;break;


      case 7:
        dst.x--;dst.y--;break;
      case 8:
        dst.x--;break;
      case 9:
        dst.x--;dst.y++;break;

      default:
        break;
    }
    primeiraexec=0;
  }
  while (matriz[dst.x][dst.y].ocupado==0 || (dst.x==s.x && dst.y==s.y));
  colocaremcima(&(matriz[s.x][s.y]),&(matriz[dst.x][dst.y]));
  return dst;
};
Par selecionar(Elemento**matriz,char p){
  Par s;
  int primeiraexec=1;
  do{
    if(!primeiraexec){
      printf("\nLocalização inválida tente novamente: ");
    }else{
      printf("\nDigite a linha e a coluna da pilha que deseja selecionar: ");
    }
    scanf("%d %d",&s.x,&s.y);
    primeiraexec=0;
  }
  while (matriz[s.x][s.y].pc.letra!=p || matriz[s.x][s.y].ocupado==0);
  return s;

}
int jogo(){
  int n,p;
  printf("Tamanho do tabuleiro nxn(5 à 10): ");
  scanf("%d",&n);

  printf("\nQuantas pessoas: ");
  scanf("%d",&p);

  Elemento** matriz=criamtrz(n,p);
  printaMatriz(matriz,n);
  Par s=selecionar(matriz,'A');
  Par dst=comer(matriz,s,'A');
//  printf("\n%d, %d",s.x,s.y);
//  printf("\n%d, %d\n",dst.x,dst.y);

  printaMatriz(matriz,n);
}

Pilha * criar() {
  Pilha *pd;
  pd = (Pilha *)malloc(sizeof(Pilha));
  if (pd != NULL) {
    *pd=NULL;
//    (*pd)->pc = NULL;
//    (*pd)->tmh=0;
//    (*pd)->prox=NULL;
  }

  return pd;
}

int inserir(Pilha *pd, struct peca novapecas) {
  if (pd == NULL) {
    return 0;
  } else {
    Elemento *novo = (Elemento *)malloc(sizeof(Elemento));
    if (novo == NULL)
      return 0;
    novo->pc = novapecas;
    novo->prox = *pd;
    *pd = novo;
    return 1;
  }
}
int vazia(Pilha *pd) {
  if (pd == NULL || *pd == NULL)
    return 1;
  else
    return 0;
}

int remover(Pilha *pd) {
  if (vazia(pd))
    return 0;
  else {
    Elemento *aux = *pd;
    *pd = aux->prox;
    free(aux);
    return 1;
  }
}
void printaPeca(struct peca pc){

  uint8_t r = (pc.cor_hex>> 24) & 0xFF;
  uint8_t g = (pc.cor_hex>> 16) & 0xFF;
  uint8_t b = (pc.cor_hex>> 8)  & 0xFF;

  printf("\033[38;2;%d;%d;%dm [%c] \033[0m",r,g,b,pc.letra);

}
int printaMonteMnr(Pilha p){
  if(p==NULL){
    return 0;
  }

  uint8_t r = (p->pc.cor_hex>> 24) & 0xFF;
  uint8_t g = (p->pc.cor_hex>> 16) & 0xFF;
  uint8_t b = (p->pc.cor_hex>> 8)  & 0xFF;

  printf("\033[38;2;%d;%d;%dm [%c]\033[0m",r,g,b,p->pc.letra);;
  while(p->prox!=NULL){

    uint8_t r = (p->prox->pc.cor_hex>> 24) & 0xFF;
    uint8_t g = (p->prox->pc.cor_hex>> 16) & 0xFF;
    uint8_t b = (p->prox->pc.cor_hex>> 8)  & 0xFF;
    printf("\033[38;2;%d;%d;%dm|\033[0m",r,g,b);
    p=p->prox;
  }
  printf(" ");
  return 1;
}

int printaMonte(Pilha * p){
  if(p==NULL || *p==NULL ){
    return 0;
  }
  printaPeca((*p)->pc);
  printf("\n");
  printaMonte(&((*p)->prox));
  return 1;
//  else{
//    Pilha *aux=p;
//    while (aux!=NULL){
//      printaPeca((*aux)->pc);
//      aux=(*aux)->prox;
//    }
//    return 1;
//  }
}
int acessar(Pilha *pd, struct peca *a) {
  if (vazia(pd))
    return 0;
  else {
    *a = (*pd)->pc;
    return 1;
  }
}
void destruir(Pilha *pd) {
  if (pd != NULL) {
    Elemento *aux;
    while (*pd != NULL) {
      aux = *pd;
      *pd = (*pd)->prox;
      free(aux);
    }
    free(pd);
  }
}
void printaMatriz(Elemento**matriz,int n){
  for(int i=0;i<n;i++){
    for(int j=0;j<n;j++){
      if((matriz[i][j]).ocupado==0)
        printf(" [ ] ");
      else{
        printaMonteMnr(&matriz[i][j]);
//        printf("%d",(matriz[i][j]).tmh);
      }
    }
    printf("\t[%d] \n",i);
  }
  printf("\n");
  for(int i=0;i<n;i++){
    printf(" [%d] ",i);
  }
}
Elemento **criamtrz(int n, int p) {
  if(1>=p || p>=5)
    return 0;
  srand(time(NULL));

  Elemento **matriz;
  matriz = (Elemento **)malloc(sizeof(Elemento *) * n);
  if (matriz != NULL) {
    for (int i = 0; i < n; i++) {
      matriz[i] = (Elemento *)malloc(sizeof(Elemento) * n);
    }
    int pessoas[p];
    char letras[4]={'A','B','C','D'};
    int32_t cores[4]={COR_VERMELHO_RGBA,COR_VERDE_RGBA,COR_AMARELO_RGBA,COR_AZUL_RGBA};
    int qtd=floor((n*n-4)/p);
    for(int i=0;i<p;i++){
      pessoas[i]=qtd;
    }

    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        (matriz[i][j]).ocupado=1;
      }
    }
    if (((n*n)-4)%p){
      int meio= n/2;

      matriz[meio][meio].ocupado=0;
    }
    (matriz[0][0]).ocupado=0;
    (matriz[0][n-1]).ocupado=0;
    (matriz[n-1][0]).ocupado=0;
    (matriz[n-1][n-1]).ocupado=0;

    for(int i=0;i<n;i++){
      for(int j=0;j<n;j++){
        if(matriz[i][j].ocupado==1){
          int pr=rand()%p;
          for(int k=0;k<p;k++){

            if (pr==k){//pr=pessoa randola
              if(pessoas[k]>0){
                (matriz[i][j]).prox=NULL;
                (matriz[i][j]).tmh++;
                (matriz[i][j]).pc.cor_hex=cores[k];
                (matriz[i][j]).pc.letra=letras[k];
                pessoas[k]--;
              }
              else{
                pr=rand()%p;
                k=-1;
              }
            }
          }
        }
      }
    }
      return matriz;
    }

  return 0;
}
