#include <iostream>
#include <cmath>
#include <cctype>
#include "bigint.h"

using namespace std;


BigInt :: BigInt(): neg(false), nDig(1), d( new int8_t[1]{0}){} ///construtor default

BigInt :: ~BigInt() /// Destrutor
{
    delete [] this->d;
}

BigInt :: BigInt(bool IsNeg, int Size): neg(IsNeg), nDig(0), d(nullptr) ///construtor privado
{
   if(Size >= 0) this->nDig = Size;

   if(this->nDig > 0)
   {
       this->d = new int8_t[this->nDig]{0};
   }
}

BigInt :: BigInt(const BigInt& B): neg(B.neg), nDig(B.nDig), d(new int8_t[this->nDig]) ///construtor por c�pia
{

   for(int i = 0; i<this->nDig; ++i) this->d[i] = B.d[i];
}

BigInt :: BigInt(BigInt&& B) noexcept: neg(B.neg), nDig(B.nDig), d(B.d)  ///construtor por movimento
{
    B.nDig = 0;
    B.d = nullptr;
}

BigInt& BigInt :: operator=(const BigInt& B) ///operador de atribuicao por copia
{
    if(this == &B) return *this;

    delete[] this->d;
    this ->neg = B.neg;
    this ->nDig = B.nDig;
    if(this->nDig > 0) this->d = new int8_t[this->nDig];
    else this->d = nullptr;
    for(int i = 0; i<this->nDig; i++)
        this->d[i] = B.d[i];

    return *this;

}

BigInt& BigInt :: operator=(BigInt && B) noexcept ///operador de atribuicao por movimento
{
    delete[] this->d;

    this->neg = B.neg;
    this->nDig = B.nDig;
    this->d = B.d;

    B.neg = false;
    B.nDig = 0;
    B.d = nullptr;

    return *this;
}

int BigInt :: operator[](int i) const /// operador []
{
    if(i < 0 || i >= nDig) return 0;

    return static_cast<int8_t>(this->d[i]);
}

BigInt :: BigInt(long long int N): BigInt(N<0, N == 0 ? 1: 1 + int(log10(fabs(N))))    ///construtor para long long int e conversor para bigInt
{
    for(int i = 0; i < this->size(); ++i)
    {
         this->d[i] =  fabs(N % 10);
         N /= 10;
    }
}

void BigInt :: correct() ///funcao privada correct
{
    if(this->size() <= 0 || this->d == nullptr)
        {
            *this = BigInt();
            return;
        }

        int newSize(this->size());

        while(newSize > 1 && this->d[newSize-1] == 0) --newSize;

        if(newSize != size())
        {
            BigInt prov(this->isNeg(),newSize);

            for(int i = 0; i<newSize; ++i) prov.d[i] = this->d[i];

            *this = move(prov);

        }

        if(size()==1)
        {
            if(this->d[0]<0)
            {
                this->neg = !(this->neg);
                this->d[0] = abs(this->d[0]);
            }

            if(this->d[0] == 0) this->neg = false;
        }

}

BigInt :: BigInt(const string& S) : neg(false), nDig(0), d(nullptr)  /// construtor string que nao eh conversor
{
    BigInt prov = BigInt();
    if(S.empty())
    {
        *this = prov;
        cerr << "\nErro: string vazia nao pode ser convertida em BigInt" << endl;
        return;
    }

    int ini(0);

    bool IsNeg = false;

    if(S[0] == '+' || S[0] == '-')
    {
        if(S.size() == 1)
        {
            *this = BigInt();
            cerr << "\nErro: apenas sinal '+' ou '-' sem digitos nao e valido para BigInt" << endl;
            return;
        }

        IsNeg = (S[0] == '-');
        ini = 1;
    }

    prov = BigInt(IsNeg, S.size()-ini);


    for(int i = 0; i<prov.size(); ++i)
    {
        char c = S[S.size()-1-i];
        if(!(isdigit(c)))
        {
            *this = BigInt();
            cerr << "\nErro: caractere invalido encontrado na string para BigInt" << endl;
            return;
        }

        prov.d[i] = static_cast<int8_t>(c -'0');
    }

    prov.correct();

    *this = move(prov);
}

