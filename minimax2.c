#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char **tabla;
	struct node **fii, *parent;
	int nivel;
	int val1;
	char val2;
}node;

node *init_node(node *parent, char **a) {
	node *nou = malloc(sizeof(node));
	if(parent == NULL) {
		nou->nivel = 0;
	}
	else {
		nou->nivel = parent->nivel + 1;
	}
	nou->parent = parent;
	nou->fii = NULL;
	nou->tabla = a;
	/*nod SAU */
	if(nou->nivel % 2 == 0) {
		nou->val1 = 1; 
	}
	/*nod SI */
	else {
		nou->val1 = 2;
	}
	/* nodul este "SI" sau "SAU" in functie de 
	paritatea nivelului*/
	return nou;
}

void alloc_fii( node **n, int cnt ) {
	(*n)->fii = (node**) malloc(cnt * sizeof(node*));
}

char **read_mat_from_file(FILE *f, char *c) {
	int i;
	char **a;
	*c = fgetc(f);
	a = (char **)malloc(3*sizeof(char*));
	for(i = 0 ; i < 3 ; i++) {
		a[i] = (char*) malloc(7 * sizeof(char));
	}
	fseek(f, 2, 0);
	for(i = 0 ; i < 3 ; i++) {
		fgets(a[i], 7, f);
	}
	return a;
}

int verif_castig(char **a, char c) {
	int i;
	/*verificare castig pentru oricare din cei doi jucatori*/
	if(c == 'N') {
		for(i = 0; i < 3; i++) {
			if(a[i][0] == a[i][2] && a[i][2] == a[i][4] && a[i][0] != '-') {
				return 1;
			}
			if(a[0][2*i] == a[1][2*i] && a[1][2*i] == a[2][2*i] &&
				a[0][2*i] != '-') {
				return 1;
			}
		}
		if(a[0][0] == a[1][2] && a[1][2] == a[2][4] && a[0][0]!='-') {
			return 1;
		}
		if( a[0][4] == a[1][2] && a[1][2] == a[2][0] && a[0][4]!='-' ) {
			return 1;
		}
		return 0;
	} else {
		for(i = 0; i < 3; i++) {
			if( a[i][0] == a[i][2] && a[i][2] == a[i][4] && a[i][0] != '-'
				&& a[i][0] == c) {
				return 1;
			}
			if( a[0][2*i] == a[1][2*i] && a[1][2*i] == a[2][2*i]
			 && a[0][2*i] != '-' && a[0][2*i] == c) {
				return 1;
			}
		}
		if( a[0][0] == a[1][2] && a[1][2] == a[2][4] && a[0][0] != '-'
			&& a[0][0] == c ) {
			return 1;
		}
		if( a[0][4] == a[1][2] && a[1][2] == a[2][0] && a[0][4]!='-'
			&& a[0][4] == c ) {
			return 1;
		}
		return 0;
	}
}

int goluri( char **a ) {
	int contor = 0, i, j;
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 5 ; j++) {
			if( a[i][j] == '-') {
				contor++;
			}
		}
	}
	return contor;
}

char **modif(char **a, int x, int y, const char c) {
	char **aux;
	int i;
	aux = (char **) malloc(3 * sizeof(char*));
	for(i = 0; i < 3; i++) {
		aux[i] = strdup(a[i]);
	}
	aux[x][2*y] = c;
	return aux;
}

void print_mat_to_file(char **a, FILE *f, int taburi) {
	int i, j;
	for(i = 0; i<3; i++) {
		for(j = 0; j < taburi ; j++) {
			fputc('\t', f);
		}
		fputs(a[i], f);
	}
}

void construire(node *root, int mutare ) {
	int cnt = goluri(root->tabla);
	alloc_fii(&root, cnt);
	int i, j, k = 0;
	for(i = 0; i < 3; i++) {
		for(j = 0; j < 5; j++) {
			/* se parcurge matricea pana la
			gasirea unei pozitii goale*/
			if(root->tabla[i][j] == '-') {
				if( mutare % 2 == 0 ) {
					root->fii[k] = init_node(root, modif(root->tabla, i, j/2, 'O'));
				}
				else {
					root->fii[k] = init_node(root, modif(root->tabla, i, j/2, 'X'));
				}
				k++;
			}
		}
	}
	if(root->fii) {
		for(i = 0; i < cnt; i++) {
			if(verif_castig(root->fii[i]->tabla, 'N') == 0) {
				construire(root->fii[i], mutare+1);
			}
			/*se repeta recursiv functia, schimband paritatea mutarii*/
		}
	}
}

