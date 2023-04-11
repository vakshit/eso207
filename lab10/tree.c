#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct node
{
    int key;
    int rank;
    struct node *parent;
    struct node *left;
    struct node *right;
};
struct node *root1 = NULL;
struct node *root2 = NULL;

struct node *newNode(int key)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = key;
    temp->rank = 0;
    temp->parent = NULL;
    temp->left = NULL;
    temp->right = NULL;
    return temp;
}

int isRed(struct node *z)
{
    if (z->rank == z->parent->rank)
        return 1;
    else
        return 0;
}

int get_rank(struct node *z)
{
    if (z == NULL)
        return 0;
    else
        return z->rank;
}

struct node *TriNode(struct node *T, struct node *z)
{
    struct node *p = z->parent;
    struct node *g = z->parent->parent;

    if ((g->key > p->key) && (p->key > z->key))
    {
        g->left = p->right;
        if (p->right != NULL)
            p->right->parent = g;
        p->parent = g->parent;
        if (g->parent == NULL)
            T = p;
        else if (g == g->parent->left)
            g->parent->left = p;
        else
            g->parent->right = p;
        p->right = g;
        g->parent = p;
    }

    else if ((g->key > p->key) && (p->key < z->key))
    {
        p->right = z->left;
        if (z->left != NULL)
            z->left->parent = p;
        g->left = z->right;
        if (z->right != NULL)
            z->right->parent = g;
        z->parent = g->parent;
        if (g->parent == NULL)
            T = z;
        else if (g == g->parent->left)
            g->parent->left = z;
        else
            g->parent->right = z;
        z->left = p;
        z->right = g;
        p->parent = z;
        g->parent = z;
    }

    else if ((g->key < p->key) && (p->key > z->key))
    {
        p->left = z->right;
        if (z->right != NULL)
            z->right->parent = p;
        g->right = z->left;
        if (z->left != NULL)
            z->left->parent = g;
        z->parent = g->parent;
        if (g->parent == NULL)
            T = z;
        else if (g == g->parent->left)
            g->parent->left = z;
        else
            g->parent->right = z;
        z->left = g;
        z->right = p;
        g->parent = z;
        p->parent = z;
    }

    else if ((g->key < p->key) && (p->key < z->key))
    {
        g->right = p->left;
        if (p->left != NULL)
            p->left->parent = g;
        p->parent = g->parent;
        if (g->parent == NULL)
            T = p;
        else if (g == g->parent->left)
            g->parent->left = p;
        else
            g->parent->right = p;
        p->left = g;
        g->parent = p;
    }
    return T;
}

struct node *RB_FixInsert(struct node *T, struct node *z)
{
    struct node *p = z->parent;
    struct node *g = p->parent;

    while (p != NULL && g != NULL)
    {
        if (isRed(z) == isRed(p))
        {
            if (p == g->right)
            {
                if (g->left == NULL)
                    T = TriNode(T, z);
                else
                {
                    if (g->rank == g->left->rank)
                    {
                        g->rank = g->rank + 1;

                        z = g;
                        p = g->parent;
                        if (g->parent != NULL)
                            g = g->parent->parent;
                        // p = g->parent;
                        // if (g->parent == NULL)
                        //     g = NULL;
                        // else
                        //     g = g->parent->parent;
                        continue;
                    }
                    else
                        T = TriNode(T, z);
                }
            }
            else if (p == g->left)
            {
                if (g->right == NULL)
                    T = TriNode(T, z);
                else
                {
                    if (g->right->rank == g->rank)
                    {
                        g->rank++;
                        z = g;
                        p = g->parent;
                        if (g->parent != NULL)
                            g = g->parent->parent;
                        // p = g->parent;
                        // if (g->parent == NULL)
                        //     g = NULL;
                        // else
                        //     g = g->parent->parent;
                        continue;
                    }
                    else
                        T = TriNode(T, z);
                }
            }
            return T;
        }
        else
            return T;
    }
    return T;
}

struct node *insert(struct node *T, int key)
{
    struct node *z = newNode(key);
    if (T == NULL)
    {
        z->rank = 1;
        T = z;
        return T;
    }

