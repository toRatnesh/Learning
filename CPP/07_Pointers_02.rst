
.. contents::	Table of Contents

Pointers
========

Pointers and const
-------------------

Pointer to const value
^^^^^^^^^^^^^^^^^^^^^^

A pointer to a const value (sometimes called a pointer to const for short) is a (non-const) pointer that points to a constant value.

To declare a pointer to a const value, use the const keyword before the pointer’s data type

.. code:: cpp

	#include <stdio.h>
	int main() {
		const int x = 5;
		const int* ptr = &x;    // ptr points to const int x
		printf("*ptr %d\n", *ptr);
		//*ptr = 6;   // error: assignment of read-only location '* ptr'

		const int y = 6;
		ptr = &y; // okay: ptr now points at const int y
		printf("*ptr %d\n", *ptr);
		return 0;
	}

Output::

	*ptr 5
	*ptr 6

Const pointers
^^^^^^^^^^^^^^

We can also make a pointer itself constant. A const pointer is a pointer whose address can not be changed after initialization.

To declare a const pointer, use the const keyword after the asterisk in the pointer declaration

.. code:: cpp

	#include <stdio.h>
	int main() {
    	int x = 5;
    	int * const ptr = &x; // okay: the const pointer is initialized to the address of x
    	printf("x: %d, *ptr: %d\n", x , *ptr);
    
    	x = 7;
    	printf("x: %d, *ptr: %d\n", x , *ptr);
	
	    int y = 6;
	    //ptr = &y; //error: assignment of read-only variable 'ptr'
	
	    return 0;
	}

Output::

	x: 5, *ptr: 5
	x: 7, *ptr: 7


Const pointer to a const value
^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

To declare a const pointer to a const value by using the const keyword both before the type and after the asterisk

.. code:: cpp

	#include <stdio.h>
	int main() {
    	int x = 5;
    	const int* const ptr = &x; // a const pointer to a const value
    	printf("x: %d, *ptr: %d\n", x , *ptr);
    
    	//*ptr=7; // error: assignment of read-only location '*(const int *)ptr'

    	int cx = 8;
    	//ptr = &cx;  // error: assignment of read-only variable 'ptr'

    	return 0;
	}

Output::

	x: 5, *ptr: 5

A const pointer to a const value can not have its address changed, nor can the value it is pointing to be changed through the pointer. It can only be dereferenced to get the value it is pointing at.

‘this’ pointer in C++
---------------------

- 'this' pointer is a constant pointer that holds the memory address of the current object
- passed as a hidden argument to all nonstatic member function calls
- available as a local variable within the body of all nonstatic functions
- ‘this’ pointer is not available in static member functions as static member functions can be called without any object (with class name)
- For a class M
	- 'this' pointer is 'M * const this'
	- 'this' pointer is 'const M * const this' if a member function of M is declared as const


Use of 'this' pointer
^^^^^^^^^^^^^

#. When local variable’s name is same as member’s name

   .. code:: cpp

    void setX (int x) {
        // The 'this' pointer is used to retrieve the object's x
        // hidden by the local variable 'x'
        this->x = x;
    }

#. To return reference to the calling object

   .. code:: cpp

    Test& Test::func () {
        // Some processing
        return *this;
    }

#. Method chaining

   When a reference to a local object is returned, the returned reference can be used to chain function calls on a single object

   Example

   .. code:: cpp

    positionObj->setX(15)->setY(16)->setZ(17);
    
   The methods setX, setY and setZ are chained to the object positionObj
   This is possible because each method return \*this pointer
   This is equivalent to

   positionObj->setX(15)
   positionObj->setY(16)
   positionObj->setZ(17)

   .. code:: cpp

    #include <iostream>
    using namespace std;
    class Test { 
		private: int x; int y; 
		
		public: 
		Test(int x = 0, int y = 0) { this->x = x; this->y = y; } 
		Test & setX(int a) { x = a; return *this; } 
		Test & setY(int b) { y = b; return *this; } 
		void print() { cout << "x = " << x << " y = " << y << endl; } 
    };
    
    int main() {
        Test obj1(5, 5);
        // Chained function calls.  All calls modify the same object 
        // as the same object is returned by reference 
        obj1.setX(10).setY(20);
        obj1.print();
        return 0;
    }
    
   Output::

	x = 10 y = 20

#. Very important when operators are overloaded

**Exercise**

Predict the output of following programs. If there are compilation errors, then fix them.

