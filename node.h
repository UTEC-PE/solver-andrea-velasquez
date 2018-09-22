#ifndef NODE_H
#define NODE_H

#include <cctype> //isdigit ()

bool isOperator(char x);
char sumOperator(char op1, char op2);

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char data) : data(data) {
        left = right = nullptr;
    };

    bool isOperator(){
      return ::isOperator(this->data);
    };
    bool mergeOperator(char op){
      if (!(data=='+' || data=='-')) return false; // data is * or / or ^
      data = sumOperator(op, data);
      return true;
    }
};

bool isOperator(char x){
  return x=='+' ||  x=='-' ||  x=='/' ||  x=='*' ||  x=='^';
};

char sumOperator(char op1, char op2){
  //Different: +- or -+ = -
  //Equal: ++ or -- = +
  return op1==op2 ? '+' : '-';
}

#endif
