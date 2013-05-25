#include <iostream> 
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept> 
#include <algorithm>
#include <cstdlib>
#include <unordered_map>
#include <map>

#include "BookIndex.h"

using namespace std;

static inline bool is_not_alpha(char c)
{
  return (!isalpha(c));
}

static inline bool is_alpha(char c)
{
  return (isalpha(c));
}


bool BookIndex::AddToIndex(const std::string &addMe)
{
  unordered_map<string,vector<int>>::iterator 
    got = this->indexHash.find(addMe);

  if (got != this->indexHash.end()) {
    vector<int> *currPages = &(got->second);
    
    if (currPages->back() == this->curPage) {
      //cerr << "multiple on same page!" << addMe << endl;
      return false;
    }
    else if (currPages->back() > this->curPage) {
      cerr << "outoforderpagenum:" <<  this->curPage << endl;
      return false;
    }
    else {
      currPages->push_back(this->curPage);
      //cout << "+ " << got->first << ": " << this->curPage << endl;  
      return true;
    }
  } 
  else {
    vector<int> pnums;
    pnums.push_back(this->curPage);

    pair<string, vector<int>> addPair (addMe, pnums);
    
    this->indexHash.insert(addPair);
    //cout << "# " << addPair.first << ": " << pnums.front() <<endl;
    return true;
  }
}
  

//tokenize based on space
//if only one token (a number), update curpage
//drop non-alpha strings (123, :, %, etc)
//lowercase
//if (!commonword) insert into index
void BookIndex::ProcessBookLine(string &thisLine)
{
  stringstream lineStream(thisLine);

  vector<string> tokens;
  string temp;

  while(lineStream >> temp) {
    tokens.push_back(temp);
    //std::cout << "Token(" << token << ")\n";
  }
  if (tokens.size() == 0) return;
  
  if (tokens.size() == 1) {
    try {      
      string foo = tokens.front();
      int pagenum = 0;

      if (find_if(foo.begin(), foo.end(), is_alpha) == foo.end()) {
        pagenum = atoi(foo.c_str());
        
        if (this->curPage >= pagenum){
          cerr << "out-of-order: " <<  pagenum << \
            ", " << this->curPage << endl;
        } 
        else if (this->curPage + 20 < pagenum) {
          //sanity check for bad pagenum
              cerr << "too big jump: " <<  pagenum << \
                ", " << this->curPage << endl;      
        }
        else {
          //set new pagenum
          this->curPage = pagenum;
          //cout << "currPage: " << this->curPage << endl;
          return;
        }
      }
    } 
    catch (std::exception e) {
      cerr << "pagenumerr: "  << endl;
    }
  }
  
  for(vector<string>::iterator it = tokens.begin(); it != tokens.end(); ++it) {
    string foo = *it;
    if (find_if(foo.begin(), foo.end(), is_not_alpha) == foo.end()) {
      if (!(this->cwords->isCommonWord(foo))) {
        transform(foo.begin(), foo.end(), foo.begin(), ::tolower);
        AddToIndex(foo);
      }
    }
  }
  
}
 


BookIndex::BookIndex(CommonWordHash *cwords, std::ifstream &book)
{
  if (!book.is_open()) {
    std::cerr << "book file closed!\n" << std::endl;
    return;
  }

  this->cwords = cwords;
  this->curPage = 1;

  book.exceptions(std::ifstream::badbit);
  string oneBookLine;

  while (getline (book, oneBookLine)) {
    //cout << oneBookLine << endl;
    ProcessBookLine(oneBookLine);
  }
  
  cout << "book index loaded!" << endl;
  
  //printIndex();
}

void BookIndex::printIndex(void)
{
  /*for(unordered_map<string, vector<int>>::iterator iter = this->indexHash.begin(); 
      iter != this->indexHash.end(); iter++) {
    cout << iter->first << " ";
    vector<int>pages = iter->second;
    for (vector<int>::iterator it = pages.begin(); 
         it != pages.end(); it++) {
      cout << *it;
      if ((it+1) != pages.end())
        cout << ", ";
    }
    cout << endl;
    }*/

  //ordered print
  
  map<string, vector<int>> ordered(this->indexHash.begin(), this->indexHash.end());

  for(map<string, vector<int>>::iterator iter = ordered.begin(); 
      iter != ordered.end(); iter++) {
    cout << iter->first << " ";
    vector<int> *pages = &(iter->second);
    if (pages->size() < 20) {
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


