#ifndef _BIGINT_H
#define _BIGINT_H

#include <iostream> /// para ostream e istream
#include <cstdint> /// para int8_t
#include <string> /// para string





class BigInt
{
private:
    bool neg;
    int nDig;
    std::int8_t * d;

    BigInt(bool IsNeg, int Size); /// construtor privado
    void correct(); /// metodo privado correct
    void increment(); /// metodo privado increment
    void decrement(); /// metodo privado decrement



public:
    BigInt(); /// construtor default
    ~BigInt(); /// destutor


    BigInt(const BigInt& B); /// constutor por copia
    BigInt(BigInt && B) noexcept; /// construtor por movimento
    BigInt(long long int N); /// construtor long long int que tambem eh conversor para bigInt
    explicit BigInt(const std::string& S); /// construtor string nao conversor de tipo

    BigInt& operator=(const BigInt& B); /// operador de atribuicao por copia
    BigInt& operator=(BigInt&& B) noexcept; /// operador de atribuicao por movimento

   inline bool isNeg() const {return neg;} /// funcao de consulta de neg
   inline int size() const {return nDig;} /// funcao de consulta de nDIg
   inline bool isZero() const {return (this ->nDig == 1 && this->d[0] == 0);} /// funcao de consulta para 0

   int operator[](int i) const; ///operador []

   long long int toInt() const;  /// metodo toInt

   friend std::ostream& operator << (std::ostream &X, const BigInt &B); ///funcao classica operator<<
   friend std::istream& operator >> (std::istream &I,  BigInt &B); /// funcao classica operator >>
   friend BigInt abs(const BigInt& B);
   bool operator==(const BigInt & B) const; ///operador ==
   inline bool operator!=(const BigInt & B) const {return !(*this == B);} /// operador != ou !(==)
   bool operator<(const BigInt & B) const; /// operador <
   inline bool operator>(const BigInt & B) const {return B < *this;} /// operador >
   inline bool operator>=(const BigInt &B) const {return !(*this < B);} /// operador >=
   inline bool operator <=(const BigInt &B) const {return !(B < *this);} /// operador <=
   BigInt& operator++(); ///operador de incremento pre-fixado
   BigInt& operator--(); ///operador de decremento pre-fixado
   BigInt operator++(int);///operador de incremento pos-fixado
   BigInt operator--(int); ///operador de decremento pos-fixado
   inline const BigInt& operator+() const {return *this;}  /// operador + unario
   BigInt operator-()const; /// operador - unario
   BigInt operator+(const BigInt& B) const; /// operador + binario
   BigInt operator-(const BigInt& B) const {return (*this)+(-B);} /// operador - binario


   BigInt operator*(const BigInt& B) const; /// operador *
   BigInt operator!() const; /// operador !
   BigInt operator<<(int N) const; /// operador << (deslocamento esquerda)
   BigInt operator>>(int N) const; /// operador >> (deslocamento direita)
   void division(const BigInt& D, BigInt& Q,  BigInt& R) const; /// metodo publico division
   BigInt operator/(const BigInt& B) const; /// operador / quociente
   BigInt operator%(const BigInt& B) const; /// operador % resto da divisao

};


#endif // _BIGINT_H
