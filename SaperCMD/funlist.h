#pragma once
#include <string>

void board_fill(int);
void game_info();
void array_clean();
void board_make(int);
char board_field(int, int, int);
void board_show(int);
void field_show(int, int, int);
bool field(int, std::string);
void game_over(int);
void game_start(int);
void game(int);
void menu_akcja(int);
void menu();