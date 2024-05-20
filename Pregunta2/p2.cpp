#include <iostream>

using namespace std;

int suma(int *a, int *b) {
    return *a + *b;
}

int resta(int *a, int *b) {
    return *a - *b;
}

int multi(int *a, int *b) {
    int i, s, resu;
    s = *b;
    resu = *b;
    for(i = 0; i < *a; i++) {
        resu = resu + s;
    }
    return resu;
}

int division(int *a, int *b) {
    int i, c;
    c = 0;
    while(*a >= *b) {
        *a = *a - *b;
        c = c + 1;
    }
    return c;
}

int main() {
    int a, b;
    cout << "Introduce dos numeros: " << endl;
    cin >> a >> b;

    cout << "La suma es: " << suma(&a, &b) << endl;
    cout << "La resta es: " << resta(&a, &b) << endl;
    cout << "La multiplicacion es: " << multi(&a, &b) << endl;

    if (b != 0)
        cout << "La division es: " << division(&a, &b) << endl;
    else
        cout << "No existe division entre cero" << endl;

    return 0;
}