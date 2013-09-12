Problem Statement:

1. Write a backend library for auction house for their online auction system so it supports the following operations( assume that we have a in memory key-value store lib available)

Add an item that can be auctioned. An item has a name and reserved price
Start an auction on an item
Submit a bid to a normal auction, a bid has the bidder's number and a price, a new bid has to have a price higher than the current highest bid otherwise it's not allowed
Call the normal auction - bring it to an end. If the current highest bid is higher than the reserved price of the item, the auction is deemed as a success other wise it's marked as failure. The item sold should be no longer available for future auctions
Query an auction - the system returns the status of a specified auction: if it's a success and if so who's the winner.

Solution:

First let's define a clean API:

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


This implies a specific data model.

-The "key" will be the auction item's name

Here are the data points associated with a unique key:

-double reservePrice (defined when entry is initialized)
-bool auctionStarted (has this auction started)
-int highbidderNum (unique identifier of the highest bidder)
-double highBidPrice (highest bidder's bid price)
-bool auctionEnded (has this auction ended)