    else
    {
        struct node *y = NULL;
        struct node *x = T;
        while (x != NULL)
        {
            y = x;
            if (z->key < x->key)
                x = x->left;
            else if (z->key == x->key)
                return T;
            else
                x = x->right;
        }
        z->rank = 1;
        z->parent = y;
        if (z->key < y->key)
            y->left = z;
        else
            y->right = z;
        T = RB_FixInsert(T, z);
    }
    return T;
}

struct node* search(struct node *T, int k)
{
    if (T == NULL)
    {
        printf("Provided key is not Present:(\n");
        return NULL;
    }
    if (k > T->key)
        return search(T->right, k);
    else if (k < T->key)
        return search(T->left, k);
    else
    {
        printf("Provided key is present:)\n");
        return T;
    }
    // struct node *tmp = T;
    // while (tmp != NULL)
    // {
    //     if (k > tmp->key)
    //     {
    //         tmp = tmp->right;
    //     }
    //     else if (k < tmp->key)
    //     {
    //         tmp = tmp->left;
    //     }
    //     else
    //     {
    //         printf("Provided key is present:)\n");
    //         return;
    //     }
    // }
    // printf("Provided key is not Present:(\n");
    // return;
}

void inOrder(struct node *T)
{
    if (T == NULL)
        return;
    if (T != NULL)
    {
        inOrder(T->left);
        printf("(%d : %d) ", T->key, T->rank);
        inOrder(T->right);
    }
}

struct node *findMin(struct node *z)
{
    if (z == NULL)
        return z;
    else
    {
        while (z->left != NULL)
        {
            z = z->left;
        }
    }
    return z;
}

struct node *RB_FixDelete(struct node *T, struct node *z)
{
    struct node *p = z->parent;
    if (p == NULL)
        return T;

    if (z == p->left)
    {
        struct node *s = p->right;
        while (z != NULL)
        {
            if (s->rank == p->rank - 1 && s->left != NULL && s->right != NULL)
            {
                if (2 * p->rank - (s->left->rank + s->right->rank) == 4)
                {
                    p->rank--;
                    z = p;
                    continue;
                }
                else if (2 * p->rank - (s->left->rank + s->right->rank) == 2)
                {
                    T = TriNode(T, s->right);
                    return T;
                }
                else
                {
                    if (s->left->rank == p->rank - 1)
                        T = TriNode(T, s->left);
                    else if (s->right->rank == p->rank - 1)
                        T = TriNode(T, s->right);
                    return T;
                }
                return T;
            } // case 1
            else if (s->rank == p->rank && s->left != NULL && s->right != NULL)
            {
                T = TriNode(T, s->right);
                return T;
            } // case 2
            else
                return T;
        }
    }
    else if (z == p->right)
    {
        struct node *s = p->left;
        while (z != NULL)
        {
            if (s->rank == p->rank - 1 && s->left != NULL && s->right != NULL)
            {
                if (2 * p->rank - (s->left->rank + s->right->rank) == 4)
                {
                    p->rank--;
                    z = p;
                    continue;
                }
                else if (2 * p->rank - (s->left->rank + s->right->rank) == 2)
                {
                    T = TriNode(T, s->left);
                    return T;
                }
                else
                {
                    if (s->left->rank == p->rank - 1)
                        T = TriNode(T, s->left);
                    else if (s->right->rank == p->rank - 1)
                        T = TriNode(T, s->right);
                    return T;
                }
                return T;
            }
            else if (s->rank == p->rank && s->left != NULL && s->right != NULL)
            {
                T = TriNode(T, s->right);
                return T;
            }
            else
                return T;
        }
    }
}

