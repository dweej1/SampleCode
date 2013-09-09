#ifndef BOOK_INDEX_RBTREE_H_
#define BOOK_INDEX_RBTREE_H_

#include <vector>
#include <string>
#include <sstream>
#include <map>

#include "BookIndex.h"

//RBTree implementation
class BookIndexRBTree : public BookIndex
{
 private:
  std::map <std::string, std::vector<int>> indexTree;  
  bool addToIndex(const std::string &addMe, int pageNum);
  
 public:
  bool buildIndex();
  void printIndex();
};

#endif
