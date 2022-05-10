#define H 30
#define W 60
#define NB_GHOSTS 5
#define NB_LIVES 3
#define POS_X 1
#define POS_Y 1

#include <stdio.h>
#include <stdlib.h>


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
};

void keyboard_in (struct PacMan PacMan, struct Ghost allGhosts) {
	char move;
	while (PacMan.nb_lives > 0) {
		scanf("%c",&move);
		if (move = 'z') {
			PacMan.dir_y = 0;
			PacMan.dir_x = -1;
		}
		
		else if (move = 'q') {
			PacMan.dir_y = -1;
			PacMan.dir_x = 0;
		}

		else if (move = 's') {
			PacMan.dir_y = 0;
			PacMan.dir_x = 1;
		}

		else if (move = 'd') {
			PacMan.dir_y = 1;
			PacMan.dir_x = 0;
		}

	int i = 0;
	int c = 1;
	int k;
	int* t = {0,0,0,0,0,0,0,0,0,0};
	while (i < NB_GHOSTS) {
		c = 0;
		if (area[allGhosts[i].coord.x,allGhosts[i].coord.y-1] != '#') {
			t[2*c+1] = -1;
			c++;

		}

		if (area[allGhosts[i].coord.x,allGhosts[i].coord.y+1] != '#') {
			t[2*c+1] = -1;
			c++;

		} 

		if (area[allGhosts[i].coord.x-1,allGhosts[i].coord.y] != '#') {
			t[2*c] = -1;
			c++;

		}

		if (area[allGhosts[i].coord.x+1,allGhosts[i].coord.y] != '#') {
			t[2*c] = 1;
			c++

		}

		k = rand()/c;

		if (allGhosts[i].food == 1) {
			area[allGhosts[i].coord.x,allGhosts[i].coord.y] = '.';
		}

		else {
			area[allGhosts[i].coord.x,allGhosts[i].coord.y] = ' ';
		}

		allGhosts[i].coord.x = t[2*k];
		allGhosts[i].coord.y = t[2*k+1];

		if (area[t[2*k],t[2*k+1]] == '.') {
			allGhosts[i].food = 1;
		}

		else {
			allGhosts[i].food = 0;
		}

		area[allGhosts[i].coord.x,allGhosts[i].coord.y] = 'G';

		i++;




	}








	}
}


void initialize(struct Ghost* allGhosts, char** area) {
	int i = 0;
	while (i<NB_GHOSTS) {

		int a = 1;
		int b = 1;

		while (area[a][b] == '#' || a*b == 1) {
			int a = rand()/(W-2)+1;
			int b = rand()/(H-2)+1;			
		}

		allGhosts[i].coord.x = a;
		allGhosts[i].coord.y = b;

		allGhosts[i].dir_x = 0;
		allGhosts[i].dir_y = 0;

		area[a][b] = 'G';
	
	}

	i = 1;
	int j = 1;

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


int main () {

	struct Ghost allGhosts[NB_GHOSTS];
	struct Coord coord = {POS_X,POS_Y};
	struct PacMan PacMan = {coord,0,0,NB_LIVES,0};

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



	

}