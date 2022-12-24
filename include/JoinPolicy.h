#pragma once
#include <string>

class JoinPolicy 
{
public:
    virtual std::string getJoinPolicyType() = 0;
    virtual ~JoinPolicy() = default;
};

class MandatesJoinPolicy : public JoinPolicy 
{
public:
    virtual std::string getJoinPolicyType();
    virtual ~MandatesJoinPolicy() = default;

};

class LastOfferJoinPolicy : public JoinPolicy 
{
public:
    virtual std::string getJoinPolicyType();
    virtual ~LastOfferJoinPolicy() = default;

};