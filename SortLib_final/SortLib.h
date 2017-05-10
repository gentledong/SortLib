#pragma once
#include<vector>
using std::vector;
using std::less;

template<typename Elem, typename Storage = vector<Elem>, typename Compare = less<Elem> >
class SortLib {
private:
	Storage nums;
	Compare comp;
	bool numsIsReady = false;
public:
	SortLib() {}
	SortLib(const Storage &nums) {
		this->nums = nums;
		numsIsReady = true;
	}//SortLib
	void resetNums(const Storage &nums) {
		this->nums = nums;
		numsIsReady = true;
		return;
	}//resetNums
	void clearNums() {
		this->nums.clear();
		numsIsReady = false;
		return;
	}//clearNums
	Storage getNums() const {
		return nums;
	}//getNums
public:
	void quickSort_intro();//introSort ,basically imitating the source code of Sort of STL
	void mergeSort_recur();//mergeSort, based on recur
	void mergeSort_iterate();//mergeSort, based on iterate
	void heapSort();
	void selectSort();
	void bubbleSort();
	void shellSort();
	void shellSort_binary();
	inline void insertSort_line() {//插入排序，线性查找的
		insertSort_line(0, nums.size() - 1);
		return;
	}//insertSort
	inline void insertSort_binary() {//插入排序，折半查找的
		insertSort_binary(0, nums.size() - 1);
		return;
	}//insertSort_binary
	inline void quickSort() {//quickSort based on tail recrusion
		quickSort_loop(0, (int)nums.size() - 1);
		return;
	}//quickSort
private:
	const int stl_threshold = 16;//one const of introSort
	inline Elem medianOfThree(const Elem &a, const Elem &b, const Elem &c);//solve the medium value among a,b,c
	inline int lg(int n);//solve the maximum k, satisfing 2^k<=n
	void quickSort_loop(const int &left, int right, int deep_limit);//the core function of introSort
	void quickSort_loop(const int &left, int right);//the core function of quickSort
	int partition_median(int left, int right);//get the pivot of the sequence, range [left,right]
	void heapSort(int left, int right);//heapSort sequence, range [left,right]
	void siftDown(int root, int end);//sift the heap from up to down
	void insertSort_binary(int left, int right);//insertSort, range [left,right], based on binarySearch
	void insertSort_line(int left, int right);//insertSort, range [left,right], based on lineSearch
	void mergeSort_recur(const Storage &nums, Storage &nums_res, int start, int end);//mergeSort nums[start,end], result sequence will be stored in nums_res[start,end]
	void merge(const Storage &r, Storage &r1, int s, int m, int t);//one merge operator, merge r[s,m] and r[m+1,t], result sequence will be stored in r1 
	void mergePass(Storage &nums, int end, int step);//mergePass based on step
};

#include"SortLib.inl"
