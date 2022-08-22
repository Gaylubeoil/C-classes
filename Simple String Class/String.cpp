#define _CRT_SECURE_NO_WARNINGS
#include "String.hpp"

String::String(const char* new_string) {
	this->str = nullptr;
	this->m_size = strlen(new_string);
	this->str = new char[this->m_size + 1];
	strcpy(this->str, new_string);
}

String::String(const String& other) {
	if (other.str == nullptr) {
		std::bad_alloc exception;
		throw (exception);
	}
	// if (this->str != nullptr) {
	// 	delete[] this->str;
	// }  /TODO
	this->m_size = other.m_size;
	this->str = new char[this->m_size + 1];
	strcpy(this->str, other.str);

}

String::String(String&& other) noexcept {
	this->str = other.str;
	this->m_size = other.m_size;

	other.m_size = 0;
	other.str = nullptr;
}

String::String() {
	this->m_size = 0;
	this->str = nullptr;
}

const char* String::get() const {
	return this->str;
}

const size_t String::size() const {
	return this->m_size;
}

const bool String::includes(const String& search_value) const {
	if (this->str == nullptr) {
		return false;
	}
	if (search_value.m_size > this->m_size)
		return false;
	char first_char = search_value.str[0];
	for (size_t i = 0; i < m_size; ++i) {
		if (str[i] == first_char) {
			for (size_t j = 0; j < search_value.m_size; ++j) {
				if (str[i++] != search_value.str[j]) {
					break;
				}
			}
			return true;
		}
	}
	return false;
}

const bool String::includes(const char search_character) const {
	for (size_t i = 0; i < this->m_size; ++i) {
		if (this->str[i] == search_character) {
			return true;
		}
	}
	return false;
}

String& String::replace(const String& search_value, const String& replace_value) {
	if (!(this->includes(search_value))) {
		return *this;
	}
	bool value_found = false;

	char first_char = search_value.str[0];
	char first_string[128] = { '\0', };
	size_t first_index = 0, second_index = 0;
	char second_string[128] = { '\0', };
	for (size_t i = 0; i < m_size; ++i) {
		if (str[i] == first_char) {
			for (size_t j = 0; j < search_value.m_size; ++j) {
				if (str[i++] != search_value.str[j]) {
					i -= 2;
					break;
				}
				if (j == search_value.m_size - 1) {
					value_found = true;
				}
			}
		}
		if (!value_found) {
			first_string[first_index++] = str[i];
		}
		else {
			second_string[second_index++] = str[i];
		}
	}

	strcat(first_string, replace_value.str);
	strcat(first_string, second_string);
	delete[] str;
	m_size = strlen(first_string);
	str = new char[m_size + 1];
	strcpy(str, first_string);
	return *this;
}

const char& String::char_at(const size_t& index) const {
	if (index >= this->m_size) {
		throw;
	}
	return this->str[index];
}

String& String::to_upper_case() {
	for (size_t i = 0; i < this->m_size; ++i) {
		if (str[i] >= 'a' && str[i] <= 'z') {
			str[i] -= 32;
		}
	}
	return *this;
}

String& String::to_lower_case() {
	for (size_t i = 0; i < this->m_size; ++i) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] += 32;
		}
	}
	return *this;
}

size_t String::last_index_of(const char& value) const {
	for (size_t i = m_size - 1; i > 0; i--) {
		if (str[i] == value) {
			return i;
		}
	}
	return 0;
}

void String::split(const char split_character, Vector<String>& returned) const {
	char* current = new char[128](); // '()' sets all elements to 0;
	size_t current_size = 0;
	for (size_t i = 0; i < this->m_size; ++i) {
		if (this->str[i] == split_character) {
			String temp(current);
			returned.push_back(temp);
			current_size = 0;
			delete[] current;
			current = new char[128]();
		}
		else {
			current[current_size++] = this->str[i];
		}
		if (i == this->m_size - 1) {
			String temp(current);
			returned.push_back(temp);
			current_size = 0;
		}
	}
	delete[] current;
}

int String::stoi() const {
	int num = 0;
	for (int i = (int)m_size - 1; i >=0; i--) {
		int power = m_size - i - 1;
		int t = str[i] - '0';
		num += (std::pow(10, power) * t);
	}
	return num;
}

bool String::compare_str(const String& str1, const String& str2) const {
	for (size_t i = 0; i < str1.size(); ++i) {
		if (str1.str[i] != str2.str[i]) {
			return false;
		}
	}
	return true;
}
bool String::operator==(const String& other) const {
	if (this->m_size == other.m_size) {
		return (compare_str(*this, other));
	}
	return false;
}

String& String::operator=(const String& other) {
	if (other.str == nullptr)
		return *this;

	if (this->str != nullptr)
		delete[] this->str;

	this->m_size = other.m_size;
	this->str = new char[this->m_size + 1];
	strcpy(this->str, other.str);
	return *this;
}

String& String::operator+=(const String& other) {
	if (other.str == nullptr)
		return *this;

	char* temp = this->str;
	this->m_size += other.m_size;
	this->str = new char[this->m_size + 1];

	strcpy(this->str, temp);
	strcat(this->str, other.str);
	delete[] temp;
	return *this;
}

String& String::operator+=(const char* other) {
	if (other == nullptr)
		return *this;

	char* temp = this->str;

	this->m_size += strlen(other);
	this->str = new char[this->m_size + 1];

	strcpy(this->str, temp);
	strcat(this->str, other);

	delete[] temp;
	return *this;
}

char& String::operator[](const size_t index) const
{
	return this->str[index];
}

std::ostream& operator<<(std::ostream& os, const String& string) {
	os << string.str;
	return os;
}

String::~String() {
	delete[] this->str;
}