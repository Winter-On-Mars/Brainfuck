#include <iostream>
#include <fstream>
#include <string>

// > increment the data pointer one cell to the right
// < increment the data pointer one cell to the left
// + increment the byte at the data pointer
// - decrement the byte at the data pointer
// . output the byte at the data pointer
// , accept one byte of input, storing its value in the byte at the data pointer
// [ if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the nex command, jump it forward to the command after the matching ] command
// ] if the byte at the datapointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump back to the command after the matching [ command 

int main(int argc, char** argv) {
  std::string if$ = "";
  // this will be the compiler the interpretor will be written later
  if (argc > 1) {
    if$ = argv[1];
  }
  else {
    std::cout << "Must input a file";
    return 1;
  }

  std::ifstream ifs(if$);
  if (!ifs) {
    std::cout << "!!!Unable to open " << if$ << "!!!\n";
    return 1;
  }

  char array[30] = { 0 };
  char* ptr = array;

  char buf = 0;
  while (ifs >> buf) {
    std::cout << buf;
  }

  return 0;
}

