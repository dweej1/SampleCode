#include <stdio>

//Problem Thoughts:
/*
  -2 graphs: friendGraph(bidirectional) sentIntroGraph (directional)
  -friendGraph: edge where friendship existds
  -sentIntroGraph edge where intro was sent [sendRow] -> [receiveCol] 
  -retweets are directional (bottom half triangle of arraygraph)
  -compute initial friendgraph
  -add retweets until graph is complete
  
  1)concat actual start:end times for each rabbit

  2)construct initial friend graph:
    -sort based on end time (earliest to latest)
    -foreach endtime[i], if starttime[other] < starttime[i], i and
    other are friends.  Add both directions

  3)if graph is not connected (no MST exists), return -1

  directed graph A: retweet recipients (this stays unchanged)
  directed graph B: 
  
  4)Figure out retweets:
    loop until complete source graph (bottom half of triangle is all filled):
    -sort nodes by # of sources (most to least retweet options)
    -retweet node that will add most new directed edges to graph
    -add new sources (bottom triangle in arraygraph datastruct) to all
    recipients of that source
    

 */


int main(int argc, char *argv[])
{

  
  return 0;
}
