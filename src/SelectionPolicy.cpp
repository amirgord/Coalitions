#include "SelectionPolicy.h"


std::string SelectionPolicy::getPolicy()
{
    return "E";
}

std::string MandatesSelectionPolicy::getPolicy()
{ 

    return "M";
}

std:: string EdgeWeightSelectionPolicy::getPolicy()
{
    return "E";

}

