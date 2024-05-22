#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <ctime>


using namespace std;

class Ant{
    int cur;
    int start;



    int pathLen = 0;

    vector<int> visited;

    void chooseVertex(int **graph, int size){
        bool fl;

        if (visited.empty()){//Проверка на начальную вершину
            visited.push_back(start);
        }

        map<int, int> neighbor;

        for (int i = 0; i<size; i++){
            if (graph[cur][i] != -1 && neighbor.count(i) == 0){//Все соседние вершины, не учитывая посещенные
                neighbor[i] = graph[cur][i];
            }
        }

        if (neighbor.empty()){
            fl = false;
            if (graph[cur][start] != -1){
                pathLen += graph[cur][start];
            }
            return;
        }
    }

    float randomChoice() {
        // Инициализация генератора случайных чисел
        srand(time(nullptr));

        // Генерация случайного числа от 0.0 до 1.0
        float random_number = rand() / RAND_MAX;

        return random_number;
    }

};



int main() {


    return 0;
}
