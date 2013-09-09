#include <iostream> 
#include <map>

#include "BookIndexRBTree.h"

using namespace std;

//BookIndexRBTree
bool BookIndexRBTree::addToIndex(const std::string &addMe, int pageNum)
{
  map<string,vector<int>>::iterator 
    got = this->indexTree.find(addMe);

  if (got != this->indexTree.end()) {
    vector<int> *currPages = &(got->second);
    if (currPages->back() == pageNum) { //duplicate
      return false;
    }
    else { //add pageNum to vector
      currPages->push_back(pageNum);
      return true;
    }
  }
  //new entry
  vector<int> pageNums;
  pageNums.push_back(pageNum);
  BookIndex::IndexPair addPair(addMe, pageNums);
  this->indexTree.insert(addPair);
  return true;
}

bool BookIndexRBTree::buildIndex(void)
{
  for (vector<BookIndex::PagePair>::const_iterator it = this->byPage.begin();
       it != this->byPage.end(); ++it) {
    stringstream pageStream(it->second);
    string currToken;
    
    while(pageStream >> currToken) {
      if (!(this->cWords->isCommonWord(currToken))) { //add to hash
        addToIndex(currToken, it->first);
      }
    }
    
  }
  
  return true;  
}

void BookIndexRBTree::printIndex(void)
{
  ///iterate over tree and print
  for(map<string, vector<int>>::iterator iter = this->indexTree.begin(); 
      iter != this->indexTree.end(); iter++) {
    cout << iter->first << " ";
    vector<int> *pages = &(iter->second);
    for (vector<int>::iterator it = pages->begin(); 
         it != pages->end(); it++) {
      cout << *it;
      if ((it+1) != pages->end())
        cout << ", ";
    }
    cout << endl;
  }

}
