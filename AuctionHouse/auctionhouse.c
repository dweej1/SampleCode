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

//error codes for more descriptive return values
typedef enum
{
  AUCTION_ERR_KEY = 0,
  AUCTION_SUCCESS,
  AUCTION_ERR_DATASTORE,
  AUCTION_ERR_LOWBID, //not sure if this is an error or not
  AUCTION_ERR_ENDED,
  AUCTION_ERR_STARTED,
  AUCTION_ERR_INPUT_NULL,
} auctionErrorCode;

//~~~~End of Auction House Data Model



//~~~~Auction House API
/*
-Add an item that can be auctioned. An item has a name and reserved price
auctionErrorCode addAuctionItem(const char *name, double reservePrice)

-Start an auction on an item
auctionErrorCode startAuction(const char *name)

-Submit a bid to a normal auction, a bid has the bidder's number and a price, a new bid has to have a price higher than the current highest bid otherwise it's not allowed
auctionErrorCode submitBidToAuction(int bidderNum, double bidderPrice, const char *auctionItemName)

-Call the normal auction - bring it to an end. If the current highest bid is higher than the reserved price of the item, the auction is deemed as a success other wise it's marked as failure. The item sold should be no longer available for future auctions
auctionErrorCode endAuction(const char *auctionItemName)

Query an auction - the system returns the status of a specified auction: if it's a success and if so who's the winner.
auctionErrorCode queryAuction(const char *auctionItemName, int *winningBidder)
*/


//Add an item that can be auctioned. An item has a name and reserve price
auctionErrorCode addAuctionItem(const char *name, double reservePrice)
{
  auctionData *thisAuction;

  if (!addKey(name)) {
    return AUCTION_ERR_KEY; //key may already exist, or may be "bad"
  }

  thisAuction = keyLookup(name);

  if (thisAuction == NULL) {
    return AUCTION_ERR_DATASTORE; //datastore invariant broken
  }

  thisAuction->reservePrice = reservePrice;

  return AUCTION_SUCCESS;
}

//Start an auction on an item
auctionErrorCode startAuction(const char *name)
{
  auctionData *thisAuction = keyLookup(name);

  if (thisAuction == NULL) {
    return AUCTION_ERR_KEY; 
  }

  if (thisAuction->auctionStarted) {
    return AUCTION_ERR_STARTED;
  }

  if (thisAuction->auctionEnded) {
    return AUCTION_ERR_ENDED;
  }

  thisAuction->auctionStarted = true;

  return AUCTION_SUCCESS;
}

//Submit a bid to a normal auction, a bid has the bidder's number
// and a price, a new bid has to have a price higher than the 
//current highest bid otherwise it's not allowed
auctionErrorCode submitBidToAuction(int bidderNum, double bidderPrice, const char *auctionItemName)
{
  auctionData *thisAuction = keyLookup(auctionItemName);

  if (thisAuction == NULL) {
    return AUCTION_ERR_KEY; 
  }

  if (thisAuction->auctionStarted == false) {
    return AUCTION_ERR_STARTED;
  }

  if (thisAuction->auctionEnded == true) {
    return AUCTION_ERR_ENDED;
  }
  
  if (thisAuction->highBidPrice > bidderPrice) {
    return AUCTION_ERR_LOWBID;
  }

  thisAuction->highBidNum = bidderNum;
  thisAuction->highBidPrice = bidderPrice;

  return AUCTION_SUCCESS;
}

//Call the normal auction - bring it to an end. If the current highest
//bid is higher than the reserved price of the item, the auction is 
//deemed as a success other wise it's marked as failure. The item sold 
//should be no longer available for future auctions
auctionErrorCode endAuction(const char *auctionItemName)
{
  auctionData *thisAuction = keyLookup(auctionItemName);

  if (thisAuction == NULL) {
    return AUCTION_ERR_KEY; 
  }

  if (thisAuction->auctionStarted == false) {
    return AUCTION_ERR_STARTED;
  }
  
  thisAuction->auctionEnded = true;
  thisAuction->itemSold = (thisAuction->reservePrice < thisAuction->highBidPrice);

  return AUCTION_SUCCESS;
}

//Query an auction - the system returns the status of a specified
//auction: if it's a success and if so who's the winner.
auctionErrorCode queryAuction(const char *auctionItemName, bool *itemSold, int *winningBidder)
{
  auctionData *thisAuction;

  if ((winningBidder == NULL) || (itemSold == NULL)) {
    return AUCTION_ERR_INPUT_NULL;
  }

  thisAuction = keylookup(auctionItemName);

  if (thisAuction == NULL) {
    return AUCTION_ERR_KEY;
  }

  //update return values with stored data
  *itemSold = thisAuction->itemSold;
  *winningBidder = thisAuction->highBidNum;

  return AUCTION_SUCCESS;
}

//~~~~Auction House API



int main()
{
  return 0;
}
