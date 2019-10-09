#include <iostream>
#include "bstree.h"
using namespace std;

int main(){

    //  RESISTENTE A MAL USO DE '(' ó ')' y a espacios en blanco innecesarios.


    Evaluador evaluador;
    cout<<evaluador.Resolver("7/4*((3+1)*3)+            3))))))))))");
    return 0;
}


