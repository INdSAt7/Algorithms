#include <iostream>
#include "stack.h"
#include "dfs.h"
#include "bfs.h"
#include <vector>

using namespace std;

int main() {
    // Обход в глубину ор графа
    Node *orGraphHead = createOrGraph();

    string curNodeMarker;
    cout << "Enter start-node: ";
    cin >> curNodeMarker;

    Node *curNode = searchNodeOrGraph(orGraphHead, curNodeMarker);
    if (!curNode) {
        cout << "Node not found";
        return 0;
    }

    stack *st = new stack(12);
    if (!st->push(curNode)) {
        cout << "Error due pushing node in stack" << endl;
        return 1;
    };

    vector<string> visitedNodes;
    visitedNodes.push_back(curNode->data);

    cout << "Depth traversal: ";
    DFS(st, visitedNodes);

    st->free();
    visitedNodes.clear();

    // Обход в ширину неорграфа
    Graph *graph = createGraph();

    cout << endl << "Enter start-node: ";
    cin >> curNodeMarker;

    int curIntNode = searchNode(graph, curNodeMarker);
    if (curIntNode==-1) {
        cout << "Node not found";
        return 0;
    }

    queue *q = new queue(12);
    if (!q->push(curIntNode)) {
        cout << "Error due pushing node in stack" << endl;
        return 1;
    };

    visitedNodes.push_back( graph->indexToStrMap.find(curIntNode)->second);

    cout << "Width traversal: ";
    BFS(q, visitedNodes, graph);

    q->free();
    visitedNodes.clear();

    return 0;
}
