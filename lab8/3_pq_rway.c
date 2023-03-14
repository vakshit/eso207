#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_HEAP_SIZE 100
#define DEFAULT_R 5

typedef struct
{
  int key;
  int value;
} HeapNode;

typedef struct
{
  int size;
  int r;
  HeapNode *nodes;
} Heap;

Heap *createHeap(int r)
{
  Heap *h = malloc(sizeof(Heap));
  h->size = 0;
  h->r = r;
  h->nodes = malloc(sizeof(HeapNode) * MAX_HEAP_SIZE);
  return h;
}

void destroyHeap(Heap *h)
{
  free(h->nodes);
  free(h);
}

int parentIndex(int i, int r)
{
  return (i - 1) / r;
}

int childIndex(int i, int k, int r)
{
  return r * i + k;
}

HeapNode getMin(Heap *h)
{
  return h->nodes[0];
}

void swapNodes(Heap *h, int i, int j)
{
  HeapNode temp = h->nodes[i];
  h->nodes[i] = h->nodes[j];
  h->nodes[j] = temp;
}

void bubbleUp(Heap *h, int i)
{
  int parent = parentIndex(i, h->r);
  while (i > 0 && h->nodes[i].key < h->nodes[parent].key)
  {
    swapNodes(h, i, parent);
    i = parent;
    parent = parentIndex(i, h->r);
  }
}

void bubbleDown(Heap *h, int i)
{
  while (1)
  {
    int minChildIndex = -1;
    for (int k = 0; k < h->r; k++)
    {
      int child = childIndex(i, k, h->r);
      if (child < h->size && (minChildIndex == -1 || h->nodes[child].key < h->nodes[minChildIndex].key))
      {
        minChildIndex = child;
      }
    }
    if (minChildIndex == -1)
    {
      break;
    }
    if (h->nodes[i].key > h->nodes[minChildIndex].key)
    {
      swapNodes(h, i, minChildIndex);
      i = minChildIndex;
    }
    else
    {
      break;
    }
  }
}

void insert(Heap *h, int key, int value)
{
  if (h->size >= MAX_HEAP_SIZE)
  {
    printf("Heap overflow!\n");
    return;
  }
  HeapNode node = {key, value};
  h->nodes[h->size++] = node;
  bubbleUp(h, h->size - 1);
}

void reduceKey(Heap *h, int i, int newKey)
{
  if (newKey > h->nodes[i].key)
  {
    printf("New key is greater than current key!\n");
    return;
  }
  h->nodes[i].key = newKey;
  bubbleUp(h, i);
}

HeapNode deleteMin(Heap *h)
{
  if (h->size <= 0)
  {
    printf("Heap underflow!\n");
    return (HeapNode){INT_MAX, 0};
  }
  HeapNode min = h->nodes[0];
  h->nodes[0] = h->nodes[--h->size];
  bubbleDown(h, 0);
  return min;
}

void printHeap(Heap *h)
{
  printf("Heap: ");
  for (int i = 0; i < h->size; i++)
  {
    printf("(%d,%d) ", h->nodes[i].key, h->nodes[i].value);
  }
  printf("\n");
}

int main()
{
  Heap *h = createHeap(DEFAULT_R);
  insert(h, 3, 10);
  insert(h, 2, 20);
  insert(h, 1, 30);
  insert(h, 15, 40);
  insert(h, 5, 50);
  insert(h, 4, 60);
  printHeap(h);
  reduceKey(h, 2, 100);
  printHeap(h);
  HeapNode min = deleteMin(h);
  printf("Deleted minimum node: (%d,%d)\n", min.key, min.value);
  printHeap(h);
  destroyHeap(h);
  return 0;
}