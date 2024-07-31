
#include <iostream>
#include <cstdlib>
#include "BigInteger.h"


int main()
{
    BigInteger a = 1;
    BigInteger b {2};

    BigInteger f = a + 1;
    std::cout << f << '\n';

    std::cout << "Enter two integers: ";
    BigInteger c;
    BigInteger d;
    std::cin >> c >> d;

    BigInteger e = c * d;
    f = ++b;
    std::cout << f << "-" << b << '\n';
    f = b++;
    std::cout << f << "-" << b << '\n';
    std::cout << a << "\t" << b << "\t" << e << "\t" << f << '\n';

    f = 1;
    for ( int i {2}; i <= 1000; ++i )
    {
        f *= i;
    }

    std::cout << "1000! = " << f << '\n';

    return EXIT_SUCCESS;
}
