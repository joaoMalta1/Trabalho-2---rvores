/*
Alunos:
Vinícius Machado da Rocha Viana - 2111343
João Ricardo Malta de Oliveira - 2112714
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no No;
struct no {
  int chave;
  No *esq;
  No *dir;
};

int verificaAbb(No *p);
No *insereElemento(No *p, int chave);
void exibePreOrdem(No *p);
int verificaAVL(No *p);
int altura(No *p);
No *cria(int c, No *p1, No *p2);

int main() {
  No *arvore = NULL;
  srand(time(0));
  for (int i = 0; i < 20; i++) {
    int numero = rand() % 100 + 1;
    printf("sorteei o número: %d\n",numero);
    arvore = insereElemento(arvore, numero);
  }
  exibePreOrdem(arvore);
  printf("%s", (verificaAbb(arvore)) ? "arvore é ABB\n" : "arvore nao é ABB\n");
  printf("%s", (verificaAVL(arvore)) ? "arvore é AVL\n" : "arvore nao é AVL\n");

  return 0;
}

int verificaAbb(No *p) {
  if (p == NULL) {
    return 1;
  }
  if ((p->esq != NULL && p->chave < p->esq->chave) ||
      (p->dir != NULL && p->chave > p->dir->chave)) {
    return 0;
  }
  int caminhoEsq = verificaAbb(p->esq);
  int caminhoDir = verificaAbb(p->dir);
  return caminhoEsq && caminhoDir;
}



No *insereElemento(No *p, int chave) {

  if (p == NULL){//Se o nó recebido for vazio, ele cria o nó
    return cria(chave,NULL,NULL);
  }
  else if(p-> esq == NULL || p->dir == NULL){//Se algum dos filhos for nulo
    if(p->esq == NULL){//Verifica se o filho da esquerda é nulo
      p->esq = cria(chave,NULL,NULL);
    }
    else{
      p->dir = cria(chave,NULL,NULL);
    }
  }
  else{
    if(p->esq->esq == NULL || p->esq->dir == NULL){
      p->esq = insereElemento(p->esq, chave);
    }
    else {
      p->dir = insereElemento(p->dir, chave);
    }
    
  }
  
  return p;
}

void exibePreOrdem(No *p) {
  if (p != NULL) {
    printf("valor: %d\n", p->chave);
    exibePreOrdem(p->esq);
    exibePreOrdem(p->dir);
  }
}

int verificaAVL(No *p) {
  if (p == NULL) {
    return 1;
  }

  if(!verificaAbb(p)) return 0;

  int alturaEsq = altura(p->esq);
  int alturaDir = altura(p->dir);

  if (abs(alturaEsq - alturaDir) > 1) {
    return 0;
  }

  if (!verificaAVL(p->esq) || !verificaAVL(p->dir)) {
    return 0;
  }

  return 1;
}

int altura(No *p) {
  if (p == NULL) {
    return 0;
  }
  int alturaEsq = altura(p->esq);
  int alturaDir = altura(p->dir);
  return 1 + ((alturaEsq > alturaDir) ? alturaEsq : alturaDir);
}

No *cria(int c, No *p1, No *p2) {
  No *p = (No *)malloc(sizeof(No));
  p->chave = c;
  p->esq = p1;
  p->dir = p2;
  return p;
}
