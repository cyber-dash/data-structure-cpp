//
// Created by alei_go@163.com(����: cyberdash_yuan) on 2020/11/1.
//

#include <iostream>
#include <stdlib.h>
#include "min_heap.h"


using namespace std;


template <class E>
MinHeap<E>::MinHeap(int sz) {
  maxHeapSize = (sz > DEFAULT_SIZE) ? sz : DEFAULT_SIZE;
  heap = new E[maxHeapSize];

  if (heap == NULL) {
    cerr << "�Ѵ洢����ʧ�ܣ�" << endl;
    exit(1);
  }

  currentSize = 0;
}


template <class E>
MinHeap<E>::MinHeap(E arr[], int n) {
  maxHeapSize = (n > DEFAULT_SIZE) ? n : DEFAULT_SIZE;
  heap = new E[maxHeapSize];

  if (heap == NULL) {
    cerr << "�Ѵ洢����ʧ�ܣ�" << endl;
    exit(1);
  }

  for (int i = 0; i < n; i++) {
    heap[i] = arr[i];
  }

  currentSize = n;

  int currentPos = (currentSize - 2) / 2;

  while (currentPos >= 0) {
    siftDown(currentPos, currentSize - 1);
    currentPos--;
  }
}


template <class E>
void MinHeap<E>::siftDown(int start, int m) {
  int i = start, j = 2 * i + 1;
  E temp = heap[i];

  while (j <= m) {
    if (j < m && heap[j] > heap[j + 1]) {
      j++;
    }

    if (temp <= heap[j]) {
      break;
    } else {
      heap[i] =  heap[j];
      i = j;
      j = 2 * j + 1;
    }
  }

  heap[i] = temp;
}


template <class E>
void MinHeap<E>::siftUp(int start) {
  int j = start, i = (j - 1) / 2;
  E temp = heap[j];

  while (j > 0) {
    if (heap[i] <= temp) {
      break;
    } else {
      heap[j] = heap[i];
      j = i;
      i = (i - 1) / 2;
    }
  }

  heap[j] = temp;
}


template <class E>
bool MinHeap<E>::Insert(const E& x) {
  if (currentSize == maxHeapSize) {
    cerr << "Heap Full." << endl;
    return false;
  }

  heap[currentSize] = x;
  siftUp(currentSize);

  currentSize++;

  return true;
}


template <class E>
bool MinHeap<E>::RemoveMin(E& x) {
  if (!currentSize) {
    cerr << "Heap Empty." << endl;
    return false;
  }

  x = heap[0];
  heap[0] = heap[currentSize - 1];
  currentSize--;

  siftDown(0, currentSize - 1);

  return true;
}
