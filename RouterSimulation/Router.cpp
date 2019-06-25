#include "Router.h"
#include <string>

using namespace std;

//Constructor with bucket size n
Router::Router() {
  routeNum = 0;
}

//Set up the networks on the given router
void Router::initialize(int n) {
  name = n;
  routeNum = 2;
  for (int i=0; i < routeNum; i++){
    routingTable[i][0] = "N" + to_string(n + i);
    routingTable[i][1] = "";
    routingTable[i][2] = "0";
  }
  return;
}

//Add neighbouring routers
void Router::getNeighbour(Router* nb1, Router* nb2){
  neighbour1 = nb1;
  if (name != 1 && name != 7) {
    neighbour2 = nb2;
  }
  return;
}

//Returns the number of destination networks the given router knows
int Router::numNetworks(){
  return routeNum;
}

//Returns the Router number (which will be the name of the Router (ie. the number in "R1"))
int Router::routerNum(){
  return name;
}

//Updates router's routing table
void Router::update() {
  for (int i=0; i < neighbour1->numNetworks(); i++) {
    if (!contains(neighbour1->routingTable[i][0])) {
      routingTable[routeNum][0] = neighbour1->routingTable[i][0];
      routingTable[routeNum][1] = "R" + to_string(neighbour1->routerNum());
      routingTable[routeNum][2] = to_string(stoi(neighbour1->routingTable[i][2]) + 1);
      routeNum = routeNum + 1;
    }
  }
  //if router has 2 neighbours
  if (name != 1 && name != 7){
    for (int i=0; i < neighbour2->numNetworks(); i++) {
      if (!contains(neighbour2->routingTable[i][0])) {
        routingTable[routeNum][0] = neighbour2->routingTable[i][0];
        routingTable[routeNum][1] = "R" + to_string(neighbour2->routerNum());
        routingTable[routeNum][2] = to_string(stoi(neighbour2->routingTable[i][2]) + 1);
        routeNum = routeNum + 1;
      }
    }
  }
  return;
}

//number of destination routers known in routing table
bool Router::contains(string network){
  for (int i=0; i < routeNum; i++) {
    if (routingTable[i][0] == network) {
      return true;
    }
  }
  return false;
}

//Returns router information of given networks 
string Router::printRoutingInfo() {
  string output = "Router R" + to_string(name) + ":\n";
  for (int i = 0; i < routeNum; i++){
    output.append("Destination Network: " + routingTable[i][0] + "\t Next Router: ");
    if (routingTable[i][1].empty()) {
      output.append("*");
    } else {
      output.append(routingTable[i][1]);
    }
    output.append("\t Number of Hops: " + routingTable[i][2] + "\n");
  }
  return output;
}