#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept> 
#include <algorithm>
#include <cstdlib>
#include <unordered_map>
#include <map>
#include <boost/regex.hpp>
#include <boost/thread.hpp>

#include "BookIndex.h"

using namespace std;

//page number search tool
//
static inline bool is_not_alpha(char c)
{
  return (!isalpha(c));
}

static inline bool is_alpha(char c)
{
  return (isalpha(c));
}


// Factory to determine index builder type
//
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
    //newIndex = new BookIndexMapReduce();
    break;
  case (BookIndexFactory::IndexTypeThread): 
    //newIndex = new BookIndexThread();
    break;
  default: //DVP: default to hashtype
    newIndex = new BookIndexHash();    
    break;
  };

  return (newIndex);
}


  
//BookIndex
//loads byPage class variable with book contents
bool BookIndex::splitIntoPages(stringstream &book)
{
  //newline,any number of whitespaces, 1 or more digits, any amt of
  //whitespace, newline
  string bookstr(book.str()); //DVP:revisit, wasted extra copy?
  boost::regex pageNumRegex("[\n|\r]\\s*\\d+\\s*[\n|\r]");
  boost::regex_iterator<string::iterator> findPageNum (bookstr.begin(), bookstr.end(), pageNumRegex);
  boost::regex_iterator<string::iterator> rEnd; //defaults to end-of-seq
  unsigned int currMatchPos = 0, currMatchLen = 0, lastMatchPos = 0;
  
  for (; findPageNum != rEnd; ++findPageNum) {
    currMatchPos = findPageNum->position();
    string matchStr = findPageNum->str();
    currMatchLen = matchStr.length();    
    string pgnum = matchStr.substr(0,currMatchLen-1);
    int pgnumint = atoi(pgnum.c_str());    
    
    BookIndex::PagePair newPair;
    newPair.first = pgnumint;
    newPair.second = bookstr.substr(lastMatchPos, currMatchPos);
    this->byPage.push_back(newPair);

    lastMatchPos = currMatchPos + currMatchLen;
    }

  /*for (vector<BookIndex::PagePair>::const_iterator it = this->byPage.begin();
       it != this->byPage.end(); ++it) {
    cout << "-------------------PAGE " << it->first << "-------------------" << endl;
    cout << it->second << endl;
    }*/
  return true;
}


//BookIndex 
//loads & formats data needed to generate index
bool BookIndex::LoadBookInfo(CommonWordHash* cwords, stringstream &book)
{
  this->cWords = cwords;

  return (splitIntoPages(book));
}


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


//BookIndexHash
bool BookIndexHash::buildIndex(void)
{
  for (vector<BookIndex::PagePair>::const_iterator it = this->byPage.begin();
       it != this->byPage.end(); ++it) {
    
    stringstream pageStream(it->second);
    string currToken;
    
    while(pageStream >> currToken) {
      //
      transform(currToken.begin(), currToken.end(), currToken.begin(), ::tolower);    
      currToken.erase(remove_if(currToken.begin(), currToken.end(), is_not_alpha), 
                      currToken.end());
      
      if (!(this->cWords->isCommonWord(currToken))) { //add to hash
        addToIndex(currToken, it->first);
      }
    }
    
  }    
  
  return true;
}

void BookIndexHash::printIndex(void)
{
  //build ordered tree
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
      //
      transform(currToken.begin(), currToken.end(), currToken.begin(), ::tolower);    
      currToken.erase(remove_if(currToken.begin(), currToken.end(), is_not_alpha), 
                      currToken.end());
      
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
    cout << iter->first << "-";
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

