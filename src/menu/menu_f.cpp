#include "menu_f.h"
#include "emoji.h"

#ifdef _WIN32 
void set_color(int textColor, int bgColor) {
    
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}
#else 
set_color(string textColor, string  bgColor) {

    std::cout << textColor;
}
#endif


void reset_color() {
    #ifdef _WIN32
    set_color(WHITE, BLACK);
    #else 
    std::cout << "\033[0m"; 
    #endif
}
void print_header(const string& title) {
    set_color(BRIGHT_CYAN);
    cout << "+-------------------------------------------------------------+" << endl;
    cout << "|                      " << setw(39) << left << title << "|" << endl;
    cout << "+-------------------------------------------------------------+" << endl;
    reset_color();
}
void clear_screen() {
    #ifdef _WIN32 
    system("cls");
#else 
    system("clear");
#endif
    
}
void printEmoji(const std::string& text) {
    UINT originalCP = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);

    std::cout << text;

    SetConsoleOutputCP(originalCP);
}

void print_menu(const vector<string>& options, int selected) {
    clear_screen();
    print_header("СИСТЕМА УПРАВЛЕНИЯ ПОСТАВКАМИ");

    set_color(BRIGHT_YELLOW);
    cout << "Используйте стрелки  для навигации, Enter для выбора, ESC для выхода" << endl << endl;
    reset_color();

    for (int i = 0; i < options.size(); ++i) {
        if (i == selected) {
            
            set_color(BLACK, BRIGHT_YELLOW);
            printEmoji(emojicpp::emojize(":smile:"));
            cout << "-> " << options[i] << endl;
            reset_color();
        }
        else {
            set_color(WHITE);
            printEmoji(emojicpp::emojize(":dollar:"));
            cout << "  " << options[i] << endl;
        }
    }
    
}

void print_suppliers_table(const vector<unique_ptr<supplier>>& suppliers) {
    if (suppliers.empty()) {
        set_color(BRIGHT_YELLOW);
        cout << "Нет данных о поставщиках." << endl;
        reset_color();
        return;
    }
    print_header("ТАБЛИЦА ПОСТАВЩИКОВ");

    set_color(BRIGHT_CYAN);
    cout << "+--------------------+--------------+------------+------------+" << endl;
    cout << "│ Название фирмы     │ Контракт     │ Оплачено   │ Сальдо     │" << endl;
    cout << "+--------------------+--------------+------------+------------+" << endl;
    reset_color();

    for (const auto& supp : suppliers) {
        set_color(WHITE);
        cout << "| " << setw(18) << left << supp->get_company_name().substr(0, 18)
            << " | " << setw(12 ) << right << fixed << setprecision(2) << supp->get_contract_amount()
            << " | " << setw(10 ) << right << supp->get_paid_amount()
            << " | " << setw(10 ) << right << supp->get_balance() << " |" << endl;
    }

    set_color(BRIGHT_CYAN);
    cout << "+--------------------+--------------+------------+------------+" << endl;
    reset_color();
}
void print_shipments_table(const vector<unique_ptr<shipment>>& shipments) {
    if (shipments.empty()) {
        set_color(BRIGHT_YELLOW);
        cout << "Нет данных о поставках." << endl;
        reset_color();
        return;
    }

    print_header("ТАБЛИЦА ПОСТАВОК");

    set_color(BRIGHT_CYAN);
    cout << "+--------------------+------------+------------+------------+------------+" << endl;
    cout << "| Название фирмы     | Дата       | Поставка   | Оплата     | Сальдо     |" << endl;
    cout << "+--------------------+------------+------------+------------+------------+" << endl;
    reset_color();

    for (const auto& ship : shipments) {
        date dt = ship->get_delivery_date();
        string date_str = to_string(dt.getDay()) + "." + to_string(dt.getMonth()) + "." + to_string(dt.getYear());

        set_color(WHITE);
        cout << "| " << setw(18) << left << ship->get_company_name().substr(0, 18)
            << " | " << setw(10) << left << date_str
            << " | " << setw(10) << right << fixed << setprecision(2) << ship->get_supply_amount()
            << " | " << setw(10) << right << ship->get_payment_amount()
            << " | " << setw(10) << right << ship->get_balance() << " |" << endl;
    }

    set_color(BRIGHT_CYAN);
    cout << "+--------------------+------------+------------+------------+------------+" << endl;
    reset_color();
}

void show_All_data(const vector<unique_ptr<supplier>>& suppliers,
    const vector<unique_ptr<shipment>>& shipments) {
    clear_screen();
    print_suppliers_table(suppliers);
    cout << endl;
    print_shipments_table(shipments);

    set_color(BRIGHT_YELLOW);
    cout << "\nНажмите любую клавишу для продолжения...";
    reset_color();
    _getch();
}