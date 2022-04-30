#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Permet d'afficher un tableau linéairement
void print_tableau (int* p, int n) {
	int i = 0;

	while (i<n) {
		printf("%d ",p[i]);
		i++;
	}

	printf("\n");

} 

// Crée des bijections aléatoires de Sn dans Sn
void build_bijection(int* p, int n) {

	int* T = malloc(n*sizeof(int)); ;
	int i = 0;

	while (i<n) {
		T[i] = i;
		i ++;
	}

	i = 0;
	int j;
	while (i<n) {
		j = rand()%(n-i);
		p[i] = T[j];

		while (j<n-1-i) {
			T[j] = T[j+1];
			j++;
		}

		i++;
	}

	free(T);
}

// Construit nos blocs diagonaux aléatoirement
void build_diagonals(int* area) {

	int tableau[9];

	build_bijection(tableau,9);

	int i = 0;
	while (i<9) {
		area[(i/3)*9+i%3] = tableau[i]+1;
		i++;
	}

	build_bijection(tableau,9);

	i = 0;
	while (i<9) {
		area[(3+i/3)*9+i%3+3] = tableau[i]+1;
		i++;
	}

	build_bijection(tableau,9);

	i = 0;
	while (i<9) {
		area[(6+i/3)*9+i%3+6] = tableau[i]+1;
		i++;
	}
}

// Met à jours les possibilités en chaque case
void update_poss(int* area, int* possible) {

	int i = 0;
	int j;

	while (i<10*81) {
		possible[i] = 1;
		i++;
	}

	i = 0;

	while (i<81) {

			// On se balade sur la ligne
			j = (i/9)*9;
			while (j/9 == i/9) {
				if (area[j] != 0) {
					possible[i*10+area[j]] = 0;
				}
				j++;
			}

			// Sur la colonne 
			j = i%9;
			while(j<81) {
				if (area[j] != 0) {
					possible[i*10+area[j]] = 0;
				}
				j += 9;
			}	
			
			// Sur le carré 
			j = (i/27)*27+((i%9)/3)*3;
			int k = 0;
			int l = 0;
			while (k<3) {
				while(l<3) {
					if (area[j+k*9+l] != 0) {
						possible[i*10+area[j+l+9*k]] = 0;
					}
					l++;
				}
				l = 0;
				k++;	
			}	
		i++;
	}
}

// Affiche le sudoku
void print_grid(int* area) {

	int i = 0;
	printf("\n");
	while (i<9) {
		print_tableau(area+9*i,9);
		i++;
	}
}

// à un indice associe le prochain qui puisse être modifié
int suivant(int i, int* diago) {
	if (i == 80) {
		return (-1);
	}

	else if (diago[i+1] == 1) {
		suivant(i+1, diago);
	}

	else {
		return i+1;
	}
}

// à un indice associe le precedetn pouvant être modifié
int precedent(int i, int* diago) {
	if (i == 0) {
		return (-1);
	}

	else if (diago[i-1] == 1) {
		precedent(i-1, diago);
	}

	else {
		return i-1;
	}
}

int premier_possible(int i,int* area, int* possible, int* tested) {
	int j = 1;
	while (j<10) {
		if (possible[i*10+j] == 1 && tested[i*10+j] == 0) {
			return j;
		}
		j++;
	}
	return 0;
}

void remplir(int i,int* diago, int* area, int* possible, int* tested) {

	update_poss(area,possible); // On met à jour 

	if (i != -1) {

			int j = premier_possible(i,area,possible,tested);

			if (j == 0) { // i.e. pas possible

				// On réinitialise
				area[i] = 0;
			
				int j = 1;
				while (j<10) {
					tested[i*10+j] = 0;
					j++;
				}
			
				remplir(precedent(i,diago),diago,area,possible,tested);
				
				}

			else { 

				area[i] = j;
				tested[i*10+j] = 1;
				remplir(suivant(i,diago),diago,area,possible,tested);

			}
	}
}

void real_sudoku(int n, int* area, int* sudoku) {
	int* bij = malloc(81*sizeof(int));
	build_bijection(bij,81);

	int i = 0;
	while(i<81) {
		sudoku[i] == 0; 
		i++;
	}

	i = 0;
	while (i<n) {
		sudoku[bij[i]] = area[bij[i]];
		i++;
	}

	free(bij);
}

int count_empty(int* sudoku) {
	int i = 0;
	int j = 0;
	while (i<81) {
		if (sudoku[i] == 0) {
			j++;
		}
		i++;
	}
	return j;
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
		possible[i] = 1;
		i++;
	}

	// Nous indiquera les possibilités testées
	int* tested = malloc(81*10*sizeof(int));

	i = 0;
	while (i<81*10) {
		tested[i] = 0;
		i++;
	}

	// Nous indiquera si on est sur un bloc diagonal
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

	remplir(3,diago,area,possible,tested);	


	int* sudoku = malloc(81*sizeof(int));

	printf("Veuillez indiquer le nombre de cases découvertes : ");
	scanf("%d",&i);

	real_sudoku(i%81,area,sudoku);
	print_grid(sudoku);

	int j = 0;
	int k = 0;

	while (count_empty(sudoku) != 0) {
		printf("Ligne : ");
		scanf("%d",&j);
		printf("Colonne : ");
		scanf("%d",&k);
		printf("Chiffre : ");
		scanf("%d",&i);
		sudoku[k-1+(j-1)*9] = i;
		print_grid(sudoku);

	}

	i = 0;
	int c = 0; 
	while (i<81) {
		if (sudoku[i] != area[i]) {
			c = 1;
		}
		i++;
	}

	if (c==0) {
		printf("\nFélicitations !\n");
	}

	else {
		printf("\nC'est faux.\n");
	}

	free(area);
	free(possible);
	free(tested);
	free(diago);
	free(sudoku);
}
