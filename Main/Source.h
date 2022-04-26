#pragma once
using namespace std;

void fill_from_file(char* field, int size);
void draw_field(char* field, int size);

template<int C>
void player_turn(char field[][C], int size)
{
	int col, row;
	char temp;
	setlocale(LC_ALL, "russian");
	do {
		std::cout << "Координаты выстрела (пример:\"b 5\"):";
		cin >> temp >> row;
		col = int(temp) - 96;
		cout << col << ' ' << row;
	} while (col > 10 || col < 1 || row > 10 || row < 1);
	if (field[row - 1][col - 1] == 'X'){
		player_turn(field, size);
	}
	else if (field[row - 1][col - 1] == '#'){
		cout << "Ранен";
	}
	else {
		cout << "Мимо";
	}
}
	