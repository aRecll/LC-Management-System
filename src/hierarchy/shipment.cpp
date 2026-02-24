#include "shipment.h"

void shipment::input()
{
    try {
        common::input();

        std::cout << "Введите дату поставки: \n";
        delivery_date.input();

        std::cout << "Введите сумму поставки: ";
        std::cin >> supply_amount;
        if (supply_amount < 0) {
            throw std::invalid_argument("Сумма поставки не может быть отрицательной");
        }

        std::cout << "Введите сумму оплаты: ";
        std::cin >> payment_amount;
        if (payment_amount < 0) {
            throw std::invalid_argument("Сумма оплаты не может быть отрицательной");
        }
    }
    catch (const std::exception& e) {
        //std::cerr << "Ошибка ввода: " << e.what() << std::endl;
        throw;
    }
}

void shipment::output() const
{
    common::output();
    std::cout << ", Дата: ";
    delivery_date.output();
    std::cout << ", Поставка: " << supply_amount
        << ", Оплата: " << payment_amount
        << ", Сальдо: " << get_balance();
}

double shipment::get_balance() const
{
    return supply_amount - payment_amount;
}

bool shipment::has_delivery_date(const date& searchDate) const
{
    return delivery_date == searchDate;
}

shipment& shipment::operator=(const shipment& other)
{
     if (this != &other) {
        common::operator=(other);
        delivery_date = other.delivery_date;
        supply_amount = other.supply_amount;
        payment_amount = other.payment_amount;
    }
    return *this;
}

std::istream& operator>>(std::istream& is, shipment& obj)
{
    
    std::ios_base::iostate original_state = is.rdstate();

    try {
        is.clear();

        is >> static_cast<common&>(obj);

        std::cout << "Введите дату поставки (день месяц год): ";
        is >> obj.delivery_date;
        

        std::cout << "Введите сумму поставки: ";
        is >> obj.supply_amount;
        if (is.fail()) {
            throw std::invalid_argument("Некорректный формат суммы поставки");
        }
        if (obj.supply_amount < 0) {
            throw std::invalid_argument("Сумма поставки не может быть отрицательной");
        }

        std::cout << "Введите сумму оплаты: ";
        is >> obj.payment_amount;
        if (is.fail()) {
            throw std::invalid_argument("Некорректный формат суммы оплаты");
        }
        if (obj.payment_amount < 0) {
            throw std::invalid_argument("Сумма оплаты не может быть отрицательной");
        }

        
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    }
    catch (const std::exception& e) {
        
        is.clear(original_state);
        is.setstate(std::ios::failbit);
        is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        throw;
    }
    return is;
   
}
