
#include <stdio.h>
#include <stdlib.h>

typedef struct avl {
    int data;
    int height;
    struct avl* left;
    struct avl* right;
} AVL;


AVL* createNode(int data) {
    AVL* node;
    if((node = (AVL*)malloc(sizeof(AVL)))==NULL)
        return NULL;
    if (node != NULL) {
        node->data = data;
        node->left = NULL;
        node->right = NULL;
        node->height=1;
        return node;
    }
    return NULL;
}


int height(AVL* node) {
    if (node == NULL)
        return 0;
    return node->height;

}
void updateHeight(AVL* node) {
    node->height = __max(height(node->left), height(node->right)) + 1;
}

AVL* Rrotation(AVL* z) {
    AVL* y = z->left;
    AVL* L3 = y->right;

    z->left = L3;
    y->right = z;

    updateHeight(y);
    updateHeight(z);
    return y;


}
AVL* Lrotation(AVL* z) {

    AVL* y = z->right;								//     z                                  y
    AVL* List2 = y->left;							//    / \								 / \
													//   L1  y							   z     x
													//		/ \         -------->         / \   /  \

    y->left = z;									//	  L2   x                        L1  L2 L3  L4
    z->right = List2;								//	      / \
													//		L3	L4
    updateHeight(z);
    updateHeight(y);

    return y;
}



int balanceFactor(AVL* node) {
    if (node == NULL)
        return 0;
    return (height(node->right) - height(node->left));
}

void inOrder(AVL* node) {
    if (node == NULL) {
        return;
    }

    inOrder(node->left);
    printf(" %d", node->data);
    inOrder(node->right);

}

void inOrderBrackets(AVL* node) {
    if (node == NULL)
        return;
    printf("(");
    inOrderBrackets(node->left);
    printf("%d ", node->data);
    inOrderBrackets(node->right);
    printf(")");


}

int countLeafs(AVL* Root, int *countedLeafs) {

    if (Root == NULL)
        return 0;
    if (Root->left == NULL && Root->right == NULL)
        (*countedLeafs)++;
    countLeafs(Root->left,countedLeafs);
    countLeafs(Root->right,countedLeafs);
    return *countedLeafs;
}
AVL* LRrotation(AVL* leaf){
    leaf->left=Lrotation(leaf->left);
    leaf=Rrotation(leaf);
    return leaf;
}
AVL* RLrotation(AVL* leaf){
    leaf->right=Rrotation(leaf->right);
    leaf=Lrotation(leaf);
    return leaf;

}
AVL* searchNode(AVL* root,int data) {
    while (root!=NULL) {
        if (data < root->data)
            root = root->left;
        else if (data > root->data)
            root = root->right;
        else
            return root;
    }
    return NULL;
}

AVL* insertNode(AVL* leaf, int data) {

    //najskor si vyhladam, kde by sa mohla hodnota v strome nachadzat. a ked najdem miesto kde by mala byt,
    //tak tam vytvorim novy uzol a ulozim hodnotu
    if (leaf == NULL)
        return createNode(data);
    if (data > leaf->data)
        leaf->right = insertNode(leaf->right, data);
    else if (data < leaf->data)
        leaf->left = insertNode(leaf->left, data);
    else
        return leaf;

    //zmenim vysku uzlov podla vzorca " N(h) = N(h-1) + N(h-2) + 1 "
    updateHeight(leaf);

    int balance = balanceFactor(leaf);


    if (balance == -2) {
        if (balanceFactor(leaf->left) <= 0) {
            leaf= Rrotation(leaf);
            return leaf;
        }
        else {
            leaf = LRrotation(leaf);
            return leaf;
        }
    }
    if (balance == 2) {
        if (balanceFactor(leaf->right) >= 0) {
            leaf = Lrotation(leaf);
            return leaf;
        }
        else {
            leaf = RLrotation(leaf);
            return leaf;

        }

    }
    return leaf;
}
//prechadzam stromom podobne ako v inorder, ak je balancefactor niekde vacsi ako 1, returnem 0, inak 1;
int avlBalanced(AVL* root)
{
    if (root == NULL)
        return 0;
    if (abs(balanceFactor(root)) > 1)
        return 0;
    avlBalanced(root->left);
    avlBalanced(root->right);
    return 1;
}

void avlCorrect(){
    int countedLeafs=0;
    AVL* rootLR=NULL;
    AVL* rootRL=NULL;
    AVL* rootL=NULL;
    AVL* rootR=NULL;


    rootL= insertNode(rootL,3);
    rootL= insertNode(rootL,2);
    rootL= insertNode(rootL,1);

    rootR= insertNode(rootR,1);
    rootR=insertNode(rootR,2);
    rootR= insertNode(rootR,3);

    rootRL= insertNode(rootRL, 3);
    rootRL= insertNode(rootRL, 5);
    rootRL= insertNode(rootRL, 4);

    rootLR= insertNode(rootLR, 5);
    rootLR= insertNode(rootLR, 3);
    rootLR= insertNode(rootLR,4);


    if(countLeafs(rootL,&countedLeafs)==2){
        printf("AVL strom LEFT case: OK\n");
        countedLeafs=0;
        if(countLeafs(rootLR,&countedLeafs)==2){
            printf("AVL strom LEFT RIGHT case: OK\n");
            countedLeafs=0;
            if(countLeafs(rootR,&countedLeafs)==2){
                printf("AVL strom RIGHT case: OK\n");
                countedLeafs=0;
                if(countLeafs(rootRL,&countedLeafs)==2){
                    printf("AVL strom RIGHT LEFT case: OK\n");
                    countedLeafs=0;
                    printf("AVL strom je balancovany\n");
                    return;
                }
            }
        }
    }
}