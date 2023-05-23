#pragma once
#include <iostream>
using namespace std;

struct AVLNode {
    int key;
    char type;
    int count;
    int score;
    AVLNode* left;
    AVLNode* right;
    int height;
    AVLNode(int vale = 0, char t = '\n') :key(vale), type(t) {
        left = nullptr;
        right = nullptr;
        height = 0;
        count = 1;
        score = 10;
    }
};

class AVLTree
{
public:
    AVLNode* root;

    int height(AVLNode* node) {
        switch (node != nullptr) {
        case true:
            return node->height;
        default:
            return 0;
        }
    }

    int balanceFactor(AVLNode* node) {
        return (node == nullptr) ? 0 : AVLTree::height(node->left) - AVLTree::height(node->right);
    }

    AVLNode* rightRotate(AVLNode* a) {
        AVLNode* x = a->left;
        AVLNode* b = x->right;
        x->right = a;
        a->left = b;
        a->height = max(height(a->left), height(a->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;
        return x;
    }

    AVLNode* leftRotate(AVLNode* a) {
        AVLNode* y = a->right;
        AVLNode* b = y->left;
        y->left = a;
        a->right = b;
        a->height = max(height(a->left), height(a->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    AVLNode* insert(AVLNode* node, int key, char c) {
        if (node == nullptr) {
            AVLNode* newNode = new AVLNode;
            newNode->key = key;
            newNode->left = nullptr;
            newNode->right = nullptr;
            newNode->height = 1;
            newNode->type = c;
            return newNode;
        }
        if (key < node->key) {
            node->left = insert(node->left, key, c);
        }
        else if (key > node->key) {
            node->right = insert(node->right, key, c);
        }
        else {
            return node;
        }
        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = balanceFactor(node);
        if (balance > 1 && key < node->left->key) {
            return rightRotate(node);
        }
        if (balance < -1 && key > node->right->key) {
            return leftRotate(node);
        }
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

    AVLNode* minValueNode(AVLNode* node) {
        AVLNode* curr = node;
        do {
            if (curr->left == nullptr) {
                break;
            }
            curr = curr->left;
        } while (true);
        return curr;
    }

    AVLNode* deleteNode(AVLNode* node, int id) {

        if (node == nullptr) {
            return node;
        }
        if (id < node->key) {
            node->left = deleteNode(node->left, id);
        }
        else if (id > node->key) {
            node->right = deleteNode(node->right, id);
        }
        else {

            if ((node->left == nullptr) || (node->right == nullptr)) {
                AVLNode* temp = node->left ? node->left : node->right;
                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                }
                else {
                    *node = *temp;
                    delete temp;
                }
            }
            else {
                AVLNode* temp = minValueNode(node->right);
                node->key = temp->key;
                node->right = deleteNode(node->right, temp->key);
            }
        }

        if (node == nullptr) {
            return node;
        }
        node->height = max(height(node->left), height(node->right)) + 1;
        int balance = balanceFactor(node);
        if (balance > 1 && balanceFactor(node->left) >= 0) {
            return rightRotate(node);
        }
        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && balanceFactor(node->right) <= 0) {
            return leftRotate(node);
        }
        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorderTraversal(AVLNode* Node) {
        if (Node != nullptr) {
            inorderTraversal(Node->left);
            cout << Node->key;
            inorderTraversal(Node->right);
        }
        else
        {
            return;
        }
    }

    void PreOrderTraversal(AVLNode* Node) {
        if (Node != nullptr) {
            cout << Node->key;
            PreOrderTraversal(Node->left);
            PreOrderTraversal(Node->right);
        }
        else
        {
            return;
        }
    }

    AVLNode* search(AVLNode* root, int data) {
        return (root == nullptr) ? nullptr
            : (root->key == data) ? root
            : (root->left != nullptr) ? search(root->left, data)
            : (root->right != nullptr) ? search(root->right, data)
            : nullptr;
    }

    void PostOrderTraversal(AVLNode* Node) {
        if (Node != nullptr) {
            PostOrderTraversal(Node->left);
            PostOrderTraversal(Node->right);
            cout << Node->key;
        }
        else
        {
            return;
        }  
    }

    int countIds(AVLNode* root) {
        if (root == nullptr) {
            return 0;
        }
        int count = 0;
        if (root->type != '#') {
            count = count + root->score;
        }
        count += countIds(root->left);
        count += countIds(root->right);
        return count;
    }

};
