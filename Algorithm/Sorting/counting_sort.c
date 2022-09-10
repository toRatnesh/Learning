#include <stdio.h>
#include <string.h>

#define ERROR -1
#define N 100
#define MAX_RANGE_VAL 1000


int countingSort(int *arr_arg, int n, int max_val);

int main(void) {
	int arr[N] = {0};
	int n = 0;
	int max = 0;
	
	int i = 0;
	int ret_val = 0;
	
	fprintf(stdout, "Enter no of elements : ");
	fscanf(stdin, "%d", &n);
	
	memset(arr, 0, N);
	
	fprintf(stdout, "Enter all elements : ");
	for(i = 0; i < n; i++) {
		arr[i] = 0;
		fscanf(stdin, "%d", &arr[i]);
		
		if(0 == i) {
			max = arr[0];
		}
		
		if(max < arr[i]) {
			max = arr[i];
		}
	}
	
	if(n > 1) {
		ret_val = countingSort(arr, n, max);
	}
	
	fprintf(stdout, "\nAfter sorting \n");
	for(i = 0; i < n; i++) {
		fprintf(stdout, "%d ", arr[i]);
	}
	
	return 0;
}


int countingSort(int *arr_arg, int n, int max_val)
{
	int countArr[MAX_RANGE_VAL + 1] = {0};
	int sortArr[N] = {0};
	
	int i = 0;	
	
	memset(countArr, 0, MAX_RANGE_VAL);
	memset(sortArr, 0, N);
	
	// store frequency of each array element
	for(i = 0; i < n; i++) {
		countArr[arr_arg[i]] = countArr[arr_arg[i]] + 1;
	}
	
	// update countArr to store actual position of elements in array.
	for(i = 1; i <= max_val; i++) {
		countArr[i] = countArr[i] + countArr[i - 1];
	}
	
	for(i = (n - 1); i >= 0; i--) {
		countArr[arr_arg[i]] = countArr[arr_arg[i]] - 1;
		sortArr[countArr[arr_arg[i]]] = arr_arg[i];
	}	
	
	for(i = 0; i < n; i++) {
		arr_arg[i] = sortArr[i];
		//fprintf(stdout, "%d ", sortArr[i]);
	}
	
	return 0;
}



