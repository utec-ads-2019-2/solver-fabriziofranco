#ifndef Node_H
#define Node_H

#include <string>
#include <utility>
#include <cmath>
using namespace std;

struct Node {
    string data;
    Node*left;
    Node*right;
    int rank;
    bool im_operator;


    explicit Node(const string& data):left(nullptr),right(nullptr){
        this->data=data;
        im_operator=true;
        if (data=="+" || data=="-")
            rank=1;
        else if (data=="*" || data=="/")
            rank=2;
        else if(data=="^")
            rank=3;
        else{
            rank=0;
            im_operator= false;}
            }


    void Destroy(){
            if(this->left)
                left->Destroy();
            if(this->right)
                right->Destroy();
            delete this;
    }

    double Evaluar(){
        //eval(this);
        // y el return? No probaste que te faltaba algo

        return eval(this);
    }

private:


    bool is_leaf(){
        return (!this->left && !this->right);
    }

    static double  eval(Node* root)
    {

        if (!root)
            return 0;

        if (root->is_leaf())
            return stod(root->data);

        double resultante_izq = eval(root->left);

        double resultante_der = eval(root->right);


        if (root->data=="+")
            return resultante_izq+resultante_der;

        else if (root->data=="-")
            return resultante_izq-resultante_der;

        else if (root->data=="*")
            return resultante_izq*resultante_der;

        else if (root->data=="/")
            return resultante_izq/resultante_der;
        else
            return pow(resultante_izq,resultante_der);
    }

};

#endif



