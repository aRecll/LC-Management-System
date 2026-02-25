#pragma once

#include "../hierarchy/shipment.h"
#include "../hierarchy/supplier.h"

#include <conio.h>

#include <iomanip>
#include <iostream>
#include <memory>
#include <vector>
#include <windows.h>

enum ConsoleColors {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    YELLOW = 6,
    WHITE = 7,
    GRAY = 8,
    BRIGHT_BLUE = 9,
    BRIGHT_GREEN = 10,
    BRIGHT_CYAN = 11,
    BRIGHT_RED = 12,
    BRIGHT_MAGENTA = 13,
    BRIGHT_YELLOW = 14,
    BRIGHT_WHITE = 15
};
using namespace std;
void set_color(int textColor, int bgColor = BLACK);

void reset_color();

void print_header(const string& title);

void clear_screen();

void print_menu(const vector<string>& options, int selected);
void printEmoji(const std::string& text);


void print_shipments_table(const vector<unique_ptr<shipment>>& shipments);

void show_All_data(const vector<unique_ptr<supplier>>& suppliers,
    const vector<unique_ptr<shipment>>& shipments);