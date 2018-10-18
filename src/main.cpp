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

struct Route {
    int numberOfVertices;
    double shortestPathLength;
    vector<int> vertices;
};

struct Edge {
    int startingVertex;
    int destinationVertex;
    double weight;
};

struct Input {
    int numberOfVertices;
    int numberOfEdges;
    int numberOfRoutes;
    vector<Edge> edges;
    vector<Route> routes;
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

    cin >> input.numberOfRoutes;

    input.routes.resize(static_cast<unsigned long>(input.numberOfRoutes));

    for (int i = 0; i < input.numberOfRoutes; i++) {
        int length;
        cin >> length;

        input.routes[i].numberOfVertices = length;
        input.routes[i].vertices.resize(static_cast<unsigned long>(length));

        for (int j = 0; j < length; j++) {
            int vertex;
            cin >> vertex;
            input.routes[i].vertices[j] = vertex;
        }
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

double calculateShortestRoutes(Input &input, matrix &matrix) {
    double shortestRouteLength = -1;

    for (int i = 0; i < input.numberOfRoutes; i++) {
        double routeLength = 0;

        for (int j = 0; j < input.routes[i].numberOfVertices - 1; j++) {
            routeLength += matrix[input.routes[i].vertices[j]][input.routes[i].vertices[j + 1]];
        }

        input.routes[i].shortestPathLength = routeLength;
        if (shortestRouteLength == -1 || routeLength < shortestRouteLength) {
            shortestRouteLength = routeLength;
        }
    }

    return shortestRouteLength;
}

void printRoutes(Input &input, matrix &matrix, double shortestPathLength) {
    for (int i = 0; i < input.numberOfRoutes; i++) {
        printf("%lf\n", input.routes[i].shortestPathLength);
    }

    printf("%lf\n", shortestPathLength);
}

void findAllPaths(matrix &matrix) {
    unsigned long size = matrix.size();

#pragma omp parallel
    for (int k = 0; k < size; k++) {
#pragma omp for
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
//                printf("write: m[%i][%i]; read: m[%i][%i] m[%i][%i]\n", i, j, i, k, k, j);
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
    double shortestPath = calculateShortestRoutes(input, matrix);
    printRoutes(input, matrix, shortestPath);
}

int main() {
    run();
}
