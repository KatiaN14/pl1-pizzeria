/*
Basándose en el código anterior, implemente un programa que permita convertir un conjunto
de temperaturas en grados Celsius a temperaturas en grados Fahrenheit usando la siguiente
fórmula fahrenheit = (9.0 / 5.0) ∗ celsius + 32.0 y obteniendo el siguiente resultado

GRADOS                  GRADOS
CELSIUS                 FAHRENHEIT
----------              ----------
     5                       41
    10                       50
    15                       59
    20                       68
    25                       77
    30                       86
    35                       95
    40                      104
    45                      113
    50                      122
*/

#include <iostream>
#include <iomanip>

using namespace std;

int main() 
{
    cout << "GRADOS           GRADOS" << endl;
    cout << "CELSIUS          FAHRENHEIT" << endl;

    for (int c = 5; c < 51; c = c + 5) {
        double f = (9.0/5) * c + 32;
        cout << setw(4) << c << setw(19) << f << endl;
    }

    return 0;
}