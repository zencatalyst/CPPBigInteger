
#include "BigInteger.h"
#include <string>
#include <vector>
#include <istream>
#include <ostream>
#include <sstream>
#include <stdexcept>
#include <cstddef>


template <std::integral T>
BigInteger::BigInteger(const T& num)
: m_value { std::to_string( std::abs( num ) ) },
  m_sign { std::cmp_less( num, std::uintmax_t { 0 } ) ? true : false }
{
}

BigInteger::BigInteger(std::string_view num)
{
    if ( num.front() == '+' || num.front() == '-' )
    {
        m_sign = (num.front() == '-') ? true : false;
        num.remove_prefix(1);
    }

    const auto is_non_digit { [ ]( const char c )
                              { return !std::isdigit( c, std::locale::classic( ) ); } };

    if (const auto result { std::ranges::find_if(num, is_non_digit) }; result != std::cend(num))
        throw std::invalid_argument("Invalid string: contains non-digit characters");

    m_value = num;
}

template <std::integral T>
BigInteger& BigInteger::operator=(const T& num)
{
    m_value = std::to_string( std::abs( num ) );
    m_sign = std::cmp_less( num, std::uintmax_t { 0 } ) ? true : false;

    return *this;
}

BigInteger& BigInteger::operator=(std::string_view num)
{
    if ( num.front() == '+' || num.front() == '-' )
    {
        m_sign = (num.front() == '-') ? true : false;
        num.remove_prefix(1);
    }

    const auto is_non_digit { [ ]( const char c )
                              { return !std::isdigit( c, std::locale::classic( ) ); } };

    if (const auto result { std::ranges::find_if(num, is_non_digit) }; result != std::cend(num))
        throw std::invalid_argument("Invalid string: contains non-digit characters");

    m_value = num;

    return *this;
}

BigInteger BigInteger::operator+(long long r) const
{
    BigInteger f = BigInteger(r);
    return *this + f;
}

BigInteger BigInteger:: operator+(std::string r) const
{
    return *this + BigInteger(r);
}

BigInteger BigInteger::operator+(const BigInteger &r) const
{
    BigInteger temp;
    if (!this->data || !r.data)
    {
        return temp;
    }
    if (this->sign && !r.size)
    {
        temp = -*this;
        return r - temp;
    }
    if (!this->sign && r.sign)
    {
        temp = -r;
        return *this - temp;
    }
    unsigned maxsize = this->size > r.size ? this->size : r.size;
    unsigned minsize = this->size > r.size ? r.size : this->size;
    unsigned c = 0;
    std::vector<char> v;
    for (unsigned i = 0; i < minsize; i++)
    {
        v.push_back(((r.data[i] - '0') + (this->data[i] - '0') + c) % 10 + '0');
        c = ((r.data[i] - '0') +(this->data[i] - '0') + c) / 10;
    }
    if (this->size == maxsize)
    {
        for(unsigned i = minsize; i < maxsize; i++)
        {
            v.push_back(((this->data[i] - '0') + c) % 10 + '0');
            c = ((this->data[i] - '0') + c) / 10;
        }
    }
    else
    {
        for (unsigned i = minsize; i < maxsize; i++)
        {
            v.push_back(((r.data[i] - '0') + c) % 10 + '0');
            c = ((r.data[i] - '0') + c) / 10;
        }
    }
    if (c)
    {
        v.push_back(c + '0');
    }
    temp.data = new char[v.size()];
    if (temp.data)
    {
        temp.size = v.size();
        for(unsigned i = 0; i < temp.size; i++)
        {
            temp.data[i] = v[i];
        }
        temp.sign = this->sign;
    }
    return temp;
}

BigInteger BigInteger::operator+() const
{
    return *this;
}

template <std::integral T>
BigInteger& BigInteger::operator+=(const T& num)
{
    *this = *this + r;
    return *this;
}

BigInteger BigInteger::operator+=(std::string r)
{
    *this = *this + r;
    return *this;
}

BigInteger BigInteger::operator+=(const BigInteger &r)
{
    *this = *this + r;
    return *this;
}

BigInteger BigInteger::operator-(long long r) const
{
    return *this - BigInteger(r);
}

BigInteger BigInteger::operator-(std::string r) const
{
    return *this - BigInteger(r);
}

