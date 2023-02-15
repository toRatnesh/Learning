
.. contents:: Table of Contents

C String
========

C Strings
---------
<cstring> (string.h)
'string.h' header file defines several functions to manipulate C strings and arrays.

Macros
------

=====          =======================
NULL		Null pointer (macro )
=====          =======================

Types
-----

=======        ================================
size_t		Unsigned integral type (type )
=======        ================================

Functions
---------

Copying
^^^^^^^

.. list-table::
	:widths: 20 80

	*	-	memcpy
		-	| Copy block of memory (function ) 
			| void* memcpy( void * destination, const void * source, size_t num );
	
	*	-	memmove
		-	| Move block of memory (function ) 
			| void* memmove( void * destination, const void * source, size_t num );
		
	*	-	strcpy
		-	| Copy string (function ) 
			| char* strcpy( char * destination, const char * source );
			
	*	-	strncpy
		-	| Copy characters from string (function ) 
			| char* strncpy( char * destination, const char * source, size_t num );

Concatenation
^^^^^^^^^^^^^

.. list-table::
	:widths: 20 80

	*	-	strcat
		-	| Concatenate strings (function )
			| char* strcat(char * destination, const char * source );
	
	*	-	strncat
		-	| Append characters from string (function )
			| char* strncat(char * destination, const char * source, size_t num );

Comparison
^^^^^^^^^^


.. list-table::
	:widths: 20 80

	*	-	memcmp
		-	| Compare two blocks of memory (function )
			| int memcmp ( const void * ptr1, const void * ptr2, size_t num );
	
	*	-	strcmp
		-	| Compare two strings (function )
			| int strcmp ( const char * str1, const char * str2 );
			
	*	-	strcoll
		-	| Compare two strings using locale (function )
			| int strcoll ( const char * str1, const char * str2 );
	
	*	-	strncmp
		-	| Compare characters of two strings (function )
			| int strncmp ( const char * str1, const char * str2, size_t num );
	
	*	-	strxfrm
		-	| Transform string using locale (function )
			| size_t strxfrm ( char * destination, const char * source, size_t num );



Searching
^^^^^^^^^


.. list-table::
	:widths: 20 80

	*	-	memchr
		-	| Locate character in block of memory (function )
			| const void* memchr( const void* ptr, int ch, std::size_t count );
			|       void* memchr(       void* ptr, int ch, std::size_t count );
			|       void* memchr( const void* ptr, int ch, size_t count ); // C
			
	*	-	strchr
		-	| Locate first occurrence of character in string (function )
			| const char* strchr( const char* str, int ch );
			|       char* strchr(       char* str, int ch );
			|       char* strchr( const char* str, int ch ); // C
		
	*	-	strcspn
		-	| Get span until character in string (function )
			| size_t strcspn( const char* dest, const char* src );
			
	*	-	strpbrk
		-	| Locate characters in string (function )
			| const char* strpbrk( const char* dest, const char* breakset );
			|       char* strpbrk(       char* dest, const char* breakset );
			|       char* strpbrk( const char* dest, const char* breakset ); // C
	
	*	-	strrchr	
		-	| Locate last occurrence of character in string (function )
			| const char* strrchr( const char* str, int ch );
			|       char* strrchr(       char* str, int ch );
			|       char* strrchr( const char* str, int ch ); // C

	*	-	strspn	
		-	| Get span of character set in string (function )
			| size_t strspn( const char* dest, const char* src );
	
	*	-	strstr
		-	| Locate substring (function )
			| const char* strstr( const char* haystack, const char* needle );
			|       char* strstr(       char* haystack, const char* needle );
			|       char* strstr( const char* str, const char* substr ); // C

	*	-	strtok
		-	| Split string into tokens (function )
			| char* strtok( char* str, const char* delim );
			| char* strtok( char* str, const char* delim );
			| char* strtok( char* str, const char* delim ); (until C99)
			| char* strtok( char* restrict str, const char* restrict delim ); (since C99)
			| char* strtok_s(char* restrict str, rsize_t* restrict strmax,
                        |       const char* restrict delim, char** restrict ptr);	(since C11)




Other
^^^^^

.. list-table::
	:widths: 20 80

	*	-	memset
		-	| Fill block of memory (function )
			| void* memset ( void * ptr, int value, size_t num );
			
	*	-	strerror
		-	| Get pointer to error message string (function )
			| char* strerror ( int errnum );
		
	*	-	strlen
		-	| Get string length (function )
			| size_t strlen ( const char * str );


Macros
------

=====          =======================
NULL		Null pointer (macro )
=====          =======================

This macro expands to a null pointer constant.
A null pointer constant can be converted to any pointer type (or pointer-to-member type), which acquires a null pointer value. 
This is a special value that indicates that the pointer is not pointing to any object.

- In C, A null-pointer constant is an integral constant expression that evaluates to zero (like 0 or 0L), or the cast of such value to type void* (like (void*)0).
- In C++, A null-pointer constant is an integral constant expression that evaluates to zero (such as 0 or 0L).	
- In C++11, A null-pointer constant is either an integral constant expression that evaluates to zero (such as 0 or 0L), or a value of type nullptr_t (such as nullptr).				

Types
-----

======            ==============================
size_t            Unsigned integral type (type )
======            ==============================

**Unsigned integral type**

Alias of one of the fundamental unsigned integer types

It is a type able to represent the size of any object in bytes: 

size_t is the type returned by the sizeof operator and is widely used in the standard library to represent sizes and counts.

In <cstring>, it is used as the type of the parameter num in the functions memchr, memcmp, memcpy, memmove, memset, strncat, strncmp, strncpy and strxfrm, which in all cases it is used to specify the maximum number of bytes or characters the function has to affect.

It is also used as the return type for strcspn, strlen, strspn and strxfrm to return sizes and lengths.

References
---------

https://en.cppreference.com/w/c/string/byte


