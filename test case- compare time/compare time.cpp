#include<stdio.h>
#include<time.h>
#include<string.h>
#include<Windows.h>
#include<stdio.h>
#include<vector>
#include<functional>
#include<time.h>
#include<random>
using std::srand;
using std::vector;
using std::swap;
using std::less;
using std::greater;

void printVec(vector<int>::iterator left, vector<int>::iterator right) {
	for (auto iter(left); iter < right; ++iter)printf("%d ", *iter);
	printf("\n");
	return;
}//printVec
void print_time(const char *head) {
	SYSTEMTIME rawtime;
	GetLocalTime(&rawtime);

	static int ms = rawtime.wMilliseconds;
	int out_ms = rawtime.wMilliseconds - ms;
	ms = rawtime.wMilliseconds;
	static int s = rawtime.wSecond;
	int out_s = rawtime.wSecond - s;
	s = rawtime.wSecond;
	static int minute = rawtime.wMinute;
	int out_minute = rawtime.wMinute - minute;
	minute = rawtime.wMinute;
	static int hour = rawtime.wHour;
	int out_hour = rawtime.wHour - hour;
	hour = rawtime.wHour;

	if (out_ms < 0) {
		out_ms += 1000;
		--out_s;
	}//if
	if (out_s < 0) {
		out_s += 60;
		--out_minute;
	}//if
	if (out_minute < 0) {
		out_minute += 60;
		--out_hour;
	}//if

	static bool isFirst(true);
	if (isFirst == true) {
		char tmp[64] = "";
		const char week[][3] = { "日","一","二","三","四","五","六" };
		sprintf(tmp, "星期%s %04d年%02d月%d日 %02d:%02d:%02d", week[rawtime.wDayOfWeek], rawtime.wYear, rawtime.wMonth, rawtime.wDay, rawtime.wHour, rawtime.wMinute, rawtime.wSecond);
		printf("%s date/time is \"%s\"\n", head, tmp);
		isFirst = false;
	}
	else {
		printf("%s time consumed %02d:%02d:%02d.%04d\n", head, out_hour, out_minute, out_s, out_ms);
		isFirst = true;
	}//if else
	return;
}//print_time
template<typename Elem, typename Storage = vector<Elem>, typename Compare = less<Elem> >
class SortLib {//template <typename Elem> const 组合
public:
	SortLib(const Storage &nums) {
		this->nums = nums;
		numsIsReady = true;
		return;
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
private:
	Storage nums;
	Compare comp;
	bool numsIsReady = false;
private:
	const int stl_threshold = 16;
	Elem medianOfThree(const Elem &a, const Elem &b, const Elem &c) {
		if (comp(a, b) == true) {
			if (comp(b, c) == true)return b;//a<b<c
			if (comp(a, c) == true)return c;//a<c<=b
			return a;//b>a>=c
		}//if
		if (comp(a, c) == true)return a;//c>a>=b
		if (comp(b, c) == true)return c;//a>=c>b
		return b;//a>=b>=c
	}//medianOfThree
	int lg(int n) {//2^k<=n，求k值
		int k(0);
		for (; n > 1; n >>= 1) ++k;//1相当于2^0。
		return k;
	}//lg
	void quickSort_loop(const int &left, int right, int deep_limit) {
		while (right - left > stl_threshold) {
			if (deep_limit == 0) {
				heapSort(left, right);
				return;
			}//if
			--deep_limit;
			int mid = partition_median(left, right);
			quickSort_loop(mid, right, deep_limit);
			right = mid - 1;
		}//while
		return;
	}//quickSort_loop
	void quickSort_loop(const int &left, int right) {
		while (left < right) {
			int mid = partition_median(left, right);
			quickSort_loop(mid, right);
			right = mid - 1;
		}//while
		return;
	}//quickSort_loop
	int partition_median(int left, int right) {
		Elem pivot = medianOfThree(nums[left], nums[(left + right + 1) >> 1], nums[right]);
		while (true) {
			while (comp(nums[left], pivot) == true)++left;
			while (comp(pivot, nums[right]) == true)--right;
			if (left >= right)return left;
			swap(nums[left++], nums[right]);
		}//while
	}//partition_median
	void heapSort(int left, int right) {
		int size = right + 1;
		for (int i((size - 1 - 1) >> 1); i >= left; --i)siftDown(i, size - 1);//初始建堆，从最后一个非终端结点至根结点
		for (int i(size - 1); i>left; --i) {//重复执行移走堆顶及重建堆的操作
			swap(nums[left], nums[i]);
			siftDown(left, i - 1);
		}//for i
		return;
	}//heapSort
	void siftDown(int root, int end) {
		int indexChild((root << 1) + 1);
		while (indexChild <= end) {
			if (indexChild + 1 <= end&&comp(nums[indexChild], nums[indexChild + 1]) == true)++indexChild;
			if (comp(nums[root], nums[indexChild]) == false)break;
			swap(nums[root], nums[indexChild]);
			root = indexChild;
			indexChild = (root << 1) + 1;
		}//while
		return;
	}//siftDown
	void insertSort_binary(int left, int right) {
		//折半插入排序，不带哨兵的
		int size = right + 1;
		for (int i(left + 1); i < size; ++i) {
			if (comp(nums[i], nums[i - 1]) == false)continue;
			Elem tmpI(nums[i]);
			int low(left), high(i - 1);
			while (low <= high) {
				int mid((low + high) >> 1);
				if (comp(nums[mid], tmpI) == true || nums[mid] == tmpI)low = mid + 1;
				else high = mid - 1;
			}//while
			copy(nums.begin() + (high + 1), nums.begin() + i, nums.begin() + (high + 1 + 1));
			nums[high + 1] = tmpI;
		}//for i
		return;
	}//insertSort_binary
	void insertSort_line(int left, int right) {
		//插入排序，顺序查找的，不带哨兵的
		int size = right + 1;
		for (int i(left + 1); i < size; ++i) {
			Elem temp(nums[i]);
			if (comp(temp, nums[left]) == true) {
				copy(nums.begin() + left, nums.begin() + i, nums.begin() + left + 1);
				nums[left] = temp;
				continue;
			}//if
			int j(i - 1);
			for (; comp(nums[j], temp) == false && nums[j] != temp; --j)nums[j + 1] = nums[j];
			nums[j + 1] = temp;
		}//for i
		return;
	}//insertSort_line

public:
	//内省式排序，完全模仿sort源码
	void quickSort_intro() {
		if (numsIsReady == false)return;
		int left(0), right((int)nums.size() - 1);
		quickSort_loop(left, right, 2 * lg(right - left + 1));
		insertSort_line(left, right);
		//insertSort_binary(left, right);
		return;
	}//quickSort_intro

public:
	//归并排序的递归算法
	void mergeSort2() {
		if (numsIsReady == false)return;
		Storage nums_res(nums.size()), nums_assist(nums.size());
		mergeSort_recur(nums, nums_res, 0, nums.size() - 1);
		nums = nums_res;
		return;
	}//mergeSort2
private:
	//vector<int> nums;do something
	//mergeSort_recur递归函数省略掉了nums_assist这个形参，代之以vector<int> nums_assist(nums);这个栈数组。
	//程序功能上跟以前一致，这样也更容易理解。
	//各种版本都可以参考文件“各种排序code2.txt”。
	void mergeSort_recur(const Storage &nums, Storage &nums_res, int start, int end) {
		if (start == end) {
			nums_res[start] = nums[start];
			return;
		}//if
		int mid((start + end) >> 1);
		Storage nums_assist(nums);
		mergeSort_recur(nums, nums_assist, start, mid);//归并排序前半个子序列
		mergeSort_recur(nums, nums_assist, mid + 1, end);//归并排序后半个子序列
		merge(nums_assist, nums_res, start, mid, end);//将两个已排序的子序列归并
		return;
	}//mergeSort_recur	
	 //一次归并
	void merge(const Storage &r, Storage &r1, int s, int m, int t) {
		int i(s), j(m + 1), k(s);
		while (i <= m && j <= t) {
			if (comp(r[i], r[j]) == true || r[i] == r[j])r1[k++] = r[i++];//取r[i]和r[j]中较小者放入r1[k]
			else r1[k++] = r[j++];
		}//while
		while (i <= m)r1[k++] = r[i++];//若第一个子序列没处理完，则进行收尾处理         
		while (j <= t)r1[k++] = r[j++];//若第二个子序列没处理完，则进行收尾处理        
		return;
	}//merge
public:
	//归并排序的非递归算法
	void mergeSort1() {
		if (numsIsReady == false)return;
		int size = (int)nums.size();
		for (int step(1); step < size; step <<= 1) mergePass(nums, size - 1, step);//以步长step完成一趟归并
		return;
	}//mergeSort1
private:
	//一趟归并
	void mergePass(Storage &nums, int end, int step) {
		Storage nums_lamb(nums.size());
		int i(0);
		for (; i <= end + 1 - (step << 1); i += step << 1) merge(nums, nums_lamb, i, i + step - 1, i + (step << 1) - 1);//待归并记录至少有两个长度为step的子序列
		if (i <= end + 1 - step) merge(nums, nums_lamb, i, i + step - 1, end);//待归并序列中剩下的部分长度不足两个step，但是多余1个step
		else for (int k(i); k <= end; ++k)nums_lamb[k] = nums[k];//待归并序列中只剩一个子序列，这个子序列太短了，长度小于step
		nums = nums_lamb;
		return;
	}//mergePass
public:
	//堆排序
	void heapSort() {
		if (numsIsReady == false)return;
		heapSort(0, nums.size() - 1);
		return;
	}//heapSort
public:
	//简单选择排序
	void selectSort() {
		int size = (int)nums.size();
		//对n个记录进行n-1趟简单选择排序
		for (int i(0); i<size - 1; ++i) {
			int index(i);
			//在无序区中选取最小记录
			for (int j(i + 1); j < size; ++j)if (comp(nums[j], nums[index]) == true)index = j;
			if (index != i)swap(nums[i], nums[index]);
		}//for i
		return;
	}//selectSort
public:
	//起泡排序，这个“大数下沉”的排序相当优秀，主要是哪个exchange的变量，定义地非常赞。
	//每次exchange初始为0，如果已经全体有序了，exchange自然还为0，后面不用再工作了。
	//如果还有没有调整好的地方，exchange最终标记的就是最大的范围。
	void bubbleSort() {
		int size = (int)nums.size();
		int exchange(size - 1);
		//第一趟起泡排序的范围是r[0]到r[n-1]	          
		while (exchange) {//仅当上一趟排序有记录交换才进行本趟排序
			int bound(exchange);
			exchange = 0;
			for (int j = 0; j < bound; j++)if (comp(nums[j], nums[j + 1]) == false && nums[j] != nums[j + 1]) {//一趟起泡排序
				Elem tmp(nums[j]);
				nums[j] = nums[j + 1];
				nums[j + 1] = tmp;
				exchange = j;//记录每一次发生记录交换的位置
			}//for j;if
		}//while
		return;
	}//bubbleSort
	 //希尔排序，顺序查找的
	void shellSort() {
		int size = (int)nums.size();
		for (int d(size >> 1); d >= 1; d >>= 1) {
			for (int i(0 + d); i<size; ++i) {
				Elem tmp(nums[i]);
				int j(i - d);
				for (; j >= 0 && comp(nums[j], tmp) == false && nums[j] != tmp; j -= d)nums[j + d] = nums[j];
				nums[j + d] = tmp;
			}//for i
		}//for d
		return;
	}//ShellSort
	 //希尔排序，折半查找的，发现一个非常精妙的bug，就是当d>1时，mid的确定，需要仔细搞。并不是简单的(low+high)>>1了，也不是/d再*d这么简单。正确的处理办法需要加上low_backup，数学上的专业术语就是等差数列的列头数字。
	void shellSort_binary() {
		int size = (int)nums.size();
		for (int d(size >> 1); d >= 1; d >>= 1) {
			for (int i(0 + d); i<size; ++i) {
				if (comp(nums[i], nums[i - d]) == false)continue;
				Elem tmp(nums[i]);
				int low(i - d);
				while (low - d >= 0)low -= d;
				int low_backup(low);
				int high(i - d);
				while (low <= high) {
					//int mid((low+high)>>1);
					//int mid( ( ((low + high) / d ) >> 1) * d);
					int n1 = (low - low_backup) / d + 1;
					int n2 = (high - low_backup) / d + 1;
					int n3((n1 + n2) >> 1);
					int mid = low_backup + (n3 - 1)*d;
					if (comp(nums[mid], tmp) == true || nums[mid] == tmp)low = mid + d;
					else high = mid - d;
				}//while
				for (int j(i - d); j >= high + d; j -= d) nums[j + d] = nums[j];
				nums[high + d] = tmp;
			}//for i
		}//for d
		return;
	}//shellSort_binary
	 //插入排序，线性查找的
	void insertSort() {
		insertSort_line(0, nums.size() - 1);
		return;
	}//insertSort
	 //插入排序，折半查找的
	void insertSort_binary() {
		insertSort_binary(0, nums.size() - 1);
		return;
	}//insertSort_binary
	void quickSort() {
		quickSort_loop(0, (int)nums.size() - 1);
		return;
	}//quickSort
};

//每个小段使用insertSort_line来处理
class SortLib2 {
private:
	void quickSort_loop(const int &left, int right, int deep_limit) {
		while (right - left > stl_threshold) {
			if (deep_limit == 0) {
				heapSort(left, right);
				return;
			}//if
			--deep_limit;
			int mid = partition_median(nums, left, right);
			quickSort_loop(mid, right, deep_limit);
			right = mid - 1;
		}//while
		insertSort_line(left, right);
		//insertSort_binary(left, right);
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
	void heapSort(int left, int right) {
		int size = right + 1;
		for (int i((size - 1 - 1) >> 1); i >= left; --i)siftDown(i, size - 1);//初始建堆，从最后一个非终端结点至根结点
		for (int i(size - 1); i>left; --i) {//重复执行移走堆顶及重建堆的操作
			swap(nums[left], nums[i]);
			siftDown(left, i - 1);
		}//for i
		return;
	}//heapSort
	void siftDown(int root, int end) {
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
	void insertSort_binary(int left, int right) {
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
	void insertSort_line(int left, int right) {
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
	void quickSort_intro() {
		int left(0), right((int)nums.size() - 1);
		quickSort_loop(left, right, 2 * lg(right - left + 1));
		return;
	}//quickSort_intro
public:
	SortLib2(const vector<int> &nums) {
		this->nums = nums;
		return;
	}//SortLib2
	void resetNums(const vector<int> &nums) {
		this->nums = nums;
		return;
	}//resetNums
private:
	vector<int> nums;
};
//最后使用insertSort_binary来处理
class SortLib3 {
private:
	void quickSort_loop(const int &left, int right, int deep_limit) {
		while (right - left > stl_threshold) {
			if (deep_limit == 0) {
				heapSort(left, right);
				return;
			}//if
			--deep_limit;
			int mid = partition_median(left, right);
			quickSort_loop(mid, right, deep_limit);
			right = mid - 1;
		}//while
		return;
	}//quickSort_loop
	int partition_median(int left, int right) {
		int pivot = medianOfThree(nums[left], nums[(left + right + 1) >> 1], nums[right]);
		while (true) {
			while (nums[left] < pivot)++left;
			while (nums[right] > pivot)--right;
			if (left >= right)return left;
			swap(nums[left++], nums[right]);
		}//while
	}//partition_median
	void heapSort(int left, int right) {
		int size = right + 1;
		for (int i((size - 1 - 1) >> 1); i >= left; --i)siftDown(i, size - 1);//初始建堆，从最后一个非终端结点至根结点
		for (int i(size - 1); i>left; --i) {//重复执行移走堆顶及重建堆的操作
			swap(nums[left], nums[i]);
			siftDown(left, i - 1);
		}//for i
		return;
	}//heapSort
	void siftDown(int root, int end) {
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
	void insertSort_binary(int left, int right) {
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
	void insertSort_line(int left, int right) {
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
	void quickSort_intro() {
		int left(0), right((int)nums.size() - 1);
		quickSort_loop(left, right, 2 * lg(right - left + 1));
		//insertSort_line(left, right);
		insertSort_binary(left, right);
		return;
	}//quickSort_intro
public:
	SortLib3(const vector<int> &nums) {
		this->nums = nums;
		return;
	}//SortLib3
	void resetNums(const vector<int> &nums) {
		this->nums = nums;
		return;
	}//resetNums
private:
	vector<int> nums;
};
//每个小段使用insertSort_binary来处理
class SortLib4 {
private:
	void quickSort_loop(const int &left, int right, int deep_limit) {
		while (right - left > stl_threshold) {
			if (deep_limit == 0) {
				heapSort(left, right);
				return;
			}//if
			--deep_limit;
			int mid = partition_median(left, right);
			quickSort_loop(mid, right, deep_limit);
			right = mid - 1;
		}//while
		 //insertSort_line(left, right);
		insertSort_binary(left, right);
		return;
	}//quickSort_loop
	int partition_median(int left, int right) {
		int pivot = medianOfThree(nums[left], nums[(left + right + 1) >> 1], nums[right]);
		while (true) {
			while (nums[left] < pivot)++left;
			while (nums[right] > pivot)--right;
			if (left >= right)return left;
			swap(nums[left++], nums[right]);
		}//while
	}//partition_median
	void heapSort(int left, int right) {
		int size = right + 1;
		for (int i((size - 1 - 1) >> 1); i >= left; --i)siftDown(i, size - 1);//初始建堆，从最后一个非终端结点至根结点
		for (int i(size - 1); i>left; --i) {//重复执行移走堆顶及重建堆的操作
			swap(nums[left], nums[i]);
			siftDown(left, i - 1);
		}//for i
		return;
	}//heapSort
	void siftDown(int root, int end) {
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
	void insertSort_binary(int left, int right) {
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
	void insertSort_line(int left, int right) {
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
	void quickSort_intro() {
		int left(0), right((int)nums.size() - 1);
		quickSort_loop(left, right, 2 * lg(right - left + 1));
		return;
	}//quickSort_intro
	SortLib4(const vector<int> &nums) {
		this->nums = nums;
		return;
	}//SortLib4
	void resetNums(const vector<int> &nums) {
		this->nums = nums;
		return;
	}//resetNums
private:
	vector<int> nums;
};
//最后使用insertSort_line来处理
class SortLib5 {
private:
	void quickSort_loop(const int &left, int right, int deep_limit) {
		while (right - left > stl_threshold) {
			if (deep_limit == 0) {
				heapSort(left, right);
				return;
			}//if
			--deep_limit;
			int mid = partition_median(left, right);
			quickSort_loop(mid, right, deep_limit);
			right = mid - 1;
		}//while
		return;
	}//quickSort_loop
	int partition_median(int left, int right) {
		int pivot = medianOfThree(nums[left], nums[(left + right + 1) >> 1], nums[right]);
		while (true) {
			while (nums[left] < pivot)++left;
			while (nums[right] > pivot)--right;
			if (left >= right)return left;
			swap(nums[left++], nums[right]);
		}//while
	}//partition_median
	void heapSort(int left, int right) {
		int size = right + 1;
		for (int i((size - 1 - 1) >> 1); i >= left; --i)siftDown(i, size - 1);//初始建堆，从最后一个非终端结点至根结点
		for (int i(size - 1); i>left; --i) {//重复执行移走堆顶及重建堆的操作
			swap(nums[left], nums[i]);
			siftDown(left, i - 1);
		}//for i
		return;
	}//heapSort
	void siftDown(int root, int end) {
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
	void insertSort_binary(int left, int right) {
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
	void insertSort_line(int left, int right) {
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
	void quickSort_intro() {
		int left(0), right((int)nums.size() - 1);
		quickSort_loop(left, right, 2 * lg(right - left + 1));
		insertSort_line(left, right);
		//insertSort_binary(left, right);
		return;
	}//quickSort_intro
public:
	SortLib5(const vector<int> &nums) {
		this->nums = nums;
		return;
	}//SortLib5
	void resetNums(const vector<int> &nums) {
		this->nums = nums;
		return;
	}//resetNums
private:
	vector<int> nums;
};
int random(const int &a, const int &b) {//a<b,[a,b]
	return (int)(0.5 + a + (1.0*rand() / RAND_MAX)*(b - a));
}//random
int main() {
	//vector<int> nums{ 3,4,1,1,3,2,5,6,9,8,1,3,4,3,5 };
	//vector<int> nums{ 3,2 };
	//vector<int> nums{  };
	//vector<int> nums_{ 3,4,1,1,3,2,5,6,9,8,1,3,4,33,33,2,2,2,1,33,3 };
	srand((unsigned)time(NULL));
	vector<int> nums(100000000);
	printf("nums.size=%d\n",nums.size());
	for (int i(0); i < 100000000; ++i) {
		nums[i] = random(0, i);
	}//for i
	//SortLib<int, vector<int>, greater<int> > mySort(nums_);
	SortLib<int> mySort(nums);
	print_time("QuickSort_intro:");
	mySort.quickSort_intro();
	//mySort.mergeSort1();
	//mySort.mergeSort2();//递归的，太大栈爆了
	//mySort.heapSort();
	//mySort.selectSort();
	//mySort.bubbleSort();
	//mySort.insertSort();
	//mySort.insertSort_binary();
	//mySort.shellSort();
	//mySort.shellSort_binary();
	//mySort.quickSort();
	
	print_time("Done:");
	
	/*auto vec = mySort.getNums();
	printVec(vec.begin(), vec.end());*/

	SortLib2 mySort2(nums);
	print_time("QuickSort_intro2:");
	mySort2.quickSort_intro();
	print_time("Done:");
	
	
	SortLib3 mySort3(nums);
	print_time("QuickSort_intro3:");
	mySort3.quickSort_intro();
	print_time("Done:");

	SortLib4 mySort4(nums);
	print_time("QuickSort_intro4:");
	mySort4.quickSort_intro();
	print_time("Done:");

	SortLib5 mySort5(nums);
	print_time("QuickSort_intro5:");
	mySort5.quickSort_intro();
	print_time("Done:");

	return 0;
}//main
