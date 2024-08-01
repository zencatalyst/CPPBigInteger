////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//                        A Class for Big Integers                            //
//                                                                            //
//                  Masoud Aghdasifam - www.algorithmha.ir                    //
//                                                                            //
////////////////////////////////////////////////////////////////////////////////

#ifndef BIGINTEGER_H
#define BIGINTEGER_H

#include <string>
#include <istream>
#include <ostream>


class [[ nodiscard ]] BigInteger
{
public:
    BigInteger();
    BigInteger(long long);
    BigInteger(std::string);
    BigInteger(const BigInteger &);
    ~BigInteger();

    bool isValid();
    unsigned length();
    std::string toString();

    int operator[](unsigned) const;

    BigInteger operator=(long long);
    BigInteger operator=(std::string);
    BigInteger operator=(const BigInteger &);

    BigInteger operator+(long long) const;
    BigInteger operator+(std::string) const;
    BigInteger operator+(const BigInteger &) const;
    BigInteger operator+() const;

    BigInteger operator+=(long long);
    BigInteger operator+=(std::string);
    BigInteger operator+=(const BigInteger &);

    BigInteger operator-(long long) const;
    BigInteger operator-(std::string) const;
    BigInteger operator-(const BigInteger &) const;
    BigInteger operator-() const;

    BigInteger operator-=(long long);
    BigInteger operator-=(std::string);
    BigInteger operator-=(const BigInteger &);

    BigInteger operator*(long long) const;
    BigInteger operator*(std::string) const;
    BigInteger operator*(const BigInteger &) const;

    BigInteger operator*=(long long);
    BigInteger operator*=(std::string);
    BigInteger operator*=(const BigInteger &);

    BigInteger operator/(long long) const;
    BigInteger operator/(std::string) const;
    BigInteger operator/(const BigInteger &) const;

    BigInteger operator/=(long long);
    BigInteger operator/=(std::string);
    BigInteger operator/=(const BigInteger &);

    BigInteger operator%(long long) const;
    BigInteger operator%(std::string) const;
    BigInteger operator%(const BigInteger &) const;

    BigInteger operator%=(long long);
    BigInteger operator%=(std::string);
    BigInteger operator%=(const BigInteger &);

    BigInteger operator^(long long) const;
    BigInteger operator^(std::string) const;
    BigInteger operator^(const BigInteger &) const;

    BigInteger operator^=(long long);
    BigInteger operator^=(std::string);
    BigInteger operator^=(const BigInteger &);

    BigInteger operator++();
    BigInteger operator++(int);

    BigInteger operator--();
    BigInteger operator--(int);

    bool operator==(long long) const;
    bool operator==(std::string) const;
    bool operator==(const BigInteger &) const;

    bool operator!=(long long) const;
    bool operator!=(std::string) const;
    bool operator!=(const BigInteger &) const;

    bool operator<(long long) const;
    bool operator<(std::string) const;
    bool operator<(const BigInteger &) const;

    bool operator>(long long) const;
    bool operator>(std::string) const;
    bool operator>(const BigInteger &) const;

    bool operator<=(long long) const;
    bool operator<=(std::string) const;
    bool operator<=(const BigInteger &) const;

    bool operator>=(long long) const;
    bool operator>=(std::string) const;
    bool operator>=(const BigInteger &) const;

    friend BigInteger BigAbs(const BigInteger &);

    friend BigInteger operator+(long long, const BigInteger &);
    friend BigInteger operator+(std::string, const BigInteger &);

    friend BigInteger operator-(long long, const BigInteger &);
    friend BigInteger operator-(std::string, const BigInteger &);

    friend BigInteger operator*(long long, const BigInteger &);
    friend BigInteger operator*(std::string, const BigInteger &);

    friend BigInteger operator/(long long, const BigInteger &);
    friend BigInteger operator/(std::string, const BigInteger &);

    friend BigInteger operator%(long long, const BigInteger &);
    friend BigInteger operator%(std::string, const BigInteger &);

    friend BigInteger operator^(long long, const BigInteger &);
    friend BigInteger operator^(std::string, const BigInteger &);

    friend bool operator==(long long, const BigInteger &);
    friend bool operator==(std::string, const BigInteger &);

    friend bool operator!=(long long, const BigInteger &);
    friend bool operator!=(std::string, const BigInteger &);

    friend bool operator<(long long, const BigInteger &);
    friend bool operator<(std::string, const BigInteger &);

    friend bool operator>(long long, const BigInteger &);
    friend bool operator>(std::string, const BigInteger &);

    friend bool operator<=(long long, const BigInteger &);
    friend bool operator<=(std::string, const BigInteger &);

    friend bool operator>=(long long, const BigInteger &);
    friend bool operator>=(std::string, const BigInteger &);

    friend std::ostream& operator<<(std::ostream &, const BigInteger &);
    friend std::istream& operator>>(std::istream &, BigInteger &);

private:
    void reverse(std::string &);

private:
    char *data;
    unsigned size;
    bool sign;
};

#endif
