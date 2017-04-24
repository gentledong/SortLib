/*
思考了一下quickSort_intro，做出一些改进。
把insertSort_line或insertSort_binary安置在quickSort_loop里面，对于每个小区间（也就是小于stl_threashold的[left,right]段），用插入排序来处理。

排序结束后，整个区间是升序。

由于quickSort和heapSort都是“就地”排序，因此这种方案可行。

试验之后也能成功。
*/

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
		//insertSort_line(nums, left, right);
		insertSort_binary(nums, left, right);
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
	}//sift
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
			copy(nums.begin() + left + (high + 1), nums.begin() + left + i, nums.begin() + left + (high + 1 + 1));
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
				copy(nums.begin() + left, nums.begin() + left + i, nums.begin() + left + 1);
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
		return;
	}//quickSort_intro
};
