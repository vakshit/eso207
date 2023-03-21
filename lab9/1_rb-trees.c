// implement search insert delete in rb-trees
#include <stdio.h>
#include <stdlib.h>

#define RED 0
#define BLACK 1

typedef struct node
{
  int key;
  int color;
  struct node *left;
  struct node *right;
  struct node *parent;
} node;

node *root = NULL;
node *q = NULL;

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
}

void insert(int key)
{
  node *z = (node *)malloc(sizeof(node));
  z->key = key;
  node *x = root;
  node *y = NULL;
  while (x != q)
  {
    y = x;
    if (z->key < x->key)
    {
      x = x->left;
    }
    else
    {
      x = x->right;
    }
  }
  z->parent = y;
  if (y == NULL)
  {
    root = z;
  }
  else if (z->key < y->key)
  {
    y->left = z;
  }
  else
  {
    y->right = z;
  }
  z->left = q;
  z->right = q;
  z->color = RED;
  insertFixup(z);
}

void insertFixup(node *z)
{
  while (z->parent->color == RED)
  {
    if (z->parent == z->parent->parent->left)
    {
      node *y = z->parent->parent->right;
      if (y->color == RED)
      {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      }
      else
      {
        if (z == z->parent->right)
        {
          z = z->parent;
          leftRotate(z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        rightRotate(z->parent->parent);
      }
    }
    else
    {
      node *y = z->parent->parent->left;
      if (y->color == RED)
      {
        z->parent->color = BLACK;
        y->color = BLACK;
        z->parent->parent->color = RED;
        z = z->parent->parent;
      }
      else
      {
        if (z == z->parent->left)
        {
          z = z->parent;
          rightRotate(z);
        }
        z->parent->color = BLACK;
        z->parent->parent->color = RED;
        leftRotate(z->parent->parent);
      }
    }
  }

  root->color = BLACK;
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

node *minimum(node *x)
{
  while (x->left != q)
  {
    x = x->left;
  }
  return x;
}

void deleteFixup(node *x)
{
  while (x != root && x->color == BLACK)
  {
    if (x == x->parent->left)
    {
      node *w = x->parent->right;
      if (w->color == RED)
      {
        w->color = BLACK;
        x->parent->color = RED;
        leftRotate(x->parent);
        w = x->parent->right;
      }
      if (w->left->color == BLACK && w->right->color == BLACK)
      {
        w->color = RED;
        x = x->parent;
      }
      else
      {
        if (w->right->color == BLACK)
        {
          w->left->color = BLACK;
          w->color = RED;
          rightRotate(w);
          w = x->parent->right;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->right->color = BLACK;
        leftRotate(x->parent);
        x = root;
      }
    }
    else
    {
      node *w = x->parent->left;
      if (w->color == RED)
      {
        w->color = BLACK;
        x->parent->color = RED;
        rightRotate(x->parent);
        w = x->parent->left;
      }
      if (w->right->color == BLACK && w->left->color == BLACK)
      {
        w->color = RED;
        x = x->parent;
      }
      else
      {
        if (w->left->color == BLACK)
        {
          w->right->color = BLACK;
          w->color = RED;
          leftRotate(w);
          w = x->parent->left;
        }
        w->color = x->parent->color;
        x->parent->color = BLACK;
        w->left->color = BLACK;
        rightRotate(x->parent);
        x = root;
      }
    }
  }
  x->color = BLACK;
}

void delete(int key)
{
  node *z = root;
  while (z != q)
  {
    if (key == z->key)
    {
      break;
    }
    else if (key < z->key)
    {
      z = z->left;
    }
    else
    {
      z = z->right;
    }
  }
  if (z == q)
  {
    printf("key not found");
    return;
  }
  node *y = z;
  node *x;
  int yOriginalColor = y->color;
  if (z->left == q)
  {
    x = z->right;
    transplant(z, z->right);
  }
  else if (z->right == q)
  {
    x = z->left;
    transplant(z, z->left);
  }
  else
  {
    y = minimum(z->right);
    yOriginalColor = y->color;
    x = y->right;
    if (y->parent == z)
    {
      x->parent = y;
    }
    else
    {
      transplant(y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }
    transplant(z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;
  }
  if (yOriginalColor == BLACK)
  {
    deleteFixup(x);
  }
}
