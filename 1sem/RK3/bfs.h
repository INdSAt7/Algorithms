//
// Created by agoru on 11.06.2024.
//

#ifndef RK3_BFS_H
#define RK3_BFS_H

#include <vector>
#include <map>
#include "queue.h"
#include <iostream>

using namespace std;

struct Graph {
    vector<vector<int>> matrix;
    map<int, string> indexToStrMap; // Преобразование индекса матрицы в строковое значение узла графа
};

Graph *createGraph() {
    // Матрица смежности
    vector<vector<int>> adjMatrix = {
          // A  B  C  D  Е  F  G  H  I  J  K  L
            {0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // А
            {1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0}, // B
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0}, // C
            {0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0}, // D
            {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0}, // Е
            {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // F
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0}, // G
            {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0}, // H
            {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0}, // I
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1}, // J
            {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0}, // K
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0}, // L
    };

    map<int, string> indexToStr = {
            {0,  "A"},
            {1,  "B"},
            {2,  "C"},
            {3,  "D"},
            {4,  "E"},
            {5,  "F"},
            {6,  "G"},
            {7,  "H"},
            {8,  "I"},
            {9,  "J"},
            {10, "K"},
            {11, "L"},
    };

    Graph * g = new Graph;

    g->matrix=adjMatrix;
    g->indexToStrMap=indexToStr;
    return g;
}

int searchNode(Graph *graph, string nodeMarker) {
    for (int i = 0; i < graph->matrix.size(); i++) {
        if (graph->indexToStrMap.find(i)->second == nodeMarker) {
            return i;
        }
    }

    return -1;
}

// Функция BFS для обхода графа в ширину
void BFS(queue *q, vector<string> &visitedNodes, Graph *graph) {
    while (!q->isEmpty()) {
        int curNode;

        if (!q->pop(curNode)) {
            cout << "Ошибка при попытке достать узел из очереди" << endl;
            exit(1);
        };

        string strMarker = graph->indexToStrMap.find(curNode)->second;

        cout << strMarker << " ";

        for (int i = 0; i < graph->matrix.size(); i++) {
            string nextStrMarker = graph->indexToStrMap.find(i)->second;
            if (nodeIsVisited(nextStrMarker, visitedNodes) || graph->matrix[curNode][i]==0) {
                continue;
            }

            if (!q->push(i)) {
                cout << "Ошибка при попытке поместить узел в стек" << endl;
                exit(1);
            }

            visitedNodes.push_back(graph->indexToStrMap.find(i)->second);
        }
    }
}


#endif //RK3_BFS_H
