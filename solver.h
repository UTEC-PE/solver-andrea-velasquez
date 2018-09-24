#ifndef Solver_H
#define Solver_H

#include "node.h"
#include <string>
#include <iostream>
#include <map>
#include <cctype> // isdigit()
#include <cmath> // pow()

using namespace std;

//Some functions for node.h and parse.h
bool isOperator(char x){
  return x=='+' ||  x=='-' ||  x=='/' ||  x=='*' ||  x=='^' || x=='(' || x==')';
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
        Solver* subtree;

        float operate(char op, float n1, float n2){
          switch (op){
            case '+': return n1+n2;
            case '-': return n1-n2;
            case '*': return n1*n2;
            case '/': return n1/n2;
            case '^': return pow(n1, n2);
          }
          throw "Can't operate";
        }

        float evaluate(Node* root){
          if (!root) return 0;
          if (isdigit(root->data[0])) return stof(root->data);
          //TODO: Simplificar
          switch (root->hasLeafs()) {
            //no numbers as children
            case 0: return operate(root->data[0], evaluate(root->left), evaluate(root->right));
            //left children is number
            case 1: return operate(root->data[0], stof(root->left->data), evaluate(root->right));
            //right children is number
            case 2: return operate(root->data[0], evaluate(root->left), stof(root->right->data));
            //both leafs
            case 3: return operate(root->data[0], stof(root->left->data), stof(root->right->data));
          }
          throw "Error in evaluate method";
        };


    public:
        Solver(): root(nullptr), current(nullptr), subtree(nullptr){};

        bool insert(string c){
          if (c[0]=='(') {
            subtree = new Solver;
            return true;
          }
          if (c[0]==')') {
            //this
            c = to_string(this->subtree->evaluate());
            subtree = nullptr;
          }
          if (subtree){
            this->subtree->insert(c); return true;
          }
          Node* newnode = new Node(c);
        // empty tree
          if (!current) {
            if (!isdigit(c[0]) && (c[0])!='+' && (c[0])!='-') return false;
            root = newnode;
            if (c[0]=='-'){
              root->data = '-';
              root->left = new Node("0");
              current = root;
              if (!isdigit(c[1])) return true;
              // parenthesis returned a negative
              c.erase(c.begin(), c.begin()+1); // erase '-' of negative number`
              current = root->right = new Node(c);
              return true;
            }
            current = root;
            return true;
          }

        // not empty tree
          //input is digit
          if (isdigit(c[0]) || isdigit(c[1])){
            if (c[0]=='-' && isdigit(c[1])){
              current->right = new Node("-");
              current = current->right;
              current->left = new Node("0");
            }
            current->right = newnode;
            current = current->right; // descend to right
            return true;
          }
          //input is operator
            // current node has an operator
          if (current->isOperator()){
            if (!(c[0]=='+' || c[0]=='-')) return false; //Can't merge this operators
            if (!current->mergeOperator(c[0])){ // current has * or / or ^ (ex: 3*-5 or 3*+5)
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
          //newnode->data = current->data;
          current->data = c;
          current->left = newnode;
          return true;
        };

        float evaluate(){
          float ans = evaluate(root);
          this->clear();
          return ans;
        };

        int parse(char* expression){
          map<char, float> var;
          string number = "";
          int counter = 0;
          for (char* c=expression; c!= expression + strlen(expression); c++){
            // c is operand
            if (isOperator(*c)) this->insert(string(1, *c));
            // c is digit or point (part of a number)
            else if (isdigit(*c) || *c=='.') {
              if (*c=='.' && !isdigit(*(c+1))) return counter; //incomplete decimal
              number+=*c;

              // if next character isn't part of a number, end number
              if (!(isdigit(*(c+1)) || *(c+1)=='.')) {
                this->insert(number);
                number = "";
              }
            }
            else{
              // variable must be between operators
              if ( !isOperator(*(c-1)) || (!isOperator(*(c+1)) && counter!=strlen(expression)-1) ) return counter;
              //known variable
              if (var.count(*c)) this->insert(to_string(var[*c]));
              else{
                cout << "Enter value of " << *c << ": ";
                cin >> var[*c];
                this->insert(to_string(var[*c]));
              }
            }
            ++counter;
          }
        return -1;
      };


      float solve(char* expression){
        int errorAt = parse(expression);
        if (errorAt!=-1) throw "\nError in character '" + string(1,expression[errorAt]) + "' at index " + to_string(errorAt);
        return evaluate(root);
      };

      void clear(){
        subtree = nullptr;
        if (root) root->killSelf();
        root=current=nullptr;
      };

      ~Solver(){
        clear();
      };
};

#endif
