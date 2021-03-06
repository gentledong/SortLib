/*
堆排实现，heapSort分两步：
先建立堆。
再移走堆顶，不断调整。
详细请参考heapSort的模板实现，我的另一个仓库中。

此处与STL源码有个不同，siftDown函数中，如果当前结点的左右孩子的值相等，并且当前结点值小于左右孩子，会优先选择与左孩子交换。
*/

#include<stdio.h>
#include<vector>
using std::vector;
using std::swap;

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
void heapSort(vector<int> &nums, int left, int right) {
	int size = right + 1;
	for (int i((size - 1 - 1) >> 1); i >= left; --i)siftDown(nums, i, size - 1);//初始建堆，从最后一个非终端结点至根结点
	for (int i(size - 1); i>left; --i) {//重复执行移走堆顶及重建堆的操作
		swap(nums[left], nums[i]);
		siftDown(nums, left, i - 1);
	}//for i
	return;
}//heapSort

int main() {
	//vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,3,5 };
	//vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3 };
	//vector<int> nums{ 3,2 };
	//vector<int> nums{  };
	vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3 ,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3,3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3 };
	heapSort(nums, 0, nums.size() - 1);
	for (auto num : nums)printf("%d ", num); putchar(10);
	return 0;
}//main
