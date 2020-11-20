#include "Structures/open_addressing.h"
#include <stdio.h>
#include <windows.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

#define TEST_SIZE 10000000


#include "Structures/AVL.c"
#include "Structures/HashTable.c"
#include "Structures/RBTree_implementation.c"
#include "Structures/open_addressing_prime.c"
#define START_TEST QueryPerformanceFrequency(&frequency); QueryPerformanceCounter(&start);
#define END_TEST QueryPerformanceCounter(&end); interval = (double)(end.QuadPart - start.QuadPart)/ frequency.QuadPart;

// Utility function to swap two elements A[i] and A[j] in the array
void swap(int A[], int i, int j) {
    int temp = A[i];
    A[i] = A[j];
    A[j] = temp;
}

// Function to shuffle an array A[] of n elements
void shuffle(int A[], int n)
{
    // read array from highest index to lowest
    for (int i = n - 1; i >= 1; i--)
    {
        // generate a random number j such that 0 <= j <= i
        int j = rand() % (i + 1);

        // swap current element with randomly generated index
        swap(A, i, j);
    }
}
void test_inARow_hashtable(){

    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;

    //Vkladanie za sebou iducich cisel start

    //Moja vlastna hashTable
    h_table* table = create_hashTable(primeNumbers[0]);
    START_TEST
    for(int i = 0; i< TEST_SIZE;i++){
        insert(table,i);
    }
    END_TEST
    printf("(HT) Cas INSERT za sebou iducich %d cisel : %lf\n", TEST_SIZE, interval);

    //prevzata hashTable open adressing
    float load_limit = 0.75f;
    struct hash_table *table_prevzata = empty_table(2, load_limit);
    START_TEST
    for(int i = 0; i < TEST_SIZE; i++){
        insert_key(table_prevzata,i);}
    END_TEST
    printf("(HT_p) Cas INSERT za sebou iducich %d cisel : %lf\n",TEST_SIZE,interval);




    putchar('\n');


    ENTRY* searched_entry;
    START_TEST
    for(int i = 0; i<TEST_SIZE;i++){
        searched_entry=search(table,i);
    }
    END_TEST
    printf("(HT) Cas SEARCH za sebou iducich %d cisel : %lf\n",TEST_SIZE,interval);



    START_TEST
    for(int i = 0; i < TEST_SIZE; i++){
        contains_key(table_prevzata,i);
    }
    END_TEST
    printf("(HT_p) Cas SEARCH za sebou iducich %d cisel : %lf\n", TEST_SIZE,interval);



}

