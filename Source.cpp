#include "TVector.h"
#include "BitField.h"


int main()
{
	TVector<BitField> obj1(3);
	TVector<BitField> obj2(3);

	try
	{
		obj1.ScalarProduct(obj2);
	}
	catch (const std::exception& ex)
	{
		std::cout << ex.what() << std::endl;
	}
}