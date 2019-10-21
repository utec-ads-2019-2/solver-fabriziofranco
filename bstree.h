#ifndef Evaluador_H
#define Evaluador_H

#include "node.h"
#include <vector>
#include <map>
#include<stack>
#include <algorithm>

class Evaluador {
    Node *root;
    vector<Node*> numeros;
    stack<Node*> operadores;
    map<string,string> variables;



    static bool is_not_operator(char x){
        return (x != '+' and x != '-' and x != '/' and x!='*' and x!='^' and x!='(' and x!=')' );
    }

    static bool parentesis(const string& x){
        return x== "(" or x== ")" ;
    }

    static string remover_espacios_blancos(string &str)
    {
        str.erase(std::remove(str.begin(), str.end(), ' '), str.end());
        return str;
    }

    void resolver_variables(){
        for(auto i:numeros){
            if(isalpha(i->data[0])){
                auto it = variables.find(i->data);
                if(it==variables.end()){
                    string temp;
                    cout<<"Inserte el valor de "<<i->data<<": ";
                    cin>>variables[i->data];
                    cout<<endl;
                }
                i->data=variables[i->data];
            }
        }
    }

    void update_stack(){
        if(operadores.size()==1 or operadores.top()->data=="(")
            return;

        else if(operadores.top()->data==")"){
            operadores.pop();
            if(operadores.empty())
                return;

            while(operadores.top()->data!="("){

                if(operadores.top()->data!=")")
                    numeros.push_back(operadores.top());

                operadores.pop();
                if(operadores.empty())
                    return;
            }
            operadores.pop();
        }
        else{
            auto operador=operadores.top();
            operadores.pop();
            while(operadores.top()->rank>=operador->rank){
                numeros.push_back(operadores.top());
                operadores.pop();
                if(operadores.empty())
                    break;
            }
            operadores.push(operador);}
    }

    void llenar_faltantes(){
        while(!operadores.empty()){
            if(!parentesis(operadores.top()->data))
                numeros.push_back(operadores.top());
            operadores.pop();
        }
    }

    void postfijo(string expresion){
        string temp;
        remover_espacios_blancos(expresion);
        for (char i : expresion) {
            if (is_not_operator(i)){
                temp += i;
            }
            else {
                auto node = new Node(temp);
                auto operador = new Node(string(1,i));
                if(!temp.empty())
                    numeros.push_back(node);
                operadores.push(operador);
                update_stack();
                temp = "";
            }
        }

        if(is_not_operator(expresion[expresion.length()-1]))
            numeros.push_back(new Node(temp));

        llenar_faltantes();
    }

    void Crear_arbol(){

        stack<Node*> stack_1;

        for(auto numero : numeros){
            stack_1.push(numero);
            if(stack_1.top()->im_operator){
                auto temp=stack_1.top();
                stack_1.pop();

                temp->right=stack_1.top();
                stack_1.pop();

                temp->left=stack_1.top();
                stack_1.pop();

                stack_1.push(temp);
            }
        }
        root=stack_1.top();
    }


public:
        Evaluador() : root(nullptr){};

        double Resolver(const string& expresion){
            postfijo(expresion);
            resolver_variables();
            Crear_arbol();
            if(root) {
                return root->Evaluar();
            }
            return double();
        }

        ~Evaluador() {
            if(root)
                root->Destroy();
        }
};

#endif
