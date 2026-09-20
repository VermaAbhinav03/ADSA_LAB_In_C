#include <stdio.h>
#include <stdlib.h>

/* 
   Red-Black Tree Node

   color = 0 -> RED
   color = 1 -> BLACK
*/
struct Node
{
    int data;
    int color;

    struct Node *left;
    struct Node *right;
    struct Node *parent;
};


/* =========================================================
   CREATE TREE
   ========================================================= */

struct Node* createTree()
{
    return NULL;
}


/* =========================================================
   CREATE NEW NODE
   ========================================================= */

struct Node* createNode(int item)
{
    struct Node *newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));

    newNode->data = item;

    /* New nodes are always inserted as RED */
    newNode->color = 0;

    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;

    return newNode;
}


/* =========================================================
   LEFT ROTATION
   ========================================================= */

void leftRotate(struct Node **root, struct Node *x)
{
    struct Node *y = x->right;

    /* Move y's left subtree to x's right */
    x->right = y->left;

    if (y->left != NULL)
        y->left->parent = x;

    /* Connect y with x's parent */
    y->parent = x->parent;

    if (x->parent == NULL)
    {
        *root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }

    /* Put x below y */
    y->left = x;
    x->parent = y;
}


/* =========================================================
   RIGHT ROTATION
   ========================================================= */

void rightRotate(struct Node **root, struct Node *y)
{
    struct Node *x = y->left;

    /* Move x's right subtree to y's left */
    y->left = x->right;

    if (x->right != NULL)
        x->right->parent = y;

    /* Connect x with y's parent */
    x->parent = y->parent;

    if (y->parent == NULL)
    {
        *root = x;
    }
    else if (y == y->parent->left)
    {
        y->parent->left = x;
    }
    else
    {
        y->parent->right = x;
    }

    /* Put y below x */
    x->right = y;
    y->parent = x;
}


/* =========================================================
   INSERT FIX
   ========================================================= */

void insertFix(struct Node **root, struct Node *z)
{
    struct Node *parent;
    struct Node *grandparent;
    struct Node *uncle;

    while (z != *root &&
           z->parent != NULL &&
           z->parent->color == 0)
    {
        parent = z->parent;
        grandparent = parent->parent;

        /* Parent is left child of grandparent */
        if (parent == grandparent->left)
        {
            uncle = grandparent->right;

            /* CASE 1: Uncle is RED */
            if (uncle != NULL && uncle->color == 0)
            {
                parent->color = 1;
                uncle->color = 1;
                grandparent->color = 0;

                z = grandparent;
            }
            else
            {
                /* CASE 2: z is right child */
                if (z == parent->right)
                {
                    z = parent;
                    leftRotate(root, z);

                    parent = z->parent;
                    grandparent = parent->parent;
                }

                /* CASE 3: z is left child */
                parent->color = 1;
                grandparent->color = 0;

                rightRotate(root, grandparent);
            }
        }

        /* Parent is right child of grandparent */
        else
        {
            uncle = grandparent->left;

            /* CASE 1: Uncle is RED */
            if (uncle != NULL && uncle->color == 0)
            {
                parent->color = 1;
                uncle->color = 1;
                grandparent->color = 0;

                z = grandparent;
            }
            else
            {
                /* CASE 2: z is left child */
                if (z == parent->left)
                {
                    z = parent;
                    rightRotate(root, z);

                    parent = z->parent;
                    grandparent = parent->parent;
                }

                /* CASE 3: z is right child */
                parent->color = 1;
                grandparent->color = 0;

                leftRotate(root, grandparent);
            }
        }
    }

    /* Root must always be BLACK */
    (*root)->color = 1;
}


/* =========================================================
   INSERT ITEM
   ========================================================= */

