#include <fstream>
#include <iostream>
#include <ctime>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include "funlist.h"

using namespace std;

HANDLE hOut;

int checked; 
int wanted; 
bool status;

struct pole {
	int zaw;
	bool odk;
	bool ozn;
};

pole basic[5][5];
pole easy[10][10];
pole medium[16][16];
pole hard[20][20];

char legend[] = { '1','2','3','4','5','6','7','8','9','0','1','2','3','4','5','6','7','8','9','0' };

////////////////////

void board_fill(int poz) {
	int max, sum = 0;
	if (poz < 11) {
		max = 5;
		for (int X = 0; X < max; X++) {
			for (int Y = 0; Y < max; Y++) {
				basic[X][Y].ozn = 0;
				basic[X][Y].odk = 0;
				if (basic[X][Y].zaw != 9) {
					sum = 0;

					if (X > 0 && Y > 0 && basic[X - 1][Y - 1].zaw==9)sum++;
					if (X > 0 && basic[X - 1][Y].zaw == 9)sum++;
					if (X > 0 && Y < max-1 && basic[X - 1][Y + 1].zaw == 9)sum++;
					if (Y > 0 && basic[X][Y - 1].zaw == 9)sum++;
					if (Y < max-1 && basic[X][Y + 1].zaw == 9)sum++;
					if (X < max-1 && Y > 0 && basic[X + 1][Y - 1].zaw == 9)sum++;
					if (X < max-1 && basic[X + 1][Y].zaw == 9)sum++;
					if (X < max-1 && Y < max-1 && basic[X + 1][Y + 1].zaw == 9)sum++;

					basic[X][Y].zaw = sum;
				}
			}
			
		}
	}
	else if (poz < 26) {
		max = 10;
		for (int X = 0; X < max; X++) {
			for (int Y = 0; Y < max; Y++) {
				easy[X][Y].ozn = 0;
				easy[X][Y].odk = 0;
				if (easy[X][Y].zaw != 9) {
					sum = 0;

					if (X > 0 && Y > 0 && easy[X - 1][Y - 1].zaw == 9)sum++;
					if (X > 0 && easy[X - 1][Y].zaw == 9)sum++;
					if (X > 0 && Y < max - 1 && easy[X - 1][Y + 1].zaw == 9)sum++;
					if (Y > 0 && easy[X][Y - 1].zaw == 9)sum++;
					if (Y < max - 1 && easy[X][Y + 1].zaw == 9)sum++;
					if (X < max - 1 && Y > 0 && easy[X + 1][Y - 1].zaw == 9)sum++;
					if (X < max - 1 && easy[X + 1][Y].zaw == 9)sum++;
					if (X < max - 1 && Y < max - 1 && easy[X + 1][Y + 1].zaw == 9)sum++;

					easy[X][Y].zaw = sum;
				}
			}
		}
	}
	else if (poz < 51) {
		max = 16;
		for (int X = 0; X < max; X++) {
			for (int Y = 0; Y < max; Y++) {
				medium[X][Y].ozn = 0;
				medium[X][Y].odk = 0;
				if (medium[X][Y].zaw != 9) {
					sum = 0;

					if (X > 0 && Y > 0 && medium[X - 1][Y - 1].zaw == 9)sum++;
					if (X > 0 && medium[X - 1][Y].zaw == 9)sum++;
					if (X > 0 && Y < max - 1 && medium[X - 1][Y + 1].zaw == 9)sum++;
					if (Y > 0 && medium[X][Y - 1].zaw == 9)sum++;
					if (Y < max - 1 && medium[X][Y + 1].zaw == 9)sum++;
					if (X < max - 1 && Y > 0 && medium[X + 1][Y - 1].zaw == 9)sum++;
					if (X < max - 1 && medium[X + 1][Y].zaw == 9)sum++;
					if (X < max - 1 && Y < max - 1 && medium[X + 1][Y + 1].zaw == 9)sum++;

					medium[X][Y].zaw = sum;
				}
			}
		}
	}
	else {
		max = 20;
		for (int X = 0; X < max; X++) {
			for (int Y = 0; Y < max; Y++) {
				hard[X][Y].ozn = 0;
				hard[X][Y].odk = 0;
				if (hard[X][Y].zaw != 9) {
					sum = 0;

					if (X > 0 && Y > 0 && hard[X - 1][Y - 1].zaw == 9)sum++;
					if (X > 0 && hard[X - 1][Y].zaw == 9)sum++;
					if (X > 0 && Y < max - 1 && hard[X - 1][Y + 1].zaw == 9)sum++;
					if (Y > 0 && hard[X][Y - 1].zaw == 9)sum++;
					if (Y < max - 1 && hard[X][Y + 1].zaw == 9)sum++;
					if (X < max - 1 && Y > 0 && hard[X + 1][Y - 1].zaw == 9)sum++;
					if (X < max - 1 && hard[X + 1][Y].zaw == 9)sum++;
					if (X < max - 1 && Y < max - 1 && hard[X + 1][Y + 1].zaw == 9)sum++;

					hard[X][Y].zaw = sum;
				}
			}
		}
	}
} 

