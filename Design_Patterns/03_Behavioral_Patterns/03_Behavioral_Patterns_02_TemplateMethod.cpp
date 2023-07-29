/*******
    This example is implementation of Template method Design Pattern
**************/

#include <iostream>
#include <vector>

class Sort {

    protected :

    virtual void readData(std::vector<int> & ) { }       // hook operation
    virtual void writeData(std::vector<int> & vec)    {    // primitive operation
        for(auto & elem : vec) {
            std::cout << elem << ' ';
        }
    }
    virtual void sortData(std::vector<int> & vec) =   0;    // primitive operation

    void swap(int & a, int & b) {
        int temp = a;
        a = b;
        b = temp;
    }

    public:
    virtual void processData(std::vector<int> & vec) final {
        readData(vec);
        std::cout << "Before sort: ";
        writeData(vec);
        std::cout << '\n';
        sortData(vec);
        std::cout << "After sort: ";
        writeData(vec);
        std::cout << '\n';
    }
};

class SelectionSort : public Sort {
    virtual void readData(std::vector<int> & vec) { 
        for(int i = 1; i < 10; ++i) {
            vec.push_back(10-i);
        }    
    }
    
    virtual void sortData(std::vector<int> & vec) {
        size_t i, j, min_idx;
        size_t  n = vec.size();
        // One by one move boundary of unsorted subarray
        for (i = 0; i < n-1; i++) {
            
            // Find the minimum element in unsorted array
            min_idx = i;
            for (j = i+1; j < n; j++)
                if (vec[j] < vec[min_idx])
                    min_idx = j;
                    
            // Swap the found minimum element with the first element
            swap(vec[min_idx], vec[i]);
        }

    }
};

class BubbleDescendingSort : public Sort {
    virtual void readData(std::vector<int> & vec) { 
        for(int i = 1; i < 10; ++i) {
            vec.push_back(i);
        }    
    }
    
    virtual void sortData(std::vector<int> & vec) {
        size_t i, j;
        size_t  n = vec.size();
        for (i = 0; i < n-1; i++) {
            // Last i elements are already in place
            for (j = 0; j < n-i-1; j++) {
                if (vec[j] < vec[j+1])
                    swap(vec[j], vec[j+1]);
            }
        }
    }
};

int main() {
    std::vector<int> vec;

    Sort * sort = nullptr;

    std::cout << "Selection sort: \n";
    SelectionSort sel_sort;
    sort = &sel_sort;
    sort->processData(vec);

    vec.clear();

    std::cout << "Bubble descending sort: \n";
    BubbleDescendingSort bub_sort;
    sort = &bub_sort;
    sort->processData(vec);


    return 0;
}

/*******
    END OF FILE
***********/


