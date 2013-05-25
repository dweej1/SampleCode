#ifndef BOOK_INDEX_H_
#define BOOK_INDEX_H_

#include <vector>
#include <string>

#include "CommonWordHash.h"

class BookIndex
{
private:
   
  //two versions - red-black tree vs. hash
  //DVP:add r-b tree here
  std::unordered_map <std::string, std::vector<int>> indexHash;
  
  
  CommonWordHash *cwords;
  int curPage;
  

  void ProcessBookLine(std::string &);
  bool AddToIndex(const std::string &);

public:
  
  //constructor
  BookIndex(CommonWordHash*, std::ifstream&);
  
  //output the index
  void printIndex();
  
};

#endif
