#include "Router.h"
#include <fstream>
#include <string>

using namespace std;

// Note we do not use router #0
static int numRouters = 8;

//this function gets neighbouring routers for the routers
void getNeighbours(Router* routers) {
  for (int i = 1; i < numRouters; i++) {
    if (i == 1){
      routers[i].getNeighbour(&routers[i+1], nullptr);
    } else if (i == 7){
      routers[i].getNeighbour(&routers[i-1], nullptr);
    } else {
      routers[i].getNeighbour(&routers[i-1], &routers[i+1]);
    }
  }
}

//Checks to see if the routers have finished getting destination networks
bool finished(Router* routers) {
  for (int i=1; i < numRouters; i++){
    if (routers[i].numNetworks() < numRouters) {
      return false;
    }
  }
  return true;
}

int main() {
  //Print to file
  ofstream outputFile;
  outputFile.open("routingTableOutput.txt");

  // Initialize routers. Not using router 0
  Router* routers = new Router[numRouters];
  for(int i=1; i< numRouters; i++){
    routers[i].initialize(i);
  }
  getNeighbours(routers);

  //Prints initial routing info
  for(int i=1; i< numRouters; i++){
    outputFile << routers[i].printRoutingInfo() << "\n";
  }
  
  int passCounter = 1;

  //While the routing tables are not complete
  while (!finished(routers)){
    outputFile << "Pass number: " << passCounter << endl;
    for (int i=1; i<numRouters; i++){
      routers[i].update();
      outputFile << routers[i].printRoutingInfo() << "\n";
    }
    passCounter = passCounter + 1;
  } 

  outputFile.close();
  return 0;
}