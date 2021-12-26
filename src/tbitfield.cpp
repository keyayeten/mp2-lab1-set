
#include "tbitfield.h"
#include <algorithm>
#include <bitset>

TBitField::TBitField(int len)
{
	if (len < 0) throw invalid_argument("negative bitfield length");
	BitLen = len;
	MemLen = (len + 8 * sizeof(TELEM) - 1) / (8 * sizeof(TELEM));
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	pMem = new TELEM[bf.MemLen];
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	for (int i = 0; i < bf.MemLen; ++i)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete[] pMem;
	pMem = nullptr;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= BitLen || n < 0)
		throw 0;
	else
		return n / (sizeof(TELEM) * 8);
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n >= BitLen)
		throw "Wrong position of bit n";
	return 1 << (n % (sizeof(TELEM) * 8));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0 || n >= BitLen)
	{
		throw "Out of bounds(SetBit)";
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	pMem[GetMemIndex(n)] |= GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= BitLen || n < 0)
		throw 0;
	int k = GetMemIndex(n);

	TELEM mask = GetMemMask(n);
	return (pMem[k] & mask) > 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	if (pMem != bf.pMem) {
		delete[] pMem;
		TELEM* newMem = new TELEM[bf.MemLen];
		for (int i = 0; i < MemLen; i++) {
			newMem[i] = bf.pMem[i];
		}
		this->pMem = newMem;

		this->MemLen = bf.MemLen;
		this->BitLen = bf.BitLen;
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; ++i)
			if (pMem[i] != bf.pMem[i])
				return 0;
		return 1;
	}
	return 0;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	if (*this == bf)
		return 0;
	else
		return 1;
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	TBitField tField(BitLen > bf.BitLen ? *this : bf);
	for (int i = 0; i < min(this->MemLen, bf.MemLen); i++) {
		tField.pMem[i] = this->pMem[i] | bf.pMem[i];
	}
	return tField;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	TBitField tField(BitLen > bf.BitLen ? *this : bf);
	for (int i = 0; i < min(this->MemLen, bf.MemLen); i++) {
		tField.pMem[i] = this->pMem[i] & bf.pMem[i];
	}
	return tField;
}

TBitField TBitField::operator~(void) // отрицание
{
	int BitSize = sizeof(TELEM) * 8;
	for (int i = 0; i < MemLen; ++i)
		pMem[i] = ~pMem[i];
	pMem[MemLen - 1] = (pMem[MemLen - 1] << BitSize - (BitLen % BitSize)) >> BitSize - (BitLen % BitSize);
	return *this;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
	int i = 0;
	char ch;

	do
	{
		istr >> ch;
		if (ch == '1')
		{
			bf.SetBit(i++);
		}
		else if (ch == '0')
		{
			bf.ClrBit(i++);
		}
		else break;
	} while ((ch == '1') || (ch == '0'));
	return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
	for (int i = 0; i < bf.BitLen; i++)
	{
		ostr << bf.GetBit(i);
	}
	return ostr;
}