#include <stdio.h>
#include <stdlib.h>

/* AVL Tree Node */
struct Node
{
    int data;
    int height;
    struct Node *left;
    struct Node *right;
};


/* ---------- Helper Functions ---------- */

int max(int a, int b)
{
    return (a > b) ? a : b;
}


int getHeight(struct Node *root)
{
    if (root == NULL)
        return 0;

    return root->height;
}


int getBalanceFactor(struct Node *root)
{
    if (root == NULL)
        return 0;

    return getHeight(root->left) -
           getHeight(root->right);
}


/* ---------- Right Rotation ---------- */

struct Node* rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    /* Perform rotation */
    x->right = y;
    y->left = T2;

    /* Update heights */
    y->height = 1 + max(getHeight(y->left),
                        getHeight(y->right));

    x->height = 1 + max(getHeight(x->left),
                        getHeight(x->right));

    return x;
}


/* ---------- Left Rotation ---------- */

struct Node* leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    /* Perform rotation */
    y->left = x;
    x->right = T2;

    /* Update heights */
    x->height = 1 + max(getHeight(x->left),
                        getHeight(x->right));

    y->height = 1 + max(getHeight(y->left),
                        getHeight(y->right));

    return y;
}


/* ---------- Find Minimum ---------- */

struct Node* findMin(struct Node *root)
{
    struct Node *current = root;

    while (current->left != NULL)
    {
        current = current->left;
    }

    return current;
}


/* ==================================================
   1. CREATE TREE
   ================================================== */

struct Node* createTree()
{
    return NULL;
}


/* ==================================================
   2. INSERT ITEM
   ================================================== */

struct Node* insertItem(struct Node *root, int item)
{
    /* Step 1: Normal BST insertion */

    if (root == NULL)
    {
        struct Node *newNode;

        newNode = (struct Node*)malloc(sizeof(struct Node));

        newNode->data = item;
        newNode->left = NULL;
        newNode->right = NULL;

        /* New node is a leaf */
        newNode->height = 1;

        return newNode;
    }


    /* Go to left subtree */
    if (item < root->data)
    {
        root->left = insertItem(root->left, item);
    }

    /* Go to right subtree */
    else if (item > root->data)
    {
        root->right = insertItem(root->right, item);
    }

    /* Duplicate value */
    else
    {
        return root;
    }


    /* Step 2: Update height */

    root->height = 1 + max(getHeight(root->left),
                           getHeight(root->right));


    /* Step 3: Calculate balance factor */

    int balance = getBalanceFactor(root);


    /* Step 4: Check four AVL cases */


    /* LL Case */
    if (balance > 1 &&
        item < root->left->data)
    {
        return rightRotate(root);
    }


    /* RR Case */
    if (balance < -1 &&
        item > root->right->data)
    {
        return leftRotate(root);
    }


    /* LR Case */
    if (balance > 1 &&
        item > root->left->data)
    {
        root->left = leftRotate(root->left);

        return rightRotate(root);
    }


    /* RL Case */
    if (balance < -1 &&
        item < root->right->data)
    {
        root->right = rightRotate(root->right);

        return leftRotate(root);
    }


    /* Return unchanged root */
    return root;
}


/* ==================================================
   3. SEARCH ITEM
   ================================================== */

struct Node* searchItem(struct Node *root, int item)
{
    /* Tree is empty / item not found */

    if (root == NULL)
    {
        return NULL;
    }


    /* Item found */

    if (root->data == item)
    {
        return root;
    }


    /* Search left */

    if (item < root->data)
    {
        return searchItem(root->left, item);
    }


    /* Search right */

    return searchItem(root->right, item);
}


/* ==================================================
   4. DELETE ITEM
   ================================================== */

struct Node* deleteItem(struct Node *root, int item)
{
    /* Step 1: Normal BST deletion */

    if (root == NULL)
    {
        return NULL;
    }


    /* Search in left subtree */

    if (item < root->data)
    {
        root->left = deleteItem(root->left, item);
    }


    /* Search in right subtree */

    else if (item > root->data)
    {
        root->right = deleteItem(root->right, item);
    }


    /* Item found */

    else
    {
        /* Case 1: No child */

        if (root->left == NULL &&
            root->right == NULL)
        {
            free(root);

            return NULL;
        }


        /* Case 2: Only right child */

        else if (root->left == NULL)
        {
            struct Node *temp = root->right;

            free(root);

            return temp;
        }


        /* Case 3: Only left child */

        else if (root->right == NULL)
        {
            struct Node *temp = root->left;

            free(root);

            return temp;
        }


        /* Case 4: Two children */

        else
        {
            struct Node *temp;

            temp = findMin(root->right);

            /* Copy successor value */

            root->data = temp->data;

            /* Delete successor */

            root->right =
                deleteItem(root->right,
                           temp->data);
        }
    }


    /* Step 2: Update height */

    root->height = 1 + max(getHeight(root->left),
                           getHeight(root->right));


    /* Step 3: Get balance factor */

    int balance = getBalanceFactor(root);


    /* Step 4: Balance the tree */


    /* LL Case */

    if (balance > 1 &&
        getBalanceFactor(root->left) >= 0)
    {
        return rightRotate(root);
    }


    /* LR Case */

    if (balance > 1 &&
        getBalanceFactor(root->left) < 0)
    {
        root->left =
            leftRotate(root->left);

        return rightRotate(root);
    }


    /* RR Case */

    if (balance < -1 &&
        getBalanceFactor(root->right) <= 0)
    {
        return leftRotate(root);
    }


    /* RL Case */

    if (balance < -1 &&
        getBalanceFactor(root->right) > 0)
    {
        root->right =
            rightRotate(root->right);

        return leftRotate(root);
    }


    return root;
}


/* ==================================================
   5. DELETE ENTIRE TREE
   ================================================== */

void deleteTree(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }


    /* Delete left subtree */

    deleteTree(root->left);


    /* Delete right subtree */

    deleteTree(root->right);


    /* Delete current node */

    free(root);
}


/* ---------- Inorder Traversal ---------- */

void inorder(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    inorder(root->left);

    printf("%d ", root->data);

    inorder(root->right);
}


/* ---------- Main ---------- */

int main()
{
    struct Node *root;
    struct Node *result;


    /* Create empty AVL tree */

    root = createTree();


    /* Insert elements */

    root = insertItem(root, 30);
    root = insertItem(root, 20);
    root = insertItem(root, 10);
    root = insertItem(root, 25);
    root = insertItem(root, 40);
    root = insertItem(root, 50);


    printf("AVL Tree (Inorder): ");
    inorder(root);


    /* Search */

    result = searchItem(root, 25);

    if (result != NULL)
    {
        printf("\n25 found in AVL tree.");
    }
    else
    {
        printf("\n25 not found.");
    }


    /* Delete */

    root = deleteItem(root, 20);

    printf("\nAfter deleting 20: ");
    inorder(root);


    /* Delete entire tree */

    deleteTree(root);

    root = NULL;

    printf("\nTree deleted successfully.\n");


    return 0;
}