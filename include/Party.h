#pragma once
#include <string>
#include <vector>

#include "SelectionPolicy.h"
#include "JoinPolicy.h"

using std::string;
using std::vector;

class Simulation;

enum State
{
    Waiting,
    CollectingOffers,
    Joined
};

class Party
{
public:
    Party(int id, string name, int mandates, JoinPolicy *); 

    State getState() const;
    void setState(State state);
    int getMandates() const;
    int getId() const;
    const string &getName() const;
    int getCoalitionId() const;
    void setCoalitionId(int cId);
    void step(Simulation &s);
    void reciveOffer(int cId);
    bool hasOfferFrom(int cId) const;


    // rule of 5

    ~Party();
    Party& operator=(const Party& other);
    Party& operator=(Party &&other) noexcept;
    Party(const Party &other);
    Party(Party &&other)noexcept;





private:
    int mId;
    string mName;
    int mMandates;
    JoinPolicy *mJoinPolicy;
    State mState;

    //added:
    int timer;
    vector<int> offers;
    int coalitionId;
};