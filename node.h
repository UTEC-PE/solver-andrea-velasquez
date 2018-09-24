#ifndef NODE_H
#define NODE_H

#include <cctype> //isdigit()
#include <string>

bool isOperator(char x);
char sumOperator(char op1, char op2);

struct Node {
    std::string data;
    Node* left;
    Node* right;

    Node(std::string data) : data(data), left(nullptr), right(nullptr){};

    void killSelf(){
      if (left) left->killSelf();
      if (right) right->killSelf();
      delete this;
    };
    bool isOperator(){
      return ::isOperator(this->data[0]);
    };
    bool mergeOperator(char op){
      if (!(data[0]=='+' || data[0]=='-')) return false; // data is * or / or ^
      data = sumOperator(op, data[0]);
      return true;
    };
    int hasLeafs(){ // 0: no leafs, 1: left leaf, 2: right leaf, 3: both leafs
      if (isdigit(left->data[0]) && isdigit(right->data[0])) return 3;
      if (isdigit(left->data[0])) return 1;
      if (isdigit(right->data[0])) return 2;
      return 0;
    }
};

char sumOperator(char op1, char op2){
  //Different: +- or -+ = -
  //Equal: ++ or -- = +
  return op1==op2 ? '+' : '-';
}

#endif
