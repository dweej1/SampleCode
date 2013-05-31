#ifndef BOOK_INDEX_H_
#define BOOK_INDEX_H_

#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <unordered_map>

#include "CommonWordHash.h"


//simple base class (should be uninstantiable).
class BookIndex 
{
protected:

typedef std::pair<int, std::string> pagePair;

  CommonWordHash *cwords;
  std::vector<BookIndex::pagePair> byPage;

  bool splitIntoPages(std::stringstream &book);

public:
  //loads protected vars: cwords, byPage
  bool LoadBookInfo(CommonWordHash* cwords, 
                    std::stringstream &book);

  //implemented by derived classes
  virtual bool buildIndex() {return false;}
  virtual void printIndex(void) {}

};

//factory to control creation of Index Generator
class BookIndexFactory
{
public:

enum BookIndexType {IndexTypeHash, IndexTypeRBTree, IndexTypeThread, IndexTypeMapReduce};

BookIndex *BookIndexCreate(BookIndexFactory::BookIndexType btype);
};


//hash table implementation
class BookIndexHash : public BookIndex
{
private:
  std::unordered_map <std::string, std::vector<int>> indexHash;  

public:
  bool buildIndex();
  void printIndex();
};

//RBTree implementation
class BookIndexRBTree : public BookIndex
{
private:
  std::map <std::string, std::vector<int>> indexMap;  

public:
  bool buildIndex();
  void printIndex();
};






//DVP:
//MapReduce: split pages based on cores, hash concurrently, combine hashes
//threads: same thing as above
//move fwd based on results
#endif
