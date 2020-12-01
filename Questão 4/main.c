#include <stdio.h>
#include <stdlib.h>
#include "automatoQ4.h"

int main(int argc, char const *argv[]){
  int ligacoes = 0, arestas = 0, i = 0, inicial, qf;
  char alfabeto[200];
  int nDigitos;
  
  printf("Numero de Estados: ");
  scanf("%d", &ligacoes);
  setbuf(stdin, NULL);
  
  printf("\nNumero de Arestas: ");
  scanf("%d", &arestas);
  setbuf(stdin, NULL);

  printf("\nDigite o Alfabeto: ");
  scanf("%s", alfabeto); 
  setbuf(stdin, NULL);

  printf("\nEstado Inicial: S");
  scanf("%d", &inicial); 
  setbuf(stdin, NULL);

  printf("Numero de Estados Finais: ");
  scanf("%d", &qf); 
  setbuf(stdin, NULL);

  int *fim = (int *)malloc(qf*sizeof(int));

  while(i < qf){
    printf("\n%d -> Estado Final: q",i+1);
    scanf("%d", &fim[i]);
    setbuf(stdin, NULL);
    i++;
  }
  
  printf("Digite o tamanho da senteca: ");
  scanf("%d", &nDigitos);
  char *senteca = (char *)malloc(nDigitos*sizeof(char));
  
  printf("\nDigite a Senteca: ");
  scanf("%s", senteca); 
  setbuf(stdin, NULL);

  Automato *aut = quintupla(ligacoes, arestas, alfabeto, inicial, fim);
  addEstados(aut);
  mostraAutomato(aut);
  sentenca(aut, senteca);
  
  return 0;
}
