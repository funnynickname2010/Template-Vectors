#include "TVector.h"
#define MyType int
#define MyTypeScalar double

/*
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
*/

int main()
{
	unsigned int temp_size1, temp_size2;

	std::cout << "Input vec1 size: ";
	std::cin >> temp_size1;
	std::cout << "Input vec2 size: ";
	std::cin >> temp_size2;

	TVector<MyType> vec1(temp_size1);	
	TVector<MyType> vec2(temp_size2);

	std::cout << "Input vec1: ";
	std::cin >> vec1;
	std::cout << "Input vec2: ";
	std::cin >> vec2;

	std::cout << "+" << std::endl;
	try
	{
		std::cout << vec1 + vec2 << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "-" << std::endl;
	try
	{
		std::cout << vec1 - vec2 << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "*" << std::endl;
	try
	{
		MyTypeScalar temp_scalar;
		std::cout << std::endl << "Input scalar: ";
		std::cin >> temp_scalar;
		std::cout << vec1 * temp_scalar << std::endl;
		std::cout << vec2 * temp_scalar << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "/" << std::endl;
	try
	{
		MyTypeScalar temp_scalar;
		std::cout << std::endl << "Input scalar: ";
		std::cin >> temp_scalar;
		std::cout << vec1 / temp_scalar << std::endl;
		std::cout << vec2 / temp_scalar << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "+=" << std::endl;
	try
	{
		std::cout << vec1 << std::endl << vec2 << std::endl;
		TVector<MyType> res = vec1;
		res += vec1 + vec2;
		std::cout << res << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "-=" << std::endl;
	try
	{
		TVector<MyType> res = vec1;
		res -= vec2;
		std::cout << res << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "[]" << std::endl;
	try
	{
		unsigned int temp_index1, temp_index2;
		std::cout << "Input index for vec1: ";
		std::cin >> temp_index1;
		std::cout << "Input index for vec2: ";
		std::cin >> temp_index2;
		std::cout << vec1[temp_index1] << std::endl;
		std::cout << vec2[temp_index2] << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "++(int)" << std::endl;
	try
	{
		std::cout << ++vec1 << std::endl;
		std::cout << ++vec2 << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "++" << std::endl;
	try
	{
		std::cout << vec1++ << std::endl;
		std::cout << vec1 << std::endl;
		std::cout << vec2++ << std::endl;
		std::cout << vec2 << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "--(int)" << std::endl;
	try
	{
		std::cout << --vec1 << std::endl;
		std::cout << --vec2 << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "--" << std::endl;
	try
	{
		std::cout << vec1-- << std::endl;
		std::cout << vec1 << std::endl;
		std::cout << vec2-- << std::endl;
		std::cout << vec2 << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "==" << std::endl;
	try
	{
		std::cout << (vec1 == vec2) << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "!=" << std::endl;
	try
	{
		std::cout << (vec1 != vec2) << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "ScalarProduct" << std::endl;
	try
	{
		std::cout << vec1.ScalarProduct(vec2) << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	std::cout << "CrossProduct" << std::endl;
	try
	{
		std::cout << vec1.CrossProduct(vec2) << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}

	/*
	std::cout << "TripleProduct" << std::endl;
	try
	{
		std::cout << vec1.TripleProduct(ve << std::endl;
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}*/
}
