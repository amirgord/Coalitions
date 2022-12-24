#pragma once

#include <vector>

#include "Graph.h"
#include "Agent.h"
#include "Coalition.h"
#include "Party.h"

using std::string;
using std::vector;

class Simulation
{
public:
    Simulation(Graph g, vector<Agent> agents);

    void step();
    bool shouldTerminate() const;

    const Graph &getGraph() const;
    Graph &getGraph();
    const vector<Agent> &getAgents() const;
    const Party &getParty(int partyId) const;
    Party &getParty(int partyId);

    void cloneAgent(int agentIdToClone, int partyId);
    Coalition &getCoaliotion(int coalitionId);
    const vector<vector<int>> getPartiesByCoalitions() const;


private:
    Graph mGraph;
    vector<Agent> mAgents;
    vector<Coalition> coalitions;

};
