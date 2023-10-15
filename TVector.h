#pragma once
#include <cmath>
#include <iostream>
#include <string>
#include <sstream>


template <class T>
class TVector
{
	int size;
	T* val;

public:

	explicit TVector(int n);
	TVector(int n, T* p);
	TVector(const TVector<T>& vec);
	~TVector();

	TVector<T> operator +(const TVector<T>& vec);
	TVector<T> operator -(const TVector<T>& vec);
	TVector<T> operator *(const double scalar);
	TVector<T> operator /(const double scalar);
	TVector<T>& operator =(const TVector<T>& vec);
	TVector<T>& operator +=(const TVector<T>& vec);
	TVector<T>& operator -=(const TVector<T>& vec);
	T& operator [](const int index);
	TVector<T>& operator ++();
	TVector<T> operator ++(int);
	TVector<T>& operator --();
	TVector<T> operator --(int);

	bool operator ==(const TVector<T>& vec) const;
	bool operator !=(const TVector<T>& vec) const;

	double ScalarProduct(const TVector<T>& vec) const;
	TVector<T> CrossProduct(const TVector<T>& vec) const;
	double TripleProduct(const TVector<T>& vec2, const TVector<T>& vec3) const;

	void SetSize(unsigned int new_size);
	void SetVal(unsigned int index, const T);

	int GetSize();

	friend std::ostream& operator <<(std::ostream& os, const TVector<T>& vec);
	friend std::istream& operator >>(std::istream& os, TVector<T>& vec);
};

#include "TVector.h"

template <class T>
void TVector<T>::SetSize(unsigned int new_size)
{
	if (size != new_size)
	{
		T* new_val;
		unsigned int breakpoint_size;

		if (new_size > size) { breakpoint_size = size;  }
		else { breakpoint_size = new_size; }
		
		try
		{
			new_val = new T[new_size];
		}
		catch (...)
		{
			throw std::exception("TVector.SetSize memory allocation failure.");
		}

		for (int i; i < breakpoint_size; i++)
		{
			try
			{
				new_val[i] = val[i];
			}
			catch (...)
			{
				throw std::exception("TVector.SetSize assignment failure.");
			}
		}

		delete[] val;

		val = new_val;
		size = new_size;
	}
}

template <class T>
void TVector<T>::SetVal(unsigned int index, const T)
{
	try
	{
		val[index] = T;
	}
	catch (...)
	{
		throw std::exception("TVector assignment failure.");
	}
}

template <class T>
std::ostream& operator <<(std::ostream& os, const TVector<T>& vec)
{
	os << "(" << vec.val[0];

	for (int i = 1; i < vec.size; i++)
	{
		try
		{
			os << ", " << vec.val[i];
		}
		catch (...)
		{
			throw std::exception("TVector std::ostream& operator << failure");
		}
	}

	os << ")";
	return os;
}

template <class T>
std::istream& operator>>(std::istream& is, TVector<T>& vec)
{
	if (is.peek() == '\n')
	{
		is.ignore();
	}

	std::string input;
	std::getline(is, input);
	std::istringstream inps(input);

	if (inps.peek() == '(')
	{
		inps.ignore();
	}

	for (int i = 0; i < vec.size; i++)
	{
		try
		{
			if (i != 0)
			{
				if (!(inps.get() == ','))
				{
					// Error handling: Failed to extract comma
					is.setstate(std::ios::failbit);
					break;
				}
			}
			if (!(inps >> vec.val[i]))
			{
				// Error handling: Failed to extract vector element
				is.setstate(std::ios::failbit);
				break;
			}
		}
		catch (...)
		{
			throw std::exception("TVector std::istream& operator>> failure.");
		}
	}

	if (inps.peek() == ' ')
	{
		inps.ignore(); // Skipping the space before ')' if there's one
	}

	if (inps.peek() == ')')
	{
		inps.ignore();
	}

	if (is.rdstate() == std::ios::failbit)
	{
		std::cout << "//////INPUT ERROR\n";
	}

	// Clear any error flags that may have been set on the stream
	is.clear();

	return is;
}

template <class T>
inline TVector<T>& TVector<T>::operator +=(const TVector<T>& vec)
{
	try
	{
		*this = *this + vec;
	}
	catch (...)
	{
		throw std::exception("TVector operator += failure.");
	}

	return (*this = *this + vec);
}

template <class T>
inline TVector<T>& TVector<T>::operator -=(const TVector<T>& vec)
{
	try
	{
		*this = *this - vec;
	}
	catch (...)
	{
		throw std::exception("TVector operator -= failure.");
	}

	return (*this = *this - vec);
}

