// Elwin van 't Wout
// Pontificia Universidad Católica de Chile
// 9-9-2023

// Read a matrix from a text file and store specific lines in an array.

#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int nrows, ncols;
    double *my_matrix;
    double tmp;

    ifstream file;

    file.open("matrix.txt");

    if (file.is_open())
    {
        file >> nrows;
        cout << "Number of rows: " << nrows << endl;

        file >> ncols;
        cout << "Number of columns: " << ncols << endl;

        int my_firstrow = 2;
        int my_nrows = 3;
        cout << "Read " << my_nrows << " rows starting from row " << my_firstrow << endl;

        my_matrix = new double [my_nrows * ncols];

        for (int i=0; i<(my_firstrow-1)*ncols; i++) {
            file >> tmp;
            cout << "skipped: " << tmp << endl;
        }

        cout << "Store matrix elements" << endl;
        for (int i=0; i<my_nrows*ncols; i++) {
            file >> my_matrix[i];
            cout << i << " " << my_matrix[i] << endl;
        }

        file.close();
    }
    else
    {
        cout << "Unable to open file." << endl;
    }

    delete[] my_matrix;

    return 0;
}
