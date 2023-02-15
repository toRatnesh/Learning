
#. Predict output of the following program

   .. code:: cpp

    #include <stdio.h>
    int main() {
        printf("\new_c_question\by");
        printf("\rgeeksforgeeks");
        getchar();
        return 0;
    }
   
i. | ew_c_question
   | geeksforgeeks

ii. | new_c_ques
   | geeksforgeeks
   
iii. geeksforgeeks
   
iv. **Depends on terminal configuration**
   
It is up to the terminal's implementation then how those characters get actually displayed


#. Predict output of the following program

   .. code:: cpp

    #include <stdio.h>
    // Assume base address of "GeeksQuiz" to be 1000
    int main() {
        printf(5 + "GeeksQuiz");
        return 0;
    }


i. GeeksQuiz

ii. **Quiz**

iii. 1005

iv. Compile-time error

The compiler adds 5 to the base address of the string through the expression 5 + "GeeksQuiz" . Then the string "Quiz" gets passed to the standard library function as an argument.



3. Predict the output of the below program

   .. code:: cpp

    #include <stdio.h>
    int main() {
        printf("%c ", 5["GeeksQuiz"]);
        return 0;
    }

i. Compile-time error

ii. Runtime error

iii. **Q**

iv. s

5["GeeksQuiz"] is equivalent to \*(5 + pointer for char array) it will print character present at 5th index 'Q'


