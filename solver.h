#ifndef Solver_H
#define Solver_H

#include "node.h"
#include <string>
#include <iostream>
#include <map>
#include <cctype>

using namespace std;

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

        bool insert(char c){ // TODO: accept 2+ digit numbers
          Node* newnode = new Node(c);
        // empty tree
          if (!current) {
            if (!isdigit(c) && c!='+' && c!='-') return false;
            root = current = newnode;
            return true;
          }

        // not empty tree
          //input is digit
          if (isdigit(c)){
            current->right = newnode;
            current = current->right; // descend to right
            return true;
          }
          //input is operator
            // current node has an operator
          if (current->isOperator()) return current->mergeOperator(c);
            // current node has a number
              // current node is the first one
          if (current==root || weight[root->data]>=weight[c]){
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

        void parser(char* expression);

        ~Solver();
};

#endif
