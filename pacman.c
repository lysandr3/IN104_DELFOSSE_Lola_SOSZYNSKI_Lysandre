#define H 30
#define W 60
#define NB_GHOSTS 5
#define NB_LIVES 3
#define POS_X 1
#define POS_Y 1

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>


struct Coord {
	int x;
	int y;
};

struct PacMan {
	struct Coord coord;
	int dir_x;
	int dir_y;
	int nb_lives;
	int nb_food;
};

struct Ghost {
	struct Coord coord;
	int dir_x;
	int dir_y;
	int food; 
// J'ajoute cette composante dans la structure du fantôme pour me souvenir si sur la case où il se place il y avait de la food
};



struct Ghost allGhosts[NB_GHOSTS];
struct PacMan PacMan = {{POS_X,POS_Y},0,0,NB_LIVES,0};
char area[H][W] = {
	   { "############################################################" },
	   { "#                                                          #" },
	   { "#                                                          #" },
	   { "#        # # # # #          #             # # # # # #      #" },
	   { "#        #       #         # #            #                #" },
	   { "#        #       #        #   #           #                #" },
	   { "#        # # # # #       #     #          #                #" },
	   { "#        #              # # # # #         #                #" },
	   { "#        #             #         #        #                #" },
	   { "#        #            #           #       #                #" },
	   { "#        #           #             #      #                #" },
	   { "#        #          #               #     # # # # # #      #" },
	   { "#                                                          #" },
	   { "#                                                          #" },
	   { "#                                                          #" },
	   { "#        ##        ##           #          ##        #     #" },
	   { "#        # #      # #          # #         # #       #     #" },
	   { "#        #  #    #  #         #   #        #  #      #     #" },
	   { "#        #    # #   #        #     #       #   #     #     #" },
	   { "#        #     #    #       # # # # #      #    #    #     #" },
	   { "#        #          #      #         #     #     #   #     #" },
	   { "#        #          #     #           #    #      #  #     #" },
	   { "#        #          #    #             #   #       # #     #" },
	   { "#        #          #   #               #  #        ##     #" },
	   { "#                                                          #" },
	   { "#                                                          #" },
	   { "#                                                          #" },
	   { "#                                                          #" },
	   { "#                                                          #" },
	   { "############################################################" }
};
char deplacement;

void print_field() {
	int i = 0;
	int j = 0;
	while (i<H) {
		while(j<W)  {
			printf("%c", area[i][j]);
			j++;			
		}
		printf("\n");
		i++;
		j = 0;

	}
	printf("\n");
}

void initialize() {
	int i = 0;
	int j = 1;
	area[POS_X][POS_Y] = 'P';
	while (i<NB_GHOSTS) {

		int a = POS_X;
		int b = POS_Y;

		while (area[a][b] == '#' || ((a == POS_X) && (b == POS_Y))) {
			a = (rand()%(H-2))+1;
			b = (rand()%(W-2))+1;			
		}

		allGhosts[i].coord.x = a;
		allGhosts[i].coord.y = b;

		allGhosts[i].dir_x = 0;
		allGhosts[i].dir_y = 0;

		area[a][b] = 'G';

		allGhosts[i].food = 1;

		i++;
	}

	i = 1;
	while (i<H) {
		while (j<W) {
			if (area[i][j] == ' ') {
				area[i][j] = '.';
			}
			j++;
		}
		j = 1;
		i++;
	}
}

int alive() {

	if (PacMan.nb_lives == 0) {
		printf("Your score is  : %d\n", PacMan.nb_food);
		return 0;
	}

	else {
		printf("\n\nLives : %d\nFood : %d\n",PacMan.nb_lives,PacMan.nb_food);
		print_field(area);
		return 1;
	}

}


void move() {
	area[PacMan.coord.x][PacMan.coord.y] = ' ';

	if (area[PacMan.coord.x+PacMan.dir_x][PacMan.coord.y+PacMan.dir_y] == 'G' 
		|| area[PacMan.coord.x+PacMan.dir_x][PacMan.coord.y+PacMan.dir_y] == '#') {

		printf("\nPacman has been hurt !\n");
		PacMan.nb_lives--;
		PacMan.coord.x = POS_X;
		PacMan.coord.y = POS_Y;
		area[POS_X][POS_Y] = 'P'; 
	}

	else {

		PacMan.coord.x += PacMan.dir_x;
		PacMan.coord.y += PacMan.dir_y;

		if (area[PacMan.coord.x][PacMan.coord.y] == '.') {
			PacMan.nb_food++;

		}

		area[PacMan.coord.x][PacMan.coord.y] = 'P';
	}	
}


void keyboard_in() {

	while (alive() == 1) {
		scanf("%c",&deplacement);
		if (deplacement == 'z' || deplacement == 'q' || deplacement == 's' || deplacement == 'd') { 
			// Parce que sinon capte le 'Enter' 
			if (deplacement == 'z') {
				PacMan.dir_y = 0;
				PacMan.dir_x = -1;
			}
			
			if (deplacement =='q') {
				PacMan.dir_y = -1;
				PacMan.dir_x = 0;
			}

			if (deplacement == 's') {
				PacMan.dir_y = 0;
				PacMan.dir_x = 1;
			}

			if (deplacement == 'd') {
				PacMan.dir_y = 1;
				PacMan.dir_x = 0;
			}
			int i = 0;
			int c = 0;
			int k;
			// On souhaite  ici choisir uniformément un mouvement parmi ceux qui sont possibles
			// c compte le nombre de mouvement, et t contient les mouvements possibles
			while (i < NB_GHOSTS) {
				int t[10] = {0,0,0,0,0,0,0,0,0,0};
				c = 0;
				if (area[allGhosts[i].coord.x][allGhosts[i].coord.y-1] != '#') {
					t[2*c+1] = -1;
					c++;

				}

				if (area[allGhosts[i].coord.x][allGhosts[i].coord.y+1] != '#') {
					t[2*c+1] = 1;
					c++;

				} 

				if (area[allGhosts[i].coord.x-1][allGhosts[i].coord.y] != '#') {
					t[2*c] = -1;
					c++;

				}

				if (area[allGhosts[i].coord.x+1][allGhosts[i].coord.y] != '#') {
					t[2*c] = 1;
					c++;

				}

				k = rand()%c;

				if (allGhosts[i].food == 1) {
					printf("\n");
					area[allGhosts[i].coord.x][allGhosts[i].coord.y] = '.';
				}

				else {
					area[allGhosts[i].coord.x][allGhosts[i].coord.y] = ' ';
				}

				allGhosts[i].coord.x += t[2*k];
				allGhosts[i].coord.y += t[2*k+1];

				if (area[allGhosts[i].coord.x][allGhosts[i].coord.y] == '.') {
					allGhosts[i].food = 1;
				}

				else {
					allGhosts[i].food = 0;
				}

				area[allGhosts[i].coord.x][allGhosts[i].coord.y] = 'G';

				i++;
			}
			//scanf("%c",&deplacement);
			move();
		}
	}
}

int main() {

   srand(time(NULL));
   initialize();
   keyboard_in();
 
}
