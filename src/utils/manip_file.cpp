#include "manip_file.h"


const string SUPPLIER_FILE = "suppliers.dat";
const string SHIPMENT_FILE = "shipments.dat";

void save_suppliers_to_file(const vector<unique_ptr<supplier>>& suppliers) {
    ofstream file(SUPPLIER_FILE);
    if (!file) {
        set_�olor(BRIGHT_RED);
        cout << "������ �������� ����� ��� ������ �����������!" << endl;
        reset_�olor();
        return;
    }

    file << suppliers.size() << endl;
    for (const auto& supp : suppliers) {
        file << supp->get_company_name() << endl;
        file << supp->get_contract_amount() << endl;
        file << supp->get_paid_amount() << endl;
    }
    set_�olor(BRIGHT_GREEN);
    cout << "  ������ ����������� ��������� � ����." << endl;
    reset_�olor();
}
void save_shipments_to_file(const vector<unique_ptr<shipment>>& shipments) {
    ofstream file(SHIPMENT_FILE);
    if (!file) {
        set_�olor(BRIGHT_RED);
        cout << "������ �������� ����� ��� ������ ��������!" << endl;
        reset_�olor();
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
    set_�olor(BRIGHT_GREEN);
    cout << "  ������ �������� ��������� � ����." << endl;
    reset_�olor();
}

void load_suppliers_from_file(vector<unique_ptr<supplier>>& suppliers) {
    ifstream file(SUPPLIER_FILE);
    if (!file) {
        set_�olor(BRIGHT_YELLOW);
        cout << "���� ����������� �� ������. ����� ������ �����." << endl;
        reset_�olor();
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
    set_�olor(BRIGHT_GREEN);
    cout << "  ��������� " << count << " ����������� �� �����." << endl;
    reset_�olor();
}

void load_shipments_from_file(vector<unique_ptr<shipment>>& shipments) {
    ifstream file(SHIPMENT_FILE);
    if (!file) {
        set_�olor(BRIGHT_YELLOW);
        cout << "���� �������� �� ������. ����� ������ �����." << endl;
        reset_�olor();
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
    set_�olor(BRIGHT_GREEN);
    cout << "- ��������� " << count << " �������� �� �����." << endl;
    reset_�olor();
}