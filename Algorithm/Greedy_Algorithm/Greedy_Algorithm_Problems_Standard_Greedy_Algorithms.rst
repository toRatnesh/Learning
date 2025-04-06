.. contents:: Table of Contents

1.  Activity Selection Problem
--------------------------------

Problem:
^^^^^^^^^^^^

You are given n activities with their start and finish times. Select the maximum number of activities that can be performed by a single person, assuming that a person can only work on a single activity at a time.

Example 1 : Consider the following 3 activities sortd by by finish time.

	start[]  =  {10, 12, 20};

	finish[] =  {20, 25, 30};

    A person can perform at most two activities. The maximum set of activities that can be executed is {0, 2} [ These are indexes in start[] and finish[] ]

Example 2 : Consider the following 6 activities sorted by by finish time.

	start[]  =  {1, 3, 0, 5, 8, 5};

	finish[] =  {2, 4, 6, 7, 9, 9};

    A person can perform at most four activities. The maximum set of activities that can be executed is {0,1,3,4} [ These are indexes in start[] and  finish[] ]

Solution:
^^^^^^^^^^^^

Greedy choice is to always pick the next activity whose finish time is least among the remaining activities and the start time is more than or equal to the finish time of previously selected activity. We can sort the activities according to their finishing time so that we always consider the next activity as minimum finishing time activity.

Algorithm:
^^^^^^^^^^^^^^^

#.  Sort the activities according to their finishing time
#.  Select the first activity from the sorted array and print it.
#.  Do following for remaining activities in the sorted array.

    a.  If the start time of this activity is greater than or equal to the finish time of previously selected activity, then select this activity and print it.


.. code:: cpp

    #include <iostream>
    #include <cstdlib>
    #include <cstring>
    #include <algorithm>

    using namespace std;

    #define SIZE 100000

    struct Activitiy {
        int start, finish;
    };


    bool compare_fun(struct Activitiy s1, struct Activitiy s2);

    class ActivitySelection {
        private:
            int no_act;
            int start[SIZE];
            int finish[SIZE];
            
        public:
            ActivitySelection() {
                no_act = 0;
                memset(start, 0, SIZE);
                memset(finish, 0, SIZE);
            }

            ~ActivitySelection() {
                no_act = 0;
                memset(start, 0, SIZE);
                memset(finish, 0, SIZE);			
            }
            
            int set_noOfActivity(void);
            int set_startTime(void);
            int set_finishTime(void);
            int get_maxNoOfActivity(void);
            
        
    };


    int ActivitySelection::set_noOfActivity(void) {
        cin >> no_act;
        return 0;
    }

    int ActivitySelection::set_startTime(void) {
        for(int i = 0; i < no_act; i++) {
            cin >> start[i];
        }
        
        return 0;
    }
    int ActivitySelection::set_finishTime(void) {
        for(int i = 0; i < no_act; i++) {
            cin >> finish[i];
        }
        
        return 0;
    }


    bool compare_fun(struct Activitiy s1, struct Activitiy s2) {
        return (s1.finish < s2.finish);
    }
            
    int ActivitySelection::get_maxNoOfActivity(void) {
        int max_act = 0;
        int next_act_index = 0;
        int prev_act_index = 0;
        int n = 0;

        struct Activitiy arr[no_act];
        
        for(int i = 0; i < no_act; i++) {
            arr[i].start = start[i];
            arr[i].finish = finish[i];
        }
        
        n = sizeof(arr)/sizeof(arr[0]);
        sort(arr, arr + n, compare_fun);
        //sort(arr, arr + no_act, );

    /*
        for(int i = 0; i < no_act; i++) {
            cout << finish[i] << " ";
        }
    */
        
        prev_act_index = 0;
        max_act = 1;		// to consider first activity
        for(next_act_index = 1; next_act_index < no_act; next_act_index++) {

            if(arr[next_act_index].start >= arr[prev_act_index].finish) {
                max_act = max_act + 1;
                prev_act_index = next_act_index;
            }		
        }	// end of for loop
        
        
        return max_act;
    }
            
            
    int main(void) {
        int maxAct = 0;
        
        ActivitySelection objact;
        
        objact.set_noOfActivity();
        objact.set_startTime();
        objact.set_finishTime();
        
        maxAct = objact.get_maxNoOfActivity();
        cout << maxAct;
        
        return 0;
    }


Input::

    3
    10 12 20
    20 25 30

Output::

    2


2.  Huffman Coding
----------------------


3.  Job Sequencing Problem
-----------------------------


4.  Efficient Huffman Coding for Sorted Input
------------------------------------------------


References
--------------

https://www.geeksforgeeks.org/greedy-algorithms/

