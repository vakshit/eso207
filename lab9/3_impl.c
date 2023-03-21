#include <stdio.h>
#include <stdlib.h>

typedef enum
{
  RED,
  BLACK
} color_t;

typedef struct Node
{
  int key;
  color_t color;
  int rank;
  struct Node *left;
  struct Node *right;
  struct Node *parent;
} node_t;

node_t *create_node(int key, int rank, color_t color, node_t *parent)
{
  node_t *node = (node_t *)malloc(sizeof(node_t));
  node->key = key;
  node->rank = rank;
  node->color = color;
  node->left = NULL;
  node->right = NULL;
  node->parent = parent;
  return node;
}

node_t *insert(node_t *root, int key)
{
  // Insert new node into tree using binary search tree insertion algorithm
  if (root == NULL)
  {
    return create_node(key, 0, RED, NULL);
  }
  else if (key < root->key)
  {
    root->left = insert(root->left, key);
    root->left->parent = root;
  }
  else if (key > root->key)
  {
    root->right = insert(root->right, key);
    root->right->parent = root;
  }
  else
  {
    return root; // key already exists in tree
  }

  // Update rank and color of node
  root->rank = root->parent->rank + 1;
  root->color = RED;

  // Rebalance tree to maintain STREE properties
  node_t *p, *gp, *u;
  while (root->parent != NULL && root->parent->color == RED)
  {
    p = root->parent;
    gp = p->parent;
    if (p == gp->left)
    {
      u = gp->right;
      if (u != NULL && u->color == RED)
      {
        // Case 1: Parent and uncle are both red
        p->color = BLACK;
        u->color = BLACK;
        gp->color = RED;
        root = gp;
      }
      else
      {
        if (root == p->right)
        {
          // Case 2: Parent is red and root is a right child
          root = p;
          root->left = p;
          p->right = root->left;
          p = root->parent;
        }
        // Case 3: Parent is red and root is a left child
        p->color = BLACK;
        gp->color = RED;
        root = gp;
      }
    }
    else
    {
      u = gp->left;
      if (u != NULL && u->color == RED)
      {
        // Case 1: Parent and uncle are both red
        p->color = BLACK;
        u->color = BLACK;
        gp->color = RED;
        root = gp;
      }
      else
      {
        if (root == p->left)
        {
          // Case 2: Parent is red and root is a left child
          root = p;
          root->right = p;
          p->left = root->right;
          p = root->parent;
        }
        // Case 3: Parent is red and root is a right child
        p->color = BLACK;
        gp->color = RED;
        root = gp;
      }
    }
  }

  // Set root color to black to maintain STREE properties
  root->color = BLACK;
  return root;
}

node_t *search(node_t *root, int key)
{
  if (root == NULL || root->key == key)
  {
    return root;
  }
  else if (key < root->key)
  {
    return search(root->left, key);
  }
  else
  {
    return search(root->right, key);
  }
}

node_t *delete(node_t *root, int key)
{
  // Search for node to delete
  node_t *node = search(root, key);
  if (node == NULL)
  {
    return root; // Key not found
  }

  // If node has two children, find successor and swap keys
  if (node->left != NULL && node->right != NULL)
  {
    node_t *successor = node->right;
    while (successor->left != NULL)
    {
      successor = successor->left;
    }
    node->key = successor->key;
    node = successor;
  }

  // If node has at most one child, find child (if any) and update parent link
  node_t *child = (node->left != NULL) ? node->left : node->right;
  if (child != NULL)
  {
    child->parent = node->parent;
  }

  // Update rank of all nodes on path to root
  node_t *current = node;
  while (current != NULL)
  {
    current->rank--;
    current = current->parent;
  }

  // If node is root, replace with child (if any) and set color to black
  if (node->parent == NULL)
  {
    if (child != NULL)
    {
      child->color = BLACK;
      child->parent = NULL;
    }
    free(node);
    return child;
  }

  // If node is red, simply remove it and return root
  if (node->color == RED)
  {
    if (node->parent->left == node)
    {
      node->parent->left = child;
    }
    else
    {
      node->parent->right = child;
    }
    if (child != NULL)
    {
      child->parent = node->parent;
    }
    free(node);
    return root;
  }

  // Node is black and has at most one child, so fix tree to maintain RB tree properties
  node_t *sibling;
  node_t *parent;
  while (node != root && (child == NULL || child->color == BLACK))
  {
    parent = node->parent;
    if (node == parent->left)
    {
      sibling = parent->right;
      if (sibling->color == RED)
      {
        // Case 1: Sibling is red
        sibling->color = BLACK;
        parent->color = RED;
        rotate_left(parent);
        sibling = parent->right;
      }
      if ((sibling->left == NULL || sibling->left->color == BLACK) &&
          (sibling->right == NULL || sibling->right->color == BLACK))
      {
        // Case 2: Sibling is black and has two black children
        sibling->color = RED;
        node = parent;
      }
      else
      {
        if (sibling->right == NULL || sibling->right->color == BLACK)
        {
          // Case 3: Sibling is black and has a red left child
          sibling->left->color = BLACK;
          sibling->color = RED;
          rotate_right(sibling);
          sibling = parent->right;
        }
        // Case 4: Sibling is black and has a red right child
        sibling->color = parent->color;
        parent->color = BLACK;
        sibling->right->color = BLACK;
        rotate_left(parent);
        node = root;
      }
    }
    else
    {
      sibling = parent->left;
      if (sibling->color == RED)
      {
        // Case 1: Sibling is red
        sibling->color = BLACK;
        parent->color = RED;
        rotate_right(parent);
        sibling = parent->left;
      }
      if ((sibling->left == NULL || sibling->left->color == BLACK) &&
          (sibling->right == NULL || sibling->right->color == BLACK))
      {
        // Case 2: Sibling and sibling's children are black
        sibling->color = RED;
        root = parent;
        parent = root->parent;
      }
      else
      {
        if (sibling->left == NULL || sibling->left->color == BLACK)
        {
          // Case 3: Sibling's left child is black
          sibling->right->color = BLACK;
          sibling->color = RED;
          rotate_left(sibling);
          sibling = parent->left;
        }
        // Case 4: Sibling's left child is red
        sibling->color = parent->color;
        parent->color = BLACK;
        sibling->left->color = BLACK;
        rotate_right(parent);
        root = parent;
        break;
      }
    }
  }
  if (root != NULL)
  {
    root->color = BLACK;
  }
  return root;
}

int main()
{
  node_t *root = NULL;
  // Insert nodes into tree
  root = insert(root, 10);
  root = insert(root, 20);
  root = insert(root, 30);
  root = insert(root, 15);
  root = insert(root, 5);

  // Search for a node in the tree
  node_t *node = search(root, 20);
  if (node != NULL)
  {
    printf("Found node with key %d\n", node->key);
  }
  else
  {
    printf("Node not found\n");
  }

  // Delete a node from the tree
  root = delete (root, 15);

  return 0;
}