BigInteger BigInteger::operator-(const BigInteger &r) const
{
    BigInteger temp;
    if(!this->data || !r.data)
    {
        return temp;
    }
    if(sign && !r.sign)
    {
        temp =(-*this + r);
        temp.sign = !temp.sign;
        return temp;
    }
    if(!sign && r.sign)
    {
        temp = r;
        temp.sign = !temp.sign;
        return *this + temp;
    }
    if(*this < r)
    {
        temp = r - *this;
        temp.sign = !temp.sign;
        return temp;
    }
    BigInteger t1, t2;
    if(this->sign)
    {
        t1 = r;
        t2 = *this;
    }
    else
    {
        t1 = *this;
        t2 = r;
    }
    temp.sign = false;
    std::vector<char> result(t1.size);
    for(unsigned i = 0; i < t2.size; i++)
    {
        if(t1.data[i] < t2.data[i])
        {
            t1.data[i] += 10;
            t1.data[i + 1]--;
        }
        result[i] += t1.data[i] - t2.data[i];
    }
    for(unsigned i = t2.size; i < t1.size; i++)
    {
        if(t1.data[i] < 0)
        {
            t1.data[i] += 10;
            t1.data[i + 1]--;
        }
        result[i] += t1.data[i] - '0';
    }
    unsigned i;
    for(i = 0; i < t1.size; i++)
    {
        if(result[t1.size - i - 1] != 0)
        {
            break;
        }
    }
    temp.data = new char[t1.size - i];
    if(temp.data)
    {
        temp.size = t1.size - i;
        for(unsigned j = 0; j < temp.size; j++)
        {
            temp.data[j] = result[j] + '0';
        }
    }
    return temp;
}

BigInteger BigInteger::operator-() const
{
    BigInteger temp = *this;
    temp.sign = !temp.sign;
    return temp;
}

BigInteger BigInteger::operator-=(long long r)
{
    *this = *this - r;
    return *this;
}

BigInteger BigInteger::operator-=(std::string r)
{
    *this = *this - r;
    return *this;
}

BigInteger BigInteger::operator-=(const BigInteger &r)
{
    *this = *this - r;
    return *this;
}

BigInteger BigInteger::operator*(long long r) const
{
    return *this * BigInteger(r);
}

BigInteger BigInteger::operator*(std::string r) const
{
    return *this * BigInteger(r);
}

BigInteger BigInteger::operator*(const BigInteger &r) const
{
    BigInteger temp;
    if(!this->data || !r.data)
    {
        return temp;
    }
    if(*this == "0" || r == "0")
    {
        temp.data = new char[1];
        if(temp.data)
        {
            temp.size = 1;
            temp.sign = false;
            temp.data[0] = '0';
            return temp;
        }
    }
    std::vector< unsigned > v(this->size + r.size);
    unsigned i, j, t, c;
    for(i = 0; i < this->size; i++)
    {
        c = 0;
        for(j = 0; j < r.size; j++)
        {
            t = v[i + j];
            v[i + j] =(t + c +(this->data[i] - '0') *(r.data[j] - '0')) % 10;
            c =(t + c +(this->data[i] - '0') *(r.data[j] - '0')) / 10;
        }
        if(c)
        {
            v[i + j] = c;
        }
    }
    for(i = 0; i < v.size(); i++)
    {
        if(v[v.size() - i - 1] != 0)
        {
            break;
        }
    }
    temp.data = new char[v.size()];
    if(temp.data)
    {
        temp.size = v.size() - i;
        temp.sign =(sign && !r.sign) ||(!sign && r.sign);
        for(j = 0; j < temp.size; j++)
        {
            temp.data[j] = v[j] + '0';
        }
    }
    return temp;
}

BigInteger BigInteger::operator*=(long long r)
{
    *this = *this * r;
    return *this;
}

BigInteger BigInteger::operator*=(std::string r)
{
    *this = *this * r;
    return *this;
}

BigInteger BigInteger::operator*=(const BigInteger &r)
{
    *this = *this * r;
    return *this;
}

BigInteger BigInteger::operator/(long long r) const
{
    return *this / BigInteger(r);
}

BigInteger BigInteger::operator/(std::string r) const
{
    return *this / BigInteger(r);
}

