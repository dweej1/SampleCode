#include <iostream> 
#include <fstream>
#include <algorithm>

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
  try {
    string wordBuf;
    while (getline (commonWordStream, wordBuf)) {
      transform(wordBuf.begin(), wordBuf.end(), wordBuf.begin(), ::tolower);        
      
      std::pair<std::string,bool> addMe (wordBuf, true);
      this->commonHash.insert(addMe);
    }
  }
  catch (std::ifstream::failure e) {
    std::cerr << "Error reading commonword file" << endl << "Reason: " << e.what() << endl;
  }
}


bool CommonWordHash::isCommonWord(const std::string &checkMe)
{
  unordered_map<string,bool>::const_iterator 
    got = this->commonHash.find(checkMe);

  return (got != this->commonHash.end());

}
