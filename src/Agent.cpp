// to delete
#include <iostream>
#include <algorithm>
// 

#include "../include/Agent.h"
#include "../include/Simulation.h"
#include "../include/SelectionPolicy.h"


Agent::Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy) : mAgentId(agentId), mPartyId(partyId), mSelectionPolicy(selectionPolicy),toOffer() ,coalitionId(agentId)
{
}

int Agent::getId() const
{
    return mAgentId;
}

int Agent::getPartyId() const
{
    return mPartyId;
}

std::string Agent::getSelectionPolicy() const
{
    return mSelectionPolicy->getPolicy();
}

int Agent::getCoalitionId()
{
    return coalitionId;
}


void Agent::step(Simulation &sim)
{
    

    Graph &g = sim.getGraph();

    // get prefrences vector
    if (toOffer.empty()){

        // set vector build of vectors each look like {party index, value = mandates/edge}
        // fill all paties in the graph with thier value according to thier policy (M/E weight) 
        // sort after all parties where added

        if ((*mSelectionPolicy).getPolicy() == "E"){
            for(int i = 0; i < g.getNumVertices();i++){
                if(g.getEdgeWeight(mPartyId,i) != 0){
                    toOffer.push_back(vector<int>{i,g.getEdgeWeight(mPartyId,i)});
                    }
                }
        }
        else{ //case 'M' policy
            for(int i = 0; i < g.getNumVertices();i++){
                if(g.getEdgeWeight(mPartyId,i) != 0){
                    toOffer.push_back(vector<int>{i,g.getMandates(i)});
                    }
                }

            }

        // sort the offers according to the policy
        std::sort(toOffer.begin(), toOffer.end(), compareVector);
        }
        
    // send offer to the party that first in the offers vector and
    // still not in a coalition and hasn't got offer from the agent
    // coalition alrdeay
    bool added = false;
    for (unsigned int i = 0; i < toOffer.size() && !added; i++)
    {
        Party &p = g.getParty(toOffer[i][0]);
        if (p.hasOfferFrom(coalitionId) == false && p.getCoalitionId() == -1){

            g.partyReciveOffer(toOffer[i][0],coalitionId);
            added = true;
        }
    }
    
}

// compare vector first according to value (M/E)
// if value is the same take the one with smaller index
bool compareVector(vector<int> v1,vector<int> v2)
{   
    if(v1[1] > v2[1])return true;
    if (v1[1] == v2[1])
    {
        return v1[0] < v2[0];
    }
    return false;
    
}

void Agent::setCoalitionId(int cId){
    coalitionId = cId;
}


// -------------Rule of 5-------------

// Destructor
Agent::~Agent()
{
    if(mSelectionPolicy) delete mSelectionPolicy;
    mSelectionPolicy = nullptr;
}

// Copy Assignment Operator
Agent& Agent::operator=(const Agent& other)
{
    if (this != &other)
    {
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mSelectionPolicy = other.mSelectionPolicy;
        toOffer.clear();
        for(unsigned int i=0; i<other.toOffer.size(); i++) 
        {
            vector<int> v;
            v.push_back(other.toOffer[i][0]);
            v.push_back(other.toOffer[i][1]);
            toOffer.push_back(v);
        }
        coalitionId = other.coalitionId;

    }
    return *this;
}

// Move Assignment Operator
Agent& Agent::operator=(Agent &&other) noexcept
{
    if (this != &other)
    {
        mAgentId = other.mAgentId;
        mPartyId = other.mPartyId;
        mSelectionPolicy = other.mSelectionPolicy; 
        toOffer.clear();
        for(unsigned int i=0; i<other.toOffer.size(); i++) 
        {
            vector<int> v;
            v.push_back(other.toOffer[i][0]);
            v.push_back(other.toOffer[i][1]);
            toOffer.push_back(v);
        }
        coalitionId = other.coalitionId;

        other.mSelectionPolicy = nullptr;
    }
    return *this;
} 

// Copy Constructor
Agent::Agent(const Agent &other)
    : mAgentId{other.mAgentId}, mPartyId{other.mPartyId},mSelectionPolicy{}, toOffer{} ,coalitionId{other.coalitionId}
{
    //copy offers
    for(unsigned int i=0; i<other.toOffer.size(); i++) 
    {
        vector<int> v;
        v.push_back(other.toOffer[i][0]);
        v.push_back(other.toOffer[i][1]);
        toOffer.push_back(v);
    }
    
    //copy mJoinPolicy
    if(other.mSelectionPolicy){

        std::string selectionPolicy = other.mSelectionPolicy->getPolicy();
        if (selectionPolicy == "E")
            mSelectionPolicy = new EdgeWeightSelectionPolicy;
        else if (selectionPolicy == "M")
            mSelectionPolicy = new MandatesSelectionPolicy;
        else
            throw std::invalid_argument("Invalid selection policy");
    }

}

// Move Constructor
Agent::Agent(Agent &&other) noexcept
    :mAgentId{other.mAgentId}, mPartyId{other.mPartyId},mSelectionPolicy{other.mSelectionPolicy}, toOffer{} ,coalitionId{other.coalitionId}
{
    //copy offers
    for(unsigned int i=0; i<other.toOffer.size(); i++) 
    {
        vector<int> v;
        v.push_back(other.toOffer[i][0]);
        v.push_back(other.toOffer[i][1]);
        toOffer.push_back(v);
    }
    
    other.mSelectionPolicy = nullptr;
}
