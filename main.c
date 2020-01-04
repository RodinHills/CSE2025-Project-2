/* Talha Bayburtlu 150118066
 * This program tries to find and print every sequence that builds same BST as given sequence's BST.
 * It DOES NOT uses every combination for finding intended sequences, it uses recursive function
 * that compares original BST with strings which created based on comparative algorithm */

/* Output gets created at output.txt and it takes a while to create output because of recursive functions. */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BST { // BST Struct
    int data;
    struct BST* left;
    struct BST* right;
}BST , *BSTPtr;

/*----------------------------------------------- FUNCTION DECLARATIONS ----------------------------------------------------------- */
char *takeInput();
void printInOrder(BSTPtr BSTPtr,FILE *fp);
BSTPtr insert(BSTPtr BSTPtr , int data);
void findSequences(BSTPtr root , BSTPtr BSTPtr , int sequence[] , int arrSize ,int currentData,int *isOnSequence ,int currentIndex,FILE* fp,int shouldPrint);
/*----------------------------------------------- FUNCTION DECLARATIONS ----------------------------------------------------------- */

int main() {
    BSTPtr root = NULL;
    char *sequence = takeInput(); // Taking and storing input.
    int size = 1;

    char *data = strtok(sequence," ");
    root = insert(root,atoi(data)); // Inserting root to BST.

    while ((data = strtok(NULL, " ")) != NULL) { // Inserting all nodes to BST.
        insert(root,atoi(data));
        size++;
    }

    FILE *fp = fopen("output.txt" , "w"); // Creating output file.
    if (fp == NULL)
        exit(0);

    fprintf(fp, "Entered sequence printed in order: ");
    printInOrder(root,fp); // Printing BST in order.
    fprintf(fp,"\n");

    int isOnSequence = 0, newSequence[size];
    for (int i = 0; i < size ; i++) // Making every index -1.
        newSequence[i] = -1;

    fprintf(fp ,"All sequences that builds same BST topology: \n");
    findSequences(root,root,newSequence,size,-1,&isOnSequence,0,fp,0); // Finding sequences that can build same BST as given sequence.
    printf("Output created at output.txt");
}

char *takeInput() { // Takes input from user.
    printf("Enter a sequence:");
    char *input = calloc(1024, sizeof(char));
    fgets(input, 1024 , stdin);
    return input;
}

void printInOrder(BSTPtr BSTPtr,FILE *fp) { // Prints given BST in-order recursively.
    if (BSTPtr!= NULL){
        printInOrder(BSTPtr->left,fp);
        fprintf(fp , "%d ", BSTPtr->data);
        printInOrder(BSTPtr->right,fp);
    }
}

BSTPtr insert(BSTPtr BSTPtr , int data) { // Inserts data to BST recursively.
    if (BSTPtr == NULL) { // Inserts data as a leaf.
        BSTPtr = malloc(sizeof(BST));
        BSTPtr->data = data;
        BSTPtr->left = NULL; BSTPtr->right = NULL;
    } else if (data < BSTPtr->data) // Checking data is smaller than current node's data.
        BSTPtr->left = insert(BSTPtr->left,data);
    else if (data > BSTPtr->data) // Checking data is bigger than current node's data.
        BSTPtr->right = insert(BSTPtr->right,data);
    return BSTPtr;
}

void findSequences(BSTPtr root , BSTPtr BSTPtr , int sequence[] ,int arrSize , int currentData,int *isOnSequence ,int currentIndex,FILE* fp, int shouldPrint) { // Finds sequences that can build same BST as given sequence.
    if (BSTPtr == NULL) { // Base condition for multiple cases.
        // Checking original and current sequences length and current data for printing sequence only once.
        if (sequence[arrSize - 1] == currentData && shouldPrint){
            for (int i = 0; i < arrSize ; i++)
                fprintf(fp,"%d " , sequence[i]);
            fprintf(fp,"\n");
        }; return;
    }

    for (int i = 0; i < arrSize ; i++) { // Determining current data is on sequence or not.
        if (sequence[i] == BSTPtr->data) {
            *isOnSequence = 1; break;
        } else if (sequence[i] == -1)
            break;
    }

    if ((*isOnSequence)) { // Checking data is inside current sequence or not. If it is, search BST from current node's left and right child.
        *isOnSequence = 0;
        findSequences(root, BSTPtr->left,sequence,arrSize,BSTPtr->data,isOnSequence,currentIndex,fp,1);
        findSequences(root, BSTPtr->right,sequence,arrSize,BSTPtr->data,isOnSequence,currentIndex,fp,0);
    } else { // Current data inserted to current sequence then searching BST for finding all other combinations from the beginning.
        sequence[currentIndex] = BSTPtr->data;
        findSequences(root,root,sequence,arrSize,BSTPtr->data,isOnSequence,currentIndex + 1,fp,0);
        sequence[currentIndex] = -1;
    }
}