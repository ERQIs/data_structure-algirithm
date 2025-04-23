# 快速排序
## 快速排序是什么
这个问题就不展开多说力，总的来说快速排序算法基于分治的思想。基于分治法 $devide$ , $conquer$, 的步骤去理解快排可能会更好的吧！
>$devide$:  
这个过程需要在序列中跳出一个元素 $pivot$, 然后把所有的比 $pivot$ “小”（也就意味着在排好序的序列中应该在 $pivot$ 前面的元素）统统赶到 $pivot$ 前面，所有的比 $pivot$ “大”的元素统统赶到 $pivot$ 后面。这样一来，只需要对 $pivot$ 的左右两边各做一次排序就ok了，我们将看到这个过程是${O(n)}$的。  
>$conquer$:  
没必要多做什么事情，${O(1)}$。
>根据主方法，${T(n) = 2T(\frac{n}{2}) + O(n)}$, 总的时间复杂度为${O(nlogn)}$

## 模板 1（升序排序数字为例）
这是一个在 ***"Introduction to Algorithm"*** 上介绍的快排算法
### 伪代码

```python
QUICK_SORT(A, L, R)   #递归调用分治思想
if L < R
    M = PARTITION(A, L, R)  #这是devide的部分
    QUICK_SORT(A, M + 1, R)
    QUECI_SORT(A, L, M - 1)



PARTITION(A, L, R)
PIVOT = A[R]                #基准元素PIVOT在这里默认为最右端的元素
LP = L - 1                  #LP一直指向 已经扔到PIVOT左面的最后一个元素
for HP from L to R - 1      #HP则指向 下一个待处理的元素
    if A[HP] <= PIVOT
        LP = LP + 1
        exchange A[LP] with A[HP]
exchange A[R] with A[LP + 1]
return LP + 1

#建议翻书，因为书上有图例，很好懂
```

但是在实际的使用过程中会发现这个模板有一些问题：  

1. 当整个序列在一开始的时候就是有序的时（不论是升序或者降序），当“默认”地只从序列的两端取 $pivot$ 时会发现 `PARTITION` 把整个长度为 $n$ 的序列分成长度为 $0$ 和长度为 $n - 1$ 的两个子序列，这样一来，递归式会变成 ${T(n) = 2T(n - 1) + O(n)}$, 可以知道整个复杂度是 $O(n^2)$ 的。
   
2. 当整个序列中包含较多的相同元素时，从某一次调用开始 `PARTITION` 会不可避免地为一长串相同的元素做分割。可是我们“仔细看看”就会发现`PARTITION` 会将长度长度为 $n$ 的相同元素序列分成长度为 $0$ 和长度为 $n - 1$ 的两个相同元素子序列。这是因为我们“默认”了将等于 $pivot$ 的元素只放到 $pivot$ 之前（或者之后）。

要解决这两个问题，我们可以进行随机化：

1. 随机地选取 $pivot$
2. 将等于 $pivot$ 的元素随机地放到 $pivot$ 之前或者之后。

```python
PARTITION(A, L, R)

choose an element A[rand] between A[L] and A[R] randomly
then exchange A[rand] and A[R]
PIVOT = A[R]                #随机选取基准元素

LP = L - 1                  #LP一直指向 已经扔到PIVOT左面的最后一个元素
for HP from L to R - 1      #HP则指向 下一个待处理的元素
    if A[HP] < PIVOT
        LP = LP + 1
        exchange A[LP] with A[HP]

    if A[HP] == PIVOT       #随机决定相等元素的去向
        randomly decide wether exchange A[LP] with A[HP] or not

exchange A[R] with A[LP + 1]
return LP + 1               #返回pivot的位置（换到哪儿就是哪儿咯）
```

### C代码

```c

void swap(int* _a, int* _b)
{
    int a = *_a;
    int b = *_b;
    *_a = b;
    *_b = a;
}

int partition(int* nums, int l, int r)
{
//----------------------------------------------------
    int RAND = l + rand()%(r - l + 1);
    swap(&nums[RAND], &nums[r]);            //随机化处理
//----------------------------------------------------
    int pivot = nums[r];
    int lp = l - 1;
    for (int hp = l; hp <= r - 1; hp ++){
        if (nums[hp] < pivot){
            swap(&nums[++ lp], &nums[hp]);
        }
//----------------------------------------------------
        else if (nums[hp] == pivot){
            swap(&nums[++ lp], &nums[hp]);
        }                                   //随机化处理
//----------------------------------------------------
    }
    swap(&nums[lp + 1], &nums[r]);
    return lp + 1;
}


void quick_sort(int* nums, int l, int r)
{
    if (l >= r)
        return;
    int m = partition(nums, l, r);
    quick_sort(nums, l, m - 1);
    quick_sort(nums, m + 1, r);
}


quick_sort(nums, 0, n - 1);
//初始调用：nums是待排序数组，长度为n
```
## 为什么这个能跑？？？
这里还有一个别人的提交，我实在是搞不懂边界条件是怎么成立的。跳出while之后有的时候i == j,有的时候 i == j + 1还有的时候 i == j + 2 总之搞不懂怎么回事，但是它就是能跑。。。。
```c
void quick_sort(int* nums, int l, int r)
{
    if (l >= r)
        return;
    int i = l, j = r, k = nums[l + (r - l)/2];

    while (i < j){
        while (nums[i] < k) i ++;
        while (nums[j] > k) j --;
        if (i <= j) swap(&nums[i ++], &nums[j --]);
    }

    if (i == j + 1) printf("YES\n");
    else printf("NO i = %d, j = %d\n", i, j);

    quick_sort(nums, l, j);
    quick_sort(nums, i, r);

//调用跟之前的一样。
}
```

<br>

###### 最后更改 2023/4/17