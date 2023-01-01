

.. contents:: Table of Contents


Variable Arguments
==================

Variable Arguments
------------------
C supports variable numbers of arguments. But there is no language provided way for finding out total number of arguments passed. User has to handle this in one of the following ways:

1. By passing first argument as count of arguments.
2. By passing last argument as NULL (or 0).
3. Using some printf (or scanf) like mechanism where first argument has placeholders for rest of the arguments.

- Define a function with its last parameter as ellipses and the one just before the ellipses is always an int which will represent the number of arguments.
- Create a va_list type variable in the function definition. This type is defined in stdarg.h header file.
- Use int parameter and va_start macro to initialize the va_list variable to an argument list. The macro va_start is defined in stdarg.h header file.
- Use va_arg macro and va_list variable to access each item in argument list.
- Use a macro va_end to clean up the memory assigned to va_list variable.

.. code:: cpp

	#include <stdarg.h>
	#include <stdio.h>
	// this function returns average of integer numbers passed. First argument is count of arguments.
	double average(int arg_count, ...) {
		int i;
		double avg = 0;
		double sum = 0;

		// va_list is a type to hold information about variable arguments
		va_list ap;

		// va_start must be called before accessing variable argument list
		va_start(ap, arg_count);

		// Now arguments can be accessed one by one using va_arg macro
		// traverse rest of the arguments to find out sum
		for(i = 0; i < arg_count; i++) {
			sum = sum + va_arg(ap, int);
		} 

		// calculate avg
		avg = (sum / arg_count);
		
		//va_end should be executed before the function returns whenever
		// va_start has been previously used in that function 
		va_end(ap);
		
		return avg;
	}

	int main() {
		printf("avg value is %f\n", average(3,5,10,15));
		printf("avg value is %f\n", average(4,2,3,4,5));
		
		return 0;
	}

Output::

	avg value is 10.000000
	avg value is 3.500000


