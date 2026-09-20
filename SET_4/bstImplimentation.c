#include<stdio.h>
#include<stdlib.h>
struct Node{
    int data;
    struct Node *left;
    struct Node *right;

};

struct Node* createTree(){
    return NULL;
}

struct Node* insertItem(struct Node *root,int item){
    if (root==NULL){
        struct Node *newNode;
        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data=item;
        newNode->left=NULL;
        newNode->right=NULL;

        return newNode;
    }
    if (item<root->data){
        root->left=insertItem(root->left,item);
    }
    else if (item>root->data){
        root->right=insertItem(root->right,item);
    }

    return root;
}

struct Node* searchItem(struct Node* root,int item){
    if (root==NULL){
        return NULL;
    }
    if(root->data==item){
        return root;
    }
    if(item<root->data){
        return searchItem(root->left,item);
    }
    if(item>root->data){
        return searchItem(root->right,item);
    }

}

struct Node* findMin(struct Node* root){

    struct Node* current = root;
    while(current!=NULL && current->left!=NULL){
        current=current->left;
    }

    return current;
    
}

struct Node* deleteItem(struct Node* root,int item){

    struct Node* temp;
     
    if(root==NULL){
        return NULL;
    }
    if (item<root->data){
        root->left=deleteItem(root->left,item);
    }
    else if (item>root->data){
        root->right=deleteItem(root->right,item);
    }
    else{

        if (root->left == NULL && root->right == NULL){
            free(root);
            return NULL;
        }
        else if (root->left == NULL){
            temp=root->right;
            free(root);
            return temp;
        }
        else if (root->right=NULL){
            temp=root->left;
            free(root);
            return temp;
        }
        else{
            temp=findMin(root->right);
            root->data=temp->data;
            root->right=deleteItem(root->right,temp->data);
        }
    }
    return root;
}

void deleteTree(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    deleteTree(root->left);

    deleteTree(root->right);
    free(root);
}



int main()
{
    struct Node *root;
    struct Node *result;

    /* Create empty tree */
    root = createTree();

    /* Insert items */
    root = insertItem(root, 50);
    root = insertItem(root, 30);
    root = insertItem(root, 70);
    root = insertItem(root, 20);
    root = insertItem(root, 40);
    root = insertItem(root, 60);
    root = insertItem(root, 80);


    /* Search */
    result = searchItem(root, 40);

    if (result != NULL)
    {
        printf("\n40 found in BST.");
    }
    else
    {
        printf("\n40 not found in BST.");
    }

    /* Delete */
    root = deleteItem(root, 30);



    /* Delete entire tree */
    deleteTree(root);
    root = NULL;

    printf("\nTree deleted successfully.\n");

    return 0;
}