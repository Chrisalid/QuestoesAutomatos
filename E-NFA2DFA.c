/* Programa de Converção de Epsilon-NFA --> DFA e NFA -->DFA*/
#include <stdio.h>
#include <string.h>

#define STATES	99
#define SYMBOLS	20

int N_simbolos;	// numero de simbolos
int N_Estados_NFA;	// numero de estados finais do NFA
char *NFAtab[STATES][SYMBOLS];
char *NFA_finais;	// Estados finais do NFA

int N_Estados_DFA;	// Numero de Estados do DFA
int DFAtab[STATES][SYMBOLS];
char DFA_finais[STATES+1];	// Estados Finais do DFA

char Estados[STATES][STATES+1];	//Nome da Tabela de estados
char Eclose[STATES][STATES+1];	// epsilon closure for each state

//	Print dos Estados de Transição.
//	Nomes dos Estados: 'A', 'B', 'C', ...
void print_nfa(char *tab[][SYMBOLS], int nestados, int nsymbols, char *finais){
	int i, j;

	puts("\nESTADOS DE TRANSICAO DO NFA");

	// Simbolos de entrada: '0', '1', ... 
	printf("     | ");
	for (i = 0; i < nsymbols; i++) printf("  %-6c", '0'+i);
	printf("  e\n");	// epsilon

	printf("-----+--");
	for (i = 0; i < nsymbols+1; i++) printf("-------");
	printf("\n");

	for (i = 0; i < nestados; i++) {
		printf("  %c  | ", '0'+i);	// Estados
		for (j = 0; j < nsymbols+1; j++)
			printf("  %-6s", tab[i][j]);
		printf("\n");
	}
	printf("Estados Final = %s\n", finais);
}

void print_dfa(int tab[][SYMBOLS], int nestados, int nsymbols, char *finais){
	int i, j;

	puts("\nDFA: TABELA DOS ESTADOS DE TRANSICAO");

	// Simbolos de Entrada: '0', '1', ...
	printf("     | ");
	for (i = 0; i < nsymbols; i++) printf("  %c  ", '0'+i);

	printf("\n-----+--");
	for (i = 0; i < nsymbols; i++) printf("-----");
	printf("\n");

	for (i = 0; i < nestados; i++) {
		printf("  %c  | ", 'A'+i);	/* Estado */
		for (j = 0; j < nsymbols; j++)
			printf("  %c  ", tab[i][j]);
		printf("\n");
	}
	printf("Estados Finais = %s\n", finais);
}

void tabela_NFA(){
/*	Definindo os estados do Automato.
	Simbolos de Entrada : 0(a), 1(b), 2(epsilon)*/
	
	NFAtab[0][0] = "1";
	NFAtab[0][1] = "";
	NFAtab[0][2] = "";
	NFAtab[0][3] = "2";
	NFAtab[1][0] = "";
	NFAtab[1][1] = "3";
	NFAtab[1][2] = "";
	NFAtab[1][3] = "";
	NFAtab[2][0] = "";
	NFAtab[2][1] = "";
	NFAtab[2][2] = "2";
	NFAtab[2][3] = "3";
	NFAtab[3][0] = "";
	NFAtab[3][1] = "";
	NFAtab[3][2] = "";
	NFAtab[3][3] = "";

	N_simbolos = 3;
	N_Estados_NFA = 4;
	NFA_finais = "2";
	N_Estados_DFA = 0;
}
// A String 't' se junta com a String 's' e o retorno é o número de itens que é adicionado em 's'
int meclaString(char *s, char *t){
	int n=0;
	char temp[STATES+1], *r=temp, *p=s;

	while (*p && *t) {
		if (*p == *t) {
			*r++ = *p++; t++;
		} else if (*p < *t) {
			*r++ = *p++;
		} else {
			*r++ = *t++;
			n++;
		}
	}
	*r = '\0';

	if (*t) {
		strcat(r, t);
		n += strlen(t);
	} else if (*p) strcat(r, p);

	strcpy(s, temp);

	return n;
}

void prox_estado_NFA(char *proxestado, char *estados, char *nfa[STATES][SYMBOLS], int symbol){
	int i;
	char temp[STATES+1];

	temp[0] = '\0';
	for (i = 0; i < strlen(estados); i++) meclaString(temp, nfa[estados[i]-'0'][symbol]);
	strcpy(proxestado, temp);
}

int ind_estados(char *estado, char stnt[][STATES+1], int *pn){
	int i;
// Se não houver estado "" retorna -1
	if (!*estado) return -1;

	for (i = 0; i < *pn; i++) if (!strcmp(estado, stnt[i])) return i;

	strcpy(stnt[i], estado);
	return (*pn)++;
}
// Pega os estados que recebem epsilon
void estados_ep(int state, char *epstates, char *nfa[][SYMBOLS], int n_sym){
	int i, n=0;
	
	strcpy(epstates, nfa[state][n_sym]);

	do {
		for (i = 0; i < strlen(epstates); i++)
			n = meclaString(epstates, nfa[epstates[i]-'0'][n_sym]);
	} while (n);
}

void Ini_Eclose(char eclose[][STATES+1], char *nfa[][SYMBOLS], int n_nfa, int n_sym){
	int i;

	printf("\nEstados Acessiveis de Epsilon:\n");
	for (i = 0; i < n_nfa; i++) {
		estados_ep(i, eclose[i], nfa, n_sym);
		printf("    Estado %d : [%s]\n", i, eclose[i]);
	}
	printf("\n");
}

void e_close(char *epstates, char *states, char eclose[][STATES+1])
{
	int i;

	strcpy(epstates, states);
	for (i = 0; i < strlen(states); i++) meclaString(epstates, eclose[states[i]-'0']);
}

int convercao(char *nfa[][SYMBOLS], int n_nfa, int n_sym, int dfa[][SYMBOLS]){
	int i = 0;
	int n = 1;

	char nextstate[STATES+1];
	char temp[STATES+1];
	int j;

	Ini_Eclose(Eclose, nfa, n_nfa, n_sym);

	e_close(temp, "0", Eclose);
	strcpy(Estados[0], temp);

	printf("Convercao E-NFA Para DFA\n");
	for (i = 0; i < n; i++) {
		for (j = 0; j < n_sym; j++) {
			prox_estado_NFA(nextstate, Estados[i], nfa, j);
			e_close(temp, nextstate, Eclose);
			dfa[i][j] = ind_estados(temp, Estados, &n);
			//Ao invés de 4 colocar o número de estados do Automato
			printf("    Estado %d(%4s) : %d --> Estado %2d(%4s)\n", i, Estados[i], j, dfa[i][j], temp);
			dfa[i][j] += 'A';
		}
	}

	return n;
}
// Automato DFA Final
void final_DFA(char *dfinals,	char *nfinals, char stnt[][STATES+1],	int n_dfa)
{
	int i, j, k=0, n=strlen(nfinals);

	for (i = 0; i < n_dfa; i++) {
		for (j = 0; j < n; j++) {
			if (strchr(stnt[i], nfinals[j])) {
				dfinals[k++] = i+'A';
				break;
			}
		}
	}
	dfinals[k] = '\0';
}

void main()
{
	tabela_NFA();
	print_nfa(NFAtab, N_Estados_NFA, N_simbolos, NFA_finais);

	N_Estados_DFA = convercao(NFAtab, N_Estados_NFA, N_simbolos, DFAtab);
	final_DFA(DFA_finais, NFA_finais, Estados, N_Estados_DFA);

	print_dfa(DFAtab, N_Estados_DFA, N_simbolos, DFA_finais);
}
