#pragma once
#include <vector>
#include "Party.h"

using std::vector;

class Graph
{
public:
    Graph(vector<Party> vertices, vector<vector<int>> edges);
    int getMandates(int partyId) const;
    int getEdgeWeight(int v1, int v2) const;
    int getNumVertices() const;
    const Party &getParty(int partyId) const;
    const unsigned int length() const;
    void partyReciveOffer(int pId, int cId);
    Party &getParty(int partyId);
    void setCoalitionId(int pId,int cId);




private:
    vector<Party> mVertices;
    vector<vector<int>> mEdges;
    int len;
};
