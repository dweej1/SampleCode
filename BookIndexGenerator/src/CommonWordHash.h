#ifndef COMMON_WORD_HASH_H_
#define COMMON_WORD_HASH_H_

#include <fstream>
#include <string>
#include <unordered_map>


class CommonWordHash
{
 private:
  std::unordered_map <std::string, bool> commonHash;

 public:
  
  CommonWordHash(std::ifstream&);
  
  bool isCommonWord(const std::string&);
};
  
#endif
 
//DVP: write a version with global hash and
//     worker threads that acquire a lock on each hash entry

