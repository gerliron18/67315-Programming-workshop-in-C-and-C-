/**
 * @file RBTree.c
 * @author  Liron Gershuny <liron.gershuny@mail.huji.ac.il>
 * @version 1.0
 * @date 12 Dec 2019
 *
 * @brief Manage a generic Red-Black tree, his initiation, insertion and rotation according to
 *        nodes data. Also will free all allocated memory if needed.
 *
 * @section LICENSE
 * This program is not a free software; bla bla bla...
 *
 * @section DESCRIPTION
 * The program will initiate RBTree, insert new nodes when needed, manage the rotation fix according
 * to the given data and free allocated memory.
 * Input  : When new RBTree needed to be initiate, the given data should be a compare function
 *          between two nodes data and a free function to the nodes data.
 * Process: Manage insertion, rotations and free allocations
 * Output : Can generate pointer to a valid RBTree
 */

// ------------------------------ includes ------------------------------
#include <stdlib.h>
#include "RBTree.h"

// -------------------------- const definitions -------------------------

// ------------------------------ functions -----------------------------

/**
 * constructs a new RBTree with the given CompareFunc.
 * comp: a function two compare two variables.
 */
RBTree *newRBTree(CompareFunc compFunc, FreeFunc freeFunc)
{
    RBTree *newRBTree = (RBTree *) malloc(sizeof(RBTree));
    if (newRBTree == NULL || compFunc == NULL || freeFunc == NULL)
    {
        return NULL;
    }

    newRBTree->compFunc = compFunc;
    newRBTree->freeFunc = freeFunc;
    newRBTree->root = NULL;
    newRBTree->size = 0;

    return newRBTree;
}

/**
 * Recursive function that checks if given data is already in given tree/sub-tree using
 * compare function that also given to it.
 * @param node The root of a tree/sub-tree
 * @param data The given data to check if is in the tree
 * @param compFunc The compare function according to the data type
 * @return 0 if data not included in the tree, 1 otherwise
 */
int doesNodeExists(Node *node, void *data, CompareFunc compFunc)
{
    if (node == NULL || node->data == NULL)
    {
        return 0;
    }

    if (!compFunc(node->data, data))
    {
        return 1;
    }

    if (node->left)
    {
        if (doesNodeExists(node->left, data, compFunc))
        {
            return 1;
        }
    }

    if (node->right)
    {
        if (doesNodeExists(node->right, data, compFunc))
        {
            return 1;
        }
    }

    return 0;
}

/**
 * check whether the tree contains this item.
 * @param tree: the tree to add an item to.
 * @param data: item to check.
 * @return: 0 if the item is not in the tree, other if it is.
 */
int containsRBTree(RBTree *tree, void *data)
{
    if (tree == NULL || data == NULL)
    {
        return 0;
    }

    Node *root = tree->root;
    if (doesNodeExists(root, data, tree->compFunc))
    {
        return 1;
    }

    return 0;
}

/**
 * Left rotation fix to the RBTree, will change the formations and colors.
 * @param tree The given tree/sub-tree to fix
 * @param newNode The node that was inserted to the tree
 */
void leftRotate(RBTree *tree, Node *pivot)
{
    if (!pivot || !pivot->right)
    {
        return;
    }

    Node *pivotParent = pivot->parent;
    int sonOrientation = 0;

    if (pivotParent != NULL)
    {
        // left or right son of parent
        sonOrientation = tree->compFunc(pivot->data, pivotParent->data);
    }

    Node *rightSon = pivot->right;
    Node *t2 = rightSon->left;
    rightSon->left = pivot;
    pivot->right = t2;

    if (t2 != NULL)
    {
        t2->parent = pivot;
    }

    rightSon->parent = pivotParent;
    pivot->parent = rightSon;

    if (pivotParent != NULL)
    {
        if (sonOrientation < 0)
        {
            pivotParent->left = rightSon;
        }
        else
        {
            pivotParent->right = rightSon;
        }
    }
    else
    {
        tree->root = rightSon;
    }
}

/**
 * Right rotation fix to the RBTree, will change the formations and colors.
 * @param tree The given tree/sub-tree to fix
 * @param pivot The node that was inserted to the tree
 */
void rightRotate(RBTree *tree, Node *pivot)
{
    if (!pivot || !pivot->left)
    {
        return;
    }

    Node *pivotParent = pivot->parent;
    int sonOrientation = 0;

    if (pivotParent != NULL)
    {
        // left or right son of parent
        sonOrientation = tree->compFunc(pivot->data, pivotParent->data);
    }

    Node *leftSon = pivot->left;
    Node *t3 = leftSon->right;
    leftSon->right = pivot;
    pivot->left = t3;

    if (t3 != NULL)
    {
        t3->parent = pivot;
    }

    leftSon->parent = pivotParent;
    pivot->parent = leftSon;
    if (pivotParent != NULL)
    {
        if (sonOrientation < 0)
        {
            pivotParent->left = leftSon;
        }
        else
        {
            pivotParent->right = leftSon;
        }
    }
    else
    {
        tree->root = leftSon;
    }
}

/**
 * A function that manage the fix of a RBTree after adding a new node to it.
 * @param tree The given tree/sub-tree to fix
 * @param newNode The node that was inserted to the tree
 */
