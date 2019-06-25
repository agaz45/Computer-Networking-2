#ifndef Router_H_INCLUDED
#define Router_H_INCLUDED

#include <string>

using namespace std;

class Router {
public:   
	//routingTable consists of 8 networks (uninitialized at first)
	//routingTable[*][0] is the destination network (ie. "N1")
	//routingTable[*][1] is the next router in process. "" if network is attached to given router
	//routingTable[*][2] is the number of hops to given network 
	string routingTable[8][3];

	// Construct a new Router
	Router();

	//Set up the networks on the given router
	void initialize(int n);

	//Add neighbouring routers
	void getNeighbour(Router* nb1, Router* nb2);

	//Returns the number of destination networks the given router knows
	int numNetworks();

	//Returns the Router number (which will be the name of the Router (ie. the number in "R1"))
	int routerNum();

	//Updates router's routing table
	void update();

	//Returns router information of given networks 
	string printRoutingInfo();

private:
	//Name of router (ie. "1" which will translate to "R1")
	int name;

	Router* neighbour1;
	Router* neighbour2;

	//number of destination routers known in routing table
	int routeNum;

	//Checks to see if destination network is already in routingTable
	bool contains(string network);
};
#endif //ROUTER_H_INCLUDED
