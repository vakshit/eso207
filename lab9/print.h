#include <stdio.h>
#include <stdlib.h>

// Node structure for the tree
typedef struct Node
{
  int data;           // Data value of the node
  int rank;           // Rank of the node
  struct Node *left;  // Pointer to left child
  struct Node *right; // Pointer to right child
} Node;

typedef struct QueueNode
{
  Node *node;
  struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
  QueueNode *front;
  QueueNode *rear;
} Queue;

Queue *createQueue()
{
  Queue *queue = (Queue *)malloc(sizeof(Queue));
  queue->front = NULL;
  queue->rear = NULL;
  return queue;
}

void enqueue(Queue *queue, Node *node)
{
  QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
  newNode->node = node;
  newNode->next = NULL;

  if (queue->front == NULL)
  {
    queue->front = newNode;
  }
  else
  {
    queue->rear->next = newNode;
  }
  queue->rear = newNode;
}

Node *dequeue(Queue *queue)
{
  if (queue->front == NULL)
  {
    return NULL;
  }
  QueueNode *dequeuedNode = queue->front;
  Node *dequeuedTreeNode = dequeuedNode->node;
  queue->front = queue->front->next;
  free(dequeuedNode);
  return dequeuedTreeNode;
}

void levelOrderTraversal(Node *root)
{
  if (root == NULL)
  {
    return;
  }

  Queue *queue = createQueue();
  enqueue(queue, root);

  // int currentLevelCount = 1; // Number of nodes at current level
  // int nextLevelCount = 0;    // Number of nodes at next level

  while (queue->front != NULL)
  {
    Node *node = dequeue(queue);
    printf("%d-%d, ", node->data, node->rank);
    // currentLevelCount--;

    if (node->left != NULL)
    {
      enqueue(queue, node->left);
      // nextLevelCount++;
    }
    if (node->right != NULL)
    {
      enqueue(queue, node->right);
      // nextLevelCount++;
    }

    // if (currentLevelCount == 0) // End of current level
    // {
    //   printf("\n"); // Print new line
    //   currentLevelCount = nextLevelCount;
    //   nextLevelCount = 0;
    // }
  }
}

int mx(int a, int b)
{
  return a > b ? a : b;
}

int mn(int a, int b)
{
  return a < b ? a : b;
}
