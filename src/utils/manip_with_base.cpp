#include "manip_with_base.h"

void search_suppliers_by_name_dynamic(const vector<unique_ptr<supplier>>& suppliers) {
    clear_screen();
    print_header("ПОИСК ПОСТАВЩИКОВ ПО НАЗВАНИЮ (ДИНАМИЧЕСКИЙ МАССИВ)");

    string searchName;
    set_сolor(BRIGHT_YELLOW);
    cout << "Введите название фирмы для поиска: ";
    reset_сolor();
    //cin.ignore();
    getline(cin, searchName);

    
    vector<supplier*> foundSuppliers;
    for (const auto& supp : suppliers) {
        if (supp->get_company_name() == searchName) {
            foundSuppliers.push_back(supp.get());
        }
    }

    if (foundSuppliers.empty()) {
        set_сolor(BRIGHT_YELLOW);
        cout << "Поставщики не найдены." << endl;
        reset_сolor();
    }
    else {
        
        supplier* dynamicArray = new supplier[foundSuppliers.size()];
        for (size_t i = 0; i < foundSuppliers.size(); ++i) {
            dynamicArray[i] = *foundSuppliers[i]; // Используем оператор присваивания
        }

        set_сolor(BRIGHT_GREEN);
        cout << "\nНайдено поставщиков: " << foundSuppliers.size() << endl;
        cout << "Динамический массив создан с использованием оператора присваивания" << endl;
        reset_сolor();

        
        set_сolor(BRIGHT_CYAN);
        cout << "\n=== ДИНАМИЧЕСКИЙ МАССИВ ПОСТАВЩИКОВ ===" << endl;
        reset_сolor();

        for (size_t i = 0; i < foundSuppliers.size(); ++i) {
            set_сolor(WHITE);
            cout << i + 1 << ". ";
            dynamicArray[i].output();
            cout << endl;
        }

        delete[] dynamicArray;
    }

    set_сolor(BRIGHT_YELLOW);
    cout << "\nНажмите любую клавишу для продолжения...";
    reset_сolor();
    _getch();
}

void search_shipments_by_date_dynamic(const vector<unique_ptr<shipment>>& shipments) {
    clear_screen();
    print_header("ПОИСК ПОСТАВОК ПО ДАТЕ (ДИНАМИЧЕСКИЙ МАССИВ)");

    try {
        
        cin.clear();
        //cin.ignore((numeric_limits<streamsize>::max)(), '\n');

        set_сolor(BRIGHT_YELLOW);
        cout << "Введите дату для поиска (день месяц год): ";
        reset_сolor();

        date searchDate;
        if (!(cin >> searchDate)) {
            
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
            throw invalid_argument("Некорректный формат даты");
        }

        
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');

       
        vector<shipment*> foundShipments;
        for (const auto& ship : shipments) {
            if (ship->has_delivery_date(searchDate)) {
                foundShipments.push_back(ship.get());
            }
        }

        if (foundShipments.empty()) {
            set_сolor(BRIGHT_YELLOW);
            cout << "Поставки не найдены для даты: ";
            searchDate.output();
            cout << endl;
            reset_сolor();
        }
        else {
            
            shipment* dynamicArray = new shipment[foundShipments.size()];
            for (size_t i = 0; i < foundShipments.size(); ++i) {
                dynamicArray[i] = *foundShipments[i];
            }

            set_сolor(BRIGHT_GREEN);
            cout << "\nНайдено поставок: " << foundShipments.size() << endl;
            cout << "Динамический массив создан с использованием оператора присваивания" << endl;
            reset_сolor();

            
            set_сolor(BRIGHT_CYAN);
            cout << "\n=== ДИНАМИЧЕСКИЙ МАССИВ ПОСТАВОК ===" << endl;
            reset_сolor();

            for (size_t i = 0; i < foundShipments.size(); ++i) {
                set_сolor(WHITE);
                cout << i + 1 << ". ";
                dynamicArray[i].output();
                cout << endl;
            }

            delete[] dynamicArray;
        }
    }
    catch (const exception& e) {
        // Очищаем буфер после ошибки
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');

        set_сolor(BRIGHT_RED);
        cout << "Ошибка ввода даты: " << e.what() << endl;
        reset_сolor();
    }

    set_сolor(BRIGHT_YELLOW);
    cout << "\nНажмите любую клавишу для продолжения...";
    reset_сolor();
    _getch();
}

