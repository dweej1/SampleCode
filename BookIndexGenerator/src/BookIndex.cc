#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept> 
#include <algorithm>
#include <cstdlib>
#include <unordered_map>
#include <map>
#include <regex>

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
  regex pageNumRegex ("[\n|\r]\\s*\\d+\\s*[\n|\r]");
  /*regex_iterator<string::iterator> findPageNum (bookstr.begin(), bookstr.end(), pageNumRegex);
  regex_iterator<string::iterator> rEnd; //defaults to end-of-seq
  
  while (findPageNum != rEnd) {

    string tempstr = findPageNum->str();
    string pgnum = tempstr.substr(0,tempstr.length()-1);
    
    if (find_if(pgnum.begin(), pgnum.end(), is_alpha) == pgnum.end()) { 
      int pgnumint = atoi(pgnum.c_str());
      //number by itself
      std::cout << pgnumint << endl;
      //DVP:actually load this->byPage
    }
    ++findPageNum;
    }*/
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

