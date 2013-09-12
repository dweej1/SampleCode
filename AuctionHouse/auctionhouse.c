#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>


//~~~~Auction House Data Model (for testing purposes)

typedef struct _auctionData  auctionData;

struct _auctionData {
  double reservePrice;
  bool auctionStarted;
  int highBidNum;
  double highBidPrice;
  bool auctionEnded;
  bool itemSold;
};


//this can be any key/value datastore. 
//defining this for the purposes of the exercise

//returns ptr to the existing auctionData entry, or NULL if not found.
//Will handle the case where "auctionKey" is NULL.
auctionData *keyLookup(const char *auctionKey)
{
  return NULL;
}

//creates a new key/value entry, where key=auctionKey and value is
//blank.  Returns false if key exists, or some other error (out of
//memory, datastore unavailable, etc)
bool addKey(const char *auctionKey)
{
  return true;
}

//~~~~End of Auction House Data Model



//~~~~Auction House API
/*
-Add an item that can be auctioned. An item has a name and reserved price
bool addAuctionItem(const char *name, double reservePrice)

-Start an auction on an item
bool startAuction(const char *name)

-Submit a bid to a normal auction, a bid has the bidder's number and a price, a new bid has to have a price higher than the current highest bid otherwise it's not allowed
bool submitBidToAuction(int bidderNum, double bidderPrice, const char *auctionItemName)

-Call the normal auction - bring it to an end. If the current highest bid is higher than the reserved price of the item, the auction is deemed as a success other wise it's marked as failure. The item sold should be no longer available for future auctions
bool endAuction(const char *auctionItemName)

Query an auction - the system returns the status of a specified auction: if it's a success and if so who's the winner.
bool queryAuction(const char *auctionItemName, int *winningBidder)
*/


//Add an item that can be auctioned. An item has a name and reserve price
bool addAuctionItem(const char *name, double reservePrice)
{
  auctionData *thisAuction;

  if (!addKey(name))
    return false; //key may already exist

  thisAuction = keyLookup(name);

  if (thisAuction == NULL) {
    return false; //this should be an exception because the datastore broke
  }

  thisAuction->reservePrice = reservePrice;

  return true;
}

//Start an auction on an item
bool startAuction(const char *name)
{
  auctionData *thisAuction = keyLookup(name);

  if (thisAuction == NULL) {
    return false; //maybe have errorcodes for more granular failure
                  //information
  }

  if (thisAuction->auctionStarted) {
    return false;
  }

  if (thisAuction->auctionEnded) {
    return false;
  }

  thisAuction->auctionStarted = true;

  return true;
}

//Submit a bid to a normal auction, a bid has the bidder's number
// and a price, a new bid has to have a price higher than the 
//current highest bid otherwise it's not allowed
bool submitBidToAuction(int bidderNum, double bidderPrice, const char *auctionItemName)
{
  auctionData *thisAuction = keyLookup(auctionItemName);

  if (thisAuction == NULL) {
    return false; 
  }

  if ((thisAuction->auctionStarted == false) || (thisAuction->auctionEnded == true)) {
    return false;
  }
  
  if (thisAuction->highBidPrice > bidderPrice) {
    return false;
  }

  thisAuction->highBidNum = bidderNum;
  thisAuction->highBidPrice = bidderPrice;
}

//Call the normal auction - bring it to an end. If the current highest
//bid is higher than the reserved price of the item, the auction is 
//deemed as a success other wise it's marked as failure. The item sold 
//should be no longer available for future auctions
bool endAuction(const char *auctionItemName)
{
  auctionData *thisAuction = keyLookup(auctionItemName);

  if (thisAuction == NULL) {
    return false; 
  }

  if (thisAuction->auctionStarted == false) {
    return false;
  }
  
  thisAuction->auctionEnded = true;
  thisAuction->itemSold = (thisAuction->reservePrice < thisAuction->highBidPrice);

}

//Query an auction - the system returns the status of a specified
//auction: if it's a success and if so who's the winner.
bool queryAuction(const char *auctionItemName, bool *itemSold, int *winningBidder)
{
  auctionData *thisAuction = keyLookup(auctionItemName);

  if ((thisAuction == NULL) || (winningBidder == NULL) ||
      (itemSold == NULL)) {
    return false; 
  }

  *itemSold = thisAuction->itemSold;
  *winningBidder = thisAuction->highBidNum;

  return true;
}

//~~~~Auction House API



int main()
{
  return 0;
}