void demo_operators() {
    clear_screen();
    print_header("ДЕМОНСТРАЦИЯ ОПЕРАТОРОВ");

    try {
        
        cin.clear();
        //cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

        set_сolor(BRIGHT_CYAN);
        cout << "=== Демонстрация оператора >> для supplier ===" << endl;
        reset_сolor();

        supplier s1;
        cin >> s1;

        // Очищаем буфер между вводами
        //cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

        set_сolor(BRIGHT_CYAN);
        cout << "\n=== Демонстрация оператора >> для shipment ===" << endl;
        reset_сolor();

        shipment sh1;
        cin >> sh1;

        set_сolor(BRIGHT_CYAN);
        cout << "\n=== Демонстрация оператора = для supplier ===" << endl;
        reset_сolor();

        supplier s2 = s1;
        cout << "Создан копия поставщика: ";
        s2.output();

        set_сolor(BRIGHT_CYAN);
        cout << "\n=== Демонстрация оператора = для shipment ===" << endl;
        reset_сolor();

        shipment sh2 = sh1;
        cout << "Создана копия поставки: ";
        sh2.output();

        set_сolor(BRIGHT_GREEN);
        cout << "\n\nДемонстрация операторов завершена успешно!" << endl;
        reset_сolor();
    }
    catch (const exception& e) {
        
        cin.clear();
        cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

        set_сolor(BRIGHT_RED);
        cout << " Ошибка при демонстрации операторов: " << e.what() << endl;
        reset_сolor();
    }

    set_сolor(BRIGHT_YELLOW);
    cout << "\nНажмите любую клавишу для продолжения...";
    reset_сolor();
    _getch();
}



















void search_by_company_name(const vector<unique_ptr<supplier>>& suppliers,
    const vector<unique_ptr<shipment>>& shipments) {
    clear_screen();
    print_header("ПОИСК ПО НАЗВАНИЮ ФИРМЫ");

    string searchName;
    set_сolor(BRIGHT_YELLOW);
    cout << "Введите название фирмы для поиска: ";
    reset_сolor();
    cin.ignore();
    getline(cin, searchName);

    bool found = false;

    
    set_сolor(BRIGHT_GREEN);
    cout << "\n=== РЕЗУЛЬТАТЫ ПОИСКА В ПОСТАВЩИКАХ ===" << endl;
    reset_сolor();

    for (const auto& supp : suppliers) {
        if (supp->get_company_name() == searchName) {
            set_сolor(WHITE);
            cout << " Фирма: " << supp->get_company_name()
                << ", Контракт: " << supp->get_contract_amount()
                << ", Оплачено: " << supp->get_paid_amount()
                << ", Сальдо: " << supp->get_balance() << endl;
            found = true;
        }
    }
    if (!found) {
        set_сolor(BRIGHT_YELLOW);
        cout << "Поставщики не найдены." << endl;
    }

    found = false;
    set_сolor(BRIGHT_GREEN);
    cout << "\n=== РЕЗУЛЬТАТЫ ПОИСКА В ПОСТАВКАХ ===" << endl;
    reset_сolor();

    for (const auto& ship : shipments) {
        if (ship->get_company_name().find(searchName) != string::npos) {
            date dt = ship->get_delivery_date();
            set_сolor(WHITE);
            cout << " Фирма: " << ship->get_company_name()
                << ", Дата: " << dt.getDay() << "." << dt.getMonth() << "." << dt.getYear()
                << ", Поставка: " << ship->get_supply_amount()
                << ", Оплата: " << ship->get_payment_amount()
                << ", Сальдо: " << ship->get_balance() << endl;
            found = true;
        }
    }
    if (!found) {
        set_сolor(BRIGHT_YELLOW);
        cout << "Поставки не найдены." << endl;
    }

    reset_сolor();
    cout << "\n";
    set_сolor(BRIGHT_YELLOW);
    cout << "Нажмите любую клавишу для продолжения...";
    reset_сolor();
    _getch();
}


