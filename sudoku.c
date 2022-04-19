#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void print_tableau (int* p, int n) {
	int i = 0;

	while (i<n) {
		printf("%d ",p[i]);
		i++;
	}

	printf("\n");

} 

void build_bijection(int* p) {
	// &p est de taille 9

	int T[9];
	int i = 0;

	while (i<9) {
		T[i] = i;
		i ++;
	}

	i = 0;
	int j;
	while (i<9) {
		j = rand()%(9-i);
		p[i] = T[j];

		while (j<8-i) {
			T[j] = T[j+1];
			j++;
		}

		i++;
	}
}

void build_diagonals(int* area) {

	int tableau[9];

	build_bijection(tableau);

	int i = 0;
	while (i<9) {
		area[(i/3)*9+i%3] = tableau[i]+1;
		i++;
	}

	build_bijection(tableau);

	i = 0;
	while (i<9) {
		area[(3+i/3)*9+i%3+3] = tableau[i]+1;
		i++;
	}

	build_bijection(tableau);

	i = 0;
	while (i<9) {
		area[(6+i/3)*9+i%3+6] = tableau[i]+1;
		i++;
	}

	i = 0;
	while (i<9) {
		print_tableau(area+9*i,9);
		i++;
	}
}


void update_poss(int* area, int* possible) {

	int i = 0;
	int j;
	while (i<4) {
		if (area[i] == 0) {

			// On se balade sur la ligne
			j = (i/9)*9;
			while (j/9 == i/9) {
				if (area[j] != 0) {
					possible[i*10+area[j]] = 1;
				}
				j++;
			}

			// Sur la colonne 
			j = i%9;
			while(j<81) {
				if (area[j] != 0) {
					possible[i*10+area[j]] = 1;
				}
				j += 9;
			}	
			
			// Sur le carré 
			j = (i/27)*27+((i%9)%3)*3;
			int k = 0;
			int l = 0;
			while (k<3) {
				while(l<3) {
					if (area[j+k] != 0) {
						possible[i*10+area[j]] = 1;
					}
					l++;
				}
				l = 0;
				k++;	
			}
		}
		i++;
	}
}

void update_grid(int* area, int* possible) {
	int i = 0;
	int s = 0;
	while (i<81) {

		int j = 0;
		while (j<10) {
			s += possible[i*10+j];
			j++;
		}

		j = 1;
		if (s==8) {
			while (j<10) {
				if (possible[i*10+j] == 0) {
					area[i] = j;
				}
				j++;
			}
		}
		i++;
	}
}

void print_grid(int* area) {

	int i = 0;
	printf("\n");
	while (i<9) {
		print_tableau(area+9*i,9);
		i++;
	}
}

int main () {
	srand(time(NULL)); // Pour avoir des grilles différentes à chaque fois

	// Création de la grille
	int* area = malloc(81*sizeof(int));
	int i = 0;
	while (i<81) {
		area[i] = 0;
		i++;
	}

	// On remplit les diagonales
	build_diagonals(area);

	// Creation liste des possible
	int* possible = malloc(81*10*sizeof(int));
	i = 0;
	while (i<10*81) {
		possible[i] = 0;
		i++;
	}

	
	update_poss(area,possible);
	//print_tableau(possible+30,10);

	update_grid(area,possible);

	print_grid(area);

	int* tested = malloc(81*10*sizeof(int));	

	int* diago = malloc(81*sizeof(int));

	i = 0;
	while (i<81) {
		if (area[i] != 0) {
			diago[i] = 1;
		}

		else {
			diago[i] = 0;
		}

		i++;
	}

	i = 0;
	int j = 0;

	// fonction 

void remplir(int i) {

	if (diago[i] == 1) {
		remplir(i+1)
	}

	else if (i<81) {
		// Si possibilitée est vide 

	}
}

int poss_empty

	while (i<81) {
		if (area[i] == 0) {
			j = 0;
			while(j<10) {
				if 
				if ((tested[i*10+j] == 0) and (possible[i*10+j] == 1)) {
					area[i] = j;
					tested[i*10+j] = 1;
				}
			}
		}
		i++;
	}

	// Pour chaque case vide, on va la remplir aléatoirement parmi ses possibilités
	// On met à jour les possibilités puis la grille et on continue jusqu'a avoir un pb i.e s=9 qq part
	// A ce moment la, ça devient plus complexe 

	// Parcourir les cases vides, tableau qui indiques quelles possibilitées ont été testé, une copie de possibilities avec des 1 la où ça a été testé




}
