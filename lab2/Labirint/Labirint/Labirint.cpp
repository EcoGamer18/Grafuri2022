//https://stackoverflow.com/questions/19751429/print-out-all-the-cell-coordinates-for-the-shortest-path

#include <iostream>
#include <fstream>
#include <string>
#include <stack>
#include <list>

using namespace std;

#define WIDTH 42
#define HEIGHT 22
#define INF 100000

struct coord {
    int i, j;
};

struct endsC {
    coord start;
    coord finish;
};

endsC parseText(int matrix_output[HEIGHT][WIDTH], const char* filename) {
    ifstream file(filename);
    string line;
    endsC graphEnds;
    int i = 0;

    while (getline(file, line)) {
        for (int j = 0; j < 41; j++) {
            matrix_output[i][j] = 0;
            switch (line[j]) {
            case 'S': {
                graphEnds.start.i = i;
                graphEnds.start.j = j;
                break;
            }
            case 'F': {
                graphEnds.finish.i = i;
                graphEnds.finish.j = j;
                break;
            }
            case '1': {
                matrix_output[i][j] = 1;
                break;
            }
            }
        }
        i++;
    }

    return graphEnds;
}

void display_matrix(int matrix[HEIGHT][WIDTH]) {
    for (int i = 0; i < HEIGHT - 1; i++) {
        for (int j = 0; j < WIDTH - 1; j++) {
            if (matrix[i][j] == INF) {
                std::cout << "INF" << " ";
            }
            else{
                std::cout << matrix[i][j] << " ";
            }
        }
        std::cout << std::endl;
    }
}

// check if coordinates are inside the maze
static bool isValid(int row, int col, int maxRow, int maxCol) {
    return row >= 0 && row < maxRow&& col >= 0 && col < maxCol;
}

static void shortestPath(int map[HEIGHT][WIDTH], int n, int m, endsC coordSF) {
    stack<coord> path = stack<coord>();

    // initialize distances array filled with infinity
    int distances[HEIGHT][WIDTH];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            distances[i][j] = INF;
        }
    }

    // the start node should get distance 0
    int distance = 0;
    list<coord> currentCells = list<coord>();
    currentCells.push_back(coordSF.start);

    while (distances[coordSF.finish.i][coordSF.finish.j] == INF && !currentCells.empty()) {
        list<coord> nextCells = list<coord>();

        // loop over all cells added in previous round
        // set their distance 
        //    and add their neighbors to the list for next round
        for (coord cell : currentCells) {
            if (distances[cell.i][cell.j] == INF && map[cell.i][cell.j] != 1) {
                distances[cell.i][cell.j] = distance;
                int ds[5][3] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
                for (int* d : ds) {
                    int row = cell.i + d[0];
                    int col = cell.j + d[1];
                    if (isValid(row, col, n, m)) {
                        coord aux = { row,col };
                        nextCells.push_back(aux);
                    }

                }
            }
        }

        // prepare for next round
        currentCells = nextCells;
        distance++;
    }

    // find the path
    if (distances[coordSF.finish.i][coordSF.finish.j] < INF) {
        coord cell = coordSF.finish;
        path.push(coordSF.finish);
        for (int dist = distances[coordSF.finish.i][coordSF.finish.j] - 1; dist >= 0; dist--) {
            int ds[5][3] = { {-1, 0}, {1, 0}, {0, -1}, {0, 1} };
            int change = 0;
            for (int* d : ds) {
                int row = cell.i + d[0];
                int col = cell.j + d[1];
                if (isValid(row, col, n, m) && distances[row][col] == dist) {
                    cell = { row,col };
                    change = 1;
                }
            }
            if (change == 1) {
                path.push(cell);
            }
        }
    }

    //display_matrix(distances);

    cout << "The shortest path is this long:\n";
    cout << distances[coordSF.finish.i][coordSF.finish.j];

    cout << "\nAnd has the following path:\n";

    int matrixSolution[HEIGHT][WIDTH];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            matrixSolution[i][j] = 0;
        }
    }

    while (!path.empty()) {
        coord aux = path.top();
        cout << "{ " << aux.i << ", " << aux.j << " } ";
        matrixSolution[aux.i][aux.j] = 1;
        path.pop();
        if (!path.empty()) {
            cout << " -> ";
        }

    }

    cout << "\nAnd the solution looks like this:\n";
    display_matrix(matrixSolution);
}

int main() {
    int matrix[HEIGHT][WIDTH];
    endsC graphEnds = parseText(matrix, "labirint_1.txt");

    cout << "Start coords: (" << graphEnds.start.i << ", " << graphEnds.start.j << ")" << std::endl;
    cout << "Finish coords: (" << graphEnds.finish.i << ", " << graphEnds.finish.j << ")" << std::endl;
    cout << std::endl;

    //display_matrix(matrix);

   
    shortestPath(matrix, HEIGHT-1, WIDTH-1, graphEnds);
    
    

    return 0;
}