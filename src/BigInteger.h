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
#include <cstddef>


class [[ nodiscard ]] BigInteger
{
public:
    BigInteger() = default;
    BigInteger(const BigInteger& rhs) = default;
    template <std::integral T>
    BigInteger(const T& num);
    BigInteger(std::string_view num);


    BigInteger& operator=(const BigInteger& rhs) = default;
    template <std::integral T>
    BigInteger& operator=(const T& num);
    BigInteger& operator=(std::string_view num);

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

    unsigned operator[](const std::size_t pos) const;
    unsigned at(const std::size_t pos) const;

    std::size_t digit_count() const;
    std::string to_string() const;

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
    std::string m_value { "0" };
    bool m_sign { false };
};

#endif
