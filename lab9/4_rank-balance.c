#include <stdio.h>
#include <stdlib.h>

// Define the rank-balanced tree node
typedef struct Node
{
  int data;
  int rank;
  struct Node *left;
  struct Node *right;
} Node;

// Function to create a new node with given data
Node *newNode(int data)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = data;
  node->rank = 1;
  node->left = NULL;
  node->right = NULL;
  return node;
}

// Function to get the rank of a node (returns 0 if node is NULL)
int getRank(Node *node)
{
  return node ? node->rank : 0;
}

// Function to update the rank of a node
void updateRank(Node *node)
{
  node->rank = 1 + getRank(node->left) + getRank(node->right);
}

// Function to perform a right rotation
Node *rotateRight(Node *node)
{
  Node *newRoot = node->left;
  node->left = newRoot->right;
  newRoot->right = node;
  updateRank(node);
  updateRank(newRoot);
  return newRoot;
}

// Function to perform a left rotation
Node *rotateLeft(Node *node)
{
  Node *newRoot = node->right;
  node->right = newRoot->left;
  newRoot->left = node;
  updateRank(node);
  updateRank(newRoot);
  return newRoot;
}

// Function to balance a node
Node *balance(Node *node)
{
  int balanceFactor = getRank(node->left) - getRank(node->right);
  if (balanceFactor > 1)
  {
    if (getRank(node->left->left) < getRank(node->left->right))
    {
      node->left = rotateLeft(node->left);
    }
    node = rotateRight(node);
  }
  else if (balanceFactor < -1)
  {
    if (getRank(node->right->left) > getRank(node->right->right))
    {
      node->right = rotateRight(node->right);
    }
    node = rotateLeft(node);
  }
  return node;
}

// Function to insert a node into the tree
Node *insert(Node *root, int data)
{
  if (!root)
  {
    return newNode(data);
  }
  if (data < root->data)
  {
    root->left = insert(root->left, data);
  }
  else
  {
    root->right = insert(root->right, data);
  }
  updateRank(root);
  root = balance(root);
  return root;
}

// Function to find a node with given data in the tree
Node *find(Node *root, int data)
{
  if (!root || root->data == data)
  {
    return root;
  }
  if (data < root->data)
  {
    return find(root->left, data);
  }
  else
  {
    return find(root->right, data);
  }
}

// Function to delete a node with given data from the tree
Node *delete(Node *root, int data)
{
  if (!root)
  {
    return root;
  }
  if (data < root->data)
  {
    root->left = delete (root->left, data);
  }
  else if (data > root->data)
  {
    root->right = delete (root->right, data);
  }
  else
  {
    if (!root->left)
    {
      Node *temp = root->right;
      free(root);
      return temp;
    }
    else if (!root->right)
    {
      Node *temp = root->left;
      while (temp->right)
      {
        temp = temp->right;
      }
      root->data = temp->data;
      root->left = delete (root->left, temp->data);
    }
    else
    {
      Node *temp = root->right;
      while (temp->left)
      {
        temp = temp->left;
      }
      root->data = temp->data;
      root->right = delete (root->right, temp->data);
    }
  }
  updateRank(root);
  root = balance(root);
  return root;
}

// Function to print the tree in in-order traversal
void printInOrder(Node *root)
{
  if (root)
  {
    printInOrder(root->left);
    printf("%d %d, ", root->data, root->rank);
    printInOrder(root->right);
  }
}

// Test the implementation
int main()
{
  Node *root = NULL;
  root = insert(root, 5);
  root = insert(root, 3);
  root = insert(root, 7);
  root = insert(root, 2);
  root = insert(root, 4);
  root = insert(root, 6);
  root = insert(root, 8);
  printf("In-order traversal of the tree: ");
  printInOrder(root);
  printf("\n");
  root = delete (root, 5);
  printf("In-order traversal of the tree after deleting 5: ");
  printInOrder(root);
  printf("\n");
  return 0;
}