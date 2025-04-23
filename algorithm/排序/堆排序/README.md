# 堆排序 Heap Sort
 不知道把堆排序翻出看看的你是不是忘了怎么手撸 heap sort 了呢？

详细的解释什么的，都在 *"Introduction to Algorithms"* 里，如果忘记了的话拿出书来回顾一下吧！

## 实现代码
这是一段曾经实现过的堆排序代码（基于书里的方法）。当然可能有些繁琐的，重复的地方（反正还挺长的）。但这是一段我练到无伤速通的第一个*heap sort*力！

```c
//这是升序排序的代码

typedef struct heap{
    int size;
    int* data;
} *HEAP;
// 这个是为了封装一下相关的信息


int heap_left(int n)
{
    return (n + 1) * 2 - 1;
}
//堆的左孩子
int heap_right(int n)
{
    return (n + 1) * 2;
}
//堆的右孩子


HEAP create_heap(int* nums, int n)
{
    HEAP ret = (HEAP) malloc (sizeof(struct heap));
    ret->data = nums;
    ret->size = n;
    return ret;
}
//根据待排序数组返回封装好的"堆"，但是没有堆的性质，就是为了之后好开始操作


void swap(int* _a, int* _b)
{
    int a = *_a;
    int b = *_b;
    *_a = b;
    *_b = a;
}
//这个就不用多说


void max_heapify(HEAP A, int n)
{
    int* nums = A->data;
    int size = A->size;
    int left = heap_left(n);
    int right = heap_right(n);
    int max = n;
    if (left < size){
        max = nums[left] > nums[max] ? left : max;
    }
    if (right < size){
        max = nums[right] > nums[max] ? right : max;
    }
    if (max != n){
        swap(nums + max, nums + n);
        max_heapify(A, max);
    }
}
// 维护最大堆的性质的操作，对于堆来说很关键


void make_heap(HEAP A)
{
    int size = A->size;
    for (int i = size / 2; i >= 0; i --){
        max_heapify(A, i);
    }
}
// 把一个无序的数组转化成有着最大堆的性质的好堆


void heap_sort(HEAP A)
{
    int size = A->size;
    int* nums = A->data;
    for (int i = size - 1; i > 0; i --){
        swap(nums, nums + i);
        A->size --;
        max_heapify(A, 0);
    }
}
// 堆排序的方法咯，书上有的


//调用方式： nums 是待排序数组，长度为 n

HEAP h = create_heap(nums, n);
make_heap(h);
heap_sort(h);

```

降序排序跟升序排序很相似，只不过是在整个过程中我们要维护一个最小堆。差异主要体现在`hipify`上
```c
void min_heapify(HEAP A, int n)
{
    int* nums = A->data;
    int size = A->size;
    int left = heap_left(n);
    int right = heap_right(n);
    int min = n;
    if (left < size){
        min = nums[left] < nums[min] ? left : min;
//                        \_这个比较号是反的，下面的也是
    }
    if (right < size){
        min = nums[right] < nums[min] ? right : min;
    }
    if (min != n){
        swap(nums + min, nums + n);
        min_heapify(A, min);
    }
}


void make_heap(HEAP A)
{
    int size = A->size;
    for (int i = size / 2; i >= 0; i --){
        min_heapify(A, i);  //改一下名字
    }
}


void heap_sort(HEAP A)
{
    int size = A->size;
    int* nums = A->data;
    for (int i = size - 1; i > 0; i --){
        swap(nums, nums + i);
        A->size --;
        min_heapify(A, 0);  //改一下名字
    }
}
```
<br>

###### 最后改动日期： 2023/4/17