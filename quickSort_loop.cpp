/*
内部采用vector来实现，默认升序，默认元素是int。
主要使用尾递归的方式来完成quickSort。

partition_median将[left,right]分成两部分。
枢轴元素是首、中、尾三个值的中位数，pivot由medianOfThree来得到。

quickSort_loop是递归函数，采用尾递归来编写。
内部有while循环控制，先做右边，再做左边。
*/

#include<stdio.h>
#include<vector>
using std::vector;
using std::swap;

int medianOfThree(const int &a, const int &b, const int &c) {
	if (a < b) {
		if (b < c)return b;//a<b<c
		if (a < c)return c;//a<c<=b
		return a;//b>a>=c
	}//if
	if (a < c)return a;//c>a>=b
	if (b < c)return c;//a>=c>b
	return b;//a>=b>=c
}//medianOfThree

int partition_median(vector<int> &nums, int left,int right) {
	int pivot = medianOfThree(nums[left], nums[(left + right + 1) >> 1], nums[right]);
	//printf("left=%d,right=%d,pivot=%d\n",left,right,pivot);
	while (true) {
		while (nums[left] < pivot)++left;
		while (nums[right] > pivot)--right;
		if (left >= right)return left;
		swap(nums[left++],nums[right]);
	}//while
}//partition_median

void quickSort_loop(vector<int> &nums,const int &left, int right) {
	while (left < right) {
		int mid = partition_median(nums, left, right);
		/*printf("nums[%d]=%d\n",mid,nums[mid]);
		for (auto num : nums)printf("%d ", num); putchar(10);
		system("pause");*/
		quickSort_loop(nums, mid, right);
		right = mid - 1;
	}//while
	return;
}//quickSort_loop

void quickSort(vector<int> &nums) {
	quickSort_loop(nums, 0, (int)nums.size() - 1);
	return;
}//quickSort

int main() {
	vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,3,5 };
	//vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3 };
	//vector<int> nums{ 3,2 };
	//vector<int> nums{  };
	quickSort(nums);
	for (auto num : nums)printf("%d ", num); putchar(10);
	return 0;
}//main
