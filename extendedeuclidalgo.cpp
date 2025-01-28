#include <iostream>

using namespace std;

// Extended Euclidean Algorithm
int extendedGCD(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b; // GCD is b
    }

    int x1, y1; // To store results of recursive call
    int gcd = extendedGCD(b % a, a, x1, y1);

    // Update x and y using results of recursive call
    x = y1 - (b / a) * x1;
    y = x1;

    return gcd;
}

int main() {
    int a, b, x, y;

    // User Input
    cout << "Enter two numbers: ";
    cin >> a >> b;

    int gcd = extendedGCD(a, b, x, y);

    // Output results
    cout << "GCD(" << a << ", " << b << ") = " << gcd << endl;
    cout << "Coefficients x = " << x << ", y = " << y << " (Bezout's Identity: " 
         << a << "*" << x << " + " << b << "*" << y << " = " << gcd << ")" << endl;

    return 0;
}