struct node *delete(struct node *T, int key)
{
    if (T == NULL)
        return NULL;
    else
    {
        struct node *x = T;
        while (x != NULL)
        {
            if (key < x->key)
                x = x->left;
            else if (key == x->key)
                break;
            else
                x = x->right;
        }
        if (x == NULL)
        {
            printf("not key found\n");
            return T;
        }
        else
        {
            if (x->left == NULL)
            {
                if (x->parent == NULL)
                    T = x->right;
                else if (x == x->parent->left)
                    x->parent->left = x->right;
                else
                    x->parent->right = x->right;
                if (x->right != NULL)
                    x->right->parent = x->parent;
                if (x->parent != NULL && x->right != NULL)
                    if ((x->parent->rank) - (x->right->rank) == 2)
                        T = RB_FixDelete(T, x->right);
                return T;
            }
            else if (x->right == NULL)
            {
                if (x->parent == NULL)
                    T = x->left;
                else if (x == x->parent->left)
                    x->parent->left = x->left;
                else
                    x->parent->right = x->left;
                if (x->left != NULL)
                    x->left->parent = x->parent;
                if (x->parent != NULL && x->left != NULL)
                    if ((x->parent->rank) - (x->left->rank) == 2)
                        T = RB_FixDelete(T, x->left);
                return T;
            }
            else
            {
                struct node *y = findMin(x->right);
                if (y->parent != x)
                {
                    if (y == y->parent->left)
                        y->parent->left = y->right;
                    else
                        y->parent->right = y->right;
                    y->right = x->right;
                    if (y->right != NULL)
                        y->right->parent = y->parent;
                    if (y->parent->rank - y->right->rank == 2)
                        T = RB_FixDelete(T, y->right);
                }
                if (x->parent == NULL)
                    T = y;
                else if (x == x->parent->left)
                    x->parent->left = y;
                else
                    x->parent->right = y;
                y->parent = x->parent;
                y->rank = x->rank;
                if (y->parent != NULL)
                    if (y->parent->rank - y->rank == 2)
                        T = RB_FixDelete(T, y);
                y->left = x->left;
                if (y->left != NULL)
                    y->left->parent = y;
                if (y->left->rank - y->rank == 2)
                    T = RB_FixDelete(T, y->left);
                return T;
            }
        }
        return T;
    }
}

struct node *join(struct node *T1, struct node *T2, int k)
{

    // All the nodes in T1 have keys less than k and all the nodes in T2 have keys greater than k
    struct node *new_root = NULL;
    // printf("\nRank of T1: %d\n", get_rank(T1));
    // printf("Rank of T2: %d\n", get_rank(T2));
    
    if (get_rank(T1) > get_rank(T2))
    {
        struct node *temp = T1;

        // Take right pointers till we reach anode with same rank as T2
        while (get_rank(temp) != get_rank(T2))
        {
            temp = temp->right;
            // printf("Loop\n");
        }
        // struct node* x=temp;

        struct node *z = (struct node *)malloc(sizeof(struct node));
        z->parent = temp->parent;
        temp->parent->right = z;
        z->left = temp;
        z->right = T2;
        z->key = k;
        z->rank = get_rank(T2) + 1;
        // printf("Rank of z: %d\n", z->rank);
        new_root = RB_FixInsert(T1, z);
    }
    else if(get_rank(T1) == get_rank(T2))
    {
        struct node *z = (struct node *)malloc(sizeof(struct node));
        z->parent = NULL;
        z->left = T1;
        z->right = T2;
        z->key = k;
        z->rank = get_rank(T1) + 1;
        new_root = z;
    }
    else
    {
        struct node *temp = T2;

        // Take left pointers till we reach anode with same rank as T1
        while (get_rank(temp) != get_rank(T1))
        {
            temp = temp->left;
            // printf("Loop\n");
        }
        // struct node* x=temp;

        struct node *z = (struct node *)malloc(sizeof(struct node));
        z->parent = temp->parent;
        temp->parent->left = z;
        z->left = T1;
        z->right = temp;
        z->key = k;
        z->rank = get_rank(T1) + 1;

        new_root = RB_FixInsert(T2, z);
    }
    return new_root;
}

void split(struct node* T, int k, struct node** T1, struct node** T2)
{
    // All the nodes in T1 have keys less than k and all the nodes in T2 have keys greater than k
    struct node* z=search(T,k);
    if(z==NULL){
        printf("Key not found\n");
        return;
    }
    *T1 = z->left;
    *T2 = z->right;
    while(z->parent != NULL){
        struct node* y=z->parent;
        if(y->left==z){
            *T2 = join(*T2, y->right, y->key);
        }
        else{
            *T1 = join(*T1, y->left, y->key);
        }
        z=y;
    }
    return;
}


