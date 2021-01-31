#include "Matrix.h"

#include <iostream>
#include <math.h>
#include <vector>

using namespace std;

int main() {
    Matrix<double> m1(1, 3);
    Matrix<double> m2(1, 3);

    for(int i = 0; i < 3; i++) {
        m1[0][i] = i + 0.512;
        m2[0][i] = i + 3.512;
    }

    cout << "m1 =\n" << m1 << "m2 =\n" << m2 << endl;

    Matrix<double> negM1 = m1*m2;
    cout << "m1*m2 =\n" << negM1 << endl;
    cout << "Is m1 empty?\t" << m1.empty() << "\nIs m1*m2 empty?\t" << negM1.empty() << endl << endl;

    Matrix<double> M1pM2 = m1+m2;
    cout << "m1+m2 =\n" << M1pM2 << endl;

    Matrix<double> M1mM2 = m1-m2;
    cout << "m1-m2 =\n" << M1mM2 << endl;

    Matrix<int>* imposter = new Matrix<int>();
    delete imposter; // Can delete empty matrix

    return 0;
}
 