template <class T>
inline bool TVector<T>::operator ==(const TVector<T>& vec) const
{
	bool flag_equal = 1;

	if (size != vec.size)
	{
		flag_equal = 0;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			try
			{
				if (!(val[i] == vec.val[i]))
				{
					flag_equal = 0;
					break;
				}
			}
			catch (...)
			{
				throw std::exception("TVector operator == failure. ");
			}
		}

		return flag_equal;
	}
}

template <class T>
inline bool TVector<T>::operator !=(const TVector<T>& vec) const
{
	bool flag_equal = 1;

	if (size != vec.size)
	{
		flag_equal = 0;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			try
			{
				if (val[i] != vec.val[i])
				{
					flag_equal = 0;
					break;
				}
			}
			catch (...)
			{
				throw std::exception("TVector operator != failure. ");
			}
		}
	}

	return !flag_equal;
}

template <class T>
inline double TVector<T>::ScalarProduct(const TVector<T>& vec) const
{
	double res = 0;
	std::exception possible_exception("");

	try
	{
		if (size == vec.size)
		{
			for (int i = 0; i < size; i++)
			{
				try
				{
					res = res + (val[i] * vec.val[i]);
				}
				catch (...)
 				{
					possible_exception = "TVector.ScalarProduct multiplication failure.";
				}
			}
		}
		else
		{
			possible_exception = "TVector::ScalarProduct failure: unequal vector size.";
		}
	}
	catch (...)
	{
		possible_exception = "TVector::ScalarProduct operator == failure.";
	}

	if (possible_exception != "") { throw possible_exception; }

	return res;
}

template <class T>
inline TVector<T> TVector<T>::CrossProduct(const TVector<T>& vec) const
{
	TVector res(size);
	std::exception possible_exception('b');
	const char exception_flag = 'b';


	if (size == 3 && vec.size == 3)
	{
		//Hardcoded formulas
			
		try
		{
			res.val[0] = val[1] * vec.val[2] - val[2] * vec.val[1];
			res.val[1] = val[2] * vec.val[0] - val[0] * vec.val[2];
			res.val[2] = val[0] * vec.val[1] - val[1] * vec.val[0];
		}
		catch (...)
		{
			possible_exception = "TVector::CrossProduct multiplication, substraction or memory access failure.";
		}
	}
	else
	{
		possible_exception = "TVector::CrossProduct if (size == 3 && vec.size == 3) not fulfilled.";
	}

	if (possible_exception.what != exception_flag) { throw possible_exception; }

	return res;
}

template <class T>
inline double TVector<T>::TripleProduct(const TVector<T>& vec1, const TVector<T>& vec2) const
{
	double res;
	std::exception possible_exception("");

	if (vec1.size == 3 && vec2.size == 3 && size == 3)
	{
		try
		{
			res = (*this).ScalarProduct(vec1.CrossProduct(vec2));
		}
		catch (...)
		{
			possible_exception = "TVector::TripleProduct ScalarProduct, CrossProduct or memory access failure.";
		}
	}
	else
	{
		possible_exception = "TVector::TripleProduct if (vec1.size == 3 && vec2.size == 3 && size == 3) not fulfilled.";
		res = 0;
	}

	if (possible_exception != "") { throw possible_exception; }

	return res;
}

template <class T>
inline TVector<T>::TVector(int n)
{
	size = n;

	try
	{
		val = new double[n];
	}
	catch (...)
	{
		throw std::exception("TVector::TVector(int n) memory allocation failure.");
	}
}

template <class T>
inline TVector<T>::TVector(int n, T* p)
{
	size = n;
	std::exception possible_exception("");

	try
	{
		val = new double[n];
	}
	catch (...)
	{
		possible_exception = "TVector::TVector(int n, T* p) memory allocation failure.";
	}

	for (int i = 0; i < n; i++)
	{
		try
		{
			val[i] = p[i];
		}
		catch (...)
		{
			possible_exception = "TVector::TVector(int n, T* p) assigment failure.";
		}
	}

	if (possible_exception != "") { throw possible_exception; }
}

