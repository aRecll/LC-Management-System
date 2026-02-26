#include "menu_f.h"
#include "emoji.h"

#ifndef _WIN32
// Глобальная переменная для хранения настроек (чтобы восстановить их при выходе)
struct termios old_settings;

void restore_terminal() {
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
}
#endif

int getch_() {
#ifdef _WIN32
    int ch = _getch();
    return ch;
#else
    struct termios newt;
    int ch;
    tcgetattr(STDIN_FILENO, &old_settings);
    newt = old_settings;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    ch = getchar();
    if (ch == 27) { // Обработка ESC или стрелок
        fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);
        int next1 = getchar();
        int next2 = getchar();
        fcntl(STDIN_FILENO, F_SETFL, 0);

        if (next1 == -1) { // Это чистый ESC
             tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
             return 27; 
        }
        if (next1 == 91) { // Это стрелка
             tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
             return next2; // Вернет 65 (UP) или 66 (DOWN)
        }
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old_settings);
    return ch;
#endif
}


std::string getAnsiColor(int colorNum) {
    switch (colorNum) {
        case 0:  return "\033[30m";      // BLACK
        case 1:  return "\033[34m";      // BLUE
        case 2:  return "\033[32m";      // GREEN
        case 3:  return "\033[36m";      // CYAN
        case 4:  return "\033[31m";      // RED
        case 5:  return "\033[35m";      // MAGENTA
        case 6:  return "\033[33m";      // YELLOW
        case 7:  return "\033[37m";      // WHITE
        case 8:  return "\033[90m";      // GRAY (Bright Black)
        case 9:  return "\033[94m";      // BRIGHT_BLUE
        case 10: return "\033[92m";      // BRIGHT_GREEN
        case 11: return "\033[96m";      // BRIGHT_CYAN
        case 12: return "\033[91m";      // BRIGHT_RED
        case 13: return "\033[95m";      // BRIGHT_MAGENTA
        case 14: return "\033[93m";      // BRIGHT_YELLOW
        case 15: return "\033[97m";      // BRIGHT_WHITE
        default: return "\033[0m";       // RESET (если номер неверный)
    }
}


void set_color(int textColor, int bgColor) {
    #ifdef _WIN32 
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
    #else
    string color=getAnsiColor(textColor);
    std::cout<<color;
    #endif
    
}



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
       #ifdef _WIN32 
    UINT originalCP = GetConsoleOutputCP();
    SetConsoleOutputCP(CP_UTF8);
#else 
    #endif

    std::cout << text;
      #ifdef _WIN32 
     SetConsoleOutputCP(originalCP);
#else 
#endif
   
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
    getch_();
}