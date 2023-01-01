1. Predict output of the following program

.. code:: cpp

	#include <stdio.h>
	int main() {
	   printf("\new_c_question\by");
	   printf("\rgeeksforgeeks"); 
	   getchar();
	   return 0;
	}

A. ew_c_question
  geeksforgeeks

B. new_c_ques
  geeksforgeeks

C. geeksforgeeks

D. **Depends on terminal configuration**

	It is up to the terminal's implementation then how those characters get actually displayed



2. Predict output of the following program

.. code:: cpp

	#include <stdio.h>
	// Assume base address of "GeeksQuiz" to be 1000
	int main() {
	   printf(5 + "GeeksQuiz");
	   return 0;
	}

A. GeeksQuiz

B. **Quiz**

C. 1005

D. Compile-time error

	The compiler adds 5 to the base address of the string through the expression 5 + "GeeksQuiz" . Then the string "Quiz" gets passed to the standard library function as an argument.



3. Predict the output of the below program:

.. code:: cpp

	#include <stdio.h>
	int main() {
		printf("%c ", 5["GeeksQuiz"]);
		return 0;
	}

A. Compile-time error
B. Runtime error
C. **Q**
D. s


