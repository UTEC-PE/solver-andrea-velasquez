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
      //char str[]="2.4+(3+z)";
      char str[]= "4*((3+4))";
      //char* str="7/4*((a+b)^4*a)+3";

      Solver calculator;
      //char str[]= "(3+(4))*3";
      cout << "Answer: " << calculator.solve(str);
}

// Te faltó controlar el caso cuando una variable es el primer elemento de la ecuación tipo: a+b o 
// a-2*5/2+1-2^4+a     a=3 Resultado esperado -14 | Resultado actual: Crash
// Tener en cuenta que lo siguiente si funciona: (a-2*5/2+1-2^4+a)     a=3
// Solo se pasó el caso en que la ecucación comienza con variable
int main(int argc, char const *argv[]) {
    string myStr;
    if (argc == 2) {
        Solver calculator;
        cout << "Answer: " << calculator.solve((char*)argv[1]);
    }
    else {
      throw "One argument expected";
    }

    //menu();

    cout << "\nPress enter to continue ...";
    cin.get();
    return EXIT_SUCCESS;
}