BigInteger BigInteger::operator/(const BigInteger &r) const
{
    BigInteger result;
    if(!this->data || !r.data || r == "0")
    {
        return result;
    }
    if(this->size < r.size)
    {
        result = "0";
        return result;
    }
    std::vector<unsigned> temp;
    std::vector<char> rem;
    unsigned i, j, c;
    bool t;
    for(i = 0; i < this->size; i++)
    {
        rem.push_back(this->data[i]);
    }
    for(i = 0; i <= this->size - r.size; i++)
    {
        c = 0;
        t = true;
        while(t)
        {
            if(i == 0)
            {
                for(j = 0; j < r.size && t; j++)
                {
                    if(rem[this->size - i - j - 1] < r.data[r.size - j - 1])
                    {
                        t = false;
                    }
                    if(rem[this->size - i - j - 1] > r.data[r.size - j - 1])
                    {
                        break;
                    }
                }
            }
            else if(rem[this->size - i] == '0')
            {
                for(j = 0; j < r.size && t; j++)
                {
                    if(rem[this->size - i - j - 1] < r.data[r.size - j - 1])
                    {
                        t = false;
                    }
                    if(rem[this->size - i - j - 1] > r.data[r.size - j - 1])
                    {
                        break;
                    }
                }
            }
            if(t)
            {
                for(j = 0; j < r.size; j++)
                {
                    if(rem[this->size - r.size - i + j] < r.data[j])
                    {
                        rem[this->size - r.size - i + j] += 10;
                        rem[this->size - r.size - i + j + 1]--;
                    }
                    rem[this->size - r.size - i + j] -=(r.data[j] - '0');
                }
                c++;
            }
        }
        temp.push_back(c);
    }
    for(i = 0; i < temp.size(); i++)
    {
        if(temp[i] != 0)
        {
            break;
        }
    }
    if(i == temp.size())
    {
        result = "0";
    }
    else
    {
        result.data = new char[temp.size() - i];
        if(result.data)
        {
            result.size = temp.size() - i;
            result.sign = false;
            for(j = 0; j < result.size; j++)
            {
                result.data[result.size - j - 1] = temp[j + i] + '0';
            }
        }
    }
    if(this->sign && !r.sign)
    {
        result = result + 1;
        result.sign = true;
    }
    else if(!this->sign && r.sign)
    {
        result.sign = true;
    }
    else if(this->sign && r.sign)
    {
        result = result + 1;
    }
    return result;
}

BigInteger BigInteger::operator/=(long long r)
{
    *this = *this / r;
    return *this;
}

BigInteger BigInteger::operator/=(std::string r)
{
    *this = *this - r;
    return *this;
}

BigInteger BigInteger::operator/=(const BigInteger &r)
{
    *this = *this / r;
    return *this;
}

BigInteger BigInteger::operator%(long long r) const
{
    return *this % BigInteger(r);
}

BigInteger BigInteger::operator%(std::string r) const
{
    return *this % BigInteger(r);
}

BigInteger BigInteger::operator%(const BigInteger &r) const
{
    BigInteger result;
    if(!this->data || !r.data || r == "0")
    {
        return result;
    }
    if(this->size < r.size)
    {
        return *this;
    }
    std::vector< char > rem;
    unsigned i, j, c;
    bool t;
    for(i = 0; i < this->size; i++)
    {
        rem.push_back(this->data[i]);
    }
    for(i = 0; i <= this->size - r.size; i++)
    {
        c = 0;
        t = true;
        while(t)
        {
            if(i == 0)
            {
                for(j = 0; j < r.size && t; j++)
                {
                    if(rem[this->size - i - j - 1] < r.data[r.size - j - 1])
                    {
                        t = false;
                    }
                    if(rem[this->size - i - j - 1] > r.data[r.size - j - 1])
                    {
                        break;
                    }
                }
            }
            else if(rem[this->size - i] == '0')
            {
                for(j = 0; j < r.size && t; j++)
                {
                    if(rem[this->size - i - j - 1] < r.data[r.size - j - 1])
                    {
                        t = false;
                    }
                    if(rem[this->size - i - j - 1] > r.data[r.size - j - 1])
                    {
                        break;
                    }
                }
            }
            if(t)
            {
                for(j = 0; j < r.size; j++)
                {
                    if(rem[this->size - r.size - i + j] < r.data[j])
                    {
                        rem[this->size - r.size - i + j] += 10;
                        rem[this->size - r.size - i + j + 1]--;
                    }
                    rem[this->size - r.size - i + j] -=(r.data[j] - '0');
                }
                c++;
            }
        }
    }
    for(i = 0; i < rem.size(); i++)
    {
        if(rem[rem.size() - i - 1] != '0')
        {
            break;
        }
    }
    if(i == rem.size())
    {
        result = "0";
    }
    else
    {
        result.data = new char[rem.size() - i];
        if(result.data)
        {
            result.size = rem.size() - i;
            result.sign = false;
            for(j = 0; j < result.size; j++)
            {
                result.data[j] = rem[j];
            }
        }
    }
    if(this->sign)
    {
        result = BigAbs(r) - result;
    }
    return result;
}

