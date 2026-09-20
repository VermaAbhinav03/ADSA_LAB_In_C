#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(int data) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

void preorderTraversal(struct Node *root) {

    if (root == NULL) {
        return;
    }

    struct Node *stack[100];
    int top = -1;

    stack[++top] = root;

    while (top != -1) {
        struct Node *current = stack[top--];

        printf("%d\t", current->data);

        // Push right first so that left is processed first
        if (current->right != NULL) {
            stack[++top] = current->right;
        }

        if (current->left != NULL) {
            stack[++top] = current->left;
        }
    }
}

int main() {

    struct Node *root = createNode(1);

    root->left = createNode(2);
    root->right = createNode(3);

    root->left->left = createNode(4);
    root->left->right = createNode(5);

    printf("Preorder traversal: ");
    preorderTraversal(root);

    return 0;
}
