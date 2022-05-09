#include <iostream>
#include <iomanip>
#include <fstream>
using std::cout;
using std::cin;

enum Symbols {EMPTY = ' ', SHIP = '#', MISS = '*', HURT = '/', DESTROYED = 'X' };

const int size = 10;

char p1Field[size + 2][size + 2] = {};
char p2Field[size + 2][size + 2] = {};

bool isTurnP1 = false;

void fill_from_file(char field[][size + 2], const char* file) {
	char buffer[1000] = {};

	std::ifstream input(file);
	input.getline(buffer, sizeof(buffer));
	int k = 0;

	for (int i = 1; i < size + 1; i++) {
		for (int j = 1; j < size + 1; j++) {
			field[i][j] = buffer[k++];
		}
	}
}

void fill_fields() {
	fill_from_file(p1Field, "P1Ships.txt");
	fill_from_file(p2Field, "P2Ships.txt");
}

void draw_field(char field[][size + 2]) {
	cout << ' ' << ' ';
	for (int i = 0; i < size; i++){
		cout << ' ' << char(97 + i);
	}

	cout << '\n';

	for (int i = 1; i < size + 1; i++){
		cout << std::setw(2) << i << '|';
		for (int j = 1; j < size + 1; j++){
			if (field[i][j] == SHIP) {
				cout << ' ' << '|';
			}
			else {
				cout << field[i][j] << '|';
			}
		}
		cout << '\n';
	}
}

bool ships_is_destroyed(char field[][size + 2], int row, int col) {
	char* currentCell;
	bool shipsIsDestroyed = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			currentCell = &field[(row - 1) + i][(col - 1) + j];
			if (*currentCell == SHIP) {
				return false;
			}
			else if (*currentCell == HURT) {
				*currentCell = 'P';
				shipsIsDestroyed = ships_is_destroyed(field, ((row - 1) + i), ((col - 1) + j));
				if (shipsIsDestroyed == false) {
					*currentCell = HURT;
					return false;
				}
				*currentCell = HURT;
			}
		}
	}
	return shipsIsDestroyed;
}

void destroy(char field[][size + 2], int row, int col) {
	char* currentCell;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			currentCell = &field[(row - 1) + i][(col - 1) + j];
			if (*currentCell == HURT) {
				*currentCell = DESTROYED;
				destroy(field, ((row - 1) + i), ((col - 1) + j));
			}
			else if (*currentCell == EMPTY) {
				*currentCell = MISS;
			}
		}
	}
}

Symbols shot(char field[][size + 2], int row, int col) {
	if (field[row][col] == SHIP) {
		field[row][col] = 'P';
		if (ships_is_destroyed(field, row, col)) {
			field[row][col] = DESTROYED;
			destroy(field, row, col);
			cout << "destroyed\n";
			return HURT;
		}
		field[row][col] = HURT;
		cout << "injured\n";
		return HURT;
	}
	else if (field[row][col] == EMPTY) {
		cout << "past\n";
		field[row][col] = MISS;
		return MISS;
	}
}

void player_turn(char field[][size + 2]){
	int col, row;
	char temp;

	do {
		cout << '\t' << (isTurnP1 ? 2 : 1) << "p field\n";
		draw_field(field);
		cout << '\t' << (isTurnP1 ? 1 : 2) << "p turn\n";

		do {
			cin.clear();
			cout << "Shot coordinates: ";
			cin >> temp >> row;
			col = int(temp) - 96;
		} while (col > size || col < 1 || row > size || row < 1 ||
			field[row][col] != EMPTY && field[row][col] != SHIP);

	} while (shot(field, row, col) == HURT);
	
	cout << '\n' << '\n';
}

bool game_over(char field[][size + 2]) {
	for (int i = 1; i < size + 1; i++) {
		for (int j = 1; j < size + 1; j++) {
			if (field[i][j] == SHIP)
				return false;
		}
	}
	return true;
}

void run() {
	fill_fields();
	do {
		isTurnP1 = !isTurnP1;
		player_turn(isTurnP1 ? p2Field : p1Field);
	} while (!game_over(isTurnP1 ? p2Field : p1Field));
	cout << (isTurnP1 ? 1 : 2) << " PLAYER WINNER!!!!!!!!!!!!!!!!!!!!!";
}

