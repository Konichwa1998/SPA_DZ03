#include <iostream>
#include <queue>

using namespace std;
#define ROW 20
#define COLLUM 40

int dRow[] = { -1, 0, 1, 0 };
int dCol[] = { 0, 1, 0, -1 };

void display2DMatrix(char M[][COLLUM])
{
    for (unsigned i = 0; i < ROW; i++)
    {
        for (unsigned j = 0; j < COLLUM; j++)
        {
            cout << M[i][j];
        }
        cout << endl;
    }
}

class QItem {
public:
    int row;
    int col;
    int dist;
    QItem(int x, int y, int w)
        : row(x), col(y), dist(w)
    {
    }
};

int minDistance(char M[ROW][COLLUM], int rowA, int collumA, int rowB, int collumB)
{
    QItem source(0, 0, 0);

    bool visited[ROW][COLLUM];
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLLUM; j++)
        {
            if (M[i][j] == '0')
                visited[i][j] = true;
            else
                visited[i][j] = false;

            // Finding source
            if (M[i][j] == 'A')
            {
                source.row = i;
                source.col = j;
            }
        }
    }

    queue<QItem> q;
    q.push(source);
    visited[source.row][source.col] = true;
    while (!q.empty()) {
        QItem p = q.front();
        q.pop();

        if (M[p.row][p.col] == 'B')
            return p.dist;

        if (p.row - 1 >= 0 &&
            visited[p.row - 1][p.col] == false) {
            q.push(QItem(p.row - 1, p.col, p.dist + 1));
            visited[p.row - 1][p.col] = true;
            M[p.row - 1][p.col - 1] = '*';
        }

        if (p.row + 1 < ROW &&
            visited[p.row + 1][p.col] == false) {
            q.push(QItem(p.row + 1, p.col, p.dist + 1));
            visited[p.row + 1][p.col] = true;
            M[p.row + 1][p.col] = '*';
        }

        if (p.col - 1 >= 0 &&
            visited[p.row][p.col - 1] == false) {
            q.push(QItem(p.row, p.col - 1, p.dist + 1));
            visited[p.row][p.col - 1] = true;
            M[p.row][p.col - 1] = '*';
        }

        if (p.col + 1 < COLLUM &&
            visited[p.row][p.col + 1] == false) {
            q.push(QItem(p.row, p.col + 1, p.dist + 1));
            visited[p.row][p.col + 1] = true;
            M[p.row][p.col + 1] = '*';
        }
        M[rowA - 1][collumA - 1] = 'A';
        M[rowB - 1][collumB - 1] = 'B';
        display2DMatrix(M);
        system("cls");
    }
    return -1;
}

void userInput(int& rowA, int& collumA, int& rowB, int& collumB)
{
    cout << "A Row (1 - 20): ";
    cin >> rowA;
    cout << "A Collum (1 - 40): ";
    cin >> collumA;

    cout << "B Row (1 - 20): ";
    cin >> rowB;
    cout << "B Collum (1 - 40): ";
    cin >> collumB;
}


int main()
{
    int rowA, collumA, rowB, collumB;
    userInput(rowA, collumA, rowB, collumB);

    char M[ROW][COLLUM];
    for (unsigned i = 0; i < ROW; i++)
    {
        for (unsigned j = 0; j < COLLUM; j++)
        {
            M[i][j] = '-';
        }
    }
    M[rowA - 1][collumA - 1] = 'A';
    M[rowB - 1][collumB - 1] = 'B';

    cout << minDistance(M, rowA, collumA, rowB, collumB) << endl;
    display2DMatrix(M);

    return 0;
}