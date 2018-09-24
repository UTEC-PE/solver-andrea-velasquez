#include <iostream>
#include "solver.h"

using namespace std;

void menu() {
      system("cls");
      cout<<"==========================================================="<<endl;
      cout<<"\t\tPractica Operaciones"<<endl;
      cout<<"==========================================================="<<endl;

      //Note: Variables can be floats

      //char* str="7/4*((a+b)*a)+3";
      //char* str="7/4*((a+-+--b)*a)+3";
      //char str[]="2+(3)";
      char str[]="2.4+(3+z)";
      //char* str="7/4*((a+b)^4*a)+3";

      Solver calculator;
      //char str[]= "(3+(4))*3";
      cout << "Answer: " << calculator.solve(str);
}

int main(int argc, char const *argv[]) {
    menu();

    cout << "\nPress enter to continue ..."; 
    cin.get(); 
    return EXIT_SUCCESS;
}