.. code:: cpp

	#include <iostream> 
	using namespace std; 

	class Test { 
		private: int x; 
		public: 
		Test(int x = 0) { this->x = x; } 
		void change(Test *t) { this = t; } 
		void print() { cout << "x = " << x << endl; } 
	}; 

	int main() { 
		Test obj(5); 
		Test *ptr = new Test (10); 
		obj.change(ptr); 
		obj.print(); 
		return 0; 
	} 
	
Output::
	
	Compilation Error: lvalue required as left operand of assignment void change(Test *t) { this = t; }

.. code:: cpp

	#include <iostream> 
	using namespace std; 

	class Test { 
		private:  int x; int y; 
		public: 
		Test(int x = 0, int y = 0) { this->x = x; this->y = y; } 
		static void fun1() { cout << "Inside fun1()"; } 
		static void fun2() { cout << "Inside fun2()"; this->fun1(); } 
	}; 

	int main() { 
		Test obj; 
		obj.fun2(); 
		return 0; 
	}

Output::
 
	Compilation Error: 'this' is unavailable for static member functions static void fun2() { cout << "Inside fun2()"; this->fun1(); }


.. code:: cpp

	#include <iostream> 
	using namespace std; 

	class Test { 
		private:  int x;  int y; 
		public: 
		Test (int x = 0, int y = 0) { this->x = x; this->y = y; } 
		Test setX(int a) { x = a; return *this; } 
		Test setY(int b) { y = b; return *this; } 
		void print() { cout << "x = " << x << " y = " << y << endl; } 
	}; 

	int main() { 
		Test obj1; 
		obj1.setX(10).setY(20); 
		obj1.print(); 
		return 0; 
	} 

Output::

	x = 10 y = 0

.. code:: cpp

	#include <iostream> 
	using namespace std; 

	class Test { 
		private:  int x; int y; 
		public: 
		Test(int x = 0, int y = 0) { this->x = x; this->y = y; } 
		void setX(int a) { x = a; } 
		void setY(int b) { y = b; } 
		void destroy()  { delete this; } 
		void print() { cout << "x = " << x << " y = " << y << endl; } 
	}; 

	int main() { 
		Test obj; 
		obj.destroy(); 
		obj.print(); 
		return 0; 
	} 

Output::

	Runtime Errors:
	Abort signal from abort(3) (SIGABRT)

Type of this pointer in C++
^^^^^^^^^^^^^^

This pointer is passed as a hidden argument to all non-static member function calls

Type of this pointer depends upon function declaration


const X*          if the member function of a class X is declared const

volatile X*       if the member function is declared volatile

const volatile X* if the member function is declared const volatile

.. code:: cpp

    class X {
		void fun() const { ... } 
	}
    // 'this' is const X*

.. code:: cpp

	class X {
		void fun() volatile { ... }
	}
	// 'this' is volatile X*

.. code:: cpp

	class X {
		void fun() const volatile { ... }
	}
	// 'this' is const volatile X*


‘delete this’ in C++
^^^^^^^^^^^^^^

Ideally **delete operator should not be used for this pointer**

Deleting ‘this’ leaves it as a ‘dangling pointer’ which leads to undefined behaviour if it is accessed

Deleting ‘this’ is only valid if it is guaranteed 
    - That the this pointer is never dereferenced gain
    - That the object was allocated using ‘new’ operator

Example

.. code:: cpp

	//non-complaint code
	class X {
		public:
			void doSomething();
			void destroy();
	};

	void X::destroy() {
		delete this;
		// NOTE: object is allocated on the stack and deleting it will fail
	}

	int main() {
		X obj;
		obj.destroy();
		...
		return 0;
	}


.. code:: cpp

	// complaint solution (destructor)
	{
		X obj;
		...
	}
	//	obj.~X() is implicitly invoked
	// objects allocated on the stack have their destructors invoked when the object goes out of scope

.. code:: cpp

	// complaint solution (dynamic objects)
	{
		X* pobj = new X();
		...
		pobj->destroy();
		pobj = NULL;	// prevent future reference to deleted object
	}
	// must ensure that this always points to an object on the heap
	// must ensure that the deleted object is never dereferenced again

.. note::

    - best is not to use 'delete this' at all

Understanding ‘nullptr’ in C++
------------------------------

.. note::

    - NULL and nullptr are different

.. code:: cpp

	#include <iostream>
	using namespace std;

	void fun(int n) { cout << "fun(int)" << endl; }
	void fun(char * s) { cout << "fun(char*)" << endl; }
	int main() {
		//fun(NULL);
		// Compilation error: call of overloaded 'fun(NULL)' is ambiguous
		
		fun(nullptr);
		return 0;
	}

