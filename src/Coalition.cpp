#include "Coalition.h"

Coalition::Coalition(int coalitionId, Party party) : Id(coalitionId),mandates(party.getMandates()), pendings(), partiesId()
{
    partiesId.push_back(party.getId());
}


int Coalition :: getId() const
{
    return Id;
}
int Coalition :: getMandates() const
{
    return mandates;
}

vector<int> Coalition :: getParties() const
{
    return partiesId;
}

// return true if a party already got an offer from the coalition
bool Coalition :: isPending(int partyId)
{
    for(int id:pendings){
        if(id == partyId) return true;
    }
    return false;
}

// add party and its mandates to the coalition
void Coalition :: addParty(int partyId,int pMandates)
{
    mandates += pMandates;
    partiesId.push_back(partyId);
}


