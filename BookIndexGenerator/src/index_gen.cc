#include <iostream> 
#include <fstream>
#include <cstdio>
#include <ctime>
#include <algorithm>

#include "CommonWordHash.h"
#include "BookIndex.h"

using namespace std;

#define MIN_ARGS 3
#define MAX_ARGS 4
#define COMMONWORD_ARG 1
#define BOOK_ARG 2
#define ITYPE_ARG 3


//main: returns 0 on SUCCESS
bool verifyInput(int argc, char *argv[], 
                 ifstream &commonWordFile, ifstream &bookFile,
                 BookIndexFactory::BookIndexType &btype)
{
  if (argc < MIN_ARGS || argc > MAX_ARGS) {
    cerr << "Usage: " << argv[0] <<                                     \
      "[commonwords.file] [book.file] [optional arg]\n" << endl;
    cerr << "optional arg(default hash): [H[ASH]|R[BTREE]|T[HREAD]|M[APREDUCE]]" << endl;
    return false;
  }
  
  commonWordFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  //open commonwords file
  try {
    commonWordFile.open(argv[COMMONWORD_ARG]);
  }
  catch (std::ifstream::failure e) {
    std::cerr << "Could not open: " << argv[COMMONWORD_ARG] <<".\nReason: " << e.what();
    return false;
  }

  bookFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  //open book file
  try {
    bookFile.open(argv[BOOK_ARG]);
  }
  catch (std::ifstream::failure e) {
    std::cerr << "Could not open: " << argv[BOOK_ARG] <<".\nReason: " << e.what();
    commonWordFile.close();
    return false;
  }
  
  //configure index type
  btype = BookIndexFactory::IndexTypeHash;  
  if (argc == MAX_ARGS) {
    string typeStr(argv[ITYPE_ARG]);
    std::transform(typeStr.begin(), typeStr.end(), typeStr.begin(), ::tolower);
    
    switch (argv[ITYPE_ARG][0]) {
    case 'R':
    case 'r':
      btype = BookIndexFactory::IndexTypeRBTree;
      break;
    case 'T':
    case 't':
      btype = BookIndexFactory::IndexTypeThread;
      break;
    case 'M':
    case 'm':
      btype = BookIndexFactory::IndexTypeMapReduce;
      break;
    case 'H':
    case 'h':
      break;
    default :
      bookFile.close();
      commonWordFile.close();
      return false;
    }  
  }
  return true;
}

//main: returns 0 on SUCCESS
int main(int argc, char *argv[]) {   
  
  std::ifstream commonWordFile;
  std::ifstream bookFile;
  BookIndexFactory::BookIndexType btype; 

  //verify files can be opened and datastruct type is valid
  if (!verifyInput(argc, argv, commonWordFile, bookFile, btype))
    return 1;

  //build common word hashtable
  CommonWordHash *commonWords = new CommonWordHash(commonWordFile);
  //push book into a stringstream
  stringstream bookStream;
  bookStream << bookFile.rdbuf();

  //build and print index.  time how long it takes
  std::clock_t starttime;
  double load_duration, build_duration, print_duration;
  BookIndexFactory bif;
  BookIndex *bookIndex; 

  //BookIndexCreate uses new operator
  bookIndex = bif.BookIndexCreate(btype);

  //Load book data into the index object
  starttime = std::clock();
  if (!bookIndex->LoadBookInfo(commonWords, bookStream)) {
    cerr << "loading book info failed!" << endl;
  }
  load_duration =  std::clock() - starttime;

  //Build the index
  starttime = std::clock();
  if (!bookIndex->buildIndex()) {
    cerr << "building index failed!" << endl;
  }
  build_duration = std::clock() - starttime;

  //Print the index
  starttime = std::clock();
  bookIndex->printIndex();
  print_duration = std::clock() - starttime;

  cout << endl << "Load  Time: " << load_duration       \
       << endl << "Build Time: " << build_duration      \
       << endl << "Print Time: " << print_duration << endl;
  
  //Clean up
  delete(commonWords);
  delete(bookIndex);
  
  return 0;        
}
