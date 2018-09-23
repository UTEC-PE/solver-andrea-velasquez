#ifndef NODE_H
#define NODE_H

#include <cctype> //isdigit ()
#include <string>

bool isOperator(char x);
char sumOperator(char op1, char op2);

struct Node {
    std::string data;
    Node* left;
    Node* right;

    Node(std::string data) : data(data), left(nullptr), right(nullptr){};

    bool isOperator(){
      return ::isOperator(this->data[0]);
    };
    bool mergeOperator(char op){
      if (!(data[0]=='+' || data[0]=='-')) return false; // data is * or / or ^
      data = sumOperator(op, data[0]);
      return true;
    }
};

char sumOperator(char op1, char op2){
  //Different: +- or -+ = -
  //Equal: ++ or -- = +
  return op1==op2 ? '+' : '-';
}

#endif
