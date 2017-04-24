#include<stdio.h>
#include"SortLib.h"
#include<vector>
using std::vector;

int main() {
	vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,3,5 };
	//vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3 };
	//vector<int> nums{ 3,2 };
	//vector<int> nums{  };
	//vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3 ,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3 };
	SortLib<int> mySort;
	mySort.resetNums(nums);
	mySort.quickSort_intro();
	//mySort.bubbleSort();
	//mySort.heapSort();
	//mySort.insertSort_binary();
	//mySort.insertSort_line();
	//mySort.mergeSort_iterate();
	//mySort.mergeSort_recur();
	//mySort.quickSort();
	auto vec = mySort.getNums();
	for (auto num : vec)printf("%d ", num); putchar(10);

	return 0;
}//main
