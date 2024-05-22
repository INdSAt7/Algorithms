#ifndef NODE_H
#define NODE_H

class Node {
public:
    int key;
    Node* left;
    Node* right;
    Node* parent;
    int height;
    Node(int k) : key(k), left(nullptr), right(nullptr), parent(nullptr), height(1) {}
};

#endif // NODE_H