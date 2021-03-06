/*!
 * @file heap_sort.cpp
 * @author CyberDash计算机考研, cyberdash@163.com(抖音id:cyberdash_yuan)
 * @brief 堆排序
 * @version 0.2.1
 * @date 2021-09-19
 * @copyright Copyright (c) 2021
 *  CyberDash计算机考研
 */

#include "util.h"


/*!
 * 大顶堆SiftDown
 * @param arr 数组
 * @param idx 执行SiftDown的数组索引
 * @param heap_size 堆size
 */
void MaxHeapSiftDown(int* arr, int idx, int heap_size) {
  for (int child_idx = 2 * idx + 1; child_idx < heap_size; idx = child_idx, child_idx = child_idx * 2 + 1) {

    //! index的孩子结点中, 权重较大的结点索引, 赋给child_idx
    if (child_idx < heap_size && arr[child_idx] < arr[child_idx + 1]) {
      child_idx++;
    }

    //! 如果父节点 >= 子节点, sift down结束
    if (arr[idx] >= arr[child_idx]) {
      break;
    }

    //! 交换父子结点
    Swap(arr + idx, arr + child_idx);
  }
}


/*!
 * 大顶堆SiftUp
 * @param arr 数组
 * @param idx 执行SiftUp的数组索引
 */
void MaxHeapSiftUp(int* arr, int idx) {
  for (int parent_idx = (idx - 1) / 2; parent_idx >= 0; idx = parent_idx, parent_idx = (idx - 1) / 2) {
    if (arr[parent_idx] >= arr[idx]) {
      break;
    }

    Swap(arr + parent_idx, arr + idx);
  }
}


/*!
 * 构造堆(使用SiftDown)
 * @param arr 数组
 * @param size 数组长度
 */
void BuildHeapBySiftDown(int* arr, int size) {
    int pivot = (size - 2) / 2;
    for (int i = pivot; i >= 0; i--) {
        MaxHeapSiftDown(arr, i, size);
    }
}


/*!
 * 构造堆(使用SiftUp)
 * @param arr 数组
 * @param size 数组长度
 */
void BuildHeapBySiftUp(int* arr, int size) {
    int pivot = (size - 2) / 2;
    for (int i = size - 1; i > pivot; i--) {
        MaxHeapSiftUp(arr, i);
    }
}


/*!
 * 堆排序
 * @param arr 数组
 * @param length 数组长度
 */
void HeapSort(int* arr, int length) {

    BuildHeapBySiftDown(arr, length);

    for (int i = length - 1; i > 0; i--) {
        Swap(arr, arr + i);
        MaxHeapSiftDown(arr, 0, i - 1);
    }
}
