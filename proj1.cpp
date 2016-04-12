#include <iostream>
#include <limits>

//struct to hold maxSum and sub array start and endpoints
struct SubArr {
    int leftIndex;
    int rightIndex;
    int maxSum;
};

//prototypes
SubArr max_enumeration_subarray(int arr[], int count);
SubArr max_better_enumeration_subarray(int arr[], int count);
SubArr max_divid_conquer_subarray(int arr[], int count);
SubArr max_linear_subarray(int arr[], int count);


//main
int main(){ 
    
    return 0;
}

//Enumeration
SubArr max_subarray_enumeration(int arr[], int count){
    int sum = 0;
    int best = 0;
    SubArr SubArr;
    
    for(int i = 0; i < count; i++){
        for(int j = i; j < count; j++){
            sum = 0;
            for(int k = i; k <= j k++){
                sum += arr[k];
            }
            if(sum > best){
                best = sum;
                SubArr.leftIndex = i;
                SubArr.rightIndex = j;
            }
        }
    }
    SubArr.maxSum = best;
    
    return SubArr;    
};


//Better Enumeration
SubArr max_better_enumeration_subarray(int arr[], int count){
    int sum = 0;
    int best = 0;
    SubArr SubArr;
    
    for(int i = 0; i < count; i++){
        sum += arr[i];
        for(int j = 1; j < count; j++){
            sum += arr[j];
            if(sum > best){
                best = sum;
                SubArr.leftIndex = i;
                SubArr.rightIndex = j;
            }
        }
    }
    SubArr.maxSum = best;
    
    return SubArr;
};

//Divid and Conquer
SubArr max_divid_conquer_subarray(int arr[], int count){
  
    return SubArr;  
};

//Linear-time
SubArr max_linear_subarray(int arr[], int count){
    //infinity from http://en.cppreference.com/w/cpp/types/numeric_limits/infinity
    int max-sum = -std::numeric_limits<double>::infinity();
    int ending-here-sum = -std::numeric_limits<double>::infinity();
    int ending-here-high = 0;
    int ending-here-low = 0;
    
    for(int i = 0; i < count; i++){
        ending-here-high = 0;
        if(ending-here-sum > 0){
            ending-here-sum = ending-here-sum + a[i];
        }
        else {
            ending-here-low = j;
            ending-here-sum = a[j];
        }
        if(ending-here-sum > max-sum){
            max-sum = ending-here-sum;
            SubArr.maxSum = max-sum;
            SubArr.leftIndex = einding-here-low;
            SubArr.rightIndex = ending-here=high;
        }
    }
    return SubArr;
};