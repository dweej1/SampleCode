#ifndef BOOK_INDEX_H_
#define BOOK_INDEX_H_

#include <vector>
#include <string>
#include <sstream>

#include "CommonWordHash.h"


//simple uninstantiable base class 
//handles book text scrubbing and page num identification
class BookIndex 
{
 protected:

  typedef std::pair<int, std::string> PagePair;
  typedef std::pair<std::string, std::vector<int>> IndexPair;
  
  CommonWordHash *cWords;
  std::vector<BookIndex::PagePair*> byPage;
  
  bool splitIntoPages(std::stringstream &book);
  
 public:
  //constructor used when book is already Loaded
  BookIndex(CommonWordHash *cWords, std::vector<BookIndex::PagePair> *thesePages);
  //loads protected vars: cwords, byPage
  bool LoadBookInfo(CommonWordHash* cwords, 
                    std::stringstream &book);
  
  
  //implemented by derived classes
  virtual bool buildIndex() = 0;
  virtual void printIndex(void) = 0;
  virtual bool mergeIndex(BookIndex *mergeMe) {return false;}
};


//DVP:
//MapReduce: split pages based on cores, hash concurrently, combine hashes
//threads: same thing as above
//move fwd based on results
#endif
