#pragma once
#include <iostream>
#include <string>
#include <variant>
#include <algorithm>

using namespace std;

enum DataIndex
{
	DATA_BEGIN = -1,
	CHAR_DATA, BOOL_DATA, INT_DATA, DOUBLE_DATA,
	LONG_INT_DATA, LONG_DOUBLE_DATA,
	DATA_END
};

using StandartTypes = variant<char, bool, int, double, long int, long double>;

class AnyType
{
public:
	AnyType() = default;
	AnyType(StandartTypes);
	AnyType(string) = delete;

	AnyType(const AnyType&);
	AnyType(const AnyType&&) = delete;

	template<typename Type>
	AnyType& operator=(const Type&);

	AnyType& operator=(const AnyType&);

	string get_type()const;

	template<typename Type>
	Type extract_value()const;

	void swap(AnyType&);

private:
	const int get_index(const string&)const;

	StandartTypes m_data;
};

// constructors
AnyType::AnyType(StandartTypes data) : m_data(data) {}
AnyType::AnyType(const AnyType& other) : m_data(other.m_data) {};

// operator=
template<typename Type>
AnyType& AnyType::operator=(const Type& other)
{
	int index = get_index(typeid(other).name());

	if (DATA_BEGIN < index && index < DATA_END)
	{
		this->m_data = other;
		return *this;
	}
	else throw bad_cast();
}

AnyType& AnyType::operator=(const AnyType& other)
{
	if (this->m_data == other.m_data) return *this;

	this->m_data = other.m_data;
	return *this;
}

// Return type of data
string AnyType::get_type() const
{
	string type = visit([](auto const& data)
		{
			return typeid(data).name();
		}, this->m_data);

	return type;
}

// Extracts value from variant, throw bad variant access
template<typename Type>
Type AnyType::extract_value() const
{
	Type result = get<Type>(m_data);
	return result;
}

// Swap two objects
void AnyType::swap(AnyType& other)
{
	StandartTypes to_swap = this->m_data;
	this->m_data = other.m_data;
	other.m_data = to_swap;
}

// Return index for string
const int AnyType::get_index(const string& str) const
{
	if ("char" == str)return CHAR_DATA;
	else if ("bool" == str)return BOOL_DATA;
	else if ("int" == str)return INT_DATA;
	else if ("double" == str)return DOUBLE_DATA;
	else if ("long int" == str)return LONG_INT_DATA;
	else if ("long double" == str) return LONG_DOUBLE_DATA;
	else return DATA_BEGIN;
}
