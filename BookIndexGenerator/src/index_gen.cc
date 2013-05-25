#include <iostream> 
#include <fstream>
#include <cstdio>
#include <ctime>

#include "CommonWordHash.h"
#include "BookIndex.h"

using namespace std;

#define MIN_ARGS 3
#define MAX_ARGS 4
#define COMMONWORD_ARG 1
#define BOOK_ARG 2

//main: returns 0 on SUCCESS
int main(int argc, char *argv[]) {   
  
  std::ifstream commonWordFile;
  std::ifstream bookFile;
  
  if (argc < MIN_ARGS || argc > MAX_ARGS) {
    cerr << "Usage: " << argv[0] <<                                     \
      "[commonwords.file] [book.file] [optional arg]\n" << endl;
    cerr << "optional arg: [HASH|RBTREE|THREAD|HADOOP]" << endl;
    return 1;
  }
  
  commonWordFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  //open commonwords file
  try {
    commonWordFile.open(argv[COMMONWORD_ARG]);
  }
  catch (std::ifstream::failure e) {
    std::cerr << "Could not open: " << argv[COMMONWORD_ARG] <<".\nReason: " << e.what();
    return 2;
  }

  bookFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  //open book file
  try {
    bookFile.open(argv[BOOK_ARG]);
  }
  catch (std::ifstream::failure e) {
    std::cerr << "Could not open: " << argv[BOOK_ARG] <<".\nReason: " << e.what();
    return 3;
  }
  
  //configure index factory type, virtual index
  

  std::clock_t start;
  double duration;

  //build common word hashtable
  CommonWordHash *commonWords = new CommonWordHash(commonWordFile);
  
  start = std::clock();

  BookIndex *bookIndex = new BookIndex(commonWords, bookFile);

  duration = ( std::clock() - start );// / (double) CLOCKS_PER_SEC;

  std::cout<<"build index: "<< duration <<'\n';

  start = std::clock();

  bookIndex->printIndex();
  duration = ( std::clock() - start );// / (double) CLOCKS_PER_SEC;

  std::cout<<"print index: "<< duration <<'\n';  

  //Clean up
  delete(bookIndex);
  delete(commonWords);
  
  std::cout << "argc: " << argc << "\n";
  std::cout << "argv[0]: " << argv[0] << "\n";
  
  return 0;        
}
