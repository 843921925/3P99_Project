
#ifndef RESOURCE_POOL_H
#define RESOURCE_POOL_H

#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include "ResourcePool.h"
#include "Vehicle.h"
#include "Request.h"

//*****************************************************
/// jiahao pang
/// for complie: g++ -std=c++11 *.cpp
//*****************************************************

class ResourcePool
{
    public:

        ResourcePool();
        
        ~ResourcePool();

        void addVehicle(Vehicle *vehicle);

        void removeVehicle(Vehicle *vehicle);

        void sortVehicleByRequest(Request *request);

        Request requestResource(Request *request);

        Request releaseResource(Request *request);

        double peekResource(std::string resourceName);

        double peekUsedResource(std::string resourceName);

        std::set<std::string> getAllNames();

        Vehicle getVehicleByID(std::string vehicleID);

        static bool sortByResourceScore(std::pair<std::string, Vehicle> v1, std::pair<std::string, Vehicle> v2);

        static bool sortByDistance(std::pair<std::string, Vehicle> v1, std::pair<std::string, Vehicle> v2);
    
        static bool sortVehicleScore(std::pair<std::string, int> v1, std::pair<std::string, int> v2);
    private:
        
        std::vector<std::pair<std::string, Vehicle>> pool;
        std::unordered_map<std::string, Vehicle> dictionary;

        

};
#endif