int main()
{
    int n = 5;
    int arr1[5] = {1, 2, 3, 4, 5};
    int arr2[20] = {7,8,9,10,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28};

    for (int i = 0; i < 5; i++)
    {
        root1 = insert(root1, arr1[i]);
    }
    for (int i = 0; i < 20; i++)
    {
        root2 = insert(root2, arr2[i]);
    }

    printf("Inorder traversal of tree1 is: ");
    inOrder(root1);
    printf("\nInorder traversal of tree2 is: ");
    inOrder(root2);
    
    root1 = join(root1, root2, 6);
    printf("Inorder traversal of new tree is: ");
    inOrder(root1);
    printf("\n");
    printf("New root is: %d\n", root1->key);
    printf("New root rank: %d\n", root1->rank);

    struct node* T1=NULL;
    struct node* T2=NULL;
    split(root1, 6, &T1, &T2);
    printf("Inorder traversal of T1 is: ");
    inOrder(T1);
    printf("\nRoot of T1 is: %d\n", T1->key);
    printf("Rank of T1 is: %d\n", T1->rank);
    printf("Inorder traversal of T2 is: ");
    inOrder(T2);
    printf("\nRoot of T2 is: %d\n", T2->key);
    printf("Rank of T2 is: %d\n", T2->rank);


    // while (1)
    // {
    //     printf("\n");
    //     printf("choose the following\n");
    //     printf("1 to insert\n");
    //     printf("2 to search\n");
    //     printf("3 to print inorder\n");
    //     printf("4 to Delete a key\n");
    //     printf("5 to join two trees\n");
    //     printf("6 to exit\n");
    //     // pribntf("7 to join two trees\n");
    //     int choice;
    //     printf("enter the choice: ");
    //     scanf("%d", &choice);
    //     switch (choice)
    //     {
    //     // case 7:
    //     //     printf()
    //     case 1:
    //         printf("enter the tree: ");
    //         int l;
    //         scanf("%d", &l);
    //         if(l==1){
    //             printf("enter the size: ");
    //             int n;
    //             scanf("%d", &n);
    //             // srand(time(NULL));

    //             for (int i = 0; i < n; i++)
    //             {
    //                 struct node *z;
    //                 z = (struct node *)malloc(sizeof(struct node));
    //                 z->parent = NULL;
    //                 z->left = NULL;
    //                 z->right = NULL;
    //                 int t;
    //                 printf("enter the key: ");
    //                 scanf("%d", &t);
    //                 z->key = t;
    //                 // z->key = rand() % 100;
    //                 root1 = insert(root1, z);
    //             }
    //         }
    //         else if(l==2){
    //             printf("enter the size: ");
    //             int n;
    //             scanf("%d", &n);
    //             // srand(time(NULL));

    //             for (int i = 0; i < n; i++)
    //             {
    //                 struct node *z;
    //                 z = (struct node *)malloc(sizeof(struct node));
    //                 z->parent = NULL;
    //                 z->left = NULL;
    //                 z->right = NULL;
    //                 int t;
    //                 printf("enter the key: ");
    //                 scanf("%d", &t);
    //                 z->key = t;
    //                 // z->key = rand() % 100;
    //                 root2 = insert(root2, z);
    //             }
    //         }
    //         else{
    //             printf("enter a valid tree number\n");
    //         }
    //         break;

    //     case 2:
    //         printf("Enter the key to be searched: ");
    //         int k;
    //         scanf("%d", &k);
    //         search(root1, k);
    //         break;

    //     case 3:
    //         printf("enter the tree: ");
    //         // int l;
    //         scanf("%d", &l);
    //         if(l==1){
    //             if (root1 == NULL)
    //             {
    //                 printf("Tree is empty!!\n");
    //                 break;
    //             }

    //             inOrder(root1);
    //             printf("\n");
    //             printf("root key is: %d\n", root1->key);
    //             printf("root rank is: %d\n", root1->rank);
    //         }
    //         else if(l==2){
    //             if (root2 == NULL)
    //             {
    //                 printf("Tree is empty!!\n");
    //                 break;
    //             }

    //             inOrder(root2);
    //             printf("\n");
    //             printf("root key is: %d\n", root2->key);
    //             printf("root rank is: %d\n", root2->rank);
    //         }
    //         else{
    //             printf("enter a valid tree number\n");
    //         }
    //         break;

    //     case 4:
    //         printf("enter the key to delete: ");
    //         int key;
    //         scanf("%d", &key);
    //         root1 = delete (root1, key);
    //         break;

    //     case 5:
    //         //Join trees
    //         printf("enter the key to join: ");
    //         int h;
    //         scanf("%d", &h);
    //         root1 = join(root1, root2, h);
    //         break;
    //     case 6:
    //         exit(1);

    //     default:
    //         printf("invalid choice...\n");
    //     }
    // }
    return 0;
}
