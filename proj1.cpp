#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;


//struct to hold maxSum and sub array start and endpoints
struct SubArr {
    double leftIndex;
    double rightIndex;
    double maxSum;
};

//prototypes
SubArr max_subarray_enumeration(vector<int>);
SubArr max_better_enumeration_subarray(vector<int>);
int max_divide_conquer_subarray(vector<int>, int, int);
SubArr max_linear_subarray(vector<int>);
int countVec(vector<int>);

//main
int main(){ 
    
	SubArr alg1;
	SubArr alg2;
	int alg3;
	SubArr alg4;

	vector<int> numArray;
	numArray.push_back(31);
	numArray.push_back(-41);
	numArray.push_back(59);
	numArray.push_back(26);
	numArray.push_back(-53);
	numArray.push_back(58);
	numArray.push_back(97);
	numArray.push_back(-93);
	numArray.push_back(-23);
	numArray.push_back(84);

	alg1 = max_subarray_enumeration(numArray);
	cout << alg1.maxSum << " ";

	alg2 = max_better_enumeration_subarray(numArray);
	cout << alg2.maxSum << " ";

	alg3 = max_divide_conquer_subarray(numArray, 0, countVec(numArray) - 1);
	cout << alg3 << " ";

	alg4 = max_linear_subarray(numArray);
	cout << alg4.maxSum << " ";

    //open file for reading
	ifstream inputfile("MSS_Problems.txt");
	if(inputfile.is_open()) {
        
    } else {
		cout <<"Unable to open file";
	}

	inputfile.close();

    return 0;
}

//Enumeration
SubArr max_subarray_enumeration(vector<int> arr){
    double sum = 0;
    double best = 0;
    SubArr testArr;

    for(int i = 0; i < arr.size(); i++){
        for(int j = i; j < arr.size(); j++){
            sum = 0;
			for (int k = i; k <= j; k++) {
                sum += arr[k];
            }
            if(sum > best){
                best = sum;
                testArr.leftIndex = i;
                testArr.rightIndex = j;
            }
        }
    }

    testArr.maxSum = best;
    
    return testArr;    
};


//Better Enumeration
SubArr max_better_enumeration_subarray(vector<int> arr){
    int sum = 0;
    int best = 0;
    SubArr testArr;
    
    for(int i = 0; i < arr.size(); i++){
		sum = 0;
        for(int j = i; j < arr.size(); j++){
            sum += arr[j];
            if(sum > best){
                best = sum;
                testArr.leftIndex = i;
                testArr.rightIndex = j;
            }
        }
	}
    testArr.maxSum = best;
    
    return testArr;
};

//Divid and Conquer
int max_divide_conquer_subarray(vector<int> arr, int left, int right){
	int middle;
	int leftres;
	int rightres;
	int leftmax;
	int rightmax;
	int temp;

	//this is the base case.  If it is down to 1 number, return that number
	if (right == left)  
		return arr[left];

	//finds the middle of the array
	middle = (left + right) / 2;

	//These next two lines are the recursion that send the newly formed left/right halves back into the max_divide function
	leftres = max_divide_conquer_subarray(arr, left, middle);
	rightres = max_divide_conquer_subarray(arr, middle + 1, right);
	
	leftmax = arr[middle];
	rightmax = arr[middle + 1];
	
	temp = 0;

	//This for loop adds up all of the numbers, starting from the middle and working towards the beginning.
	//When it is through, it will have the max sum for the left half of the array.
	for (int i = middle; i >= left; i--) {
		temp += arr[i];
		if (temp > leftmax)
			leftmax = temp;
	}
	temp = 0;

	//This for loop adds up all of the numbers, starting from the middle and working towards the end.
	//When it is through, it will have the max sum for the right half of the array.
	for (int i = middle + 1; i <= right; i++) {
		temp += arr[i];
		if (temp > rightmax)
			rightmax = temp;
	}

	//This returns the larger of the left half maximum, the right half maximum or the left + right max.
	return max(max(leftres, rightres), leftmax + rightmax);
};

//Linear-time
SubArr max_linear_subarray(vector<int> arr){
    //infinity from http://en.cppreference.com/w/cpp/types/numeric_limits/infinity
    double max_sum = -std::numeric_limits<double>::infinity();
    double ending_here_sum = -std::numeric_limits<double>::infinity();
    double ending_here_high = 0;
    double ending_here_low = 0;
	SubArr newArr;
	
    for(int i = 0; i < arr.size(); i++){
        ending_here_high = 0;
        if(ending_here_sum > 0){
            ending_here_sum = ending_here_sum + arr[i];
        }
        else {
            ending_here_low = i;
            ending_here_sum = arr[i];
        }
        if(ending_here_sum > max_sum){
            max_sum = ending_here_sum;
            newArr.maxSum = max_sum;
            newArr.leftIndex = ending_here_low;
            newArr.rightIndex = ending_here_high;
        }
    }
    return newArr;
};

int countVec(vector<int> arr) {
	int total;

	total = 0;

	for (int i = 0; i < arr.size(); i++)
	{
		total++;
	}

	return total;
};
