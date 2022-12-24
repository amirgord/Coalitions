#pragma once
#include <string>

class SelectionPolicy {

    public:
        virtual std::string getPolicy() = 0;
        virtual ~SelectionPolicy() = default;

 };

class MandatesSelectionPolicy: public SelectionPolicy{ 
    
    public:
        virtual std::string getPolicy();
        virtual ~MandatesSelectionPolicy() = default;

};

class EdgeWeightSelectionPolicy: public SelectionPolicy{

    public:
        virtual std::string getPolicy();
        virtual ~EdgeWeightSelectionPolicy() = default;

};
