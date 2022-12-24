#pragma once

#include <vector>
#include "Party.h"

using std::vector;

// class Party;

class Coalition
{
public:
    Coalition(int coalitionId, Party party);

    int getId() const;
    int getMandates() const;
    vector<int> getParties() const;
    bool isPending(int partyId);
    void addParty(int partyId,int pMandates);
    void addPending(int partyId);


private:
    int Id;
    int mandates;
    vector<int> pendings;
    vector<int> partiesId;
};

