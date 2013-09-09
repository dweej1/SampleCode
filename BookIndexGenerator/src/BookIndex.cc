#include <iostream> 
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

//page text cleanup tool
static inline char formatWords(char c)
{
  return (isalpha(c) ? ::tolower(c) : ' ');
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

    //new pair to insert
    BookIndex::PagePair *newPair = new(BookIndex::PagePair);
    newPair->first = pgnumint;
    newPair->second = bookstr.substr(lastMatchPos, currMatchPos);
    
    //scrub text on page - tolower, remove non alpha
    transform(newPair.second.begin(), newPair.second.end(), 
              newPair.second.begin(), formatWords);    
    
    this->byPage.push_back(newPair);
    
    lastMatchPos = currMatchPos + currMatchLen;
  }
  return true;
}

//constructor when book info has been already loaded
BookIndex::BookIndex(CommonWordHash *cWords, 
                     std::vector<BookIndex::PagePair> *thesePages)
{
  this->cWords = cWords;
  this->byPage = *thesePages;
}


//BookIndex 
//loads & formats data needed to generate index
bool BookIndex::LoadBookInfo(CommonWordHash* cwords, stringstream &book)
{
  this->cWords = cwords;

  return (splitIntoPages(book));
}

