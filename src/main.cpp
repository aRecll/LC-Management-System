// main.cpp

#include "utils/manip_with_base.h"

#include "thread"

using namespace std;
#ifdef _WIN32

#else
#include <termios.h> 
#include <unistd.h>  
    #endif


void setUp(){
#ifdef _WIN32
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
    fontInfo.dwFontSize.Y = size;
    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
#else
    #endif

}
void setConsoleFontSize(short size) {
    #ifdef _WIN32
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX fontInfo;
    fontInfo.cbSize = sizeof(fontInfo);
    GetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
    fontInfo.dwFontSize.Y = size;
    SetCurrentConsoleFontEx(hConsole, FALSE, &fontInfo);
#else
    #endif
}
int getch_linux() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}


int main() {
    //setlocale(LC_ALL, "");
    
    /*SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);*/
    
    vector<unique_ptr<supplier>> suppliers;
    vector<unique_ptr<shipment>> shipments;

    
    load_suppliers_from_file(suppliers);
    load_shipments_from_file(shipments);

    // Меню
    vector<string> menuOptions = {
        "Показать все данные",
        " Добавить новых поставщиков",
        " Добавить новые поставки",
        " Поиск по названию фирмы",
        " Сортировка данных",
        " Сохранить данные в файлы",
        " Демонстрация операторов",           
        " Поиск поставщиков (динамический массив)", 
        " Поиск поставок по дате (динамический массив)", 
        " Выход"
    };
    setConsoleFontSize(32);
    int selected = 0;
    bool running = true;
   // std::cout << emojicpp::emojize("Emoji :smile: for c++ :+1:") << std::endl;

    while (running) {
        print_menu(menuOptions, selected);
        #ifdef _WIN32
        int key = _getch();
    #else
    int key = getch_linux();
    #endif
        
        if (key == 224) { 
            key = _getch();
            switch (key) {
            case 72: 
                selected = (selected - 1 + menuOptions.size()) % menuOptions.size();
                break;
            case 80: 
                selected = (selected + 1) % menuOptions.size();
                break;
            }
        }
        else if (key == 13) { 
            switch (selected) {
            case 0:
                show_All_data(suppliers, shipments);
                break;
            case 1:
                add_new_suppliers(suppliers);
                break;
            case 2:
               add_new_shipments(shipments);
                break;
            case 3:
                search_by_company_name(suppliers, shipments);
                break;
            case 4:
                perform_sorting(suppliers, shipments);
                break;
            case 5:
                save_all_data(suppliers, shipments);
                break;
            case 6: 
                demo_operators();
                break;
            case 7: 
                search_suppliers_by_name_dynamic(suppliers);
                break;
            case 8: 
                search_shipments_by_date_dynamic(shipments);
                break;
            case 9:
                running = false;
                break;
            }
        }
        else if (key == 27) { // ESC
            running = false;
        }
    }

    clear_screen();
    print_header("ВЫХОД ИЗ ПРОГРАММЫ");
    set_color(BRIGHT_GREEN);
    std::cout << "Спасибо за использование программы!" << endl;
    reset_color();

    return 0;
}