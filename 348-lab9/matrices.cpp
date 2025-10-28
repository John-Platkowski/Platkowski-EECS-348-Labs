#include <iostream>
#include <fstream>

void printMatrix(int** matrix, int n)
{
    // Iterate through the matrix and print each value
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << "\n";
    }
}


void printSum(int** A, int** B, int n)
{
    // Iterate through the matrix indexes and print the sum at each value
    std::cout << "Sum of the matrices:\n";
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            std::cout << A[i][j] + B[i][j] << " ";
        }
        std::cout << "\n";
    }
}

void printDiagonal(int** matrix, int n)
{
    // Iterate through the matrix and add each value at the main and secondary diagonal.
    // Main diagonal is where row = col
    // Secondary diagonal is where row + col = length
    int mainSum = 0;
    int secondarySum = 0;
    for (int i = 0; i < n; i++)
    {
        mainSum += matrix[i][i];
        secondarySum += matrix[i][(n - 1) - i];
    }
    std::cout << "Main diagonal sum: " << mainSum << "\n";
    std::cout << "Secondary diagonal sum: " << secondarySum << "\n";
}

int** swapRows(int** matrix, int row1, int row2, int n)
{
    // Validate indices
    if (row1 < 0 || row1 >= n || row2 < 0 || row2 >= n)
    {
        std::cout << "Error: Invalid row indices\n";
        return nullptr;
    }
    // Allocate a new matrix
    int** result = new int*[n];
    for (int i = 0; i < n; i++)
    {
        result[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            result[i][j] = matrix[i][j];
        }
    }
    // Swap the two rows in the copy
    int* temp = result[row1];
    result[row1] = result[row2];
    result[row2] = temp;
    printMatrix(result);
    return result;
}

int** swapCols(int** matrix, int col1, int col2, int n)
{
    // Validate indices
    if (col1 < 0 || col1 >= n || col2 < 0 || col2 >= n)
    {
        std::cout << "Error: Invalid column indices\n";
        return nullptr;
    }
    // Allocate a new matrix
    int** result = new int*[n];
    for (int i = 0; i < n; i++)
    {
        result[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            result[i][j] = matrix[i][j];
        }
    }
    
    // Swap the two columns in the copy by iterating across the rows
    // And swapping between the column values
    for (int i = 0; i < n; i++)
    {
        int temp = result[i][col1];
        result[i][col1] = result[i][col2];
        result[i][col2] = temp;
    }
    printMatrix(result);
    return result;
}

int** updateVal(int** matrix, int row, int col, int val, int n)
{
    // Validate indices
    if (row < 0 || row >= n || col < 0 || col >= n)
    {
        std::cout << "Error: Invalid row or column index\n";
        return nullptr;
    }
    // Allocate a new matrix
    int** result = new int*[n];
    for (int i = 0; i < n; i++)
    {
        result[i] = new int[n];
        for (int j = 0; j < n; j++)
        {
            result[i][j] = matrix[i][j];
        }
    }
    
    // Update the value in the copy
    result[row][col] = val;
    printMatrix(result);
    return result;
}

