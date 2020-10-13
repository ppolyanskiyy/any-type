#pragma once
#include<iostream>
#include<string>
#include<variant>
#include<algorithm>

using namespace std;

enum DataIndex { DATA_BEGIN = -1, CHAR_DATA, BOOL_DATA, INT_DATA, DOUBLE_DATA, DATA_END };

using StandartTypes = variant<char, bool, int, double>;

class AnyType {
private:
	StandartTypes m_data;
	
	inline const int get_index(const string& str)const {
		if ("char" == str)return CHAR_DATA;
		else if ("bool" == str)return BOOL_DATA;
		else if ("int" == str)return INT_DATA;
		else if ("double" == str)return DOUBLE_DATA;
		else return DATA_BEGIN;
	}

public:

	AnyType() = default;
	AnyType(StandartTypes);
	AnyType(string) = delete;

	AnyType(const AnyType&);
	AnyType(const AnyType&&) = delete;

	bool operator==(const AnyType&);

	template<typename Type>
	AnyType& operator=(const Type&);

	AnyType& operator=(const AnyType&);

	string get_type()const;

	template<typename Type>
	Type& extract_value()const;

	void swap(AnyType&);
};

// constructors
AnyType::AnyType(StandartTypes data) : m_data(data) {}
AnyType::AnyType(const AnyType& other) : m_data(other.m_data) {};

// operator==
inline bool AnyType::operator==(const AnyType& other) {
	return this->m_data == other.m_data;
};

// operator=
template<typename Type>
inline AnyType& AnyType::operator=(const Type& other) {
	int index = get_index(typeid(other).name());

	if (DATA_BEGIN < index && index < DATA_END) {
		this->m_data = other;
		return *this;
	}
	else {
		throw bad_cast();
	}
}

inline AnyType& AnyType::operator=(const AnyType& other) {
	if (this->m_data == other.m_data) return *this;

	this->m_data = other.m_data;
	return *this;
}

// Return type of data
inline string AnyType::get_type() const {
	string type = visit([](auto const& data) {
		return typeid(data).name();
		}, this->m_data);

	return type;
}

// Extracts value from variant 
template<typename Type>
inline Type& AnyType::extract_value() const {
	Type result{};

	if (typeid(result) == typeid(Type)) {
		result = get<Type>(m_data);
		return result;
	}
	else {
		throw bad_cast();
	}
}

// Swap two objects
inline void AnyType::swap(AnyType& other) {
	StandartTypes to_swap = this->m_data;
	this->m_data = other.m_data;
	other.m_data = to_swap;
}
