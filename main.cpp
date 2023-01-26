//
//  main.cpp
//  Linear Project
//
//  Created by Merna Abdelbadie on 27/02/2022.
//

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<double>> getCofactors(vector<vector<double>> matrix, int size, int row, int col)
{
    vector<vector<double>> cofactors;
    cofactors.resize(size, vector<double>(size));
    //col and rows of cofactors
    int x = 0;
    int y = 0;
    //creating cofactors
    for(int i = 0; i < size + 1; i++)
    {
        for(int j = 0; j < size + 1; j++)
        {
            if(i != row && j != col)
            {
                cofactors[x].at(y) = matrix[i].at(j);
                y++;
                // increment rows when col reach the end and puts col back to zero
                if(y == size)
                {
                    x++;
                    y = 0;
                }
            }
        }
    }
    return cofactors;
}
double getDeterminant(vector<vector<double>> matrix, int size)
{
    double determinant = 0;
    vector<vector<double>> cofactors;
    cofactors.resize(size, vector<double>(size));
    
    if(size == 1)
        determinant = matrix[0][0];
    else if(size == 2)
        determinant += ((matrix[1][1] * matrix[0][0])-(matrix[0][1] * matrix[1][0]));
    else
    {
        for(int i = 0; i < size; i++)
        {
            cofactors = getCofactors(matrix, size - 1, 1, i);
            determinant += pow(-1,(1 + i)) * matrix[1][i] * getDeterminant(cofactors, size - 1);
        }
    }
    return determinant;
}
double getAn(vector<double> solution, vector<vector<double>> matrix, int size, int col)
{
    double d = 0;
    vector<vector<double>> An;
    An.resize(size, vector<double>(size));
    //get An for each iteration
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            if(j == col)
            {
                An[i].at(j) = solution.at(i);
            }
            else
            {
                An[i].at(j) = matrix[i].at(j);
            }
        }
    }
    //call getDeterminant on An to get determinant and send it to the main
    d = getDeterminant(An, size);
    return d;
}
double getSolution(double d, double dn)
{
    double soln = 0;
    soln = dn/d;
    return soln;
}
int main()
{
    vector<vector<double>> matrix;
    vector<double> solution;
    int size;
    do{
    cout << "Please identify the size of the square matrix:\n";
    cin >> size;
        if(size <= 0)
            cout << "Size is invalid\n";
    }while(size <= 0);
    matrix.resize(size, vector<double>(size));
    solution.resize(size);
    
    cout << "Please set the matrix:\n";
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            cin >> matrix[i].at(j);
        }
    }
    
    cout << "Please set the solution matrix:\n";
    for(int i = 0; i < size; i++)
    {
            cin >> solution.at(i);
    }
  
    double det = getDeterminant(matrix, size);
    double detOfN = 0;
    double solnOfX = 0;
    if(det == 0)
    {
        cout << "matrix not invertible\n";
        exit(0);
    }
    else
    {
        //do cramer's rule
        for(int i = 0; i < size; i++)
        {
            detOfN = getAn(solution, matrix, size, i);
            //call the function that gets the solution of unknowns
            solnOfX = getSolution(det, detOfN);
            //cout the unknowns
            cout << "X" << (i + 1) << " = " << solnOfX << endl;
        }
    }
    return 0;
}
