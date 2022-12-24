#pragma once

#include <vector>
#include "Graph.h"
#include "SelectionPolicy.h"


class SelectionPolicy;


bool compareVector(vector<int> v1,vector<int> v2);
class Agent
{
public:
    Agent(int agentId, int partyId, SelectionPolicy *selectionPolicy);

    int getPartyId() const;
    int getId() const;
    std::string getSelectionPolicy() const;
    int getCoalitionId();
    void step(Simulation &);
    void setCoalitionId(int cId);


    //-------------Rule of 5-------------
    ~Agent();
    Agent& operator=(const Agent& other);
    Agent& operator=(Agent &&other) noexcept;
    Agent(const Agent &other);
    Agent(Agent &&other)noexcept;



private:
    int mAgentId;
    int mPartyId;
    SelectionPolicy *mSelectionPolicy;
    vector<vector<int>> toOffer;
    int coalitionId;
};