void fixTree(RBTree *tree, Node *newNode)
{
    while (newNode != tree->root && newNode->parent->color == RED)
    {
        Node *uncle = NULL;

        //Find uncle
        if (newNode->parent && newNode->parent->parent &&
            newNode->parent == newNode->parent->parent->left)
        {
            uncle = newNode->parent->parent->right;
        }
        else
        {
            uncle = newNode->parent->parent->left;
        }

        //If uncle is RED
        if (uncle != NULL && uncle->color == RED)
        {
            uncle->color = BLACK;
            newNode->parent->color = BLACK;
            newNode->parent->parent->color = RED;
            newNode = newNode->parent->parent;
        }

        //If uncle is BLACK
        else
        {
            Node *parent = newNode->parent;
            Node *gradParent = parent->parent;

            //Left-left case
            if (parent == gradParent->left && newNode == parent->left)
            {
                rightRotate(tree, gradParent);
                Color tempColor = parent->color;
                parent->color = gradParent->color;
                gradParent->color = tempColor;
            }

            //Left-right case
            else if (parent == gradParent->left && newNode == parent->right)
            {
                leftRotate(tree, parent);
                rightRotate(tree, gradParent);
                Color tempColor = newNode->color;
                newNode->color = gradParent->color;
                gradParent->color = tempColor;
            }

            //Right-right case
            else if (parent == gradParent->right && newNode == parent->right)
            {
                leftRotate(tree, gradParent);
                Color tempColor = parent->color;
                parent->color = gradParent->color;
                gradParent->color = tempColor;
            }

            //Right-left case
            else if (parent == gradParent->right && newNode == parent->left)
            {
                rightRotate(tree, parent);
                leftRotate(tree, gradParent);
                Color tempColor = newNode->color;
                newNode->color = gradParent->color;
                gradParent->color = tempColor;
            }
            break;
        }
    }

    tree->root->color = BLACK; //Make sure root is BLACK
}

/**
 * Find the place to insert new node to a RBTree according to its data comparing to other nodes.
 * @param node The node to find a place to
 * @param parent A pointer to the new node parent that should be found in this function
 * @param data The new node data
 * @param compareFunc The compare function between two nodes data of the tree
 * @return A pointer to the new node parent
 */
Node *findPlace(Node *node, Node *parent, void *data, CompareFunc compareFunc)
{
    if (node == NULL)
    {
        return parent;
    }

    // assume data not in the tree
    if (compareFunc(node->data, data) < 0)
    {
        return findPlace(node->right, node, data, compareFunc);
    }
    return findPlace(node->left, node, data, compareFunc);

}

/**
 * add an item to the tree
 * @param tree: the tree to add an item to.
 * @param data: item to add to the tree.
 * @return: 0 on failure, other on success. (if the item is already in the tree - failure).
 */
int addToRBTree(RBTree *tree, void *data)
{
    if (tree == NULL || data == NULL)
    {
        return 0;
    }

    if (containsRBTree(tree, data)) //If the data is already in the tree
    {
        return 0;
    }

    Node *newNode = (Node *) malloc(sizeof(Node));
    if (newNode == NULL)
    {
        return 0;
    }

    newNode->color = RED;
    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;

    if (tree->root == NULL) //If the tree is empty, insert as root
    {
        newNode->color = BLACK;
        newNode->parent = NULL;
        tree->root = newNode;
        tree->size++;
        return 1;
    }
    else //If the tree is *not* empty, iterate over the nodes
    {
        Node *parent = findPlace(tree->root, NULL, data, tree->compFunc);
        newNode->parent = parent;

        if (tree->compFunc(newNode->data, parent->data) > 0)
        {
            parent->right = newNode;
        }
        else
        {
            parent->left = newNode;
        }
    }

    fixTree(tree, newNode);
    tree->size++;
    return 1;
}

/**
 * A help recursive function to the forEachFunc that will iterate over the tree/sub-tree
 * nodes in-order traversal and will generate the function for each node.
 * @param node The given root of a RBTree or sub-tree
 * @param func The forEach function
 * @param args Other data that the forEach function can get as argument
 * @return 1 if the operation of the forEach function gone well, 0 otherwise
 */
int inOrderTraversal(Node *node, forEachFunc func, void *args)
{
    if (node && node->left)
    {
        inOrderTraversal(node->left, func, args);
    }

    if (node && !func(node->data, args))
    {
        return 0;
    }

    if (node && node->right)
    {
        inOrderTraversal(node->right, func, args);
    }

    return 1;
}

/**
 * Activate a function on each item of the tree. the order is an ascending order.
 * if one of the activations of the function returns 0, the process stops.
 * @param tree: the tree with all the items.
 * @param func: the function to activate on all items.
 * @param args: more optional arguments to the function
 *              (may be null if the given function support it).
 * @return: 0 on failure, other on success.
 */
int forEachRBTree(RBTree *tree, forEachFunc func, void *args)
{
    if (tree == NULL)
    {
        return 0;
    }

    return inOrderTraversal(tree->root, func, args);
}

/**
 * A help function to the freeRBTree function that iterate over the sub-trees and free
 * all needed allocations.
 * @param node The given root of a RBTree or sub-root
 */
void deallocate(Node *node, FreeFunc freeFunc)
{
    if (node == NULL)
    {
        return;
    }

    deallocate(node->left, freeFunc);
    deallocate(node->right, freeFunc);
    freeFunc(node->data);
    free(node);
}

/**
 * free all memory of the data structure. does not free memory of the items themselves.
 * @param tree: the tree to free.
 */
void freeRBTree(RBTree *tree)
{
    if (tree == NULL)
    {
        return;
    }

    deallocate(tree->root, tree->freeFunc);
    free(tree);
}