void game_info() {
	cout << endl << "Liczba bomb: " << wanted << endl;
	cout << "Uzyj 'tag X Y' zeby oznaczyc pole." << endl;
	cout << "Uzyj 'untag X Y' zeby odznaczyc pole." << endl;
	cout << "Uzyj 'show X Y' zeby odkryc pole." << endl;
	cout << "Uzyj 'exit' zeby wyjsc." << endl;
}

void array_clean() {
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 5; j++) {
			basic[i][j].zaw = 0;
			easy[i][j].zaw = 0;
			medium[i][j].zaw = 0;
			hard[i][j].zaw = 0;
		}
	for (int i = 5; i < 10; i++)
		for (int j = 5; j < 10; j++) {
			easy[i][j].zaw = 0;
			medium[i][j].zaw = 0;
			hard[i][j].zaw = 0;
		}
	for (int i = 10; i < 16; i++)
		for (int j = 10; j < 16; j++) {
			medium[i][j].zaw = 0;
			hard[i][j].zaw = 0;
		}
	for (int i = 16; i < 20; i++)
		for (int j = 16; j < 20; j++) {
			hard[i][j].zaw = 0;
		}
}

void board_make(int poz) {
	int R, C;
	array_clean();
	if (poz < 11) {
		R = 5;
		C = 5;
		wanted = rand()%3 + 6;
		checked = 25;
	}
	else if (poz < 26) {
		R = 10;
		C = 10;
		wanted = rand()%11 +15;
		checked = 100;
	}
	else if (poz < 51) {
		R = 16;
		C = 16;
		wanted = rand()%11 +30;
		checked = 256;
	}
	else {
		R = 20;
		C = 20;
		wanted = rand()%21 + 60;
		checked = 400;
	}

	for (int i = 0; i < wanted; i++) {
		int bY = rand() % R;
		int bX = rand() % C;
		if ((poz < 11 && basic[bX][bY].zaw == 9) ||
			(poz < 26 && easy[bX][bY].zaw == 9) ||
			(poz < 51 && medium[bX][bY].zaw == 9) ||
			(hard[bX][bY].zaw == 9)) i--;
		else if (poz < 11)basic[bX][bY].zaw = 9;
		else if (poz < 26)easy[bX][bY].zaw = 9;
		else if (poz < 51)medium[bX][bY].zaw = 9;
		else hard[bX][bY].zaw = 9;
	}
	board_fill(poz);
}

char board_field(int poz, int i, int j) {
	if (poz < 11) {
		if (basic[i][j].ozn == 1) {
			checked++;
			return 'X';
		}
		else if (basic[i][j].odk == 0) {
			checked++;
			return '#';
		}
		else if (basic[i][j].zaw == 0) return ' ';
		else if (basic[i][j].zaw == 9) return 'o';
		else return basic[i][j].zaw + '0';
	}
	else if (poz < 26) {
		if (easy[i][j].ozn == 1) {
			checked++;
			return 'X';
		}
		else if (easy[i][j].odk == 0) {
			checked++;
			return '#';
		}
		else if (easy[i][j].zaw == 0) return ' ';
		else if (easy[i][j].zaw == 9) return 'o';
		else return easy[i][j].zaw + '0';
	}
	else if (poz < 51) {
		if (medium[i][j].ozn == 1) {
			checked++;
			return 'X';
		}
		else if (medium[i][j].odk == 0) {
			checked++;
			return '#';
		}
		else if (medium[i][j].zaw == 0) return ' ';
		else if (medium[i][j].zaw == 9) return 'o';
		else return medium[i][j].zaw + '0';
	}
	else {
		if (hard[i][j].ozn == 1) {
			checked++;
			return 'X';
		}
		else if (hard[i][j].odk == 0) {
			checked++;
			return '#';
		}
		else if (hard[i][j].zaw == 0) return ' ';
		else if (hard[i][j].zaw == 9) return 'o';
		else return hard[i][j].zaw + '0';
	}
}

