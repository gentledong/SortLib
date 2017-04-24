# SortLib
SortLib是用C++编写的一个开源库，包括目前主流的排序算法，MergeSort，QuickSort，ShellSort，InsertSort_line，InsertSort_binary。

参考STL中sort函数的"内省式排序"算法，给出改良之后的结果quickSort_intro。并做测试和对比。  

以上部分均为"内部排序"，未涉及外部排序，未涉及链表存储的。

基数排序，桶排序也有单独实现。  

# SortLib<Elem,Storage,Compare>
该模板需要必填元素类型Elem，存储器默认为vector<Elem>，比较器默认为less<Elem>。  

不是课程要求，不是实验室要求，完全是个人兴趣使然，由简到繁，由浅入深，体会成长的快乐。

因为算法和数据结构是程序员的根本，而编码技巧和优化直觉需要长期培养。
