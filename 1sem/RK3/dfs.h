//
// Created by agoru on 11.06.2024.
//

#ifndef RK3_DFS_H
#define RK3_DFS_H

#include "node.h"
#include "stack.h"

using namespace std;

// Функция для добавления ребра между вершинами
void addEdge(Node *node1, Node *node2) {
    node1->neighbors.push_back(node2);
}

Node *createOrGraph() {
    // Создаем вершины графа
    Node *node1 = new Node("A");
    Node *node2 = new Node("B");
    Node *node3 = new Node("C");
    Node *node4 = new Node("D");
    Node *node5 = new Node("E");
    Node *node6 = new Node("F");
    Node *node7 = new Node("G");
    Node *node8 = new Node("H");
    Node *node9 = new Node("I");
    Node *node10 = new Node("J");
    Node *node11 = new Node("K");
    Node *node12 = new Node("L");

    // Добавляем ребра между вершинами
    addEdge(node1, node2);
    addEdge(node1, node3);
    addEdge(node3, node6);
    addEdge(node6, node11);
    addEdge(node11, node12);
    addEdge(node2, node4);
    addEdge(node2, node9);
    addEdge(node4, node5);
    addEdge(node4, node7);
    addEdge(node7, node8);
    addEdge(node9, node10);

    return node1;
}

// Функция DFS для обхода графа в глубину
void DFS(stack *st, vector<string> &visitedNodes) {
    while (!st->isEmpty()) {
        Node *curNode;

        if (!st->pop(curNode)) {
            cout << "Ошибка при попытке достать узел из стека" << endl;
            exit(1);
        };

        cout << curNode->data << " ";

        for (int i = curNode->neighbors.size() - 1; i >= 0; --i) {
            Node *nextNode = curNode->neighbors[i];
            if (nodeIsVisited(nextNode->data, visitedNodes)) {
                continue;
            }

            if (!st->push(nextNode)) {
                cout << "Ошибка при попытке поместить узел в стек" << endl;
                exit(1);
            }

            visitedNodes.push_back(nextNode->data);
        }
    }
}

#endif //RK3_DFS_H
