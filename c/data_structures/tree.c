#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Tree
{
   int data;
   struct Tree* left;
   struct Tree* right;
};

typedef struct Tree Tree_t;

Tree_t* createNode(int data) 
{
   printf("createNode(%d)\n", data);
   Tree_t* tree = malloc(sizeof (struct Tree)); 
   if ( tree ) {
      tree->data = data;
      tree->left = 0;
      tree->right = 0;
   }
   return tree;
}

void deleteTree(Tree_t* tree)
{
   if ( tree && tree->left ) {
      printf("node: %d, delete(left)\n", tree->data);
      deleteTree(tree->left);
      tree->left = 0;

   }

   if ( tree && tree->right ) {
      printf("node: %d, delete(right)\n", tree->data);
      deleteTree(tree->right);
      tree->right = 0; 
   }

   if ( tree && !tree->left && !tree->right ) {
      printf("node: %d, delete()\n", tree->data);
      free(tree);
      tree = 0;
   }
}

int printTree(Tree_t* tree)
{
   int rc =0;

   if ( tree && tree->left) printTree(tree->left);
   if ( tree ) printf("%d \n", tree->data);
   if ( tree && tree->right) printTree(tree->right);
   return rc;
}

void insertNode(Tree_t* tree, int data)
{
   if ( tree ) 
      printf("node: %d, ", tree->data);

   if ( tree && data < tree->data && tree->left ) {
      printf("left - insertNode(%d).\n", data);
      insertNode(tree->left, data);
   }

   if ( tree && tree->data < data && tree->right ) {
      printf("right - insertNode(%d).\n", data);
      insertNode(tree->right, data);
   }

   if ( tree && data < tree->data && !tree->left ) {
      printf("left - ");
      tree->left = createNode(data);
   }

   if ( tree && tree->data < data && !tree->right ) {
      printf("right - ");
      tree->right = createNode(data);
   }
}

int main(int argc, char**argv) 
{
   Tree_t* tree = 0;
   tree = createNode(3);

   tree->left = createNode(2);
   tree->right = createNode(5);

   tree->right->right = createNode(7);
   tree->right->right->left = createNode(6);
   tree->right->left = createNode(4);
   tree->left->left = createNode(1);

   printTree(tree);

   deleteTree(tree);

   tree = createNode(6);
   insertNode(tree, 5);
   insertNode(tree, 7);
   insertNode(tree, 2);
   insertNode(tree, 4);
   insertNode(tree, 9);
   insertNode(tree, 8);
   insertNode(tree, 3);
   insertNode(tree, 1);

   printTree(tree);

   deleteTree(tree);

   return 0;
}
