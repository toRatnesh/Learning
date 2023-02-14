
.. contents:: Table of Contents


Constants/Literals
==================

Constants refer to fixed values that do not change during the execution of a program

They are called literals

Literal constants do not have memory locations

Constants can be of any of the basic data types

Example

.. list-table::

    *   -   123
        -   Decimal Integer

    *   -   12.34
        -   Floating point integer
          
    *   -   037
        -   Octal integer

    *   -   0x2
        -   Hexadecimal integer

    *   -   “C++”
        -   String Constant

    *   -   ‘A’
        -   Character constant
          
    *   -   L’ab’
        -   Wide character constant


Defining Constants
------------------

make the variable as constant using

#define preprocessor
^^^^^^^^^^^^^^^^^^^^

Defines a substitute text for a name

Creates symbolic constants, called a macro

Example

.. code:: cpp

	#define LENGTH 10

const keyword
^^^^^^^^^^^^^

You can use const prefix to declare constants with a specific type

const type variable = value;

Example

.. code:: cpp
	
	const int LENGTH = 10;

constexpr
^^^^^^^^^

since C++11 (not in C) constexpr can be used to declare variable as a guaranteed constant. 
But it would fail to compile if its initializer isn’t a constant expression.

.. code:: cpp
	
	constexpr int k = 5;

More info check in C++ 11 topics

enum
^^^^

Enumeration (or enum) is a user defined data type in C and C++. 
It is mainly used to assign names to integral constants, that make a program easy to read and maintain.
In C and C++ internally the default type of 'var' is int

.. code:: cpp

	enum VARS { var = 42 };

In C++ 11 (can have any integral type):

.. code:: cpp
	
	enum : type { var = 42; }

where mytype = int, char, long etc.
but it can't be float, double or user defined data type.

`For more info check <11_Enum_C_CPP.rst>`_

Difference between #define and const
------------------------------------

- #define is a preprocessor directive while const variables are actual variables
- Advantage of const over #define is type checking
- Disadvantage is extra space for variable which is immaterial due to optimizations done by compilers
- In general const are better options if we have choice
- There are situations where #define cannot be replaced by const
        - #deifne can take parameters
        - #define can also be used to replace some text in a program with another text

**NOTE:**

::

    1. In C++ we can use const in a constant expression, in C not
           const int size = 10;
           char name[size];     // C++ (y)		C (n)
    2. Character literals have different type in C and C++
           In C character literal is treated as an int type
           In C++ character literal is treated as char type

Raw String Literal (C++ 11)
---------------------------

From C++11 we can use raw strings in which escape characters (\n, \t or \” …) are not processed. The syntax of raw string is that the literal starts with R”(and ends in)”.

.. code:: cpp

    #include <iostream>
    using namespace std;

    int main(void) {
        std::string str1 = "Geeks\nFor\nGeeks\n";
        std::string str2 = R"(Geeks\nFor\nGeeks\n)";
        std::cout << str1 << std::endl;
        std::cout << str2 << std::endl;
        return 0;
    }

Output::

    Geeks
    For
    Geeks

    Geeks\nFor\nGeeks\n

User defined literals (C++11)
-----------------------------

Why to use UDL? Consider example

long double weight = 2.3;		// pounds?, Kilogram?, Grams?

With UDL, we attach units to the values which has following advantages

The code becomes readable 

**Conversion computations are done at compile time**

::

    weight  = 2.3kg;
    ratio   = 2.3kg/1.21b;

To calculate above ratio it is necessary to convert them to same units.

UDLs help us to overcome unit translation cost

We can define user defined literals for user defined types and new form of literals for built-in types

Value of UDLs is substituted with the actual value defined in the code by the compiler at compile time

UDLs do not save much of coding time but more and more calculation can be shifted to compile time for faster execution

Example

::

        "hello"s				// string
        4.3i					// imaginary
        101000111101001b			// binary
        53h					// hours
        234093270497230409328432840923849       // extended-precision


UDLs are treated as a call to a literal operator

Only suffix form is supported

The name of the literal operator is operator “” followed by the suffix
Example

.. code:: cpp

    #include <iostream>
    #include <iomanip>
    using namespace std; 
    
    long double operator"" _kg( long double x )	{return x*1000;}
    long double operator"" _g( long double x )	{return x;}
    long double operator"" _mg( long double x )	{return x / 1000;}
    
    int main() {
        long double weight = 3.6_kg;
        cout << weight << endl;
        cout << setprecision(8) << ( weight + 2.3_mg ) << endl;
        cout << ( 32.3_kg / 2.0_g ) << endl;
        cout << ( 32.3_mg *2.0_g ) << endl;
        return 0;
    }

Output::

    3600
    3600.0023
    16150
    0.0646


.. code:: cpp

    #include <iostream>
    #include <complex>
    using namespace std;
    
    constexpr complex <double> operator"" _i(long double d) {
        return complex <double> {0.0, static_cast<double>(d)};
    }

    int main() {
        complex <double> z = 3.0 + 4.0_i;
        complex <double> y = 2.3 + 5.0_i;
        std::cout << "z+y = " << (z+y) << std::endl;
        std::cout << "z*y = " << (z*y) << std::endl;
        std::cout << "abs(z) = " << abs(z) << std::endl;
        return 0;
    } 

Output::

    z+y = (5.3,9)
    z*y = (-13.1,24.2)
    abs(z) = 5


.. note::

    - constexpr is used to enable compile time evaluation

Restriction
-----------

UDL can only work with the following parameters:

.. code:: cpp

        char const*
        unsigned long long
        long double
        char const*,            std::size_t
        wchar_t const*,         std::size_t
        char16_t const*,        std::size_t
        char32_t const*,        std::size_t

Type difference of character literals in C and C++
--------------------------------------------------

In C, a character literal is treated as int type

In C++, a character literal is treated as char type
        It is required to support function overloading

.. code:: cpp

        #include <stdio.h>

        int main() {
            printf("sizeof('V') = %zu sizeof(char) = %zu", sizeof('V'), sizeof(char));
                return 0; 
        } 

Output::

        sizeof('V') = 4 sizeof(char) = 1		//In C
        sizeof('V') = 1 sizeof(char) = 1		//In C++

Not a Number (NaN)
------------------

“Not a Number” is an exception

Occurs in the cases when an expression results in a number that can’t be represented

Example

square root of negative numbers

**How to check for NaN?**

- Method_01: Using compare (“==”) operator
        | number is compared with itself
        | if result is false, then “nan” is returned, i.e the number is complex
        | If the result is true, then the number is not complex
- Method_02: Using inbuilt function “isnan()”
        | returns true if a number is complex else it returns false

References
----------

| https://www.geeksforgeeks.org/constants-in-c-cpp/
| https://www.geeksforgeeks.org/different-ways-declare-variable-constant-c-c/
| https://www.geeksforgeeks.org/diffference-define-const-c/
| Constants and literals | https://en.cppreference.com/w/c/language/expressions
| https://www.learncpp.com/cpp-tutorial/literals/
| Literals | https://en.cppreference.com/w/cpp/language/expressions



