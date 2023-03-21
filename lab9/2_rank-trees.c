// implement search insert delete in rank-trees
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
  int key;
  int size;
  struct node *left;
  struct node *right;
  struct node *parent;
} node;

node *root = NULL;
node *q = NULL;

int size(node *n)
{
  if (n == q)
    return 0;
  return n->size;
}

void fix(node *n)
{
  n->size = size(n->left) + size(n->right) + 1;
}

node *newNode(int key)
{
  node *n = (node *)malloc(sizeof(node));
  n->key = key;
  n->left = n->right = n->parent = q;
  n->size = 1;
  return n;
}

void leftRotate(node *x)
{
  node *y = x->right;
  x->right = y->left;
  if (y->left != q)
  {
    y->left->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NULL)
  {
    root = y;
  }
  else if (x == x->parent->left)
  {
    x->parent->left = y;
  }
  else
  {
    x->parent->right = y;
  }
  y->left = x;
  x->parent = y;
  fix(x);
  fix(y);
}

void rightRotate(node *x)
{
  node *y = x->left;
  x->left = y->right;
  if (y->right != q)
  {
    y->right->parent = x;
  }
  y->parent = x->parent;
  if (x->parent == NULL)
  {
    root = y;
  }
  else if (x == x->parent->right)
  {
    x->parent->right = y;
  }
  else
  {
    x->parent->left = y;
  }
  y->right = x;
  x->parent = y;
  fix(x);
  fix(y);
}

void insert(int key)
{
  node *n = newNode(key);
  node *x = root;
  node *y = NULL;
  while (x != q)
  {
    y = x;
    if (n->key < x->key)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }
  n->parent = y;
  if (y == NULL)
  {
    root = n;
  }
  else if (n->key < y->key)
  {
    y->left = n;
  }
  else
  {
    y->right = n;
  }
  while (n != root)
  {
    if (n->parent->left == n)
    {
      n->parent->size++;
    }
    n = n->parent;
  }
}

node *search(int key)
{
  node *n = root;
  while (n != q)
  {
    if (key == n->key)
    {
      return n;
    }
    else if (key < n->key)
    {
      n = n->left;
    }
    else
    {
      n = n->right;
    }
  }
  return NULL;
}

node *minimum(node *n)
{
  while (n->left != q)
  {
    n = n->left;
  }
  return n;
}

node *maximum(node *n)
{
  while (n->right != q)
  {
    n = n->right;
  }
  return n;
}

node *successor(node *n)
{
  if (n->right != q)
  {
    return minimum(n->right);
  }
  node *y = n->parent;
  while (y != q && n == y->right)
  {
    n = y;
    y = y->parent;
  }
  return y;
}

node *predecessor(node *n)
{
  if (n->left != q)
  {
    return maximum(n->left);
  }
  node *y = n->parent;
  while (y != q && n == y->left)
  {
    n = y;
    y = y->parent;
  }
  return y;
}

void transplant(node *u, node *v)
{
  if (u->parent == NULL)
  {
    root = v;
  }
  else if (u == u->parent->left)
  {
    u->parent->left = v;
  }
  else
  {
    u->parent->right = v;
  }
  v->parent = u->parent;
}

void delete(int key)
{
  node *n = search(key);
  if (n == NULL)
  {
    printf("key not found");
    return;
  }
  if (n->left == q)
  {
    transplant(n, n->right);
  }
  else if (n->right == q)
  {
    transplant(n, n->left);
  }
  else
  {
    node *y = minimum(n->right);
    if (y->parent != n)
    {
      transplant(y, y->right);
      y->right = n->right;
      y->right->parent = y;
    }
    transplant(n, y);
    y->left = n->left;
    y->left->parent = y;
  }
  while (n != NULL && n != root)
  {
    if (n->parent->left == n)
    {
      n->parent->size--;
    }
    n = n->parent;
  }
  if (n == root)
  {
    n->size--;
  }
}

int rank(node *n)
{
  int r = size(n->left) + 1;
  node *y = n;
  while (y != root)
  {
    if (y == y->parent->right)
    {
      r += size(y->parent->left) + 1;
    }
    y = y->parent;
  }
  return r;
}

int main()
{
  q = (node *)malloc(sizeof(node));
  q->left = q->right = q->parent = NULL;
  q->size = 0;
  root = q;

  for (int i = 100; i >= 0; i--)
    insert(i);

  delete (100);

  for (int i = 10; i <= 50; i += 7)
    delete (i);

  for (int i = 0; i <= 100; i++)
    printf("%d %d, ", i, rank(search(i)));
  return 0;
}