void sort_suppliers_by_balance(vector<unique_ptr<supplier>>& suppliers) {
    sort(suppliers.begin(), suppliers.end(),
        [](const unique_ptr<supplier>& a, const unique_ptr<supplier>& b) {
            return a->get_balance() > b->get_balance();
        });
    set_сolor(BRIGHT_GREEN);
    cout << "- Поставщики отсортированы по сальдо (по убыванию)." << endl;
    reset_сolor();
}

void sort_shipments_by_date(vector<unique_ptr<shipment>>& shipments) {
    sort(shipments.begin(), shipments.end(),
        [](const unique_ptr<shipment>& a, const unique_ptr<shipment>& b) {
            date dtA = a->get_delivery_date();
            date dtB = b->get_delivery_date();


            if (dtA.getYear() != dtB.getYear())
                return dtA.getYear() > dtB.getYear();

            if (dtA.getMonth() != dtB.getMonth())
                return dtA.getMonth() > dtB.getMonth();

            return dtA.getDay() > dtB.getDay();
        });
    set_сolor(BRIGHT_GREEN);
    cout << "- Поставки отсортированы по дате (по убыванию)." << endl;
    reset_сolor();
}


void add_new_suppliers(vector<unique_ptr<supplier>>& suppliers) {
    clear_screen();
    print_header("ДОБАВЛЕНИЕ НОВЫХ ПОСТАВЩИКОВ");

    int count;
    bool valid_input = false;

    
    while (!valid_input) {
        set_сolor(BRIGHT_YELLOW);
        cout << "Сколько новых поставщиков добавить? ";
        reset_сolor();

        cin >> count;

        if (cin.fail()) {
            set_сolor(BRIGHT_RED);
            cout << " Ошибка: введите целое число!" << endl;
            reset_сolor();

            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        }
        else if (count < 0) {
            set_сolor(BRIGHT_RED);
            cout << " Ошибка: количество не может быть отрицательным!" << endl;
            reset_сolor();

            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        }
        else if (count > 100) {
            set_сolor(BRIGHT_YELLOW);
            cout << "  Предупреждение: вы хотите добавить " << count << " поставщиков. Продолжить? (y/n): ";
            reset_сolor();

            char confirm;
            cin >> confirm;
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');

            if (confirm == 'y' || confirm == 'Y') {
                valid_input = true;
            }
            else {
                cout << "Ввод отменен. Введите новое количество:" << endl;
            }
        }
        else {
            valid_input = true;
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Очищаем буфер
        }
    }

    int successfully_added = 0;

    for (int i = 0; i < count; ++i) {
        try {
            set_сolor(BRIGHT_CYAN);
            cout << "\n=== ДОБАВЛЕНИЕ ПОСТАВЩИКА " << i + 1 << " ===" << endl;
            reset_сolor();

            auto newSupplier = make_unique<supplier>();
            cin >> *newSupplier;
            suppliers.push_back(move(newSupplier));
            successfully_added++;

        }
        catch (const exception& e) {
            set_сolor(BRIGHT_RED);
            cout << " Ошибка при добавлении поставщика " << i + 1 << ": " << e.what() << endl;
            cout << " Пропускаем этого поставщика..." << endl;
            reset_сolor();

            
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');

            
            if (i < count - 1) {
                set_сolor(BRIGHT_YELLOW);
                cout << "Продолжить добавление оставшихся " << (count - i - 1) << " поставщиков? (y/n): ";
                reset_сolor();

                char choice;
                cin >> choice;
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');

                if (choice != 'y' && choice != 'Y') {
                    break;
                }
            }
        }
    }

    set_сolor(BRIGHT_GREEN);
    cout << "\n Успешно добавлено " << successfully_added << " из " << count << " новых поставщиков." << endl;
    reset_сolor();

    set_сolor(BRIGHT_YELLOW);
    cout << "\nНажмите любую клавишу для продолжения...";
    reset_сolor();
    _getch();
}