void test_inARow_trees(){

    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;

    //Vkladanie za sebou iducich cisel start

    //Moj vlastny strom - typ AVL
    int treeLeafs = 0;
    AVL* Root = NULL;
    START_TEST
    for (int i = 0; i <TEST_SIZE; i++) {
        Root = insertNode(Root, i);
    }
    END_TEST
    printf("(AVL) Cas INSERT za sebou iducich %d cisel: %lf\n", TEST_SIZE, interval);



    //prevzaty redblack tree
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;
    ROOT = NILL;

    START_TEST
    for(int i = 0; i< TEST_SIZE;i++){
        red_black_insert(i);
    }
    END_TEST
    printf("(RB_p) Cas INSERT za sebou iducich %d cisel : %lf\n",TEST_SIZE,interval);


    putchar('\n');


    AVL* searched;
    START_TEST
    for(int i = 0; i< TEST_SIZE; i++){
        searched = searchNode(Root, i);
    }
    END_TEST
    printf("(AVL) Cas SEARCH za sebou iducich %d cisel : %lf\n", TEST_SIZE, interval);



    struct node *searchedRB;
    START_TEST
    for(int i= 0; i<TEST_SIZE;i++){
        searchedRB = tree_search(i);
    }
    END_TEST
    printf("(RB_p) Cas SEARCH za sebou iducich %d cisel : %lf\n",TEST_SIZE,interval);

}
void test_random_trees(){
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;

    //generovanie nahodnych cisel

    srand(time(NULL));
    int * keys = (int*)malloc(TEST_SIZE*sizeof(int));
    for(int i = 0; i<TEST_SIZE;i++)
        keys[i]=i;
    shuffle(keys,TEST_SIZE);

    //prevzaty redblack tree
    NILL = malloc(sizeof(struct node));
    NILL->color = BLACK;
    ROOT = NILL;

    START_TEST
    for(int i = 0; i< TEST_SIZE;i++){
        red_black_insert(keys[i]);
    }
    END_TEST
    printf("(RB_p) Cas INSERT random %d cisel : %lf\n",TEST_SIZE,interval);

    AVL* Root = NULL;
    START_TEST
    for (int i = 0; i <TEST_SIZE; i++) {
        Root = insertNode(Root, keys[i]);
    }
    END_TEST
    printf("(AVL) Cas INSERT random %d cisel : %lf\n", TEST_SIZE, interval);




    putchar('\n');


    AVL* searched;
    START_TEST
    for(int i; i<TEST_SIZE;i++){
        searched=searchNode(Root,keys[i]);
    }
    END_TEST
    printf("(AVL) Cas SEARCH random %d cisel : %lf\n",TEST_SIZE,interval);


    struct node *searchedRB;
    START_TEST
    for(int i= 0; i<TEST_SIZE;i++){
        searchedRB = tree_search(keys[i]);
    }
    END_TEST
    printf("(RB_p) Cas SEARCH random %d cisel : %lf\n",TEST_SIZE,interval);

}
void test_random_hashtables(){
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;
    double interval;

    unsigned int * keys = (unsigned int*)malloc(TEST_SIZE*sizeof(unsigned int));

    for(int i = 0; i<TEST_SIZE;i++)
        keys[i]=i;

    shuffle(keys,TEST_SIZE);

    h_table* table = create_hashTable(primeNumbers[0]);
    START_TEST
    for(int i = 0; i< TEST_SIZE;i++){
        insert(table,keys[i]);
    }
    END_TEST
    printf("(HT) Cas INSERT random %d cisel : %lf\n", TEST_SIZE, interval);


    //prevzata hashTable open adressing
    float load_limit = 0.75;
    struct hash_table *table_prevzata = empty_table(2, load_limit);
    START_TEST
    for(int i = 0; i < TEST_SIZE; i++){
        insert_key(table_prevzata,keys[i]);}
    END_TEST
    printf("(HT_p) Cas INSERT random %d cisel : %lf\n",TEST_SIZE,interval);

    putchar('\n');


    ENTRY* searched_entry;
    START_TEST
    for(int i = 0; i<TEST_SIZE;i++){
        searched_entry=search(table,keys[i]);
    }
    END_TEST
    printf("(HT) Cas SEARCH random %d cisel : %lf\n",TEST_SIZE,interval);


    bool isThere;
    START_TEST
    for(int i = 0; i < TEST_SIZE; i++){
        isThere= contains_key(table_prevzata,keys[i]);
    }
    END_TEST
    printf("(HT_p) Cas SEARCH random %d cisel : %lf\n", TEST_SIZE,interval);

}
static unsigned int random_key()
{
    unsigned int key = (unsigned int)rand();
    return key;
}
int main() {

    putchar('\n');
    int spustac = 1;
    char option;
    printf("A: zistit funkcnost mojho AVL \nB: (usporiadana postupnost cisel) porovnanie insert & search v stromoch \nC: (usporiadana postupnost cisel) porovnanie insert & search v hash tabulkach\n");
    printf("D: (random) porovnanie insert & search v stromoch \nE: (random) porovnanie insert & search v hash tabulkach\n");
    printf("Moznost: ");
    scanf("%c", &option);
    switch(option) {
        case 'A':{
            avlCorrect();
            break;
        }
        case 'B':{
            test_inARow_trees();
            break;
        }
        case 'C':{
            test_inARow_hashtable();
            break;
        }
        case 'D': {
            test_random_trees();
            break;
        }
        case 'E': {
            test_random_hashtables();
            break;
        }
        default:
            printf("ERROR INPUT");
            break;
    }
}