void board_show(int poz) {
	cout << endl;
	string baner = " Poziom " + to_string(poz) + " ";
	int c_w = (45 - baner.length())/2;
	cout.width(c_w);
	cout.fill('=');
	cout << "=";
	cout << baner;
	cout.width(c_w);
	cout.fill('=');
	cout << '=';
	cout << endl;

	int R, C;

	if (poz < 11) {
		R = 5;
		C = 5;
	}
	else if (poz < 26) {
		R = 10;
		C = 10;
	}
	else if (poz < 51) {
		R = 16;
		C = 16;
	}
	else {
		R = 20;
		C = 20;
	}

	checked = 0;
	
	cout << endl;

	cout << "    ";
	for (int i = 0; i < C; i++) {
		if (i > 8 && i < 19) cout << 1;
		else if (i == 19) cout << 2;
		else cout<<" ";
	}
	cout <<" X"<< endl;
	cout << "    ";

	for (int i = 0; i < C; i++) cout << legend[i];
	
	cout << endl<<endl;
	for (int i = 0; i < R; i++) {
		if (i > 8 && i < 19) cout << " " << 1;
		else if (i == 19) cout << " " << 2;
		else cout << "  ";
		cout << legend[i]<<" ";
		
		for (int j = 0; j < C; j++) {
			cout << board_field(poz, i, j);
		}
		cout << endl;
	}
	//cout << checked << endl;
	cout <<"Y"<< endl;

}

