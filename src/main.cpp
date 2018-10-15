#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::min;
using std::setw;
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

    cerr << "How many vertices?" << endl;
    cin >> input.numberOfVertices;

    cerr << "How many edges?" << endl;
    cin >> input.numberOfEdges;

    input.edges.resize(static_cast<unsigned long>(input.numberOfEdges));

    for (int i = 0; i < input.numberOfEdges; i++) {
        int startingVertex;
        int destinationVertex;
        double weight;

        cerr << "Starting vertex for edge " << i + 1 << endl;
        cin >> startingVertex;
        cerr << "Destination vertex for edge " << i + 1 << endl;
        cin >> destinationVertex;
        cerr << "Weight for edge " << i + 1 << endl;
        cin >> weight;

        input.edges[i] = {
                startingVertex,
                destinationVertex,
                weight
        };
    }

    return input;
}

matrix initializeMatrix(Input input) {
    matrix matrix(static_cast<unsigned long>(input.numberOfVertices), vector<double>(static_cast<unsigned long>(input.numberOfVertices), 0));

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

void printMatrix(matrix matrix) {
    for (auto &row : matrix) {
        for (auto &value : row) {
            cout << setw(4) << value;
        }
        cout << endl;
    }
}

void printResults(Input input, matrix matrix) {
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
        cout << shortestPathWeight << endl;
    }

    cout << shortestEdge.startingVertex << " " << shortestEdge.destinationVertex << " " << shortestEdge.weight << endl;
}

void findAllPaths(matrix matrix) {
    unsigned long size = matrix.size();
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

int main() {
    Input input = getInput();
    matrix matrix = initializeMatrix(input);

    cout << "Original matrix" << endl;
    printMatrix(matrix);
    cout << endl << endl;

    findAllPaths(matrix);

    cout << "Shortest path matrix" << endl;
    printMatrix(matrix);
    cout << endl << endl;

    printResults(input, matrix);
}
