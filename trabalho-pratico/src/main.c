#include "interperter.h"

// Description:

// This function checks if the program was run with 3 command line arguments (argc == 3). If it was, it calls the function interpertador with the second and third arguments argv[1] and argv[2] as parameters. If argc is not equal to 3, it calls the function interpretador_interativo. 
// In both cases, main returns 0 at the end, indicating the program ended successfully.

int main(int argc,char*argv[]) {
  
  if (argc == 3) interpertador(argv[1],argv[2]);
  else interpretador_interativo();

    return 0;
}