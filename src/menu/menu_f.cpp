#include "menu_f.h"
#include "emoji.h"

void set_сolor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}
void reset_сolor() {
    set_сolor(WHITE, BLACK);
}
void print_header(const string& title) {
    set_сolor(BRIGHT_CYAN);
    cout << "+-------------------------------------------------------------+" << endl;
    cout << "|                      " << setw(39) << left << title << "|" << endl;
    cout << "+-------------------------------------------------------------+" << endl;
    reset_сolor();
}
void clear_screen() {
    system("cls");
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

    set_сolor(BRIGHT_YELLOW);
    cout << "Используйте стрелки  для навигации, Enter для выбора, ESC для выхода" << endl << endl;
    reset_сolor();

    for (int i = 0; i < options.size(); ++i) {
        if (i == selected) {
            
            set_сolor(BLACK, BRIGHT_YELLOW);
            printEmoji(emojicpp::emojize(":smile:"));
            cout << "-> " << options[i] << endl;
            reset_сolor();
        }
        else {
            set_сolor(WHITE);
            printEmoji(emojicpp::emojize(":dollar:"));
            cout << "  " << options[i] << endl;
        }
    }
    
}

void print_suppliers_table(const vector<unique_ptr<supplier>>& suppliers) {
    if (suppliers.empty()) {
        set_сolor(BRIGHT_YELLOW);
        cout << "Нет данных о поставщиках." << endl;
        reset_сolor();
        return;
    }

    print_header("ТАБЛИЦА ПОСТАВЩИКОВ");

    set_сolor(BRIGHT_CYAN);
    cout << "+--------------------+--------------+------------+------------+" << endl;
    cout << "│ Название фирмы     │ Контракт     │ Оплачено   │ Сальдо     │" << endl;
    cout << "+--------------------+--------------+------------+------------+" << endl;
    reset_сolor();

    for (const auto& supp : suppliers) {
        set_сolor(WHITE);
        cout << "| " << setw(18) << left << supp->get_company_name().substr(0, 18)
            << " | " << setw(12 ) << right << fixed << setprecision(2) << supp->get_contract_amount()
            << " | " << setw(10 ) << right << supp->get_paid_amount()
            << " | " << setw(10 ) << right << supp->get_balance() << " |" << endl;
    }

    set_сolor(BRIGHT_CYAN);
    cout << "+--------------------+--------------+------------+------------+" << endl;
    reset_сolor();
}
void print_shipments_table(const vector<unique_ptr<shipment>>& shipments) {
    if (shipments.empty()) {
        set_сolor(BRIGHT_YELLOW);
        cout << "Нет данных о поставках." << endl;
        reset_сolor();
        return;
    }

    print_header("ТАБЛИЦА ПОСТАВОК");

    set_сolor(BRIGHT_CYAN);
    cout << "+--------------------+------------+------------+------------+------------+" << endl;
    cout << "| Название фирмы     | Дата       | Поставка   | Оплата     | Сальдо     |" << endl;
    cout << "+--------------------+------------+------------+------------+------------+" << endl;
    reset_сolor();

    for (const auto& ship : shipments) {
        date dt = ship->get_delivery_date();
        string date_str = to_string(dt.getDay()) + "." + to_string(dt.getMonth()) + "." + to_string(dt.getYear());

        set_сolor(WHITE);
        cout << "| " << setw(18) << left << ship->get_company_name().substr(0, 18)
            << " | " << setw(10) << left << date_str
            << " | " << setw(10) << right << fixed << setprecision(2) << ship->get_supply_amount()
            << " | " << setw(10) << right << ship->get_payment_amount()
            << " | " << setw(10) << right << ship->get_balance() << " |" << endl;
    }

    set_сolor(BRIGHT_CYAN);
    cout << "+--------------------+------------+------------+------------+------------+" << endl;
    reset_сolor();
}

void show_All_data(const vector<unique_ptr<supplier>>& suppliers,
    const vector<unique_ptr<shipment>>& shipments) {
    clear_screen();
    print_suppliers_table(suppliers);
    cout << endl;
    print_shipments_table(shipments);

    set_сolor(BRIGHT_YELLOW);
    cout << "\nНажмите любую клавишу для продолжения...";
    reset_сolor();
    _getch();
}