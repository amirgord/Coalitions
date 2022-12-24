#include "Graph.h"

Graph::Graph(vector<Party> vertices, vector<vector<int>> edges) : mVertices(vertices), mEdges(edges), len(vertices.size())
{
}

int Graph::getMandates(int partyId) const
{
    return mVertices[partyId].getMandates();
}

int Graph::getEdgeWeight(int v1, int v2) const
{
    return mEdges[v1][v2];
}

int Graph::getNumVertices() const
{
    return mVertices.size();
}

const Party &Graph::getParty(int partyId) const
{
    return mVertices[partyId];
}

const unsigned int Graph::length() const
{
    return len;
}

void Graph::partyReciveOffer(int pId, int cId)
{
    mVertices[pId].reciveOffer(cId);
}

Party &Graph::getParty(int partyId)
{
    return mVertices[partyId];
}

void Graph::setCoalitionId(int pId,int cId)
{
    mVertices[pId].setCoalitionId(cId);
}