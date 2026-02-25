#pragma once
#include <string>
#include <iostream>
#include <limits>
class common
{
#pragma region data
    std::string company_name;
#pragma endregion

	
public:
#pragma region constructors and destr
    common() : company_name("") {}
    common(const std::string& name) : company_name(name) {}
    virtual ~common() = default;
#pragma endregion

#pragma region functions
    virtual void input();
    virtual void output() const;
    virtual bool search_by_company(const std::string& name) const;
    std::string get_company_name() const;

#pragma endregion


#pragma region getters
    virtual double get_balance() const;
#pragma endregion

  
#pragma region operators
    /// <summary>
    /// 
    /// </summary>
    /// <param name="os"></param>
    /// <param name="obj"></param>
    /// <returns></returns>

    friend std::ostream& operator<<(std::ostream& os, const common& obj);

    /// <summary>
    /// 
    /// </summary>
    /// <param name="is"></param>
    /// <param name="obj"></param>
    /// <returns></returns>
    friend std::istream& operator>>(std::istream& is, common& obj);

#pragma endregion

    
};

