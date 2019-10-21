#include <iostream>
#include "bstree.h"
using namespace std;

int main(){

    //  RESISTENTE A MAL USO DE '(' ó ')' y a espacios en blanco innecesarios.


    Evaluador evaluador;
    string equation;
    cin >> equation;
    cout<<evaluador.Resolver(equation);
    return 0;
}