void add_new_shipments(vector<unique_ptr<shipment>>& shipments) {
    clear_screen();
    print_header("ДОБАВЛЕНИЕ НОВЫХ ПОСТАВОК");

    int count;
    bool valid_input = false;

    
    while (!valid_input) {
        set_сolor(BRIGHT_YELLOW);
        cout << "Сколько новых поставок добавить? ";
        reset_сolor();

        cin >> count;

        if (cin.fail()) {
            set_сolor(BRIGHT_RED);
            cout << " Ошибка: введите целое число!" << endl;
            reset_сolor();

            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        }
        else if (count < 0) {
            set_сolor(BRIGHT_RED);
            cout <<"Ошибка: количество не может быть отрицательным!" << endl;
            reset_сolor();

            cin.ignore((numeric_limits<streamsize>::max)(), '\n');
        }
        else if (count > 50) {
            set_сolor(BRIGHT_YELLOW);
            cout << "  Предупреждение: вы хотите добавить " << count << " поставок. Продолжить? (y/n): ";
            reset_сolor();

            char confirm;
            cin >> confirm;
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');

            if (confirm == 'y' || confirm == 'Y') {
                valid_input = true;
            }
            else {
                cout << "Ввод отменен. Введите новое количество:" << endl;
            }
        }
        else {
            valid_input = true;
            cin.ignore((numeric_limits<streamsize>::max)(), '\n'); 
        }
    }

    int successfully_added = 0;

    for (int i = 0; i < count; ++i) {
        try {
            set_сolor(BRIGHT_CYAN);
            cout << "\n=== ДОБАВЛЕНИЕ ПОСТАВКИ " << i + 1 << " ===" << endl;
            reset_сolor();

            auto newShipment = make_unique<shipment>();
            cin>>*newShipment;
            shipments.push_back(move(newShipment));
            successfully_added++;

        }
        catch (const exception& e) {
            set_сolor(BRIGHT_RED);
            cout << " Ошибка при добавлении поставки " << i + 1 << ": " << e.what() << endl;
            cout << " Пропускаем эту поставку..." << endl;
            reset_сolor();

            
            cin.clear();
            cin.ignore((numeric_limits<streamsize>::max)(), '\n');

            
            if (i < count - 1) {
                set_сolor(BRIGHT_YELLOW);
                cout << "Продолжить добавление оставшихся " << (count - i - 1) << " поставок? (y/n): ";
                reset_сolor();

                char choice;
                cin >> choice;
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');

                if (choice != 'y' && choice != 'Y') {
                    break;
                }
            }
        }
    }

    set_сolor(BRIGHT_GREEN);
    cout << "\n Успешно добавлено " << successfully_added << " из " << count << " новых поставок." << endl;
    reset_сolor();

    set_сolor(BRIGHT_YELLOW);
    cout << "\nНажмите любую клавишу для продолжения...";
    reset_сolor();
    _getch();
}



void perform_sorting(vector<unique_ptr<supplier>>& suppliers,
    vector<unique_ptr<shipment>>& shipments) {
    clear_screen();
    print_header("СОРТИРОВКА ДАННЫХ");

    sort_suppliers_by_balance(suppliers);
    sort_shipments_by_date(shipments);

    set_сolor(BRIGHT_YELLOW);
    cout << "\nНажмите любую клавишу для продолжения...";
    reset_сolor();
    _getch();
}

void save_all_data(const vector<unique_ptr<supplier>>& suppliers,
    const vector<unique_ptr<shipment>>& shipments) {
    clear_screen();
    print_header("СОХРАНЕНИЕ ДАННЫХ");

    save_suppliers_to_file(suppliers);
    save_shipments_to_file(shipments);

    set_сolor(BRIGHT_YELLOW);
    cout << "\nНажмите любую клавишу для продолжения...";
    reset_сolor();
    _getch();
}