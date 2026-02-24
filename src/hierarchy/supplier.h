#pragma once
#include "common.h"
class supplier :
    public common
{
private:
#pragma region data
    double contract_amount;  
    double paid_amount;
#pragma endregion
public:
#pragma region constructors
    supplier() : common(), contract_amount(0), paid_amount(0) {}

    supplier(const std::string& name, double contract, double paid);
        
#pragma endregion

#pragma region functions
    void input() override;
    void output() const override;
    double get_balance() const override;
#pragma endregion


#pragma region getters
    double get_contract_amount() const { return contract_amount; }
    double get_paid_amount() const { return paid_amount; }
#pragma endregion


#pragma region operators
    supplier& operator=(const supplier& other);
    friend std::istream& operator>>(std::istream& is, supplier& obj);
    
#pragma endregion
};

