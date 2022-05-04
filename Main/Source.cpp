#include <iostream>
#include <iomanip>
#include <fstream>
using std::cout;
using std::cin;

const int size = 10;

char p1Field[size + 2][size + 2] = {};
char p2Field[size + 2][size + 2] = {};

char* currentField = &p2Field[0][0];

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

void draw_field(char field[][size + 2]){
	cout << ' ' << ' ';
	for (int i = 0; i < size; i++)
	{
		cout << ' ' << char(97 + i);
	}

	cout << '\n';

	for (int i = 1; i < size + 1; i++)
	{
		cout << std::setw(2) << i << '|';
		for (int j = 1; j < size + 1; j++)
		{
			cout << field[i][j] << '|';
			
		}
		cout << '\n';
	}
}

void shot(char field[][size + 2], int row, int col) {
	if (field[row][col] == '#') {
		cout << "injured\n";
		field[row][col] = 'X';
	}

	else {
		cout << "past\n";
		field[row][col] = '*';
	}
	draw_field(p2Field);
}

void player_turn(char field[][size + 2]){
	int col, row;
	char temp;

	cout << '\t' << 2 << "p field\n";
	draw_field(p2Field);
	cout << '\t' << 1 << "p turn\n";

	do {
		cin.clear();
		cout << "Shot coordinates: ";
		cin >> temp >> row;
		col = int(temp) - 96;
	} while (col > size || col < 1 || row > size || row < 1 ||
		field[row][col] == 'X' || field[row][col] == '*');
	
	shot(field, row, col);
	cout << '\n' << '\n';
}

bool game_over() {
	return false;
}

void run() {
	fill_fields();
	while (!game_over()) {
		player_turn(p2Field);
	}
}