BigInteger BigInteger::operator%=(long long r)
{
    *this = *this % r;
    return *this;
}

BigInteger BigInteger::operator%=(std::string r)
{
    *this = *this % r;
    return *this;
}

BigInteger BigInteger::operator%=(const BigInteger &r)
{
    *this = *this % r;
    return *this;
}

BigInteger BigInteger::operator^(long long r) const
{
    return *this ^ BigInteger(r);
}

BigInteger BigInteger::operator^(std::string r) const
{
    return *this ^ BigInteger(r);
}

BigInteger BigInteger::operator^(const BigInteger &r) const
{
    BigInteger result, temp;
    if(!this->data || !r.data)
    {
        return result;
    }
    if(r < 0)
    {
        result = "0";
        return result;
    }
    if(r == 0)
    {
        result = "1";
        return result;
    }
    if(r == 1)
    {
        return *this;
    }
    temp = *this ^(r / 2);
    result = temp * temp;
    if((r.data[0] - '0') % 2 == 1)
    {
        result = result * *this;
    }
    return result;
}

BigInteger BigInteger::operator^=(long long r)
{
    *this = *this ^ r;
    return *this;
}

BigInteger BigInteger::operator^=(std::string r)
{
    *this = *this ^ r;
    return *this;
}

BigInteger BigInteger::operator^=(const BigInteger &r)
{
    *this = *this ^ r;
    return *this;
}

BigInteger BigInteger::operator++()
{
    *this = *this + 1;
    return *this;
}

BigInteger BigInteger::operator++(int)
{
    BigInteger temp = *this;
    *this = *this + 1;
    return temp;
}

BigInteger BigInteger::operator--()
{
    *this = *this - 1;
    return *this;
}

BigInteger BigInteger::operator--(int)
{
    BigInteger temp = *this;
    *this = *this - 1;
    return temp;
}

bool BigInteger::operator==(long long r) const
{
    return *this == BigInteger(r);
}

bool BigInteger::operator==(std::string r) const
{
    return *this == BigInteger(r);
}

bool BigInteger::operator==(const BigInteger &r) const
{
    if(!this->data || !r.data)
    {
        return false;
    }
    if(this->size != r.size)
    {
        return false;
    }
    if(sign != r.sign)
    {
        return false;
    }
    for(unsigned i = 0; i < this->size; i++)
    {
        if(this->data[i] != r.data[i])
        {
            return false;
        }
    }
    return true;
}

bool BigInteger::operator!=(long long r) const
{
    return !(*this == BigInteger(r));
}

bool BigInteger::operator!=(std::string r) const
{
    return !(*this == BigInteger(r));
}

bool BigInteger::operator!=(const BigInteger &r) const
{
    return !(*this == r);
}

bool BigInteger::operator<(long long r) const
{
    return *this < BigInteger(r);
}

bool BigInteger::operator<(std::string r) const
{
    return *this < BigInteger(r);
}

bool BigInteger::operator<(const BigInteger &r) const
{
    if(!this->data || !r.data)
    {
        return false;
    }
    if(this->sign && !r.sign)
    {
        return true;
    }
    if(!this->sign && r.sign)
    {
        return false;
    }
    if(!this->sign)
    {
        if(this->size > r.size)
        {
            return false;
        }
        if(this->size < r.size)
        {
            return true;
        }
        for(unsigned i = 0; i < this->size; i++)
        {
            if(this->data[this->size - i - 1] < r.data[this->size - i - 1])
            {
                return true;
            }
            if(this->data[this->size - i - 1] > r.data[this->size - i - 1])
            {
                return false;
            }
        }
        return false;
    }
    else
    {
        if(this->size < r.size)
        {
            return false;
        }
        if(this->size > r.size)
        {
            return true;
        }
        for(unsigned i = 0; i < this->size; i++)
        {
            if(this->data[this->size - i - 1] > r.data[this->size - i - 1])
            {
                return true;
            }
            if(this->data[this->size - i - 1] < r.data[this->size - i - 1])
            {
                return false;
            }
        }
        return false;
    }
}

bool BigInteger::operator>(long long r) const
{
    return *this > BigInteger(r);
}

