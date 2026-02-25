#include "manip_file.h"


const string SUPPLIER_FILE = "suppliers.dat";
const string SHIPMENT_FILE = "shipments.dat";

void save_suppliers_to_file(const vector<unique_ptr<supplier>>& suppliers) {
    ofstream file(SUPPLIER_FILE);
    if (!file) {
        set_color(BRIGHT_RED);
        cout << "Ошибка открытия файла для записи поставщиков!" << endl;
        reset_color();
        return;
    }

    file << suppliers.size() << endl;
    for (const auto& supp : suppliers) {
        file << supp->get_company_name() << endl;
        file << supp->get_contract_amount() << endl;
        file << supp->get_paid_amount() << endl;
    }
    set_color(BRIGHT_GREEN);
    cout << "  Данные поставщиков сохранены в файл." << endl;
    reset_color();
}
void save_shipments_to_file(const vector<unique_ptr<shipment>>& shipments) {
    ofstream file(SHIPMENT_FILE);
    if (!file) {
        set_color(BRIGHT_RED);
        cout << "Ошибка открытия файла для записи поставок!" << endl;
        reset_color();
        return;
    }

    file << shipments.size() << endl;
    for (const auto& ship : shipments) {
        file << ship->get_company_name() << endl;
        file << ship->get_delivery_date().getDay() << " "
            << ship->get_delivery_date().getMonth() << " "
            << ship->get_delivery_date().getYear() << endl;
        file << ship->get_supply_amount() << endl;
        file << ship->get_payment_amount() << endl;
    }
    set_color(BRIGHT_GREEN);
    cout << "  Данные поставок сохранены в файл." << endl;
    reset_color();
}

void load_suppliers_from_file(vector<unique_ptr<supplier>>& suppliers) {
    ifstream file(SUPPLIER_FILE);
    if (!file) {
        set_color(BRIGHT_YELLOW);
        cout << "Файл поставщиков не найден. Будет создан новый." << endl;
        reset_color();
        return;
    }

    size_t count;
    file >> count;
    file.ignore();

    for (size_t i = 0; i < count; ++i) {
        string name;
        double contract, paid;

        getline(file, name);
        file >> contract >> paid;
        file.ignore();

        suppliers.push_back(make_unique<supplier>(name, contract, paid));
    }
    set_color(BRIGHT_GREEN);
    cout << "  Загружено " << count << " поставщиков из файла." << endl;
    reset_color();
}

void load_shipments_from_file(vector<unique_ptr<shipment>>& shipments) {
    ifstream file(SHIPMENT_FILE);
    if (!file) {
        set_color(BRIGHT_YELLOW);
        cout << "Файл поставок не найден. Будет создан новый." << endl;
        reset_color();
        return;
    }

    size_t count;
    file >> count;
    file.ignore();

    for (size_t i = 0; i < count; ++i) {
        string name;
        int day, month, year;
        double supply, payment;

        getline(file, name);
        file >> day >> month >> year >> supply >> payment;
        file.ignore();

        date delivery_date(day, month, year);
        shipments.push_back(make_unique<shipment>(name, delivery_date, supply, payment));
    }
    set_color(BRIGHT_GREEN);
    cout << "- Загружено " << count << " поставок из файла." << endl;
    reset_color();
}