int main()
{
    // Get the filename from the user
    char filename[100];
    std::cout << "Enter filename: ";
    std::cin >> filename;

    // Open the file
    std::ifstream infile(filename);


    // Get the size of the matrix
    int n;
    infile >> n;

    // Allocate two nxn matrices
    int** matrix1 = new int*[n];
    int** matrix2 = new int*[n];
    for (int i = 0; i < n; i++)
    {
        matrix1[i] = new int[n];
        matrix2[i] = new int[n];
    }

    // Read the matrices
    for (int i = 0; i < (2 * n); i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i < n)
            {
                infile >> matrix1[i][j];
            } else {
                infile >> matrix2[i - n][j];
            }
        }
    }

    // Close the file
    infile.close();

    // Print the matrices
    std::cout << "Matrix 1: \n";
    printMatrix(matrix1, n);
    std::cout << "Matrix 2: \n";
    printMatrix(matrix2, n);
    // Create menu for user
    char choice;
    while (true)
    {
        // Present the options
        std::cout << "\nMenu:\n";
        std::cout << "1. Print matrices\n";
        std::cout << "2. Print sum of matrices\n";
        std::cout << "3. Print diagonal values\n";
        std::cout << "4. Swap rows\n";
        std::cout << "5. Swap columns\n";
        std::cout << "6. Update value\n";
        std::cout << "q. Quit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        // Quit the program if q is entered
        if (choice == 'q' || choice == 'Q')
        {
            break;
        }
        // Print both matrices
        if (choice == '1')
        {
            std::cout << "Matrix 1:\n";
            printMatrix(matrix1, n);
            std::cout << "Matrix 2:\n";
            printMatrix(matrix2, n);
        }
        // Print the sum of the matrices
        else if (choice == '2')
        {
            printSum(matrix1, matrix2, n);
        }
        // Print the main and secondary diagonal sums of both matrices
        else if (choice == '3')
        {
            std::cout << "Matrix 1 diagonal values:\n";
            printDiagonal(matrix1, n);
            std::cout << "Matrix 2 diagonal values:\n";
            printDiagonal(matrix2, n);
        }
        // Choose which matrix and which row indices to swap, then swap them
        else if (choice == '4')
        {
            int matChoice, row1, row2;
            std::cout << "Which matrix (1 or 2): ";
            std::cin >> matChoice;
            std::cout << "Enter row indices to swap: ";
            std::cin >> row1 >> row2;
            if (matChoice == 1)
            {
                int** temp = swapRows(matrix1, row1, row2, n);
                // Deallocate the temp matrix if the operation was successful
                if (temp != nullptr)
                {
                    for (int i = 0; i < n; i++) delete[] matrix1[i];
                    delete[] matrix1;
                    matrix1 = temp;
                }
            }
            else if (matChoice == 2)
            {
                int** temp = swapRows(matrix2, row1, row2, n);
                // Deallocate the temp matrix if the operation was successful
                if (temp != nullptr)
                {
                    for (int i = 0; i < n; i++) delete[] matrix2[i];
                    delete[] matrix2;
                    matrix2 = temp;
                }
            }
        }
        // Choose which matrix and which column indices to swap, then swap them
        else if (choice == '5')
        {
            int matChoice, col1, col2;
            std::cout << "Which matrix (1 or 2): ";
            std::cin >> matChoice;
            std::cout << "Enter column indices to swap: ";
            std::cin >> col1 >> col2;
            if (matChoice == 1)
            {
                int** temp = swapCols(matrix1, col1, col2, n);
                // Deallocate the temp matrix if the operation was successful
                if (temp != nullptr)
                {
                    for (int i = 0; i < n; i++) delete[] matrix1[i];
                    delete[] matrix1;
                    matrix1 = temp;
                }
            }
            else if (matChoice == 2)
            {
                int** temp = swapCols(matrix2, col1, col2, n);
                // Deallocate the temp matrix if the operation was successful
                if (temp != nullptr)
                {
                    for (int i = 0; i < n; i++) delete[] matrix2[i];
                    delete[] matrix2;
                    matrix2 = temp;
                }
            }
        }
        // Choose which matrix to update, the row and column, and the new value, and then update the matrix 
        else if (choice == '6')
        {
            int matChoice, row, col, val;
            std::cout << "Which matrix (1 or 2): ";
            std::cin >> matChoice;
            std::cout << "Enter row, column, and new value: ";
            std::cin >> row >> col >> val;
            if (matChoice == 1)
            {
                int** temp = updateVal(matrix1, row, col, val, n);
                // Deallocate the temp matrix if the operation was successful
                if (temp != nullptr)
                {
                    for (int i = 0; i < n; i++) delete[] matrix1[i];
                    delete[] matrix1;
                    matrix1 = temp;
                }
            }
            else if (matChoice == 2)
            {
                int** temp = updateVal(matrix2, row, col, val, n);
                // Deallocate the temp matrix if the operation was successful
                if (temp != nullptr)
                {
                    for (int i = 0; i < n; i++) delete[] matrix2[i];
                    delete[] matrix2;
                    matrix2 = temp;
                }
            }
        }
        else
        {
            std::cout << "Invalid choice\n";
        }
    }

}

