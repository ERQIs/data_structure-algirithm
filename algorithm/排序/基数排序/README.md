# 基数排序 radix-sorting

## 原理
基数排序的原理非常的简单，具体来说就是在在整个数据集上依次根据每一位（如果待比较的元素都是数字的话）做一次稳定的排序。  
但是正如 *"Introduction to Algorithms"* 中指出的那样，有点“反直觉”的一点是这里的“位”的取法是从低位到高位取的（如果是数字的话）。如果是一个广义的元素的话那么理应是从优先级较低的比较区域到优先级较高的比较区域来依次排序。比如如果要为很多日期排序的话首先根据day来做依次稳定排序、然后是month、然后是year。  

![visual_display](../../.assets/radix_sorting_visual.gif)

## 代码

### 伪代码

```python
RADIX_SORTING (SEQUENCE S)
# 假设S中的数字都是不超过n位的正整数
    for i from 1 to n:
        sort S with an stable sorting algorithm depending of ith bit
```

### C代码

```c
void radix_sorting(int* nums, int n)
//基数排序（升序），默认所有数字都是0~1e5之间的
{
    int (*tmp)[n] = (int(*)[10]) malloc (sizeof(int) * 10 * n);
    int *cnt = (int*) malloc (sizeof(int) * 10);
    memset(cnt, 0, sizeof(int) * 10);

    for (int i = 0; i < 6; i ++){
    // 分别对每一位做一次稳定的排序，这里是。。。计数排序？算是吧

        for (int j = 0; j < n; j ++){
            int num = nums[j];
        //对每一个数字

            int bit_i = num;
            for (int k = 0; k < i; k ++){
                bit_i /= 10;
            }
            bit_i %= 10;
            //提取它的第i位上的数

            tmp[bit_i][cnt[bit_i] ++] = num;
            /*
            放到计数排序数组里（这里的计数数组应该是cnt,
            cnt[4]表示有这么多个4，但是这些4又都是不同的
            因为它们承载了其它位上的信息）
            */
        }

        int p = 0;
        for (int j = 0; j < 10; j ++){
            int j_cnt = cnt[j];
            for (int k = 0; k < j_cnt; k ++){
                nums[p ++] = tmp[j][k];
            }
            cnt[j] = 0;
        }
        //往回放的时候是有一点不一样，如果按照counting-sort的放法就要求
        //再开一个数组，还得再提取一次位
    }

    free(tmp);
    free(cnt);
}
```