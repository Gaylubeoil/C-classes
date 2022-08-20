#pragma once
template <typename Type>
class Vector {
public:
	Vector();

	void push_back(Type new_data);
	void pop_back();

	size_t size() const;
	size_t capacity() const;
	bool empty() const;
	Type& back() const;
	Type& front() const;
	Type& at(const size_t index) const;
	void clear();

	Type& operator[](size_t index) const;

	~Vector();

private:
	Type* data;
	size_t m_capacity;
	size_t current;
};

template<typename Type>
inline Vector<Type>::Vector() {
	data = new Type[1];
	m_capacity = 1;
	current = 0;
}

template<typename Type>
inline void Vector<Type>::push_back(Type new_data) {
	if (current == m_capacity) {
		Type* temp = new Type[2 * m_capacity];

		for (size_t i = 0; i < m_capacity; i++) {
			temp[i] = data[i];
		}

		delete[] data;
		m_capacity *= 2;
		data = temp;
	}
	data[current] = new_data;
	current++;
}

template<typename Type>
inline void Vector<Type>::pop_back() {
	try {
		if (current == 0)
			throw std::invalid_argument("Vector size is zero before pop.");
		current--;
	}
	catch (std::invalid_argument& ex) {
		//ex.what();
	}
}

template<typename Type>
inline size_t Vector<Type>::size() const {
	return current;
}

template<typename Type>
inline size_t Vector<Type>::capacity() const {
	return m_capacity;
}

template<typename Type>
inline bool Vector<Type>::empty() const {
	return (current == 0 ? true : false);
}

template<typename Type>
inline Type& Vector<Type>::back() const {
	return data[current - 1];
}

template<typename Type>
inline Type& Vector<Type>::front() const {
	return data[0];
}

template<typename Type>
inline Type& Vector<Type>::at(const size_t index) const {
	return data[index];
}

template<typename Type>
inline void Vector<Type>::clear() {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}

	current = 0;
}

template<typename Type>
inline Type& Vector<Type>::operator[](size_t index) const {
	if (index >= current)
		throw;
	return data[index];
}

template<typename Type>
inline Vector<Type>::~Vector() {
	if (data != nullptr)
		delete[] data;
}


