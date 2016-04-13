#include <iostream>
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <cstring>
#include <limits>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cmath>
#include <time.h>

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
void experimentalAnalysis();

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
	cout << alg4.maxSum << " " << endl;;
    
    numArray.clear();
    
    SubArr subArr1;
	SubArr subArr2;
	//SubArr subArr3;
	SubArr subArr4;

    //open file for reading
	ifstream inputfile("MSS_Problems.txt");
	if(inputfile.is_open()) {
        string line;	//line to be read from file
		char * numline;	//c-string copy of line
		char * num;		//number from line
        while(getline(inputfile, line)) {
			//rest variables
			numline = NULL;
			num = NULL;
            
            vector<int> numVec;
            
            //convert line to numline
			numline = new char [line.size()+1];
			strcpy (numline, line.c_str());
            num = strtok (numline, " ,[]");
			while (num != NULL) {
				numVec.push_back(atoi(num));
				num = strtok (NULL, " ,[]");
			}
            
            subArr1 = max_subarray_enumeration(numVec);

            subArr2 = max_better_enumeration_subarray(numVec);
            
            //subArr3 = max_divide_conquer_subarray(numVec, 0, countVec(numVec) - 1);

            subArr4 = max_linear_subarray(numVec);
            
            ofstream outputfile ("MSS_Results.txt", ios::app);
			if(outputfile.is_open()) {
                //print original array
                outputfile << "Origional Array:" <<endl;
				outputfile << "[ ";
				for(int i=0; i< numVec.size(); i++) {
					outputfile << numVec.at(i) << " ";
				}
				outputfile << "]\n" <<endl;
                
                //Algorithm 1
				outputfile << "ALGORITHM 1:"<<endl;
				outputfile << "[ ";
				for (int i=subArr1.leftIndex; i<=subArr1.rightIndex; i++) {
				outputfile << numVec.at(i) << " ";
				}
				outputfile << "]" <<endl;
                outputfile << subArr1.maxSum<<"\n"<<endl;
                
                //Algorithm 2
				outputfile << "ALGORITHM 2:"<<endl;
				outputfile << "[ ";
				for (int i=subArr2.leftIndex; i<=subArr2.rightIndex; i++) {
				outputfile << numVec.at(i) << " ";
				}
				outputfile << "]" <<endl;
                outputfile << subArr2.maxSum<<"\n"<<endl;
                
                // //Algorithm 3
				// outputfile << "ALGORITHM 3:"<<endl;
				// outputfile << "[ ";
				// for (int i=subArr3.leftIndex; i<=subArr3.rightIndex; i++) {
				// outputfile << numVec.at(i) << " ";
				// }
				// outputfile << "]" <<endl;
                // outputfile << subArr4.maxSum<<"\n"<<endl;
                
                //Algorithm 4
				outputfile << "ALGORITHM 4:"<<endl;
				outputfile << "[ ";
				for (int i=subArr4.leftIndex; i<=subArr4.rightIndex; i++) {
				outputfile << numVec.at(i) << " ";
				}
				outputfile << "]" << endl;
                outputfile << subArr4.maxSum<<"\n"<<endl;
             
                   
  
            } else {
				cout <<"Unable to open file";
			}
            
            numVec.clear();
			outputfile << "------------------------------------------------\n"<<endl;
			outputfile.close();
        }
    } else {
		cout <<"Unable to open file";
	}

	inputfile.close();

    experimentalAnalysis();
    
    
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
                sum += arr.at(k);
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
            sum += arr.at(j);
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
    int max_sum = -std::numeric_limits<double>::infinity();
    int ending_here_sum = -std::numeric_limits<double>::infinity();
    int ending_here_high = 0;
    int ending_here_low = 0;
	SubArr newArr;
	
    for(int i = 0; i < arr.size(); i++){
        ending_here_high = i;
        if(ending_here_sum > 0){
            ending_here_sum = ending_here_sum + arr.at(i);
        }
        else {
            ending_here_low = i;
            ending_here_sum = arr.at(i);
        }
        
        if(ending_here_sum > max_sum){
            max_sum = ending_here_sum;
            newArr.leftIndex = ending_here_low;
            newArr.rightIndex = ending_here_high;
        }
        
    }
    newArr.maxSum = max_sum;
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

void experimentalAnalysis(){
    SubArr subArr1;
    SubArr subArr2;
    SubArr subArr3;
    SubArr subArr4;
    
    clock_t alg1;
    clock_t alg2;
    clock_t alg3;
    clock_t alg4;
    
    int alg1_avg = 0;
    int alg2_avg = 0;
    int alg3_avg = 0;
    int alg4_avg = 0;
    
    for(int i = 1; i <= 100; i*=2){
        int n=i*100;
        //10 arrays per count
        for(int j=0; j<10; j++){
            vector<int> numArray (n);
            
            //random array
            for(int k=0; k<n; k++){
                numArray.at(k) = (rand() % (100 - (-100))) + (-100);
            }

            //algorithm 1
            alg1 = clock();
            subArr1 = max_subarray_enumeration(numArray);
            alg1 = clock() - alg1;
            alg1_avg += alg1;
            
            //algorithm 2
            alg2 = clock();
            subArr2 = max_better_enumeration_subarray(numArray);
            alg2 = clock() - alg2;
            alg2_avg += alg2;
            
            //algorithm 3
            // alg3 = clock();
            // subArr3 = max_divide_conquer_subarray(numArray, 0, countVec(numArray) - 1);
            // alg3 = clock() - alg3;
            // alg3_avg += alg3;
            
            //algorithm 4
            alg4 = clock();
            subArr4 = max_linear_subarray(numArray);
            alg4 = clock() - alg4;
            alg4_avg += alg4;
            
            numArray.clear();
            
        }
        alg1_avg /= 10;
        alg2_avg /= 10;
        //alg3_avg /= 10;
        alg4_avg /= 10;
        
        cout<<"Algorithm 1, n="<<n<<": "<<((long double)alg1)/(CLOCKS_PER_SEC/1000)<<" ms"<<endl;
        cout<<"Algorithm 2, n="<<n<<": "<<((long double)alg2)/(CLOCKS_PER_SEC/1000)<<" ms"<<endl;
        //cout<<"Algorithm 3, n="<<n<<": "<<((double)alg3)/(CLOCKS_PER_SEC/1000)<<" ms"<<endl;
        cout<<"Algorithm 4, n="<<n<<": "<<((long double)alg4)/(CLOCKS_PER_SEC/1000)<<" ms"<<endl;

        alg1_avg = 0;
        alg2_avg = 0;
        alg3_avg = 0;
        alg4_avg = 0;
    }
};