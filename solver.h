#ifndef Solver_H
#define Solver_H

#include "node.h"
#include <string>
#include <iostream>
#include <map>
#include <cctype> // isdigit()
#include <cmath> // pow()

using namespace std;

// Functions for node.h and parser
bool isOperator(char x){
  return x=='+' ||  x=='-' ||  x=='/' ||  x=='*' ||  x=='^';
};

class Solver {
    private:
        map<char, int> weight = {
          {'+', 1},
          {'-', 1},
          {'*', 2},
          {'/', 2},
          {'^', 3}
        };
        Node* root;
        Node* current;

    public:
        Solver(): root(nullptr), current(nullptr){};

        bool insert(string c){
          Node* newnode = new Node(c);
        // empty tree
          if (!current) {
            if (!isdigit(c[0]) && (c[0])!='+' && (c[0])!='-') return false;
            root = current = newnode;
            return true;
          }

        // not empty tree
          //input is digit
          if (isdigit(c[0])){
            current->right = newnode;
            current = current->right; // descend to right
            return true;
          }
          //input is operator
            // current node has an operator
          if (current->isOperator()){
            if (!(c[0]=='+' || c[0]=='-')) return false; //Can't merge this operators
            if (!current->mergeOperator(c[0])){ // current has * or / or ^
              current->right = newnode;
              current = current->right; // descend to right
              current->left = new Node("0"); // set left node to 0 (case: 5*-3)
              return true;
            }
            return true; //op merged
          }
            // current node has a number
              // current node is the first one (==root)
          if (current==root || weight[(root->data)[0]]>=weight[c[0]]){
            // new root
            newnode->left = root;
            root = current = newnode;
            return true;
          }
          // current node isn't root and input is heavier
          newnode->data = current->data;
          current->data = c;
          current->left = newnode;
          return true;
        };

        bool parse(char* expression){
          map<char, float> var;
          string number = "";
          for (char* c=expression; c!= expression + strlen(expression); c++){
            // c is operand
            if (isOperator(*c)) this->insert(string(1, *c));
            // c is digit or point (part of a number)
            else if (isdigit(*c) || *c=='.') {
              if (*c=='.' && !isdigit(*(c+1))) return false; //incomplete decimal
              number+=*c;

              // if next character isn't part of a number, end number
              if (!(isdigit(*(c+1)) || *(c+1)=='.')) {
                this->insert(number);
                number = "";
              }
            }
            else{
              // variable must be between operators
              if ( !isOperator(*(c-1)) || !isOperator(*(c+1)) ) return false;
              //known variable
              if (var.count(*c)) this->insert(to_string(var[*c]));
              else{
                cout << "Enter value of " << *c << ": ";
                cin >> var[*c];
                this->insert(to_string(var[*c]));
              }
            }
        }
        return true;
      };

        ~Solver();
      double solve(char* expression);
};

#endif
