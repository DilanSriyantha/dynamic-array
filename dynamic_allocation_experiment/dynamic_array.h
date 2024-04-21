#pragma once

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>
#include <stdlib.h>
#include <memory>

template <typename T>
class dynamic_array {
public:
	dynamic_array() = default;

	T& push(T element)
	{
		// 1st element, 0th index
		if (m_end == 0)
		{
			m_array = malloc(sizeof(T)); // dynamically allocate sizeof(T) bytes -> pointer to the first element will be returned
			*(static_cast<T*>(m_array)) = element; // de-reference and insert data into the memory location can expect the similar behavior with `(static_cast<T*>(m_array))[0] = element` as well
			++m_end; // pre-increment of m_end attribute to keep track on the count of elements in the contiguous memory block

			return element; // return the element as a reference.
		}

		// index > 0
		++m_end; // increase the m_end attribute to keep track on the count of elements in the contiguous block of memory.
		auto* new_array = static_cast<T*>(realloc(m_array, (sizeof(T) * m_end))); // re-allocate the memory to store the required number of elements of type T.
		if (new_array == nullptr) // handle unexpected errors.
		{
			std::cerr << "Could not allocate memory.\n";
			free(m_array);
			exit(1);
		}
		new_array[m_end - 1] = element; // populate the last memory address of the contiguous block with the element passed into the method.
		m_array = new_array; 

		return element;
	}

	void removeAt(std::size_t idx)
	{
		// check whether the index is out of bound or not
		if (idx >= size())
		{
			std::cerr << "Index out of bound\n";
			return;
		}

		// shift elements in the array to left, starting from the index where it is required to be removed
		for (auto& i = idx; i < size(); i++)
		{
			(static_cast<T*>(m_array))[i] = (static_cast<T*>(m_array))[i + 1];
		}

		// decrease m_end by 1
		--m_end;

		// re-allocate the memory to store necessary elements
		auto* new_array = static_cast<T*>(realloc(m_array, (sizeof(T) * m_end)));
		if (new_array == nullptr) // handle unexpected behaviours
		{
			std::cerr << "Could not allocate memory \n";
			free(m_array);
			exit(1);
		}
	}

	std::size_t& size()
	{
		return m_end;
	}

	int* begin() const
	{
		return static_cast<T*>(m_array);
	}

	int* end() const
	{
		return static_cast<T*>(m_array) + m_end;
	}

	T& operator[](std::size_t idx) noexcept
	{
		return (static_cast<T*>(m_array))[idx];
	}

	~dynamic_array()
	{
		free(m_array);
	}
private:
	std::size_t m_begin = 0;
	std::size_t m_end = 0;
	void* m_array = nullptr;
};

#endif // !DYNAMIC_ARRAY_H
