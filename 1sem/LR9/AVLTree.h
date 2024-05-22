#ifndef AVLTREE_H
#define AVLTREE_H

#include "Node.h"
#include <iostream>
#include <iomanip>
#include <stack>
#include <algorithm>

using namespace std;

class AVLTree {
public:
    Node* root;
    Node* current;

    AVLTree() : root(nullptr), current(nullptr) {}

    int getHeight(Node* node) {
        return node == nullptr ? 0 : node->height;
    }

    int getBalance(Node* node) {
        return node == nullptr ? 0 : getHeight(node->left) - getHeight(node->right);
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        if (T2 != nullptr) T2->parent = y;
        x->parent = y->parent;
        y->parent = x;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        if (T2 != nullptr) T2->parent = x;
        y->parent = x->parent;
        x->parent = y;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    Node* insert(Node* node, int key) {
        if (node == nullptr) {
            Node* newNode = new Node(key);
            if (root == nullptr) root = newNode;
            return newNode;
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
            node->left->parent = node;
        } else if (key > node->key) {
            node->right = insert(node->right, key);
            node->right->parent = node;
        } else {
            return node;
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        if (balance > 1 && key < node->left->key)
            return rightRotate(node);

        if (balance < -1 && key > node->right->key)
            return leftRotate(node);

        if (balance > 1 && key > node->left->key) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && key < node->right->key) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void insert(int key) {
        root = insert(root, key);
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left != nullptr)
            current = current->left;
        return current;
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            if ((root->left == nullptr) || (root->right == nullptr)) {
                Node* temp = root->left ? root->left : root->right;

                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else {
                    *root = *temp;
                    root->parent = temp->parent;
                }
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);

                root->key = temp->key;

                root->right = deleteNode(root->right, temp->key);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + max(getHeight(root->left), getHeight(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    void deleteNode(int key) {
        root = deleteNode(root, key);
    }

    Node* search(Node* node, int key) {
        if (node == nullptr || node->key == key)
            return node;

        if (node->key < key)
            return search(node->right, key);

        return search(node->left, key);
    }

    Node* search(int key) {
        return search(root, key);
    }

    void printTree(Node* node, int space = 0, int height = 10) {
        if (node == nullptr) return;

        space += height;

        printTree(node->right, space);

        std::cout << std::endl;
        for (int i = height; i < space; i++)
            std::cout << ' ';
        std::cout << node->key << "\n";

        printTree(node->left, space);
    }

    void printTree() {
        printTree(root);
    }

    void startTraversal() {
        current = root;
    }

    Node* getCurrentNode() {
        return current;
    }

    void moveLeft() {
        if (current && current->left)
            current = current->left;
        else
            std::cout << "No left child.\n";
    }

    void moveRight() {
        if (current && current->right)
            current = current->right;
        else
            std::cout << "No right child.\n";
    }

    void moveParent() {
        if (current && current->parent)
            current = current->parent;
        else
            std::cout << "No parent node.\n";
    }

    int getCurrentBalance() {
        return getBalance(current);
    }

    int getCurrentHeight() {
        return getHeight(current);
    }
};

#endif // AVLTREE_H