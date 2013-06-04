#include <iostream> 
#include <fstream>
#include <algorithm>
#include <ctime>

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
  
  clock_t loadStart = std::clock();
  
  commonWordStream.exceptions(std::ifstream::badbit);
  string wordBuf;
  while (getline (commonWordStream, wordBuf)) {
    transform(wordBuf.begin(), wordBuf.end(), wordBuf.begin(), ::tolower);        
    std::pair<std::string,bool> addMe (wordBuf, true);
    this->commonHash.insert(addMe);
  }
  
  cout << "commonword hash load time: " << (std::clock() - loadStart) << endl;
}


bool CommonWordHash::isCommonWord(const std::string &checkMe)
{
  unordered_map<string,bool>::const_iterator 
    got = this->commonHash.find(checkMe);

  return (got != this->commonHash.end());

}
