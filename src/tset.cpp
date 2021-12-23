
#include "tset.h"
#include <algorithm>

TSet::TSet(int mp) :BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet& s) :BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) :BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField() {
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return 0;
	if (Elem < 0)
		throw runtime_error("IsMember: negative index is forbidden");
	if (Elem >= MaxPower)
		throw runtime_error("IsMember: too large index is forbidden");

	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if (Elem < 0)
		throw runtime_error("InsElem: negative index is forbidden");
	if (Elem >= MaxPower)
		throw runtime_error("InsElem: too large index is forbidden");

	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < 0)
		throw runtime_error("DelElem: negative index is forbidden");
	if (Elem >= MaxPower)
		throw runtime_error("DelElem: too large index is forbidden");

	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
	BitField = s.BitField;
	MaxPower = s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
	return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
	return !(*this == s);
}

TSet TSet::operator+(const TSet& s) // объединение
{
	TSet tField(std::max(MaxPower, s.MaxPower));
	tField.BitField = BitField | s.BitField;
	return tField;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem < 0 || Elem >= MaxPower) throw invalid_argument("incorrect element");
	TBitField temp(*this);
	temp.SetBit(Elem);
	return temp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem < 0 || Elem >= MaxPower) throw invalid_argument("incorrect element");
	TBitField temp(*this);
	temp.ClrBit(Elem);
	return temp;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
	TSet tField(max(s.MaxPower, MaxPower));
	tField.BitField = BitField & s.BitField;
	return tField;
}

TSet TSet::operator~(void) // дополнение
{
	TSet tField(MaxPower);
	tField.BitField = ~BitField;
	return tField;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
	int t;
	char sett;

	do
	{
		istr >> sett;
	} while (sett != '{');

	do {
		istr >> t;
		s.InsElem(t);

		do
		{
			istr >> sett;
		} while ((sett != '}') && (sett != ','));


	} while (sett != '}');

	return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
	char sett = '{';

	for (int i = 0; i < s.MaxPower; i++)
	{
		if (s.IsMember(i))
		{
			ostr << sett << i;
			sett = ',';
		}
	}

	ostr << "}";

	return ostr;
}