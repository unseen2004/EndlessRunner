#include "../headers/Table.h"

Table::Table() {}
Table::~Table() {}



void Table::update() {
    // Update table screen logic and check for user input to restart.
}

void Table::draw() {
    // Draw table screen with appropriate messages.
    DrawText("You died! Press Enter to continue", 200, 300, 20, DARKBLUE);
}