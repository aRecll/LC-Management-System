#include "common.h"


#pragma region functions
void common::input()
{
	std::cout << "Введите название фирмы поставщика: ";
	std::cin.ignore();
	std::getline(std::cin, company_name);
}

void common::output() const
{
	std::cout << "Фирма: " << company_name;
}

bool common::search_by_company(const std::string& name) const
{
	return false;
}


#pragma endregion

#pragma region getters

double common::get_balance() const
{
	return 0.00000000000000;
}

#pragma endregion


#pragma region operators

std::ostream& operator<<(std::ostream& os, const common& obj)
{
	obj.output();
	return os;
}

std::istream& operator>>(std::istream& is, common& obj)
{
	
		std::cout << "Введите название фирмы поставщика: ";
		//is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::getline(is, obj.company_name);

		if (obj.company_name.empty()) {
			throw std::invalid_argument("Название фирмы не может быть пустым");
		}

		return is;
	
}

#pragma endregion


std::string common::get_company_name() const { 
	return company_name; 
}