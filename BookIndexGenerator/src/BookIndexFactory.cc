
#include "BookIndexFactory.h"
#include "BookIndexHash.h"
#include "BookIndexRBTree.h"
#include "BookIndexMapReduce.h"

// to determine index generator type
BookIndex *BookIndexFactory::BookIndexCreate(BookIndexType btype)
{
  BookIndex *newIndex;
  switch (btype) {
  case (BookIndexFactory::IndexTypeHash): 
    newIndex = new BookIndexHash();
    break;
  case (BookIndexFactory::IndexTypeRBTree):
    newIndex = new BookIndexRBTree();
    break;
  case (BookIndexFactory::IndexTypeMapReduce):
    newIndex = new BookIndexMapReduce();
    break;
  default: //DVP: default to hashtype
    newIndex = new BookIndexHash();    
    break;
  };

  return (newIndex);
}