void field_show(int poz, int X, int Y) {
	if ((poz < 11 && checked == 25) ||
		(poz < 26 && checked == 100) ||
		(poz < 51 && checked == 256) ||
		(checked == 400)) {
		while ((poz < 11 && basic[X][Y].zaw ==9) ||
			(poz < 26 && easy[X][Y].zaw == 9) ||
			(poz < 51 && medium[X][Y].zaw == 9) ||
			(hard[X][Y].zaw == 9)) {
			board_make(poz);
		}
	}

	if (((poz < 11 && basic[X][Y].odk == 0) ||
		(poz < 26 && easy[X][Y].odk == 0) ||
		(poz < 51 && medium[X][Y].odk == 0) ||
		(hard[X][Y].odk == 0))) {

		
		if (poz < 11) {
			int max = 5;
			basic[X][Y].odk = 1;
			if (basic[X][Y].zaw == 0) {
				if (X > 0 && Y > 0) basic[X - 1][Y - 1].odk=1;
				if (X > 0) basic[X - 1][Y].odk = 1;
				if (X > 0 && Y < max-1) basic[X - 1][Y + 1].odk = 1;
				if (Y > 0) basic[X][Y - 1].odk = 1;
				if (Y < max-1) basic[X][Y + 1].odk = 1;
				if (X < max-1 && Y > 0) basic[X + 1][Y - 1].odk = 1;
				if (X < max-1) basic[X + 1][Y].odk = 1;
				if (X < max - 1 && Y < max - 1) basic[X + 1][Y + 1].odk = 1;
			}
			else if(basic[X][Y].zaw<9){
				int suma = 0;
				if (X > 0 && Y > 0 && basic[X - 1][Y - 1].zaw==9 && basic[X - 1][Y-1].ozn == 1) suma++;
				if (X > 0 && basic[X - 1][Y].zaw == 9 && basic[X - 1][Y].ozn == 1) suma++;
				if (X > 0 && Y < max - 1 && basic[X - 1][Y + 1].zaw == 9 && basic[X - 1][Y+1].ozn == 1) suma++;
				if (Y > 0 && basic[X][Y - 1].zaw == 9 && basic[X][Y-1].ozn == 1) suma++;
				if (Y < max - 1 && basic[X][Y + 1].zaw == 9 && basic[X][Y+1].ozn == 1) suma++;
				if (X < max - 1 && Y > 0 && basic[X + 1][Y - 1].zaw == 9 && basic[X + 1][Y+1].ozn == 1) suma++;
				if (X < max - 1 && basic[X + 1][Y].zaw == 9 && basic[X + 1][Y].ozn == 1) suma++;
				if (X < max - 1 && Y < max - 1 && basic[X + 1][Y + 1].zaw == 9 && basic[X + 1][Y+1].ozn == 1) suma++;
				
				if (suma == basic[X][Y].zaw) {
					if (X > 0 && Y > 0 && basic[X - 1][Y - 1].zaw != 9) basic[X - 1][Y - 1].odk = 1;
					if (X > 0 && basic[X - 1][Y].zaw != 9) basic[X - 1][Y].odk = 1;
					if (X > 0 && Y < max - 1 && basic[X - 1][Y + 1].zaw != 9) basic[X - 1][Y + 1].odk = 1;
					if (Y > 0 && basic[X][Y - 1].zaw != 9) basic[X][Y - 1].odk = 1;
					if (Y < max - 1 && basic[X][Y + 1].zaw != 9) basic[X][Y + 1].odk = 1;
					if (X < max - 1 && Y > 0 && basic[X + 1][Y - 1].zaw != 9) basic[X + 1][Y - 1].odk = 1;
					if (X < max - 1 && basic[X + 1][Y].zaw != 9) basic[X + 1][Y].odk = 1;
					if (X < max - 1 && Y < max - 1 && basic[X + 1][Y + 1].zaw != 9) basic[X + 1][Y + 1].odk = 1;
				}
			}
		}
		else if (poz < 26) {
			int max = 10;
			easy[X][Y].odk = 1;
			if (easy[X][Y].zaw == 0) {
				if (X > 0 && Y > 0) easy[X - 1][Y - 1].odk = 1;
				if (X > 0) easy[X - 1][Y].odk = 1;
				if (X > 0 && Y < max - 1) easy[X - 1][Y + 1].odk = 1;
				if (Y > 0) easy[X][Y - 1].odk = 1;
				if (Y < max - 1) easy[X][Y + 1].odk = 1;
				if (X < max - 1 && Y > 0) easy[X + 1][Y - 1].odk = 1;
				if (X < max - 1) easy[X + 1][Y].odk = 1;
				if (X < max - 1 && Y < max - 1) easy[X + 1][Y + 1].odk = 1;
			}
			else if (easy[X][Y].zaw < 9) {
				int suma = 0;
				if (X > 0 && Y > 0 && easy[X - 1][Y - 1].zaw == 9 && easy[X - 1][Y - 1].ozn == 1) suma++;
				if (X > 0 && easy[X - 1][Y].zaw == 9 && easy[X - 1][Y].ozn == 1) suma++;
				if (X > 0 && Y < max - 1 && easy[X - 1][Y + 1].zaw == 9 && easy[X - 1][Y + 1].ozn == 1) suma++;
				if (Y > 0 && easy[X][Y - 1].zaw == 9 && easy[X][Y - 1].ozn == 1) suma++;
				if (Y < max - 1 && easy[X][Y + 1].zaw == 9 && easy[X][Y + 1].ozn == 1) suma++;
				if (X < max - 1 && Y > 0 && easy[X + 1][Y - 1].zaw == 9 && easy[X + 1][Y + 1].ozn == 1) suma++;
				if (X < max - 1 && easy[X + 1][Y].zaw == 9 && easy[X + 1][Y].ozn == 1) suma++;
				if (X < max - 1 && Y < max - 1 && easy[X + 1][Y + 1].zaw == 9 && easy[X + 1][Y + 1].ozn == 1) suma++;

				if (suma == easy[X][Y].zaw) {
					if (X > 0 && Y > 0 && easy[X - 1][Y - 1].zaw != 9) easy[X - 1][Y - 1].odk = 1;
					if (X > 0 && easy[X - 1][Y].zaw != 9) easy[X - 1][Y].odk = 1;
					if (X > 0 && Y < max - 1 && easy[X - 1][Y + 1].zaw != 9) easy[X - 1][Y + 1].odk = 1;
					if (Y > 0 && easy[X][Y - 1].zaw != 9) easy[X][Y - 1].odk = 1;
					if (Y < max - 1 && easy[X][Y + 1].zaw != 9) easy[X][Y + 1].odk = 1;
					if (X < max - 1 && Y > 0 && easy[X + 1][Y - 1].zaw != 9) easy[X + 1][Y - 1].odk = 1;
					if (X < max - 1 && easy[X + 1][Y].zaw != 9) easy[X + 1][Y].odk = 1;
					if (X < max - 1 && Y < max - 1 && easy[X + 1][Y + 1].zaw != 9) easy[X + 1][Y + 1].odk = 1;
				}
			}
		}
		else if (poz < 51) {
			int max = 16;
			medium[X][Y].odk = 1;
			if (medium[X][Y].zaw == 0) {
				if (X > 0 && Y > 0) medium[X - 1][Y - 1].odk = 1;
				if (X > 0) medium[X - 1][Y].odk = 1;
				if (X > 0 && Y < max - 1) medium[X - 1][Y + 1].odk = 1;
				if (Y > 0) medium[X][Y - 1].odk = 1;
				if (Y < max - 1) medium[X][Y + 1].odk = 1;
				if (X < max - 1 && Y > 0) medium[X + 1][Y - 1].odk = 1;
				if (X < max - 1) medium[X + 1][Y].odk = 1;
				if (X < max - 1 && Y < max - 1) medium[X + 1][Y + 1].odk = 1;
			}
			else if (medium[X][Y].zaw < 9) {
				int suma = 0;
				if (X > 0 && Y > 0 && medium[X - 1][Y - 1].zaw == 9 && medium[X - 1][Y - 1].ozn == 1) suma++;
				if (X > 0 && medium[X - 1][Y].zaw == 9 && medium[X - 1][Y].ozn == 1) suma++;
				if (X > 0 && Y < max - 1 && medium[X - 1][Y + 1].zaw == 9 && medium[X - 1][Y + 1].ozn == 1) suma++;
				if (Y > 0 && medium[X][Y - 1].zaw == 9 && medium[X][Y - 1].ozn == 1) suma++;
				if (Y < max - 1 && medium[X][Y + 1].zaw == 9 && medium[X][Y + 1].ozn == 1) suma++;
				if (X < max - 1 && Y > 0 && medium[X + 1][Y - 1].zaw == 9 && medium[X + 1][Y + 1].ozn == 1) suma++;
				if (X < max - 1 && medium[X + 1][Y].zaw == 9 && medium[X + 1][Y].ozn == 1) suma++;
				if (X < max - 1 && Y < max - 1 && medium[X + 1][Y + 1].zaw == 9 && medium[X + 1][Y + 1].ozn == 1) suma++;

				if (suma == medium[X][Y].zaw) {
					if (X > 0 && Y > 0 && medium[X - 1][Y - 1].zaw != 9) medium[X - 1][Y - 1].odk = 1;
					if (X > 0 && medium[X - 1][Y].zaw != 9) medium[X - 1][Y].odk = 1;
					if (X > 0 && Y < max - 1 && medium[X - 1][Y + 1].zaw != 9) medium[X - 1][Y + 1].odk = 1;
					if (Y > 0 && medium[X][Y - 1].zaw != 9) medium[X][Y - 1].odk = 1;
					if (Y < max - 1 && medium[X][Y + 1].zaw != 9) medium[X][Y + 1].odk = 1;
					if (X < max - 1 && Y > 0 && medium[X + 1][Y - 1].zaw != 9) medium[X + 1][Y - 1].odk = 1;
					if (X < max - 1 && medium[X + 1][Y].zaw != 9) medium[X + 1][Y].odk = 1;
					if (X < max - 1 && Y < max - 1 && medium[X + 1][Y + 1].zaw != 9) medium[X + 1][Y + 1].odk = 1;
				}
			}
		}
		else {
			int max = 20;
			hard[X][Y].odk = 1;
			if (hard[X][Y].zaw == 0) {
				if (X > 0 && Y > 0) hard[X - 1][Y - 1].odk = 1;
				if (X > 0) hard[X - 1][Y].odk = 1;
				if (X > 0 && Y < max - 1) hard[X - 1][Y + 1].odk = 1;
				if (Y > 0) hard[X][Y - 1].odk = 1;
				if (Y < max - 1) hard[X][Y + 1].odk = 1;
				if (X < max - 1 && Y > 0) hard[X + 1][Y - 1].odk = 1;
				if (X < max - 1) hard[X + 1][Y].odk = 1;
				if (X < max - 1 && Y < max - 1) hard[X + 1][Y + 1].odk = 1;
			}
			else if (hard[X][Y].zaw < 9) {
				int suma = 0;
				if (X > 0 && Y > 0 && hard[X - 1][Y - 1].zaw == 9 && hard[X - 1][Y - 1].ozn == 1) suma++;
				if (X > 0 && hard[X - 1][Y].zaw == 9 && hard[X - 1][Y].ozn == 1) suma++;
				if (X > 0 && Y < max - 1 && hard[X - 1][Y + 1].zaw == 9 && hard[X - 1][Y + 1].ozn == 1) suma++;
				if (Y > 0 && hard[X][Y - 1].zaw == 9 && hard[X][Y - 1].ozn == 1) suma++;
				if (Y < max - 1 && hard[X][Y + 1].zaw == 9 && hard[X][Y + 1].ozn == 1) suma++;
				if (X < max - 1 && Y > 0 && hard[X + 1][Y - 1].zaw == 9 && hard[X + 1][Y + 1].ozn == 1) suma++;
				if (X < max - 1 && hard[X + 1][Y].zaw == 9 && hard[X + 1][Y].ozn == 1) suma++;
				if (X < max - 1 && Y < max - 1 && hard[X + 1][Y + 1].zaw == 9 && hard[X + 1][Y + 1].ozn == 1) suma++;

				if (suma == hard[X][Y].zaw) {
					if (X > 0 && Y > 0 && hard[X - 1][Y - 1].zaw != 9) hard[X - 1][Y - 1].odk = 1;
					if (X > 0 && hard[X - 1][Y].zaw != 9) hard[X - 1][Y].odk = 1;
					if (X > 0 && Y < max - 1 && hard[X - 1][Y + 1].zaw != 9) hard[X - 1][Y + 1].odk = 1;
					if (Y > 0 && hard[X][Y - 1].zaw != 9) hard[X][Y - 1].odk = 1;
					if (Y < max - 1 && hard[X][Y + 1].zaw != 9) hard[X][Y + 1].odk = 1;
					if (X < max - 1 && Y > 0 && hard[X + 1][Y - 1].zaw != 9) hard[X + 1][Y - 1].odk = 1;
					if (X < max - 1 && hard[X + 1][Y].zaw != 9) hard[X + 1][Y].odk = 1;
					if (X < max - 1 && Y < max - 1 && hard[X + 1][Y + 1].zaw != 9) hard[X + 1][Y + 1].odk = 1;
				}
			}
		}
	}
}

