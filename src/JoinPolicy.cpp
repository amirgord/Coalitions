#include "JoinPolicy.h"


std::string JoinPolicy::getJoinPolicyType()
{
    return "X";
}


std::string MandatesJoinPolicy::getJoinPolicyType()
{
    return "M";
}

std::string LastOfferJoinPolicy::getJoinPolicyType()
{
    return "L";
}