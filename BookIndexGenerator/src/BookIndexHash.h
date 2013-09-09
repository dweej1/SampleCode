#ifndef BOOK_INDEX_HASH_H_
#define BOOK_INDEX_HASH_H_

#include <vector>
#include <string>
#include <boost/unordered_map.hpp>
#include "BookIndex.h"

//hash table book index
class BookIndexHash : public BookIndex
{
public:
  typedef boost::unordered_map <std::string, std::vector<int>> indexHashType;
  //constructor when used by another BookIndex generator
  BookIndexHash(CommonWordHash *cWords, std::vector<BookIndex::PagePair> *thesePages);
  //when result data structure is needed for further processing
  indexHashType *getIndexHash(void);
  
  bool buildIndex();
  void printIndex();

 private:
  indexHashType indexHash;  
  bool addToIndex(const std::string &addMe, int pageNum);

};

#endif
