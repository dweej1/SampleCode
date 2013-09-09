#ifndef BOOK_INDEX_FACTORY_H_
#define BOOK_INDEX_FACTORY_H_

#include "BookIndex.h"

//factory to control creation of Index Generator
class BookIndexFactory
{
 public:
  
  enum BookIndexType {IndexTypeHash, IndexTypeRBTree, IndexTypeThread, IndexTypeMapReduce};
  BookIndex *BookIndexCreate(BookIndexFactory::BookIndexType btype);
};

#endif
