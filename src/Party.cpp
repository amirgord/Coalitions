#include "Party.h"
#include "Agent.h"
#include "JoinPolicy.h"
#include "Coalition.h"
#include "Simulation.h"

#include <iostream>

Party::Party(int id, string name, int mandates, JoinPolicy *jp) : mId(id), mName(name), mMandates(mandates), mJoinPolicy(jp), mState(Waiting),timer(-1),offers(),coalitionId(-1)
{ }

State Party::getState() const
{
    return mState;
}

void Party::setState(State state)
{
    mState = state;
}

int Party::getMandates() const
{
    return mMandates;
}

int Party::getId() const
{
    return mId;
}

const string & Party::getName() const
{
    return mName;
}

int Party::getCoalitionId() const
{
    return coalitionId;
}

void Party::setCoalitionId(int cId)
{
    coalitionId = cId;
}

void Party::step(Simulation &s)
{
//     //Once the timer of 3 iterations is done - join some coalition (using the JoinPolicy). 
//     //When joining, the party’s state should be changed to Joined and the agent must be cloned.

    if(timer == 0)
    {
        //1) get Join type:
        string jType = mJoinPolicy->getJoinPolicyType();

        //2) decide which coalition i should join to
        int idOfCoalition = -1;
        // int idOfParty = -1;

        if(jType == "M")
        {
            //return the id of the party with the most madetes
            int mostMandates = 0;
            for (unsigned int i = 0; i < offers.size(); ++i)
            {
                Coalition &c = s.getCoaliotion(offers[i]); 
                if(mostMandates < c.getMandates())
                {
                    mostMandates = c.getMandates();
                    idOfCoalition = c.getId();
                }
            }
        }
        else if(jType == "L")
        {
            //return the id of the last party that offer
            idOfCoalition = offers.at(offers.size()-1);  
        }

        // idOfCoalition = s.getParty(idOfParty).getCoalitionId();


        //3) add me to the coalition object
        Coalition &c = s.getCoaliotion(idOfCoalition);
        c.addParty(mId,mMandates);

        //4) clone and add agent to the agent list
        s.cloneAgent(idOfCoalition, mId);

        //5) change the state of the party and coalition id
        Party::setState(Joined);
        coalitionId = idOfCoalition;

        timer = -1;

    }

    // is to check if the status is CollectingOffers and update the timer if so. 

    if(Party::getState() == CollectingOffers)
    {
        timer--;
    }
}


//recive an offer from an agent, add the offer to your offers list:
//@pre: the party assumes that the agent sended a valid offer
void Party::reciveOffer(int cId)
{
    if(mState == Waiting)
        timer = 2;
    mState = CollectingOffers;
    offers.push_back(cId);
}

//check if the party has offer from a coalition:
bool Party::hasOfferFrom(int cId) const
{
    for(int i:offers){

        if (i == cId){
            return true;
        }
    }
    return false;
}





//-------------Rule of 5-------------

// Destructor
Party::~Party()
{
    delete(mJoinPolicy);
    mJoinPolicy = nullptr;
}

// Copy Assignment Operator
Party& Party::operator=(const Party& other)
{
    if (this != &other)
    {
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        mJoinPolicy = other.mJoinPolicy; //--
        mState = other.mState;
        timer = other.timer;
        offers.clear();
        for(int i :other.offers)
            offers.push_back(other.offers[i]);
        coalitionId = other.coalitionId;
    }
    return *this;
}

// Move Assignment Operator
Party& Party::operator=(Party &&other) noexcept
{
    if (this != &other)
    {
        mId = other.mId;
        mName = other.mName;
        mMandates = other.mMandates;
        mJoinPolicy = other.mJoinPolicy; //--
        mState = other.mState;
        timer = other.timer;
        offers.clear();
        for(int i :other.offers)
            offers.push_back(other.offers[i]);
        coalitionId = other.coalitionId;

        other.mJoinPolicy = nullptr;
    }
    return *this;
} 

// Copy Constructor
Party::Party(const Party &other)
    : mId{other.mId}, mName{other.mName}, mMandates{other.mMandates}, mJoinPolicy{} ,mState{other.mState}
    ,timer{other.timer},offers{} ,coalitionId{other.coalitionId}
{
    //copy offers
    for(int i :other.offers)
        offers.push_back(other.offers[i]);


    //copy mJoinPolicy

    if(other.mJoinPolicy){
        std::string joinPolicy = other.mJoinPolicy->getJoinPolicyType();
        if (joinPolicy == "M")
            mJoinPolicy = new MandatesJoinPolicy;
        else if (joinPolicy == "L")
            mJoinPolicy = new LastOfferJoinPolicy;
        else
            throw std::invalid_argument("Invalid join policy");
    }
}

// Move Constructor
Party::Party(Party &&other) noexcept
    : mId{other.mId}, mName{other.mName}, mMandates{other.mMandates}, mJoinPolicy{other.mJoinPolicy} ,mState{other.mState}
    ,timer{other.timer},offers{} ,coalitionId{other.coalitionId}
{
    for(int i :other.offers)
        offers.push_back(other.offers[i]);
    
    other.mJoinPolicy = nullptr;
}