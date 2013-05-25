#include <iostream> 
#include <fstream>

#include "CommonWordHash.h"


using namespace std;

//build hash table for lookup
//DVP:throw exceptions?
CommonWordHash::CommonWordHash (std::ifstream &commonWordStream)
{
  if (!commonWordStream.is_open()) {
    std::cerr << "commonword txt file closed!\n" << std::endl;
    return;
  }


 commonWordStream.exceptions(std::ifstream::badbit);
  string wordBuf;
  while (getline (commonWordStream, wordBuf)) {
    cout << wordBuf << endl;
    std::pair<std::string,bool> addMe (wordBuf, true);
    this->commonHash.insert(addMe);
    
  }
  
  cout << "done loading commonword hash!" << endl;

}


bool CommonWordHash::isCommonWord(const std::string &checkMe)
{
  unordered_map<string,bool>::const_iterator 
    got = this->commonHash.find(checkMe);

  return (got != this->commonHash.end());

}
