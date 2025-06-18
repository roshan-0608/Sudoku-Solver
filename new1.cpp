#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Function to check if it's safe to place a number at a given position
bool isSafe(vector<vector<int>> &mat, int row, int col, int num) {
    for (int x = 0; x < 9; x++) {
        if (mat[row][x] == num || mat[x][col] == num)
            return false;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (mat[startRow + i][startCol + j] == num)
                return false;

    return true;
}

// Recursive function to solve the Sudoku
bool solveSudokuRec(vector<vector<int>> &mat, int row, int col) {
    if (row == 8 && col == 9)
        return true;

    if (col == 9) {
        row++;
        col = 0;
    }

    if (mat[row][col] != 0)
        return solveSudokuRec(mat, row, col + 1);

    for (int num = 1; num <= 9; num++) {
        if (isSafe(mat, row, col, num)) {
            mat[row][col] = num;
            if (solveSudokuRec(mat, row, col + 1))
                return true;
            mat[row][col] = 0;
        }
    }

    return false;
}


void displayBoard(const vector<vector<int>> &mat) {
    cout << "\nCurrent Sudoku Board:\n";
    for (int i = 0; i < 9; i++) {
        if (i % 3 == 0 && i != 0)
            cout << "------+-------+------\n";
        for (int j = 0; j < 9; j++) {
            if (j % 3 == 0 && j != 0)
                cout << "| ";
            if (mat[i][j] == 0)
                cout << ". ";
            else
                cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}


void solveSudoku(vector<vector<int>> &mat) {
    if (solveSudokuRec(mat, 0, 0)) {
        cout << "\nSolved Sudoku:\n";
        displayBoard(mat);
    } else {
        cout << "No solution exists for this puzzle!" << endl;
    }
}

// Read puzzle from console
void inputFromConsole(vector<vector<int>> &mat) {
    cout << "WELCOME TO THE SUDOKU SOLVER\n";
    cout << "Please enter your Sudoku puzzle row by row.\n";
    cout << "Enter 9 numbers per row separated by space (0 for empty cells).\n";
    cout << "Tip: A valid Sudoku usually starts with 17 to 30 filled cells total.\n\n";

    for (int i = 0; i < 9; i++) {
        cout << "Enter 9 numbers for row " << i + 1 << ": ";
        for (int j = 0; j < 9; j++) {
            cin >> mat[i][j];
            while (mat[i][j] < 0 || mat[i][j] > 9) {
                cout << "Invalid input! Please enter a number between 0 and 9: ";
                cin >> mat[i][j];
            }
        }
    }
}

// Read puzzle from a file
bool inputFromFile(vector<vector<int>> &mat, const string &filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error: Unable to open file: " << filename << endl;
        return false;
    }

    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            inFile >> mat[i][j];

    inFile.close();
    return true;
}

int main() {
    vector<vector<int>> mat(9, vector<int>(9));
    char choice;

    cout << "Do you want to (M)anually enter the puzzle or (F)ile input? (M/F): ";
    cin >> choice;

    if (choice == 'F' || choice == 'f') {
        string filename;
        cout << "Enter filename (with path if needed): ";
        cin >> filename;
        if (!inputFromFile(mat, filename)) return 1;
    } else {
        inputFromConsole(mat);
    }

    displayBoard(mat);

    char confirm;
    cout << "\nIs this the puzzle you want to solve? (Y/N): ";
    cin >> confirm;

    if (confirm == 'N' || confirm == 'n') {
        cout << "Restart the program and enter your puzzle again.\n";
        return 0;
    }

    solveSudoku(mat);
    return 0;
}
