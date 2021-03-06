/*
插入排序的两种实现，insertSort_line是线性插入排序，参考STL源码中的实现。
insertSort_binary是折半查找一下，来确定插入位置，更快。
*/

插入排序的两种实现，insertSort_line是线性插入排序，参考STL源码中的实现。
insertSort_binary是折半查找一下，来确定插入位置，更快。

#include<stdio.h>
#include<vector>
using std::vector;
using std::swap;

void insertSort_binary(vector<int> &nums, int left, int right) {
	//折半插入排序，不带哨兵的
	int size = right + 1;
	for (int i(left + 1); i < size; ++i) {
		if (nums[i] >= nums[i - 1])continue;
		int tmpI(nums[i]);
		int low(left), high(i - 1);
		while (low <= high) {
			int mid((low + high) >> 1);
			if (nums[mid] <= tmpI)low = mid + 1;
			else high = mid - 1;
		}//while
		copy(nums.begin() + (high + 1), nums.begin() + i, nums.begin() + (high + 1 + 1));
		nums[high + 1] = tmpI;
	}//for i
	return;
}//insertSort_binary
void insertSort_line(vector<int> &nums, int left, int right) {
	//插入排序，顺序查找的，不带哨兵的
	//每次先与nums[left]做判断，非常聪明。
	int size = right + 1;
	for (int i(left + 1); i < size; ++i) {
		int temp(nums[i]);
		if (temp < nums[left]) {
			copy(nums.begin() + left, nums.begin() + i, nums.begin() + left + 1);
			nums[left] = temp;
			continue;
		}//if
		int j(i - 1);
		for (; nums[j] > temp; --j)nums[j + 1] = nums[j];
		nums[j + 1] = temp;
	}//for i
	return;
}//insertSort_line


int main() {
	//vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,3,5 };
	//vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3 };
	//vector<int> nums{ 3,2 };
	//vector<int> nums{  };
	vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3 ,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3 };
	insertSort_line(nums, 0, nums.size() - 1);
	//insertSort_binary(nums, 0, nums.size() - 1);
	for (auto num : nums)printf("%d ", num); putchar(10);
	return 0;
}//main
