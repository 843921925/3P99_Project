#ifndef RESOURCE_POOL_H
#define RESOURCE_POOL_H

#include <unordered_map>
#include <string>
#include <vector>
#include <set>
#include "Vehicle.h"
#include "Request.h"

class ResourcePool
{
    public:

        ResourcePool();
        
        ~ResourcePool();

        void addVehicle(Vehicle *vehicle);

        void removeVehicle(Vehicle *vehicle);

        Request requestResource(Request *request);

        Request releaseResource(Request *request);

        double peekResource(std::string resourceName);

        double peekUsedResource(std::string resourceName);

        std::set<std::string> getAllNames();
    private:
        std::unordered_map<std::string, Vehicle> pool;

};
#endif