bool BigInteger::operator>(std::string r) const
{
    return *this > BigInteger(r);
}

bool BigInteger::operator>(const BigInteger &r) const
{
    return !(*this <= r);
}

bool BigInteger::operator<=(long long r) const
{
    return *this <= BigInteger(r);
}

bool BigInteger::operator<=(std::string r) const
{
    return *this <= BigInteger(r);
}

bool BigInteger::operator<=(const BigInteger &r) const
{
    return *this == r || *this < r;
}

bool BigInteger::operator>=(long long r) const
{
    return !(*this < BigInteger(r));
}

bool BigInteger::operator>=(std::string r) const
{
     return !(*this < BigInteger(r));
}

bool BigInteger::operator>=(const BigInteger &r) const
{
    return !(*this < r);
}

void BigInteger::reverse(std::string &str)
{
    int len = str.size();
    char temp;
    for(int i = 0; i < len / 2; i++)
    {
        temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

unsigned BigInteger::operator[](const std::size_t pos) const
{
    return m_value[pos] - '0';
}

unsigned BigInteger::at(const std::size_t pos) const
{
    if (pos >= m_value.size()) throw std::out_of_range { "Index out of range" };

    return (*this)[pos];
}

std::size_t BigInteger::digit_count() const
{
    return m_value.length();
}

std::string BigInteger::to_string() const
{
    std::string result { std::format( "{}{}",
                                      m_sign == true ? "-" : "" ),
                                      value };
    return result;
}

BigInteger BigAbs(const BigInteger &in)
{
    BigInteger out = in;
    out.sign = false;
    return out;
}

BigInteger operator+(long long l, const BigInteger &r)
{
    return BigInteger(l) + r;
}

BigInteger operator+(std::string l, const BigInteger &r)
{
    return BigInteger(l) + r;
}

BigInteger operator-(long long l, const BigInteger &r)
{
    return BigInteger(l) - r;
}

BigInteger operator-(std::string l, const BigInteger &r)
{
    return BigInteger(l) - r;
}

BigInteger operator*(long long l, const BigInteger &r)
{
    return BigInteger(l) * r;
}

BigInteger operator*(std::string l, const BigInteger &r)
{
    return BigInteger(l) * r;
}

BigInteger operator/(long long l, const BigInteger &r)
{
    return BigInteger(l) / r;
}

BigInteger operator/(std::string l, const BigInteger &r)
{
    return BigInteger(l) / r;
}

BigInteger operator%(long long l, const BigInteger &r)
{
    return BigInteger(l) % r;
}

BigInteger operator%(std::string l, const BigInteger &r)
{
    return BigInteger(l) % r;
}

BigInteger operator^(long long l, const BigInteger &r)
{
    return BigInteger(l) ^ r;
}

BigInteger operator^(std::string l, const BigInteger &r)
{
    return BigInteger(l) ^ r;
}

bool operator==(long long l, const BigInteger &r)
{
    return BigInteger(l) == r;
}

bool operator==(std::string l, const BigInteger &r)
{
    return BigInteger(l) == r;
}

bool operator!=(long long l, const BigInteger &r)
{
    return BigInteger(l) != r;
}

bool operator!=(std::string l, const BigInteger &r)
{
    return BigInteger(l) != r;
}

bool operator<(long long l, const BigInteger &r)
{
    return BigInteger(l) < r;
}

bool operator<(std::string l, const BigInteger &r)
{
    return BigInteger(l) < r;
}

bool operator>(long long l, const BigInteger &r)
{
    return BigInteger(l) > r;
}

bool operator>(std::string l, const BigInteger &r)
{
    return BigInteger(l) > r;
}

bool operator<=(long long l, const BigInteger &r)
{
    return BigInteger(l) <= r;
}

bool operator<=(std::string l, const BigInteger &r)
{
    return BigInteger(l) <= r;
}

bool operator>=(long long l, const BigInteger &r)
{
    return BigInteger(l) >= r;
}

bool operator>=(std::string l, const BigInteger &r)
{
    return BigInteger(l) >= r;
}

std::ostream& operator<<(std::ostream &out, const BigInteger &r)
{
    std::stringstream output;
    if(r.sign)
    {
        output << "-";
    }
    for(unsigned i = 0;i < r.size;i++)
    {
        output << r.data[r.size - i - 1];
    }
    out << output.str();
    return out;
}

std::istream& operator>>(std::istream &in, BigInteger &r)
{
    std::string str;
    in >> str;
    r = str;
    return in;
}
