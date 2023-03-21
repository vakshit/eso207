#include "print.h"

// Create a new node with the given data value
Node *newNode(int data)
{
  Node *node = (Node *)malloc(sizeof(Node));
  node->data = data;
  node->rank = 0;
  node->left = NULL;
  node->right = NULL;
  return node;
}

// Get the rank of a node, or 0 if the node is NULL
int getRank(Node *node)
{
  return node ? node->rank : 0;
}

// Update the rank of a node based on the ranks of its children
void updateRank(Node *node)
{
  if (node)
  {
    // node->rank = 1 + ((node->left) ? node->left->rank : 0) + ((node->right) ? node->right->rank : 0);
    node->rank = 1 + mx((node->left) ? node->left->rank : 0, (node->right) ? node->right->rank : 0);
  }
}

// Perform a right rotation to balance the tree
Node *rotateRight(Node *node)
{
  Node *leftChild = node->left;
  Node *rightGrandchild = leftChild->right;
  leftChild->right = node;
  node->left = rightGrandchild;
  updateRank(node);
  updateRank(leftChild);
  return leftChild;
}

// Perform a left rotation to balance the tree
Node *rotateLeft(Node *node)
{
  Node *rightChild = node->right;
  Node *leftGrandchild = rightChild->left;
  rightChild->left = node;
  node->right = leftGrandchild;
  updateRank(node);
  updateRank(rightChild);
  return rightChild;
}

// Balance a node based on the balance factor
Node *balance(Node *node)
{
  int balanceFactor = getRank(node->left) - getRank(node->right);
  if (balanceFactor > 1)
  {
    if (getRank(node->left->left) >= getRank(node->left->right))
    {
      node = rotateRight(node);
    }
    else
    {
      node->left = rotateLeft(node->left);
      node = rotateRight(node);
    }
  }
  else if (balanceFactor < -1)
  {
    if (getRank(node->right->right) >= getRank(node->right->left))
    {
      node = rotateLeft(node);
    }
    else
    {
      node->right = rotateRight(node->right);
      node = rotateLeft(node);
    }
  }
  updateRank(node);
  return node;
}

// Insert a new node with the given data value into the tree
Node *insert(Node *node, int data)
{
  if (node == NULL)
  {
    return newNode(data);
  }
  else if (data < node->data)
  {
    node->left = insert(node->left, data);
    updateRank(node);
    if (getRank(node->left) > getRank(node->right) + 1)
    {
      node = balance(node);
    }
  }
  else if (data > node->data)
  {
    node->right = insert(node->right, data);
    updateRank(node);
    if (getRank(node->right) > getRank(node->left) + 1)
    {
      node = balance(node);
    }
  }
  return node;
}

// Find the node with the minimum value in the tree rooted at node
Node *findMin(Node *node)
{
  if (node == NULL)
  {
    return NULL;
  }
  while (node->left != NULL)
  {
    node = node->left;
  }
  return node;
}

// Delete the node with the given data value from the tree rooted at node
Node *delete(Node *node, int data)
{
  Node *parent = NULL;
  Node *current = node;

  while (current != NULL && current->data != data)
  {
    parent = current;
    if (data < current->data)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  if (current == NULL)
  {
    return node;
  }

  if (current->left == NULL && current->right == NULL)
  {
    if (parent == NULL)
    {
      free(current);
      return NULL;
    }
    else if (current == parent->left)
    {
      parent->left = NULL;
    }
    else
    {
      parent->right = NULL;
    }
    free(current);
  }
  else if (current->left == NULL || current->right == NULL)
  {
    Node *child = current->left ? current->left : current->right;
    if (parent == NULL)
    {
      *node = *child;
    }
    else if (current == parent->left)
    {
      parent->left = child;
    }
    else
    {
      parent->right = child;
    }
    free(current);
  }
  else
  {
    Node *successor = findMin(current->right);
    current->data = successor->data;
    current->right = delete (current->right, successor->data);
  }

  if (node == NULL)
  {
    return NULL;
  }

  updateRank(node);

  if (getRank(node->left) > getRank(node->right) + 1)
  {
    node = balance(node);
  }

  return node;
}

// Print the inorder traversal of the tree rooted at node
void inorderTraversal(Node *node)
{
  if (node)
  {
    inorderTraversal(node->left);
    printf("%d %d, ", node->data, node->rank);
    inorderTraversal(node->right);
  }
}

int main()
{
  Node *root = NULL;
  for (int i = 10; i < 20; i++)
  {
    root = insert(root, i);
  }
  // printf("Level Order traversal of the tree: \n");
  // levelOrderTraversal(root);
  // printf("\n");
  root = insert(root, 4);
  root = insert(root, 3);
  root = insert(root, 7);
  root = insert(root, 6);
  root = insert(root, 8);
  root = insert(root, 5);
  printf("Level Order traversal of the tree: \n");
  levelOrderTraversal(root);
  printf("\n");
  printf("Inorder traversal of the tree: \n");
  inorderTraversal(root);
  printf("\n");
  root = delete (root, 5);
  root = delete (root, 6);
  printf("Inorder traversal of the tree after deletion: \n");
  // inorderTraversal(root);
  // levelOrderTraversal(root);
  inorderTraversal(root);
  printf("\n");
  return 0;
}