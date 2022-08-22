#pragma once

#include <cstring>
#include <iostream>
#include "Vector.hpp"

class String {
public:
	String(const char* new_string);
	String(const String& other);
	String(String&& other) noexcept;
	String();
	~String();

	const char* get() const;
	const size_t size() const;
	const bool includes(const String& search_value) const;
	const bool includes(const char search_character) const;
	String& replace(const String& search_value, const String& replace_value);
	const char& char_at(const size_t& index) const;
	String& to_upper_case();
	String& to_lower_case();
	size_t last_index_of(const char& value) const;
	/*Modifies the passed vector, pushing new strings derived from the main string, dividen by the specified character.*/
	void split(const char split_character, Vector<String>& returned) const;
	int stoi() const;

	bool operator==(const String& other) const;
	String& operator=(const String& other);
	String& operator+=(const String& other);
	String& operator+=(const char* other);
	char& operator[] (const size_t index) const;
	friend std::ostream& operator<<(std::ostream& os, const String& string);
private:
	size_t m_size;
	char* str;

private:
	bool compare_str(const String& str1, const String& str2) const;
};