void pre_order(node *root, FILE *f) {
	if(root == NULL) {
		return;
	}	
	print_mat_to_file(root->tabla, f, root->nivel);
	fputs("\n", f);
	int k = goluri(root->tabla);
	if(root->fii) {	
		for(int i = 0; i < k; i++) {
			pre_order(root->fii[i], f);
		}
	}
}

void free_tree( node *root ) {	
	if(root == NULL) {
		return;
	}	
	int k = goluri(root->tabla);
	free(root->tabla[0]);
	free(root->tabla[1]);
	free(root->tabla[2]);
	free(root->tabla);
	if(root->fii) {
		for(int i = 0; i < k; i++) {
			free_tree(root->fii[i]);
			free(root->fii[i]);
		}
		free( root->fii );
	}
}

int adancime = 0;

void depth( node *root ) {
	if( root == NULL ) {
		return;
	}
	if(root->nivel > adancime) {
		adancime = root->nivel;
	}
	if( root->fii ) {
		for(int i = 0; i < goluri(root->tabla); i++) {
			depth(root->fii[i]);
		}
	}
}

void atribuire_frunze(node *root, char c) {
	if(root == NULL) {
		return;
	}
	/* daca jucatorul cerut castiga */
	if(verif_castig(root->tabla, c) == 1) {
		root->val2 = 'T';
	} 
	/* daca jucatorul cerut pierde */
	else if(verif_castig(root->tabla,'N')) {
		root->val2= 'F';
	}
	/* cazul remizei */
	else if(goluri(root->tabla) == 0) {
		root->val2 = 'F';
	}
	if(root->fii) {
		for(int i = 0; i < goluri(root->tabla); i++) {
			atribuire_frunze(root->fii[i], c);
		}
	}
}


void atribuire(node *root, int nivel) {
	if( root == NULL ) {
		return;
	}
	if(root->nivel == nivel && verif_castig(root->tabla,'N') == 0) {
		/* cazul pentru noduri "SAU" */
		if(nivel % 2 == 0) {
			int k1 = 0;
			for(int i = 0; i < goluri(root->tabla); i++) {
				if(root->fii[i]->val2 == 'T') {
					k1 = 1;
					break;
				}	
			}
			if(k1 == 1) {
				root->val2 = 'T';
			} else {
				root->val2 = 'F';
			}
		}
		/* cazul pentru noduri SI */
		else {
			int k1 = 0;
			for(int i = 0; i < goluri(root->tabla); i++) {
				if(root->fii[i]->val2 != 'T') {
					k1 = 1;
					break;
				}
			}
			if(k1 == 0) {
				root->val2 = 'T';
			}
			else {
				root->val2 = 'F';
			}
		}
	}
	if( root->fii ) {
		for(int i = 0; i < goluri(root->tabla); i++) {
			atribuire(root->fii[i], nivel);
			/* repetare in mod recursiv */ 
		}
	}
}

void atribuire_tree(node *root, char c) {
	atribuire_frunze(root, c);
	int aux = adancime - 1;
	while(aux >= 0) {
		atribuire(root, aux);
		aux--;
		/* pentru fiecare nivel, in ordine descrescatoare*/
	}
}

void afisare(node *root, FILE *f) {
	if( root == NULL ) {
		return;
	}
	for(int i = 0; i < root->nivel; i++) {
		fputc('\t', f);
	}
	fputc(root->val2, f);
	fputc('\n', f);
	if(root->fii) {
		for(int j = 0; j < goluri(root->tabla); j++) {
			afisare(root->fii[j], f);
		}
	}
}

int main(int argc, char **argv) {
	FILE *f1 = fopen(argv[2], "rt");
	FILE *f2 = fopen(argv[3], "wt");
	char c;
	char **a = read_mat_from_file(f1, &c);
	node *n;
	n = init_node(NULL, a);

	/* prima mutare este '0' */
	if(c == 'O') {
		construire(n, 0);
	}
	/*prima mutare este 'X' */
	else {
		construire(n, 1);
	}

	if(argv[1][2] == '1') {
		pre_order(n, f2);
	}
	if(argv[1][2] == '2') {
		depth(n);
		atribuire_tree(n, c);
		afisare(n, f2);
	}

	free_tree(n);
	free(n);

	fclose(f1);
	fclose(f2);
}