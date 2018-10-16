#include <iostream>
#include <limits>
#include <vector>
#include <omp.h>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::numeric_limits;

typedef vector<vector<double>> matrix;

struct Edge {
    int startingVertex;
    int destinationVertex;
    double weight;
};

struct Input {
    int numberOfVertices;
    int numberOfEdges;
    vector<Edge> edges;
};

Input getInput() {
    Input input = {};

    cin >> input.numberOfVertices;
    cin >> input.numberOfEdges;

    input.edges.resize(static_cast<unsigned long>(input.numberOfEdges));

    for (int i = 0; i < input.numberOfEdges; i++) {
        int startingVertex;
        int destinationVertex;
        double weight;

        cin >> startingVertex;
        cin >> destinationVertex;
        cin >> weight;

        input.edges[i] = {
                startingVertex,
                destinationVertex,
                weight
        };
    }

    return input;
}

matrix initializeMatrix(Input &input) {
    matrix matrix(static_cast<unsigned long>(input.numberOfVertices),
                  vector<double>(static_cast<unsigned long>(input.numberOfVertices), 0));

    for (int i = 0; i < input.numberOfVertices; i++) {
        for (int j = 0; j < input.numberOfVertices; j++) {
            if (i == j) {
                matrix[i][j] = 0;
            } else {
                matrix[i][j] = std::numeric_limits<double>::infinity();
            }
        }
    }

    for (auto &edge : input.edges) {
        matrix[edge.startingVertex][edge.destinationVertex] = edge.weight;
    }

    return matrix;
}

void printResults(Input &input, matrix &matrix) {
    Edge shortestEdge = {
            -1,
            -1,
            -1
    };

    for (int i = 0; i < input.numberOfEdges; i++) {
        int startingVertex = input.edges[i].startingVertex;
        int destinationVertex = input.edges[i].destinationVertex;
        double shortestPathWeight = matrix[startingVertex][destinationVertex];
        if (shortestEdge.weight == -1 || shortestPathWeight < shortestEdge.weight) {
            shortestEdge = input.edges[i];
        }
        printf("%lf\n", shortestPathWeight);
    }

    printf("%i %i %lf\n", shortestEdge.startingVertex, shortestEdge.destinationVertex, shortestEdge.weight);
}

void findAllPaths(matrix &matrix) {
    unsigned long size = matrix.size();

#pragma omp parallel for schedule(static) collapse(3)
    for (int k = 0; k < size; k++) {
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                double newValue = matrix[i][k] + matrix[k][j];
                if (newValue < matrix[i][j]) {
                    matrix[i][j] = newValue;
                }
            }
        }
    }
}

void run() {
    Input input = getInput();
    matrix matrix = initializeMatrix(input);
    findAllPaths(matrix);
    printResults(input, matrix);
}

int main() {
    run();
}