Output::

	fun(char*)


**What is the problem with above program?**

NULL is typically defined as (void \*)0 and conversion of NULL to integral types is allowed. So the function call fun(NULL) becomes ambiguous.

.. code:: cpp

	int x = NULL;
	//C	Compilation warning: initialization makes integer from pointer without a cast [-Wint-conversion]
	//C++	Compilation warning: converting to non-pointer type 'int' from NULL [-Wconversion-null]

**How does nullptr solve the problem?**

nullptr is a keyword that can be used at all places where NULL is expected. 
Like NULL, nullptr is implicitly convertible and comparable to any pointer type. 
Unlike NULL, it is not implicitly convertible or comparable to integral types.

.. code:: cpp

	int x = nullptr;
	//Compilation error: cannot convert 'std::nullptr_t' to 'int' in initialization

.. note::

    - nullptr is convertible to bool

.. code:: cpp

	#include <iostream>
	using namespace std;
	int main() {
	    int * ptr = nullptr;
	    if(ptr) { cout << "true" << endl; }
	    else    { cout << "flase" << endl; }
		return 0;
	}

Output::

	flase

- When compare two simple pointers there are some unspecified things
- Comparison between two values of nullptr_t is specified as

::

	nullptr_t	np1, np2;
	np1 >= np2	true
	np1 <= np2	true

	np1 > np2	false
	np1 < np2	false

	np1 == np2	true
	np1 != np2	false

.. code:: cpp

	#include <iostream>
	using namespace std;

	int main() {
		nullptr_t np1, np2;
		
		if(np1 >= np2) { cout << "can compare" << endl; }
		else           { cout << "can not compare" << endl; }
		
		char * x = nullptr;     // same as x = nullptr;
		if(nullptr == x) { cout << "x is null" << endl; }
		else             { cout << "x is not null" << endl; }
		return 0;
	}

Output::

	can compare
	x is null

delete nullptr
^^^^^^^^^^^^

deleting nullptr in C++ is valid

https://en.cppreference.com/w/cpp/language/delete

.. code:: cpp

	int main() {
	    int * ptr = nullptr;
	    delete ptr;

	    int * ptr2 = new int(5);
	    delete ptr2;
	    //delete ptr2;  // free(): double free detected in tcache 2
	    ptr2 = nullptr; // once pointer is set to nullptr there's no issue in deleting it    
	    delete ptr2;
	    delete ptr2;

	    return 0;
	}



Opaque Pointer
--------------

A pointer which points to DS whose counters is not exposed at the time of its definition.

Its safe to assign NULL to an opaque pointer.

.. code:: cpp

	struct STest * pSTest;
	pSTest = NULL;

can't know the data contained in STest structure by looking at the definition.

**Why opaque pointer?**

When we deal with shared code where implementation of DS is prepared at compilation unit

Example: 
Want to develop apps for windows and apple platforms
We can have shared code which would be used by all platforms and then different end-point can have platform specific code

.. code:: cpp

	// === image.h ===
	// class provides API
	// different platform can implement these operations in different way
	class CImage {
		public:
			CImage();
			~CImage();
			struct SImageInfo * pImageInfo;
			void rotate(double angle);
			void scale(double scaleFactor x, double scaleFactor y);
			void move(int toX, int toY);
		private:
			void InitImageInfo();		
	};

	// === image.cpp ===
	// constructor and destructor for CImage
	CImage::CImage()	{ InitImageInfo();		}
	CImage::~CImage()	{ /* destroy object */	}

	// === image_windows.cpp ===
	struct SImageInfo { /* windows specific dataset */ };

	void CImage::InitImageInfo() {
		pImageInfo = new SImageInfo;
		// initialize windows specific info
	}

	void CImage::rotate() { /* windows specific SImageInfo */ }

	// === image_apple.cpp ===
	struct SImageInfo {	/* apple specific dataset */ };

	void CImage::InitImageInfo() {
		pImageInfo = new SImageInfo;
		// initialize apple specific info
	}

	void CImage::rotate() {	/* apple specific SImageInfo */ }

Explanation:

While defining blueprint of class CImage we only mention there is a SImageInfo DS

Content of SImageInfo is unknown

Client (W, A) will define DS and use it as per their requirement

References
----------

| Pointers and References | https://www.geeksforgeeks.org/c-plus-plus/
| Chapter 9 Compound Types: References and Pointers | https://learncpp.com/
| https://en.cppreference.com/w/cpp/language/pointer
| https://en.cppreference.com/w/cpp/language/reference
| https://en.cppreference.com/w/cpp/language/this




