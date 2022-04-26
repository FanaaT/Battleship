
#include <iostream>
#include "Source.h"

using namespace std;


int main()
{
	const int field_size = 10;
	char field[field_size][field_size] = { };

	draw_field(field[0], field_size);
	fill_from_file(field[0], field_size);
	draw_field(field[0], field_size);
	player_turn(field, field_size);
}