long long int BigInt :: toInt() const
{
    long long int val(0);

    for(int i = this->size() - 1; i>=0; --i)
    {
        val = 10*val + this->d[i];
        if(val < 0)
        {
            cerr << "\nErro: execedeu a capacidade de um long long int" << endl;
            return 0;
        }

    }

    if(this->isNeg()) val = -val;

    return val;

}

ostream& operator<<(ostream &X, const BigInt &B)  /// operador <<
{
    if(B.isNeg()) X << "-";

    for(int i = B.size()-1; i>=0; i--) X << B[i];

    return X;
}

istream& operator >>(istream &I, BigInt &B) /// operador >>
{

    B = BigInt(false, 0);

    istream::sentry s(I);

    if(s)
    {
        char c = I.peek();

        if(c == '+' || c == '-')
        {
            c = I.get();
            B.neg = (c == '-');
            c = I.peek();

        }

        while(isdigit(c))
        {
            c = I.get();
            BigInt prov = BigInt(B.isNeg(), B.size()+1);

            for(int i = 0; i < B.size(); ++i) prov.d[i+1] = B[i];

            prov.d[0] = static_cast<int8_t>(c-'0');

            B = move(prov);

            c = I.peek();
        }

        if(B.size() == 0) I.setstate(ios::failbit);

    }

    B.correct();

    return I;
}

BigInt abs( const BigInt &B) /// funcao classica abs
{
    BigInt result = B;
    result.neg = false;
    return result;
}

bool BigInt::operator==(const BigInt &B) const ///operador ==
{
    if (this->neg != B.neg || this->nDig != B.nDig) return false;
    for (int i = 0; i < this->nDig; ++i)
        if (this->d[i] != B.d[i]) return false;
    return true;
}

bool BigInt::operator<(const BigInt &B) const /// operador <
{

    if (this->neg != B.neg)
        return this->neg;

    if (this->neg)
        return abs(B) < abs(*this);

    if (this->nDig != B.nDig)
        return this->nDig < B.nDig;

    for (int i = this->nDig - 1; i >= 0; --i) {
        if (this->d[i] != B.d[i])
            return this->d[i] < B.d[i];
    }

    return false;
}

void BigInt::increment()  /// metodo privado increment
{
    int k(0);
    this->d[k] += 1;

    while (k < this->size() - 1 && this->d[k] > 9)
    {
        this->d[k] = 0;
        k++;
        this->d[k] += 1;
    }

    if (k == this->size() - 1 && this->d[k] > 9)
        {

        BigInt prov(this->isNeg(), this->size()+1);

        for (int i = 0; i < this->size(); ++i) prov.d[i] = d[i];

        prov.d[size() - 1] = 0;
        prov.d[size()] = 1;
        *this = move(prov);
    }
}

void BigInt::decrement() /// metodo privado decrement
 {
    int k (0);
    this->d[k] -= 1;


    while (k < this->size() - 1 && this->d[k] < 0)
    {
        this->d[k] = 9;
        k++;
        this->d[k] -= 1;
    }

    this->correct();
}

 BigInt& BigInt::operator++() /// operador de incremento pre-fixado
 {
     if(!(this->isNeg())) this->increment();
     else this->decrement();
     return *this;

 }

 BigInt& BigInt::operator--() /// operador de decremento pre-fixado
 {
     if(this->isNeg()) this->increment();
     else this->decrement();
     return *this;
 }

 BigInt BigInt::operator++(int) /// operador de icremento pos-fixado
 {
     BigInt prov(*this);
     ++(*this);
     return prov;
 }

 BigInt BigInt :: operator--(int) /// operador de decremento pre-fixado
 {
     BigInt prov(*this);
     --(*this);
     return prov;
 }

BigInt BigInt :: operator-() const /// operador - unario
{
    if(this->isZero()) return *this;
    BigInt prov(*this);
    prov.neg = !(this->isNeg());
    return prov;
}

