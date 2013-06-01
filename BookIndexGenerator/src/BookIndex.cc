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
  int currMatchPos = 0, currMatchLen = 0, lastMatchPos = 0;
  
  //while (findPageNum != rEnd) 
  for (; findPageNum != rEnd; ++findPageNum) {
    boost::match_results<string::const_iterator> &currMatch= *findPageNum;
    currMatchPos = currMatch.position(0);
    string matchStr = currMatch.str();
    currMatchLen = matchStr.length();    
    string pgnum = matchStr.substr(0,currMatchLen-1);
    int pgnumint = atoi(pgnum.c_str());    
    
    BookIndex::PagePair newPair;
    newPair.first = pgnumint;
    newPair.second = bookstr.substr(lastMatchPos, currMatchPos);
    this->byPage.push_back(newPair);

    lastMatchPos = currMatchPos + currMatchLen;
    }

  for (vector<BookIndex::PagePair>::const_iterator it = this->byPage.begin();
       it != this->byPage.end(); ++it) {
    cout << "-------------------PAGE " << it->first << "-------------------" << endl;
    cout << it->second << endl;
  }
  return true;
}


//BookIndex 
//loads & formats data needed to generate index
bool BookIndex::LoadBookInfo(CommonWordHash* cwords, stringstream &book)
{
  this->cwords = cwords;

  return (splitIntoPages(book));
}


//BookIndexHash
bool BookIndexHash::buildIndex(void)
{
  return true;
}

void BookIndexHash::printIndex(void)
{

}


//BookIndexMap
bool BookIndexRBTree::buildIndex(void)
{
  return true;  
}

void BookIndexRBTree::printIndex(void)
{

}

