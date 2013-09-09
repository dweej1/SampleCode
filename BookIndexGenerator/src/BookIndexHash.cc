#include <iostream>
#include <boost/unordered_map.hpp>

#include "BookIndexHash.h"

using namespace std;

bool BookIndexHash::addToIndex(const std::string &addMe, int pageNum)
{
  boost::unordered_map<string,vector<int>>::iterator 
    got = this->indexHash.find(addMe);

  if (got != this->indexHash.end()) {
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
  this->indexHash.insert(addPair);
  return true;
}

indexHashType *BookIndexHash::getIndexHash(void)
{
  return (&(this->indexHash));
]

bool BookIndexHash::buildIndex(void)
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

void BookIndexHash::printIndex(void)
{
  //build tree from hash
  map<string, vector<int>> ordered(this->indexHash.begin(), this->indexHash.end());
  ///iterate over tree and print
  for(map<string, vector<int>>::iterator iter = ordered.begin(); 
      iter != ordered.end(); iter++) {
    cout << iter->first << " ";
    vector<int> *pages = &(iter->second);
    if (pages->size() < 50) {
      for (vector<int>::iterator it = pages->begin(); 
           it != pages->end(); it++) {
        cout << *it;
        if ((it+1) != pages->end())
          cout << ", ";
      }
      cout << endl;
    }
  }  
}

