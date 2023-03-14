#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int data;
  struct node *left;
  struct node *right;
} Node;

Node *createNode(int data)
{
  Node *newNode = (Node *)malloc(sizeof(Node));
  newNode->data = data;
  newNode->left = NULL;
  newNode->right = NULL;
  return newNode;
}

Node *insert(Node *root, int data)
{
  if (root == NULL)
  {
    return createNode(data);
  }
  if (data < root->data)
  {
    root->left = insert(root->left, data);
  }
  else if (data > root->data)
  {
    root->right = insert(root->right, data);
  }
  return root;
}

Node *search(Node *root, int data)
{
  if (root == NULL || root->data == data)
  {
    return root;
  }
  if (data < root->data)
  {
    return search(root->left, data);
  }
  return search(root->right, data);
}

Node *findMin(Node *node)
{
  Node *current = node;
  while (current && current->left != NULL)
  {
    current = current->left;
  }
  return current;
}

Node *delete(Node *root, int data)
{
  if (root == NULL)
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
    if (root->left == NULL)
    {
      Node *temp = root->right;
      free(root);
      return temp;
    }
    else if (root->right == NULL)
    {
      Node *temp = root->left;
      free(root);
      return temp;
    }
    Node *temp = findMin(root->right);
    root->data = temp->data;
    root->right = delete (root->right, temp->data);
  }
  return root;
}

void inorder(Node *root)
{
  if (root == NULL)
  {
    return;
  }
  inorder(root->left);
  printf("%d ", root->data);
  inorder(root->right);
}

int main()
{
  Node *root = NULL;
  root = insert(root, 50);
  insert(root, 30);
  insert(root, 20);
  insert(root, 40);
  insert(root, 70);
  insert(root, 60);
  insert(root, 80);
  printf("Inorder traversal of the BST: ");
  inorder(root);
  printf("\n");
  root = delete (root, 55);
  printf("Inorder traversal of the BST after deletion: ");
  inorder(root);
  printf("\n");
  return 0;
}
