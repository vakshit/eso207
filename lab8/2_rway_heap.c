#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Node structure of the binary search tree
struct Node
{
  int key;
  struct Node *left, *right;
};

// R-way heap structure
struct Heap
{
  int *heapArray;
  int heapSize;
};

// Create a new node with the given key
struct Node *newNode(int key)
{
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  node->key = key;
  node->left = node->right = NULL;
  return node;
}

// Create a new heap with the given size
struct Heap *newHeap(int heapSize)
{
  struct Heap *heap = (struct Heap *)malloc(sizeof(struct Heap));
  heap->heapArray = (int *)malloc(sizeof(int) * heapSize);
  heap->heapSize = heapSize;
  return heap;
}

// Insert a new key into the binary search tree
struct Node *insert(struct Node *root, int key, struct Heap *heap)
{
  // If the tree is empty, return a new node
  if (root == NULL)
  {
    struct Node *node = newNode(key);
    return node;
  }

  // Otherwise, recur down the tree
  if (key < root->key)
    root->left = insert(root->left, key, heap);
  else if (key > root->key)
    root->right = insert(root->right, key, heap);
  else // Duplicate keys not allowed
    return root;

  // Get the index of the next available slot in the heap
  int index = heap->heapSize - 1;
  heap->heapSize--;

  // Insert the new key into the heap at the next available slot
  heap->heapArray[index] = key;

  // Percolate up the new key to its correct position in the heap
  while (index > 0 && heap->heapArray[(index - 1) / 2] > heap->heapArray[index])
  {
    int temp = heap->heapArray[(index - 1) / 2];
    heap->heapArray[(index - 1) / 2] = heap->heapArray[index];
    heap->heapArray[index] = temp;
    index = (index - 1) / 2;
  }

  return root;
}

// Reduce the key of a node with the given old key to a new key
void reduceKey(struct Node *root, int oldKey, int newKey, struct Heap *heap)
{
  // If the tree is empty, return
  if (root == NULL)
    return;

  // If the old key is less than the root key, recur left
  if (oldKey < root->key)
    reduceKey(root->left, oldKey, newKey, heap);
  // If the old key is greater than the root key, recur right
  else if (oldKey > root->key)
    reduceKey(root->right, oldKey, newKey, heap);
  else
  { // If the old key matches the root key
    // Get the index of the old key in the heap
    int index;
    for (index = 0; index < heap->heapSize; index++)
    {
      if (heap->heapArray[index] == oldKey)
        break;
    }

    // Update the old key to the new key in the heap
    heap->heapArray[index] = newKey;

    // Percolate up or down the new key
    while (index > 0 && heap->heapArray[(index - 1) / 2] > heap->heapArray[index])
    { // Percolate up
      int temp = heap->heapArray[(index - 1) / 2];
      heap->heapArray[(index - 1) / 2] = heap->heapArray[index];
      heap->heapArray[index] = temp;
      index = (index - 1) / 2;
    }
    while ((2 * index + 1) < heap->heapSize)
    { // Percolate down
      int child = 2 * index + 1;
      if (child + 1 < heap->heapSize && heap->heapArray[child + 1] < heap->heapArray[child])
        child++;
      if (heap->heapArray[index] < heap->heapArray[child])
        break;
      int temp = heap->heapArray[index];
      heap->heapArray[index] = heap->heapArray[child];
      heap->heapArray[child] = temp;
      index = child;
    }

    // Update the key of the node in the tree to the new key
    root->key = newKey;
  }
}

// Delete the node with the minimum key value
struct Node *deleteMin(struct Node *root, struct Heap *heap)
{
  // If the tree is empty, return
  if (root == NULL)
    return root;
  // If the root node is a leaf node, delete it
  if (root->left == NULL && root->right == NULL)
  {
    free(root);
    return NULL;
  }

  // Recur down the tree to find the node with the minimum key value
  if (root->left != NULL && root->left->key < root->right->key)
  {
    root->left = deleteMin(root->left, heap);
    return root;
  }
  else if (root->right != NULL)
  {
    root->right = deleteMin(root->right, heap);
    return root;
  }

  // If the root node has both left and right children, delete the node with the minimum key value
  int minIndex = 0;
  int minValue = heap->heapArray[0];

  // Find the index of the minimum key value in the heap
  for (int i = 1; i < heap->heapSize; i++)
  {
    if (heap->heapArray[i] < minValue)
    {
      minIndex = i;
      minValue = heap->heapArray[i];
    }
  }

  // Delete the node with the minimum key value from the heap
  heap->heapArray[minIndex] = heap->heapArray[heap->heapSize - 1];
  heap->heapSize--;

  // Percolate up or down the new key value in the heap to its correct position
  while (minIndex > 0 && heap->heapArray[(minIndex - 1) / 2] > heap->heapArray[minIndex])
  { // Percolate up
    int temp = heap->heapArray[(minIndex - 1) / 2];
    heap->heapArray[(minIndex - 1) / 2] = heap->heapArray[minIndex];
    heap->heapArray[minIndex] = temp;
    minIndex = (minIndex - 1) / 2;
  }
  while ((2 * minIndex + 1) < heap->heapSize)
  { // Percolate down
    int child = 2 * minIndex + 1;
    if (child + 1 < heap->heapSize && heap->heapArray[child + 1] < heap->heapArray[child])
      child++;
    if (heap->heapArray[minIndex] < heap->heapArray[child])
      break;
    int temp = heap->heapArray[minIndex];
    heap->heapArray[minIndex] = heap->heapArray[child];
    heap->heapArray[child] = temp;
    minIndex = child;
  }
  // Create a new node with the minimum key value and update the root node with its key value
  struct Node *newRoot = newNode(minValue);
  newRoot->left = root->left;
  newRoot->right = root->right;
  free(root);

  return newRoot;
}

int main()
{
  struct Node *root = NULL;
  struct Heap *heap = newHeap(5);
  // Insert nodes with keys 10, 8, 15, 20, and 13
  root = insert(root, heap, 10);
  root = insert(root, heap, 8);
  root = insert(root, heap, 15);
  root = insert(root, heap, 20);
  root = insert(root, heap, 13);

  // Reduce the key of the node with key value 15 to 5
  reduceKey(root, heap, 15, 5);

  // Delete the node with the minimum key value
  root = deleteMin(root, heap);

  return 0;
}