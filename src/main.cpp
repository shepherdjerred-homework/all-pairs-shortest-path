#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <iomanip>

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::min;
using std::setw;
using namespace std;

struct Edge {
    int startingVertex;
    int destinationVertex;
    double weight;
};

int main() {
    int numberOfVertices;
    int numberOfEdges;

    cerr << "How many vertices?" << endl;
    cin >> numberOfVertices;

    cerr << "How many edges?" << endl;
    cin >> numberOfEdges;

    double matrix[numberOfVertices][numberOfVertices];
    memset(matrix, 0, sizeof(matrix));

    Edge edges[numberOfEdges];

    for (int i = 0; i < numberOfEdges; i++) {
        int startingVertex;
        int destinationVertex;
        double weight;

        cout << "Starting vertex for edge " << i + 1 << endl;
        cin >> startingVertex;
        cout << "Destination vertex for edge " << i + 1 << endl;
        cin >> destinationVertex;
        cout << "Weight for edge " << i + 1 << endl;
        cin >> weight;

        matrix[startingVertex][destinationVertex] = weight;
        edges[i] = {
                startingVertex,
                destinationVertex,
                weight
        };
    }

    cout << endl << endl;

    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++) {
            cout << setw(2) << matrix[i][j];
        }
        cout << endl;
    }

    //
    for (int k = 0; k < numberOfVertices - 1; k++) {
        for (int i = 0; i < numberOfVertices - 1; i++) {
            for (int j = 0; j < numberOfVertices - 1; j++) {
                matrix[i][j] = min(matrix[i][j], matrix[i][k] + matrix[k][j]);
            }
        }
    }

    cout << endl << endl;

    for (int i = 0; i < numberOfVertices; i++) {
        for (int j = 0; j < numberOfVertices; j++) {
            cout << setw(2) << matrix[i][j];
        }
        cout << endl;
    }

    Edge shortestEdge = {
            -1,
            -1,
            -1
    };
    for (int i = 0; i < numberOfEdges; i++) {
        int startingVertex = edges[i].startingVertex;
        int destinationVertex = edges[i].destinationVertex;
        double shortestPathWeight = matrix[startingVertex][destinationVertex];
        cout << "Shortest path from " << startingVertex << " to " << destinationVertex << " costs " << shortestPathWeight
             << endl;
        if (shortestEdge.weight == -1 || shortestPathWeight < shortestEdge.weight) {
            shortestEdge = edges[i];
        }
    }

    cout << "The shortest path overall is " << shortestEdge.startingVertex << " to " << shortestEdge.destinationVertex
         << " costing " << shortestEdge.weight << endl;

}
