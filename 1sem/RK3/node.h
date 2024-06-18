//
// Created by agoru on 11.06.2024.
//

#ifndef RK3_NODE_H
#define RK3_NODE_H

#include "iostream"
#include <vector>

using namespace std;

struct Node {
    string data;
    vector<Node *> neighbors;

    Node(string value) {
        data = value;
    }
};

Node *searchNodeOrGraph(Node *node, string nodeMarker) {
    if (node->data == nodeMarker) {
        return node;
    }

    for (int i = 0; i < node->neighbors.size(); i++) {
        Node *nextNode = searchNodeOrGraph(node->neighbors[i], nodeMarker);
        if (nextNode) {
            return nextNode;
        }
    }

    return nullptr;
}

bool nodeIsVisited(string nodeVal, vector<string> &visitedNodes) {
    for (int i = 0; i < visitedNodes.size(); i++) {
        if (visitedNodes[i] == nodeVal) {
            return true;
        }
    }

    return false;
}

#endif //RK3_NODE_H
