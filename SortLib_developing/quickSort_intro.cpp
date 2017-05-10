/*
参考STL的sort函数，给出的实现。
quickSort_loop中设计了stl_threshold常量和deep_limit变量，分别用来衡量区间长度和分割深度。
区间长度小于stl_threshold就停止快排，分割深度多于2*lg(right-left+1）就将[left,right]区间用heapSort来排。
quickSort_intro函数中quickSort_loop结束，
整个区间[0,nums.size()-1]是由很多小区间组成，这些小区间内部无序，但是彼此有先后顺序，所以整个区间算是基本有序。
因此对[0,nums.size()-1]来一个insertSort_line，效率会很高。
当然也可以用insertSort_binary来完成这个收尾工作。
*/

#include<stdio.h>
#include<vector>
using std::vector;
using std::swap;

class introSort {
private:
	void quickSort_loop(vector<int> &nums, const int &left, int right, int deep_limit) {
		while (right - left > stl_threshold) {
			if (deep_limit == 0) {
				heapSort(nums, left, right);
				return;
			}//if
			--deep_limit;
			int mid = partition_median(nums, left, right);
			quickSort_loop(nums, mid, right, deep_limit);
			right = mid - 1;
		}//while
		return;
	}//quickSort_loop
	int partition_median(vector<int> &nums, int left, int right) {
		int pivot = medianOfThree(nums[left], nums[(left + right + 1) >> 1], nums[right]);
		while (true) {
			while (nums[left] < pivot)++left;
			while (nums[right] > pivot)--right;
			if (left >= right)return left;
			swap(nums[left++], nums[right]);
		}//while
	}//partition_median
	void heapSort(vector<int> &nums, int left, int right) {
		int size = right + 1;
		for (int i((size - 1 - 1) >> 1); i >= left; --i)siftDown(nums, i, size - 1);//初始建堆，从最后一个非终端结点至根结点
		for (int i(size - 1); i>left; --i) {//重复执行移走堆顶及重建堆的操作
			swap(nums[left], nums[i]);
			siftDown(nums, left, i - 1);
		}//for i
		return;
	}//heapSort
	void siftDown(vector<int> &nums, int root, int end) {
		int indexChild((root << 1) + 1);
		while (indexChild <= end) {
			if (indexChild + 1 <= end&&nums[indexChild] < nums[indexChild + 1])++indexChild;
			if (nums[root] >= nums[indexChild])break;
			swap(nums[root], nums[indexChild]);
			root = indexChild;
			indexChild = (root << 1) + 1;
		}//while
		return;
	}//siftDown
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
private:
	const int stl_threshold = 16;
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
	int lg(int n) {//2^k<=n，求k值
		int k(0);
		for (; n > 1; n >>= 1) ++k;//1相当于2^0。
		return k;
	}//lg
public:
	void quickSort_intro(vector<int> &nums) {
		int left(0), right((int)nums.size() - 1);
		quickSort_loop(nums, left, right, 2 * lg(right - left + 1));
		insertSort_line(nums, left, right);
		//insertSort_binary(nums, left, right);
		return;
	}//quickSort_intro
};

int main() {
	//vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,3,5 };
	//vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3 };
	//vector<int> nums{ 3,2 };
	//vector<int> nums{  };
	vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3 ,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3 };
	introSort mySort;
	mySort.quickSort_intro(nums);
	for (auto num : nums)printf("%d ", num); putchar(10);
	return 0;
}//main
