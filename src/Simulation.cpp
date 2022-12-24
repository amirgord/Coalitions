#include <iostream>

#include "Simulation.h"
#include "SelectionPolicy.h"


Simulation::Simulation(Graph graph, vector<Agent> agents) : mGraph(graph), mAgents(agents), coalitions()
{
    //iterate agents and make coalitions:
    for(unsigned int i = 0; i < mAgents.size();i++)
    {
        Party &p = mGraph.getParty(mAgents[i].getPartyId());
        p.setCoalitionId(i);

        coalitions.push_back(Coalition(i,p));
    }
}


void Simulation::step()
{

    //step party:  
    for (int i = 0; i < mGraph.getNumVertices() ; i++)
    {
        mGraph.getParty(i).step(*this);
    }

    //step agent:
    for (Agent &a: mAgents)
    {
        a.step(*this);
    }  

}

bool Simulation::shouldTerminate() const
{   
    
    // return true if number of joined parties == number of vertices:
    // joinedParties aquals the number of agents
    if(mAgents.size() == mGraph.length())
        return true;
    
    //cheack if any coalition arrived to 61 mandates:
    for (unsigned int i = 0;i<coalitions.size();i++)
    {
        if(coalitions[i].getMandates() >= 61)
            return true;
    }
    return false;
    
}

const Graph &Simulation::getGraph() const
{
    return mGraph;
}

Graph &Simulation::getGraph()
{
    return mGraph;
}

const vector<Agent> &Simulation::getAgents() const
{
    return mAgents;
}

const Party &Simulation::getParty(int partyId) const
{
    return mGraph.getParty(partyId);
}

Party &Simulation::getParty(int partyId)
{
    return mGraph.getParty(partyId);
}

void Simulation::cloneAgent(int agentIdToClone, int partyId)
{
    
    //copy the selection policy - need to check type of *sp!
    SelectionPolicy *sp;
    std::string selectionPolicy = mAgents.at(agentIdToClone).getSelectionPolicy();

    if (selectionPolicy == "M")
        sp = new MandatesSelectionPolicy;
    else if (selectionPolicy == "E")
        sp = new EdgeWeightSelectionPolicy;
    else
        throw std::invalid_argument("Invalid selection policy");


    //make new agent and add it to the vector of agents:
    Agent a(this->getAgents().size(), partyId, sp);//agent id and coalition id by defalt constructor are the same so need to update agent coalition id
    a.setCoalitionId(mAgents[agentIdToClone].getCoalitionId());
    mAgents.push_back(a);
}

Coalition &Simulation::getCoaliotion(int coalitionId)
{
    return coalitions[coalitionId];
}


/// This method returns a "coalition" vector, where each element is a vector of party IDs in the coalition.
/// At the simulation initialization - the result will be [[agent0.partyId], [agent1.partyId], ...]
const vector<vector<int>> Simulation::getPartiesByCoalitions() const
{
    vector<vector<int>> output;
    for(unsigned int i = 0;i<coalitions.size();i++)
    {
        vector<int> v;

        for(int pId : coalitions[i].getParties())
            v.push_back(pId);
        
        output.push_back(v);
    }
    return output;
}
