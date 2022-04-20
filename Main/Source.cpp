#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

void draw_field(char* field, int size)
{
	cout << ' ' << ' ';
	for (int i = 0; i < size; i++)
	{
		cout << ' ' << char(97 + i);
	}

	cout << '\n';

	for (int i = 0; i < size; i++)
	{
		cout << setw(2) << i + 1 << '|';
		for (int j = 0; j < size; j++)
		{
			cout << *field++ << '|';
			
		}
		cout << '\n';
	}
}

void fill_from_file(char* field, const int size)
{
	ifstream input("Ships.txt");
	char buffer[1000] = {};

	input.getline(buffer, sizeof(buffer));

	for (int i = 0; i < (size * size); i++) {
	
		*field++ = buffer[i];
	}

	
	
}