template <class T>
inline TVector<T>::TVector(const TVector<T>& vec)
{
	size = vec.size;
	std::exception possible_exception("");

	try
	{
		val = new double[vec.size];
	}
	catch (...)
	{
		possible_exception = "TVector::TVector(const TVector<T>& vec) memory allocation failure.";
	}

	for (int i = 0; i < size; i++)
	{
		try
		{
			val[i] = vec.val[i];
		}
		catch (...)
		{
			possible_exception = "TVector::TVector(const TVector<T>& vec) assigment failure.";
		}
	}

	if (possible_exception != "") { throw possible_exception; }
}

template <class T>
inline TVector<T>::~TVector()
{
	delete[] val;
	size = 0;
}

template <class T>
inline TVector<T>& TVector<T>::operator =(const TVector<T>& vec)
{
	std::exception possible_exception("");

	if (this != &vec)
	{
		if (size != vec.size)
		{
			delete[] val;
			size = vec.size;
			try
			{
				val = new double[size];
			}
			catch (...)
			{
				possible_exception = "TVector::operator = memory allocation failure.";
			}
		}

		for (int i = 0; i < size; i++)
		{
			try
			{
				val[i] = vec.val[i];
			}
			catch (...)
			{
				possible_exception = "TVector::operator = assigment failure.";
			}
		}
	}
	else
	{
		possible_exception = "TVector::operator =, if (this != &vec) not fulfilled."
	}

	if (possible_exception != "") { throw possible_exception; }

	return *this;
}

template <class T>
inline TVector<T> TVector<T>::operator +(const TVector<T>& vec)
{
	TVector res(size);
	std::exception possible_exception("");

	if (size == vec.size)
	{
		for (int i = 0; i < size; i++)
		{
			try
			{
				res[i] = val[i] + vec.val[i];
			}
			catch (...)
			{
				possible_exception = "TVector::operator + addition or assignment failure.";
				break;
			}
		}
	}
	else
	{
		possible_exception = "TVector::operator +, if (size == vec.size) not fulfilled.";
	}

	if (possible_exception != "") { throw possible_exception; }

	return res;
}

template <class T>
inline TVector<T> TVector<T>::operator -(const TVector<T>& vec)
{
	TVector res(size);
	std::exception possible_exception("");

	if (size == vec.size)
	{
		for (int i = 0; i < size; i++)
		{
			try
			{
				res[i] = val[i] - vec.val[i];
			}
			catch (...)
			{
				possible_exception = "TVector::operator - substraction or assignment failure.";
				break;
			}
		}
	}
	else
	{
		possible_exception = "TVector::operator -, if (size == vec.size) not fulfilled.";
	}

	if (possible_exception != "") { throw possible_exception; }

	return res;
}

template <class T>
inline TVector<T> TVector<T>::operator *(const double scalar)
{
	TVector res(size);

	for (int i = 0; i < size; i++)
	{
		try
		{
			res[i] = val[i] * scalar;
		}
		catch (...)
		{
			throw std::exception("TVector::operator *(const double scalar) multiplication or assignment failure.");
		}
	}

	return res;
}

template <class T>
inline TVector<T> TVector<T>::operator /(const double scalar)
{
	TVector res(size);
	std::exception possible_exception("");

	if (scalar != 0)
	{
		for (int i = 0; i < size; i++)
		{
			try
			{
				res[i] = val[i] / scalar;
			}
			catch (...)
			{
				possible_exception = "TVector::operator /(const double scalar) failure: division or assignment failure.";
				break;
			}
		}
	}
	else
	{
		possible_exception = "TVector::operator /(const double scalar) failure: division by zero.";
	}

	if (possible_exception != "") { throw possible_exception; }

	return res;
}

template <class T>
inline T& TVector<T>::operator [](const int index)
{
	if (abs(index) < size && index > -1)
	{
		return val[index];
	}
	else if (abs(index) < size && index < 0)
	{
		return val[size + index];
	}
	else if (abs(index) > size)
	{
		//Error implementation
		return val[0];
	}
}

template <class T>
inline TVector<T>& TVector<T>::operator ++()
{
	for (int i = 0; i < size; i++)
	{
		val[i]++;
	}

	return *this;
}

template <class T>
inline TVector<T> TVector<T>::operator ++(int)
{
	TVector res(*this);
	
	for (int i = 0; i < size; i++)
	{
		val[i]++;
	}

	return res;
}

template <class T>
inline TVector<T>& TVector<T>::operator --()
{
	for (int i = 0; i < size; i++)
	{
		val[i]--;
	}

	return *this;
}

template <class T>
inline TVector<T> TVector<T>::operator --(int)
{
	TVector res(*this);

	for (int i = 0; i < size; i++)
	{
		val[i]--;
	}

	return res;
}