#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct RWayHeapNode {
    int data;
};

struct RWayHeap {
    int r;
    int size;
    struct RWayHeapNode* nodes;
};

struct RWayHeap* createHeap(int r, int size) {
    struct RWayHeap* heap = (struct RWayHeap*)malloc(sizeof(struct RWayHeap));
    heap->r = r;
    heap->size = 0;
    heap->nodes = (struct RWayHeapNode*)malloc(size * sizeof(struct RWayHeapNode));

    return heap;
}

void swap(struct RWayHeap* heap, int i, int j) {
    struct RWayHeapNode temp = heap->nodes[i];
    heap->nodes[i] = heap->nodes[j];
    heap->nodes[j] = temp;
}

void heapifyUp(struct RWayHeap* heap, int index) {
    if (index == 0) {
        return;
    }

    int parentIndex = (index - 1) / heap->r;
    if (heap->nodes[index].data < heap->nodes[parentIndex].data) {
        swap(heap, index, parentIndex);
        heapifyUp(heap, parentIndex);
    }
}

void heapifyDown(struct RWayHeap* heap, int index) {
    int minChild = index * heap->r + 1;
    if (minChild >= heap->size) {
        return;
    }

    for (int i = 2; i <= heap->r; i++) {
        int childIndex = index * heap->r + i;
        if (childIndex < heap->size && heap->nodes[childIndex].data < heap->nodes[minChild].data) {
            minChild = childIndex;
        }
    }

    if (heap->nodes[minChild].data < heap->nodes[index].data) {
        swap(heap, index, minChild);
        heapifyDown(heap, minChild);
    }
}

void insert(struct RWayHeap* heap, int data) {
    heap->nodes[heap->size].data = data;
    heapifyUp(heap, heap->size);
    heap->size++;
}

void reduceKey(struct RWayHeap* heap, int index, int newKey) {
    heap->nodes[index].data = newKey;
    heapifyUp(heap, index);
}

int deleteMin(struct RWayHeap* heap) {
    int minData = heap->nodes[0].data;
    heap->size--;
    heap->nodes[0] = heap->nodes[heap->size];
    heapifyDown(heap, 0);

    return minData;
}

void printHeap(struct RWayHeap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->nodes[i].data);
    }
    printf("\n");
}

int main() {
    int r = 4;
    int size = 10000;
    struct RWayHeap* heap = createHeap(r, size);

    // Insert 5000 random numbers
    srand(time(NULL));
    for (int i = 0; i < 5000; i++) {
        int data = rand() % 10000;
        insert(heap, data);
    }

    // Print the heap
    printf("Heap:\n");
    printHeap(heap);

    // Delete the minimum item 1000 times
        printf("Deleting minimum items:\n");
    for (int i = 0; i < 1000; i++) {
        int minData = deleteMin(heap);
        printf("%d ", minData);
    }
    printf("\n");

    return 0;
}
