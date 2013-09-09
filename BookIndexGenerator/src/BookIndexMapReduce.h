
#include <vector>
#include <boost/thread.hpp>

#include "BookIndex.h"
#include "BookIndexHash.h"


class BookIndexMapReduce : public BookIndex {
  
 private:
  std::vector <BookIndex *> bookSection;
  void mergeIndex();

 public:
  bool buildIndex();
  void printIndex();
  bool mergeIndex(BuildIndexHash *);
};

