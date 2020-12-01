#include <stdio.h>
#include <stdlib.h>
#include "automatoQ4.h"
#define NULL ((void *)0)

Automato *quintupla(int ligacoes, int narestas, char *alfabeto, int inicio, int *fim){
    int i = 0;
    Automato *aut = (Automato *)malloc(sizeof(Automato));
    aut->ligacoes = ligacoes;
    aut->narestas = narestas;
    aut->alfabeto = alfabeto;
    aut->inicio = inicio;
    aut->fim = fim;

    aut->lista = (Vertice *)malloc(ligacoes*sizeof(Vertice));
    while (i < ligacoes){
        aut->lista[i] = NULL;
        i++;
    }   
    return aut;
}

Vertice *criaVertice(int vertice, char aresta){
    Vertice *temp = (Vertice *)malloc(sizeof(Vertice));
    temp->ligacao = vertice;
    temp->aresta = aresta;
    temp->proximo = NULL;
    return temp;
}

void criarAresta(Automato *aut, int inicio, int fim, char aresta){
    if ((aut == NULL) || ((fim < 0) || (fim >= aut->ligacoes)) || ((inicio < 0) || (inicio >= aut->ligacoes))){
        return;
    }
    Vertice *aresta_ = criaVertice(fim, aresta);    
	aresta_->proximo = aut->lista[inicio];
    aut->lista[inicio] = aresta_;
}

void qtdAresta(Automato *aut){
    int i = 0, contAresta= 0;
    while(i <aut->ligacoes){
        Vertice *aut2 = aut->lista[i];
        while (aut2){
            if (aut2 != NULL){
                contAresta++;
            }    
            aut2 = aut2->proximo;
            i++;
        }
    }
    printf("Numero Arestas: %d", contAresta);
}

void addEstados(Automato *aut){
    int i = 0, estadoAtual = 0, proxEstado = 0;
    char caractere;
    printf("\nDigite as informações a seguir");
	while (i < aut->narestas){  
	  	caractere = 0;  
        printf("\n%d -> Estado Atual: ", i+1);
        scanf("%d", &estadoAtual);
        setbuf(stdin, NULL);
        printf("%d -> Proximo Estado: ", i+1);
        scanf("%d", &proxEstado);
        setbuf(stdin, NULL);
        printf("\n%d -> Aresta ligando o Estado %d para o Estado %d: ", i+1, estadoAtual, proxEstado);
        scanf("%c", &caractere);
  		setbuf(stdin, NULL);
        criarAresta(aut, estadoAtual, proxEstado, caractere);
        i++;
    }
}

void  mostraAutomato(Automato *aut) {
    printf ("Número de Vertices: %d . Numero de Arestas: %d.\n" , aut->ligacoes , aut->narestas);
    int i = 0;
    while (i < aut->ligacoes) {
        printf ("v%d : ",i);
        Vertice *aut2 = aut->lista[i];
        while (aut2){
            printf("v%d(%c) " , aut2->aresta , aut2->ligacao);
            aut2 = aut2->proximo;
        }
        printf("\n");
        i++;
    }
}

void sentenca(Automato *aut, char sentenca[]){
    int inicio = aut->inicio;
    int tamFinal = sizeof(aut->fim)/sizeof(int);
    int *fim = (int *)malloc(tamFinal*sizeof(int));
	int i = 0, j = 0;
    Vertice *autV = aut->lista[inicio];
    while (i < strlen(sentenca)){
        if(autV == NULL){
            printf("Palavra Invalida!");
        }
        else if(autV->aresta != sentenca[i]){
            autV = autV->proximo;
        }
        else if(autV->aresta == sentenca[i]){
            printf("\naresta: %c \tletra da sentenca: %c aceita\n",autV->aresta, sentenca[i]);
            i = i + 1;
            if(autV->ligacao == 0){
                return;
            }
            autV = aut->lista[autV->ligacao];
        }
    }
}


