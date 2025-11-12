#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
using namespace std;

class Matrix
{
private:
    int n;
    vector<vector<int>> data;
public:
    // Initialize an empty matrix based on the input size
    Matrix(int size)
    {
        n = size;
        data = vector<vector<int>>(size, vector<int>(size, 0));
    }
    
    // Overload the + operator to sum this matrix and another, returning a new resultant matrix
    Matrix operator+(const Matrix& other) const
    {
        Matrix output(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                output.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return output;
    }

    // Overload the * operator to multiply this matrix and another, returning a new resultant matrix
    Matrix operator*(const Matrix& other) const
    {
        Matrix output(n);
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    // Build the product based on the sum of the current index in the current row with the other's current row index of its column
                    output.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return output;
    }

    // Takes two row indices, returns a new matrix with the swapped rows
    Matrix swapRows(int row1=0, int row2=0) const
    {
        Matrix output = *this;
        swap(output.data[row1], output.data[row2]);
        return output;  
    }
    // Takes two column indices, returns a new matrix with the swapped columns
    Matrix swapCols(int col1=0, int col2=0) const
    {
        Matrix output = *this;
        for (int i = 0; i < n; i++)
        {
            swap(output.data[i][col1], output.data[i][col2]);
        }
        return output;
    }

    void printDiagonalSums() const
    {
        // Iterate through the matrix and add each value at the main and secondary diagonal.
        // Main diagonal is where row = col
        // Secondary diagonal is where row + col = length
        int mainSum = 0;
        int secondarySum = 0;
        for (int i = 0; i < n; i++)
        {
            mainSum += data[i][i];
            secondarySum += data[i][(n - 1) - i];
        }
        cout << "Main diagonal sum: " << mainSum << "\n";
        cout << "Secondary diagonal sum: " << secondarySum << "\n";
    }

    // Get the value at the indices
    int getValue(int i, int j) const
    {
        if (i >= 0 && j >= 0 && i < n && j < n)
        {
            return data[i][j];
        }
        return 0;
    }

    // Set the value at the indices
    void setValue(int i=0, int j=0, int val=100)
    {
        if (i >= 0 && j >= 0 && i < n && j < n)
        {
            data[i][j] = val;
        }
    }

    void printMatrix() const
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                cout << setw(8) << setfill(' ') << data[i][j];
            }
            cout << "\n";
        }
    }
};



int main()
{
    // Get the filename from the user
    char filename[1000];
    cout << "Enter filename: ";
    cin >> filename;

    // Open the file
    ifstream infile(filename);

    // Get the size of the matrix
    int n;
    infile >> n;

    // Allocate two nxn matrices
    Matrix matrix1(n), matrix2(n);

    // Read the matrices
    for (int i = 0; i < (2 * n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            int data;
            infile >> data;
            if (i < n)
            {
                matrix1.setValue(i, j, data);
            } else {
                matrix2.setValue(i - n, j, data);
            }
        }
    }

    // Close the file
    infile.close();

    // Print the matrices
    cout << "Matrix 1: \n";
    matrix1.printMatrix();
    cout << "Matrix 2: \n";
    matrix2.printMatrix();
    // Create menu for user
    char choice;
    while (true)
    {
        // Present the options
        cout << "\nMenu:\n";
        cout << "1. Print matrices\n";
        cout << "2. Print sum of matrices\n";
        cout << "3. Print diagonal values\n";
        cout << "4. Swap rows\n";
        cout << "5. Swap columns\n";
        cout << "6. Update value\n";
        cout << "q. Quit\n";
        cout << "Enter choice: ";
        cin >> choice;

        // Quit the program if q is entered
        if (choice == 'q' || choice == 'Q')
        {
            break;
        }
        // Print both matrices
        if (choice == '1')
        {
            cout << "Matrix 1:\n";
            matrix1.printMatrix();
            cout << "Matrix 2:\n";
            matrix2.printMatrix();
        }
        // Print the sum of the matrices
        else if (choice == '2')
        {
            Matrix newMatrix = matrix1 + matrix2;
            newMatrix.printMatrix();
        }
        // Print the main and secondary diagonal sums of both matrices
        else if (choice == '3')
        {
            cout << "Matrix 1 diagonal values:\n";
            matrix1.printDiagonalSums();
            cout << "Matrix 2 diagonal values:\n";
            matrix2.printDiagonalSums();
        }
        // Choose which matrix and which row indices to swap, then swap them
        else if (choice == '4')
        {
            int matChoice, row1, row2;
            Matrix swapped(n);
            cout << "Which matrix (1 or 2): ";
            cin >> matChoice;
            cout << "Enter row indices to swap: ";
            cin >> row1 >> row2;
            if (!(row1 >= 0 && row1 < n && row2 >= 0 && row2 < n))
            {
                cerr << "Invalid row indices " << endl;
                continue;
            }
            if (matChoice == 1)
            {
                swapped = matrix1.swapRows(row1, row2);
            }
            else if (matChoice == 2)
            {
                swapped = matrix2.swapRows(row1, row2);
            }
            swapped.printMatrix();
        }
        // Choose which matrix and which column indices to swap, then swap them
        else if (choice == '5')
        {
            int matChoice, col1, col2;
            Matrix swapped(n);
            cout << "Which matrix (1 or 2): ";
            cin >> matChoice;
            cout << "Enter column indices to swap: ";
            cin >> col1 >> col2;
            if (!(col1 >= 0 && col1 < n && col2 >= 0 && col2 < n))
            {
                cerr << "Invalid column indices " << endl;
                continue;
            }
            if (matChoice == 1)
            {
                swapped = matrix1.swapCols(col1, col2);
            }
            else if (matChoice == 2)
            {
                swapped = matrix2.swapCols(col1, col2);
            }
            swapped.printMatrix();
        }
        // Choose which matrix to update, the row and column, and the new value, and then update the matrix 
        else if (choice == '6')
        {
            Matrix newMatrix(n);
            int matChoice, row, col, val;
            cout << "Which matrix (1 or 2): ";
            cin >> matChoice;
            cout << "Enter row, column, and new value: ";
            cin >> row >> col >> val;
            if (!(row >= 0 && row < n && col >= 0 && col < n))
            {
                cerr << "Invalid row or column indices " << endl;
                continue;
            }
            if (matChoice == 1)
            {
                newMatrix = matrix1;
            }
            else if (matChoice == 2)
            {
                newMatrix = matrix2;
            }
            newMatrix.setValue(row, col, val);
            newMatrix.printMatrix();
        }
        else
        {
            cout << "Invalid choice\n";
        }
    }

}