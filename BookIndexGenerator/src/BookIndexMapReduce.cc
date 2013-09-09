
#include <string>
#include <vector>
#include <boost/thread.hpp>
#include "BookIndexMapReduce.h"
#include "BookIndexHash.h"

using namespace std;



bool BookIndexMapReduce::buildIndex(void)
{
  //figure out how many cores
  //split bypage into cores
  unsigned int numCores = boost::thread::hardware_concurrency();
  unsigned int numPages = this->byPage.size();
  unsigned int pagesPerThread = numPages / numCores;  
  std::vector<BookIndex::PagePair*>::iterator startPageIter;
  
  //spawn threads with relevant pieces of this->byPage
  for (unsigned int thisCore = 0; thisCore < (numCores -1); thisCore++) {
    startPageIter = this->byPage.begin() + (numPages / numCores) * thisCore;
    BookIndex *newIndex = new BookIndex(this->cWords, startPageIter, pagesPerThread);
    this->bookSection.push_back(newIndex);
    boost::thread newThread(newIndex.buildIndex());
  }

  //build index for last section of pages
  BookIndex *lastIndex = new BookIndex(this->cWords, startPageIter, -1);
  this->bookSection.push_back(newIndex);
  lastIndex.buildIndex();

  //wait for all threads to complete
  
  
  cout << numCores << endl;
  return true;
}

void BookIndexMapReduce::mergeIndex(void)
{
  for (vector<boost::thread>::iterator it = this->bookSection.begin();
       it != this->bookSection.end(); it++) {
    BookIndex *thisIndex = *it;
    //iterate over thisIndex, insert new hash
    

    delete(thisIndex);
  }
  
}

void BookIndexMapReduce::printIndex(void)
{
  
}
