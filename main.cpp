#include <iostream>
#include <fstream>
#include <string>

#define SIZE 30

// > increment the data pointer one cell to the right
// < increment the data pointer one cell to the left
// + increment the byte at the data pointer
// - decrement the byte at the data pointer
// . output the byte at the data pointer
// , accept one byte of input, storing its value in the byte at the data pointer
// [ if the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the nex command, jump it forward to the command after the matching ] command
// ] if the byte at the datapointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump back to the command after the matching [ command

void printEntireArray(char* arr) {
  for (int i = 0; i < SIZE; i++)
    std::cout << arr[i];
  std::cout << '\n';
}

// 0 = exit success
// 1 = exit failed
// this should probably return some struct with an error message 
int cleanUpFile(std::ifstream& ifs, std::fstream& temp) {
  std::string buf = "";
  while (std::getline(ifs, buf)) {
    for (char ch : buf) {
      if (ch == ';')
        break;
      temp << ch;
    }
  }
  // reset the file so it can be passed into the run function
  ifs.clear();
  ifs.seekg(std::ios::beg);
  temp.clear();
  temp.seekg(std::ios::beg);
  return 0;
}

int run(std::fstream& ifs) {
  std::fstream executable("bfexe.cpp", std::fstream::trunc | std::fstream::in | std::fstream::out);
  if (!executable) {
    executable.close();
    std::ofstream tmp("bfexe.cpp");
    tmp.close();
    executable.open("bfexe.cpp", std::fstream::trunc | std::fstream::in | std::fstream::out);
  }

  executable << "#include<iostream>\nint main(void) {\nchar array[30000] = { 0 };\nchar* ptr = array;\n";

  int count = 0;
  char buf = 0;
  while (ifs >> buf) {
    switch (buf) {
      case '>':
        executable << "++ptr;";
        break;
      case '<':
        executable << "--ptr;";
        break;
      case '+':
        executable << "++(*ptr);";
        break;
      case '-':
        executable << "--(*ptr);";
        break;
      case '.':
        executable << "std::cout << (char)(*ptr);\n";
        break;
      case ',':
        executable << "std::cin >> *ptr;\n";
        break;
      case '[':
        executable << "while (*ptr) {\n";
        break;
      case ']':
        executable << "}\n";
        break;
      default:
        std::cout << "Error\n";
        return 1;
    }
    if (count % 10 == 0) {
      executable << "\n";
    }
    count++;
  }
  executable << "\n\treturn 0;\n}\n\n";
  return 0;
}

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
  
  std::fstream tmp("temp.bft", std::fstream::trunc | std::fstream::in | std::fstream::out);
  if (!tmp) {
    std::ofstream ltmp("temp.bft");
    tmp.open("temp.bft");
    ltmp.close();
  }
  if (cleanUpFile(ifs, tmp)) {
    std::cout << "!!!Parsing Error!!!\n";
    return 1;
  }

  int result = run(tmp);

  ifs.close();
  tmp.close();

  system("g++ bfexe.cpp");
  system("a.exe");

  remove("temp.bft");
  remove("a.exe");
  remove("bfexe.cpp");

  return result;
}