void insertItem(struct Node **root, int item)
{
    struct Node *newNode;
    struct Node *current;
    struct Node *parent;

    newNode = createNode(item);

    /* Empty tree */
    if (*root == NULL)
    {
        newNode->color = 1;
        *root = newNode;
        return;
    }

    current = *root;
    parent = NULL;

    /* Normal BST insertion */
    while (current != NULL)
    {
        parent = current;

        if (item < current->data)
            current = current->left;

        else if (item > current->data)
            current = current->right;

        else
        {
            /* Duplicate value */
            free(newNode);
            return;
        }
    }

    newNode->parent = parent;

    if (item < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;

    /* Fix Red-Black Tree */
    insertFix(root, newNode);
}


/* =========================================================
   SEARCH ITEM
   ========================================================= */

struct Node* searchItem(struct Node *root, int item)
{
    if (root == NULL)
        return NULL;

    if (root->data == item)
        return root;

    if (item < root->data)
        return searchItem(root->left, item);

    return searchItem(root->right, item);
}


/* =========================================================
   FIND MINIMUM
   ========================================================= */

struct Node* minimum(struct Node *root)
{
    struct Node *current = root;

    while (current->left != NULL)
        current = current->left;

    return current;
}


/* =========================================================
   TRANSPLANT
   ========================================================= */

void transplant(struct Node **root,
                struct Node *u,
                struct Node *v)
{
    if (u->parent == NULL)
    {
        *root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }

    if (v != NULL)
        v->parent = u->parent;
}


/* =========================================================
   DELETE FIX
   ========================================================= */

void deleteFix(struct Node **root,
               struct Node *x,
               struct Node *parent)
{
    struct Node *sibling;

    while (x != *root &&
           (x == NULL || x->color == 1))
    {
        if (x == parent->left)
        {
            sibling = parent->right;

            /* CASE 1: Sibling is RED */
            if (sibling != NULL && sibling->color == 0)
            {
                sibling->color = 1;
                parent->color = 0;

                leftRotate(root, parent);

                sibling = parent->right;
            }

            /* CASE 2: Sibling's children are BLACK */
            if (sibling == NULL ||
                ((sibling->left == NULL ||
                  sibling->left->color == 1) &&
                 (sibling->right == NULL ||
                  sibling->right->color == 1)))
            {
                if (sibling != NULL)
                    sibling->color = 0;

                x = parent;
                parent = x->parent;
            }

            else
            {
                /* CASE 3: Near child is RED */
                if (sibling->right == NULL ||
                    sibling->right->color == 1)
                {
                    if (sibling->left != NULL)
                        sibling->left->color = 1;

                    sibling->color = 0;

                    rightRotate(root, sibling);

                    sibling = parent->right;
                }

                /* CASE 4: Far child is RED */
                sibling->color = parent->color;
                parent->color = 1;

                if (sibling->right != NULL)
                    sibling->right->color = 1;

                leftRotate(root, parent);

                x = *root;
                parent = NULL;
            }
        }

        else
        {
            sibling = parent->left;

            /* CASE 1: Sibling is RED */
            if (sibling != NULL && sibling->color == 0)
            {
                sibling->color = 1;
                parent->color = 0;

                rightRotate(root, parent);

                sibling = parent->left;
            }

            /* CASE 2: Sibling's children are BLACK */
            if (sibling == NULL ||
                ((sibling->left == NULL ||
                  sibling->left->color == 1) &&
                 (sibling->right == NULL ||
                  sibling->right->color == 1)))
            {
                if (sibling != NULL)
                    sibling->color = 0;

                x = parent;
                parent = x->parent;
            }

            else
            {
                /* CASE 3: Near child is RED */
                if (sibling->left == NULL ||
                    sibling->left->color == 1)
                {
                    if (sibling->right != NULL)
                        sibling->right->color = 1;

                    sibling->color = 0;

                    leftRotate(root, sibling);

                    sibling = parent->left;
                }

                /* CASE 4: Far child is RED */
                sibling->color = parent->color;
                parent->color = 1;

                if (sibling->left != NULL)
                    sibling->left->color = 1;

                rightRotate(root, parent);

                x = *root;
                parent = NULL;
            }
        }
    }

    if (x != NULL)
        x->color = 1;
}


/* =========================================================
   DELETE ITEM
   ========================================================= */

void deleteItem(struct Node **root, int item)
{
    struct Node *z;
    struct Node *y;
    struct Node *x;
    struct Node *xParent;

    z = searchItem(*root, item);

    /* Item not found */
    if (z == NULL)
        return;

    y = z;

    /* Save original color */
    int originalColor = y->color;

    x = NULL;
    xParent = NULL;

    /* Case 1: No left child */
    if (z->left == NULL)
    {
        x = z->right;
        xParent = z->parent;

        transplant(root, z, z->right);
    }

    /* Case 2: No right child */
    else if (z->right == NULL)
    {
        x = z->left;
        xParent = z->parent;

        transplant(root, z, z->left);
    }

    /* Case 3: Two children */
    else
    {
        y = minimum(z->right);

        originalColor = y->color;

        x = y->right;

        if (y->parent == z)
        {
            xParent = y;

            if (x != NULL)
                x->parent = y;
        }
        else
        {
            xParent = y->parent;

            transplant(root, y, y->right);

            y->right = z->right;
            y->right->parent = y;
        }

        transplant(root, z, y);

        y->left = z->left;
        y->left->parent = y;

        y->color = z->color;
    }

    free(z);

    /*
       If a BLACK node was deleted,
       Red-Black properties may be broken.
    */
    if (originalColor == 1)
    {
        deleteFix(root, x, xParent);
    }
}


/* =========================================================
   DELETE ENTIRE TREE
   ========================================================= */

void deleteTree(struct Node *root)
{
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);

    free(root);
}


/* =========================================================
   INORDER TRAVERSAL
   ========================================================= */

void inorder(struct Node *root)
{
    if (root == NULL)
        return;

    inorder(root->left);

    if (root->color == 0)
        printf("%d(R) ", root->data);
    else
        printf("%d(B) ", root->data);

    inorder(root->right);
}


/* =========================================================
   MAIN
   ========================================================= */

int main()
{
    struct Node *root;
    struct Node *result;

    root = createTree();

    /* Insert */
    insertItem(&root, 30);
    insertItem(&root, 20);
    insertItem(&root, 10);
    insertItem(&root, 25);
    insertItem(&root, 40);
    insertItem(&root, 50);

    printf("Red-Black Tree:\n");
    inorder(root);

    /* Search */
    result = searchItem(root, 25);

    if (result != NULL)
        printf("\n25 found.\n");
    else
        printf("\n25 not found.\n");

    /* Delete */
    deleteItem(&root, 20);

    printf("\nAfter deleting 20:\n");
    inorder(root);

    /* Delete complete tree */
    deleteTree(root);
    root = NULL;

    printf("\n\nTree deleted successfully.\n");

    return 0;
}