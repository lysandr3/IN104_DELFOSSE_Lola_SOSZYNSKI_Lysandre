#include <stdio.h>
#include <stdlib.h>


int** build_bijection(int** p) {
	// &p est de taille 9

	int* T[9];
	int i = 0;
	// Faut qu'on ait une liste des nombres déjà tiré
	while (i<9) {
		T[i] = i;
		i ++;
	}

	i = 0;
	int j;
	while (i<9) {
		j = rand()/(9-i);
		p[i] = j;

		print_tableau(T,9);
		print_tableau(p,9);

		while (j<8-i) {
			T[j] = T[j+1];
			j++;
		}
	}
}


void print_tableau (int** p, int n) {
	int i = 0;

	while (i<n) {
		printf("%d;",p[i]);
		i++;
	}

} 

int main () {
	int area [9][9];
	
	// 0, 4, 8
	// On va construire une permutation de [1;9]; on va construire une liste de 9 elts
	// On tire un elt au hasard entre 1 et 9-k (où k est l'itération) qui ira à la 9-k position

}