bool field(int poz, string act) {
	if (act == "exit") exit(0);
	int size = act.size();
	size_t space = act.find(" ");
	if(space==0) space = act.find(" ",1);
	string action;
	if (space != string::npos) {
		action = act.substr(0, space);
	}
	else action = "error";
	while (action != "tag" && action != "untag" && action != "show") {
		cout << "Podaj komende (tag/untag/show) : ";
		cin >> action;
		cin.ignore();
	}

	size_t space2 = act.find(" ", space + 1);
	string dX, dY;
	int X=1000, Y=1000;
	if (space2 != string::npos) {
		dY = act.substr(space + 1, space2 - space + 1);
		dX = act.substr(space2 + 1);
		try {
			X = stoi(dX);
		}
		catch (invalid_argument & e) {
			X = 1000;
		}
		catch (out_of_range & e) {
			X = 1000;
		}
		catch (...) {
			X = stoi(dX);
		}
		try {
			Y = stoi(dY);
		}
		catch (invalid_argument & e) {
			Y = 1000;
		}
		catch (out_of_range & e) {
			Y = 1000;
		}
		catch (...) {
			Y = stoi(dY);
		}
	}
	else {
		X = 1000;
		Y = 1000;
	}
	X--;
	Y--;

	int max;
	if (poz < 11) {
		max = 5;
	}
	else if (poz < 26) {
		max = 10;
	}
	else if (poz < 51) {
		max = 16;
	}
	else {
		max = 20;
	}

	while (Y >= max || Y<0) {
		cout << "Podaj poprawne X: ";
		cin >> dY;
		try {
			Y = stoi(dY);
		}
		catch (invalid_argument & e) {
			Y = 1000;
		}
		catch (out_of_range & e) {
			Y = 1000;
		}
		catch (...) {
			Y = stoi(dY);
		}
		Y--;
		cin.ignore();
	}

	while (X >= max || X<0) {
		cout << "Podaj poprawne Y: ";
		cin >> dX;
		try {
			X = stoi(dX);
		}
		catch (invalid_argument & e) {
			X = 1000;
		}
		catch (out_of_range & e) {
			X = 1000;
		}
		catch (...) {
			X = stoi(dX);
		}
		X--;
		cin.ignore();
	}
	

	if (action == "show") {
		if ((poz < 11 && basic[X][Y].ozn != 1) ||
			(poz < 26 && easy[X][Y].ozn != 1) ||
			(poz < 51 && medium[X][Y].ozn != 1) ||
			(hard[X][Y].ozn != 1)){
			field_show(poz, X, Y);

		if ((poz < 11 && basic[X][Y].zaw == 9) ||
			(poz < 26 && easy[X][Y].zaw == 9) ||
			(poz < 51 && medium[X][Y].zaw == 9) ||
			(hard[X][Y].zaw == 9)) return 1;
		}
	}

	else if (action == "tag") {
		if (poz < 11 && basic[X][Y].odk != 1) {
			basic[X][Y].ozn = 1;
		}
		else if (poz < 26 && easy[X][Y].odk != 1) {
			easy[X][Y].ozn = 1;
		}
		else if (poz < 51 && medium[X][Y].odk != 1) {
			medium[X][Y].ozn = 1;
		}
		else if(hard[X][Y].odk != 1){
			hard[X][Y].ozn = 1;
		}
	}

	else if (action == "untag") {
		if (poz < 11) {
			basic[X][Y].ozn = 0;
		}
		else if (poz < 26) {
			easy[X][Y].ozn = 0;
		}
		else if (poz < 51) {
			medium[X][Y].ozn = 0;
		}
		else {
			hard[X][Y].ozn = 0;
		}
	}

	return 0;
}