BigInt BigInt::operator+(const BigInt& B) const /// operador + binario
{

     if(this->isNeg() == B.isNeg())
     {
         BigInt C(this->neg, 1+max(this->size(),B.size()));
         int carry(0);

       for(int i = 0; i < C.size(); ++i)
        {

            C.d[i] = operator[](i) + B[i] + carry;

            if(C.d[i] > 9)
            {
                C.d[i] -= 10;
                carry = 1;
            }
            else carry = 0;
            }
        C.correct();
        return C;
     }

     if(abs(*this)>= abs(B))
     {
         BigInt C(this->neg, this->size());
         int borrow(0);
       for(int i = 0; i < C.size(); ++i)
      {

        C.d[i] = operator[](i) - B[i] - borrow;

        if(C.d[i] < 0)
        {
            C.d[i] += 10;
            borrow = 1;
        }
        else borrow = 0;
      }
         C.correct();
         return C;
     }
     else return  B+(*this);


}

BigInt BigInt::operator*(const BigInt& B) const /// operador *
{
    if(this->isZero() || B.isZero()) return BigInt();
    BigInt C(this->neg != B.neg, this->size() + B.size());
    for(int i = 0; i < this->size(); ++i)
    {
        if(this->d[i] == 0) continue;
        for(int j = 0; j < B.size(); ++j)
        {
            if(B.d[j] == 0) continue;
            int k = i + j;
            C.d[k] += this->d[i] * B.d[j];
            while(C.d[k] > 9)
            {
                int carry = C.d[k] / 10;
                C.d[k] %= 10;
                k++;
                C.d[k] += carry;
            }
        }
    }
    C.correct();
    return C;
}

BigInt BigInt::operator!() const /// operador !(fatorial)
{
    if (this->isNeg()) {
        cerr << "\nErro: fatorial de numero negativo." << endl;
        return BigInt(0);
    }

    if (this->isZero() || *this == BigInt(1)) return BigInt(1);

    BigInt C(1);
    for (BigInt N(2); N <= *this; ++N) {
        C = C * N;
    }
    return C;
}

BigInt BigInt::operator<<(int N) const /// Deslocamento a esquerda
{
    if(N<=0 || this->isZero()) return *this;

    BigInt C(this->isNeg(), this->size() + N);


    for(int i = N; i<C.size(); ++i)
    {
        C.d[i] = this->d[i-N];
    }

    return C ;
}

BigInt BigInt:: operator>>(int N) const /// Deslocamento a direita
{
    if(N<=0 || this->isZero()) return *this;
    if(N>=this->size()) return BigInt();

    BigInt C(this->isNeg(), this->size()-N);
    for(int i = 0; i<C.size(); ++i)
        C.d[i] = this->d[i+N];


    return C;
}

void BigInt :: division(const BigInt& D, BigInt& Q, BigInt& R) const /// Metodo division
{
   Q = BigInt();

   if(this->isZero() || D.isZero())
   {
       if(D.isZero())
        cerr << "\nErro: divisao por zero." << endl;

       R = BigInt();
       Q = BigInt();
       return;
   }

   if(abs(*this) < abs(D))
   {
       R = *this;
       return;
   }

   R = BigInt();

   for(int i = this->size()-1; i>=0; --i)
   {
       if(!(R.isZero())) R = R<<1;

       R.d[0] = this->d[i];

       int8_t div = 0;
       while(R >= abs(D))
       {
           R = R - abs(D);
           div = div + 1;

       }

       if(!(Q.isZero())) Q = Q<<1;
       Q.d[0] = div;
   }

   Q.neg = (this->isNeg() != D.isNeg());

   if(!(R.isZero())) R.neg = this->isNeg();

}

BigInt BigInt:: operator/(const BigInt& B) const /// operador /
{
   BigInt Q, R;
   this->division(B, Q,R);
   return Q;
}

BigInt BigInt :: operator%(const BigInt& B) const /// operador %
{
    BigInt Q, R;
    this->division(B, Q, R);
    return R;
}










