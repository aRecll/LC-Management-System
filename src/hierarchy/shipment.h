#pragma once
#include "common.h"
#include "date.h"

class shipment :
    public common
{
private:
#pragma region data
    date delivery_date;     
    double supply_amount;   
    double payment_amount;  
#pragma endregion
public:
#pragma region constructors
    shipment() : common(), delivery_date(), supply_amount(0), payment_amount(0) {}

    shipment(const std::string& name, const date& date, double supply, double payment)
        : common(name), delivery_date(date), supply_amount(supply), payment_amount(payment) {
        if (supply < 0 || payment < 0) {
            throw std::invalid_argument("Суммы не могут быть отрицательными");
        }
    }
#pragma endregion

#pragma region functions
    void input() override;
    void output() const override;
    double get_balance() const override;
#pragma endregion


#pragma region getters
    date get_delivery_date() const { return delivery_date; }
    double get_supply_amount() const { return supply_amount; }
    double get_payment_amount() const { return payment_amount; }
    bool has_delivery_date(const date& searchDate) const;
#pragma endregion

    

#pragma region operators
    shipment& operator=(const shipment& other);
    friend std::istream& operator>>(std::istream& is, shipment& obj);

#pragma endregion


    };