void game_over(int poz) {
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, BACKGROUND_RED | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	system("cls");
	board_show(poz);
	cout << "GAME OVER :("<<endl;
	cout << "Nacisnij enter zeby wrocic do menu.";
	cin.ignore();
	menu();
}

void game_start(int poz) {
	ofstream save("dnbac.data");
	save << poz;
	save.close();
	board_make(poz);
	game(poz);
}

void game(int poz) {
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	string act;
	cin.ignore();
	while (checked != wanted) {
		system("cls");
		board_show(poz);
		if (checked==wanted) {
			hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hOut,BACKGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
			system("cls");
			board_show(poz);
			cout << "Gratulacje :)" << endl << "Nacisnij enter zeby kontynuowac.";
			break;
		}
		game_info();
		cout << "Podaj polecenie: ";
		getline(cin,act);
		status = field(poz, act);
		if (status) {
			game_over(poz);
			break;
		}
	}
	poz++;
	game_start(poz);
}

void menu_akcja(int akcja) {
	if (akcja == 3) exit(0);
	else if (akcja == 2) {
		ifstream save("dnbac.data"); //do not be a cheater
		if (save) {
			int lvl;
			save >> lvl;
			game_start(lvl);
			save.close();
		}
		else game_start(1);
	}
	else game_start(1);
}

void menu() {
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
	system("cls");

	cout << endl<<"CMD Saper" <<endl<< endl;
	cout << "Menu: " << endl;
	cout << "1. Nowa gra " << endl;
	cout << "2. Wczytaj gre " << endl;
	cout << "3. Wyjscie" << endl;
	cout << "Wybierz akcje: ";
	string akcja;
	cin >> akcja;
	while (akcja != "1" && akcja != "2" && akcja != "3") {
		cout << "Podaj poprawna wartosc! : ";
		cin >> akcja;
	}
	menu_akcja(stoi(akcja));
}