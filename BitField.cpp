#include "BitField.h"

void BitField::TurnOn(unsigned int index)
{
	bitarray[index >> 5] = (bitarray[index >> 5] | BitMask(0, (index & 31)));
}

void BitField::TurnOff(unsigned int index)
{
	bitarray[index >> 5] = (bitarray[index >> 5] & BitMask(1, (index & 31)));
}

bool BitField::CheckState(unsigned int index)
{
	int op1;
	int op2;
	int res1;
	int	res2;
	int res3;
	bool res_final;

	op1 = (index >> 5);
	res1 = bitarray[op1];
	op2 = (31 & index);
	res2 = BitMask(2, op2);
	res3 = res1 & res2;
	res_final = res3 != 0;

	return res_final;
}

unsigned int BitField::BitMask(unsigned int task, unsigned int location)
{
	unsigned int result;

	switch (task)
	{
	case 0:

		result = 1 << location;
		break;

	case 1:

		result = ~(1 << location);
		break;

	case 2:

		result = 1 << location;
		break;
	}

	return result;
}

BitField::BitField()
{
	bitarray = new unsigned int[1];
	used_bits = 0;
	reserved_ints = 1;

	for (unsigned int i = 0; i < reserved_ints; i++)
	{
		bitarray[i] = 0;
	}
}

BitField::BitField(unsigned int& n)
{
	bitarray = new unsigned int[n];
	used_bits = 0;
	reserved_ints = n;

	for (unsigned int i = 0; i < reserved_ints; i++)
	{
		bitarray[i] = 0;
	}
}

BitField::BitField(BitField& obj2)
{
	used_bits = obj2.used_bits;
	reserved_ints = obj2.reserved_ints;
	bitarray = new unsigned int[obj2.reserved_ints];

	for (unsigned int i = 0; i < reserved_ints; i++)
	{
		bitarray[i] = obj2.bitarray[i];
	}
}

BitField::~BitField()
{
	delete[] bitarray;
}

bool BitField::operator ==(const BitField& obj2)
{
	bool result = 1;

	if (reserved_ints != obj2.reserved_ints || used_bits != obj2.used_bits)
	{
		result = 0;
	}
	else
	{
		for (unsigned int i = 0; i < reserved_ints; i++)
		{
			if (bitarray[i] != obj2.bitarray[i])
			{
				result = 0;
				break;
			}
		}
	}

	return result;
}

BitField& BitField::operator =(const BitField& obj2)
{
	if (this != &obj2)
	{
		if (reserved_ints != obj2.reserved_ints)
		{
			reserved_ints = obj2.reserved_ints;
			bitarray = new unsigned int[obj2.reserved_ints];
		}

		for (unsigned int i = 0; i < reserved_ints; i++)
		{
			bitarray[i] = obj2.bitarray[i];
		}

		used_bits = obj2.used_bits;
	}

	return *this;
}

BitField BitField::operator &(const BitField& obj2)
{
	unsigned int result_bitfield_size;
	int smaller_bitfield_size;

	if (reserved_ints >= obj2.reserved_ints)
	{
		result_bitfield_size = reserved_ints;
		smaller_bitfield_size = obj2.reserved_ints;
	}
	else
	{
		result_bitfield_size = obj2.reserved_ints;
		smaller_bitfield_size = reserved_ints;
	}

	BitField result(result_bitfield_size);

	if (used_bits > obj2.used_bits)
	{
		result.used_bits = used_bits;
	}
	else
	{
		result.used_bits = obj2.used_bits;
	}

	for (int i = 0; i < smaller_bitfield_size; i++)
	{
		result.bitarray[i] = (bitarray[i] & obj2.bitarray[i]);
	}

	return result;
}

BitField BitField::operator |(const BitField& obj2)
{
	unsigned int result_bitfield_size;
	int smaller_bitfield_size;

	if (reserved_ints >= obj2.reserved_ints)
	{
		result_bitfield_size = reserved_ints;
		smaller_bitfield_size = obj2.reserved_ints;
	}
	else
	{
		result_bitfield_size = obj2.reserved_ints;
		smaller_bitfield_size = reserved_ints;
	}

	BitField result(result_bitfield_size);

	if (used_bits > obj2.used_bits)
	{
		result.used_bits = used_bits;
	}
	else
	{
		result.used_bits = obj2.used_bits;
	}

	for (int i = 0; i < smaller_bitfield_size; i++)
	{
		result.bitarray[i] = (bitarray[i] | obj2.bitarray[i]);
	}

	if (smaller_bitfield_size == reserved_ints)
	{
		for (unsigned int i = smaller_bitfield_size; i < obj2.reserved_ints; i++)
		{
			result.bitarray[i] = obj2.bitarray[i];
		}
	}
	else if (smaller_bitfield_size == obj2.reserved_ints)
	{
		for (unsigned int i = smaller_bitfield_size; i < reserved_ints; i++)
		{
			result.bitarray[i] = bitarray[i];
		}
	}

	return result;
}

void BitField::ChangeSize(unsigned int size)
{
	unsigned int int_size = ((size >> 5) + 1);

	if (reserved_ints < int_size)
	{
		BitField temp = *this;

		bitarray = new unsigned int[int_size];
		used_bits = size;
		reserved_ints = int_size;

		for (unsigned int i = 0; i < ((temp.used_bits >> 5) + 1); i++)
		{
			bitarray[i] = temp.bitarray[i];
		}

		for (unsigned int i = ((temp.used_bits >> 5) + 1); i < reserved_ints; i++)
		{
			bitarray[i] = 0;
		}
	}
}