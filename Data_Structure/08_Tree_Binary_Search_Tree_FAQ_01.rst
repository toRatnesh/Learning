
.. contents:: Table of Contents

Tree FAQ 01
=================

Program to check if a binary tree is BST or not
--------------------------------------------------

A Binary search tree (BST) is a node based binary tree data structure which has the following properties.

-   The left subtree of a node contains only nodes with keys less than the node’s key.
-   The right subtree of a node contains only nodes with keys greater than the node’s key.
-   Both the left and right subtrees must also be binary search trees.

From the above properties it naturally follows that:

-   Each node (item in the tree) has a distinct key.


.. code:: cpp

    #include <stdio.h>
    #include <stdlib.h>
    #include <limits.h>

    struct tNode {
        int data;
        struct tNode * left;
        struct tNode * right;
    };

    int isBST(struct tNode * arg_root);
    int isBSTUtility(struct tNode * arg_node, int arg_min, int arg_max);
    struct tNode * newNode(int arg_val);

    int main(void) {
        struct tNode *root	= newNode(3);
        root -> left		= newNode(2);
        root -> right		= newNode(5);
        root -> left->left	= newNode(1);
        root -> left->right	= newNode(4); 
    
        if(isBST(root)) {
            printf("Tree is BST");
        }
        else {
            printf("Tree is not BST");
        }
        
        return 0;
    }

    struct tNode * newNode(int arg_val) {

        struct tNode * node = (struct tNode *)malloc(sizeof(struct tNode));
        node -> data = arg_val;
        node -> left = NULL;
        node -> right = NULL;
        
        return node;
    }

    int isBST(struct tNode * arg_root) {
        return isBSTUtility(arg_root, INT_MIN, INT_MAX);
    }


    int isBSTUtility(struct tNode * arg_node, int arg_min, int arg_max) {
        if(NULL == arg_node)
            return 1;
        
        if( ((arg_node -> data) < arg_min) || ((arg_node -> data) > arg_max) ) {
            return 0;
        }
        
        return (isBSTUtility(arg_node->left, arg_min, (arg_node->data) - 1) && isBSTUtility(arg_node->right, (arg_node->data) + 1, arg_max));
    }

Output::

    Tree is not BST




References
-------------

https://www.geeksforgeeks.org/binary-search-tree-data-structure/


