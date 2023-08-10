#include <iostream>
#include "ResourcePool.h"
#include "Vehicle.h"
#include "Request.h"

ResourcePool::ResourcePool()
{

}

ResourcePool::~ResourcePool()
{

}

void ResourcePool::addVehicle(Vehicle *vehicle)
{
    this->pool.insert({vehicle->vehicleID, *vehicle});
}

void ResourcePool::removeVehicle(Vehicle *vehicle)
{
    this->pool.erase(vehicle->vehicleID);
}

Request ResourcePool::requestResource(Request *request)
{
    std::unordered_map<std::string, double> remainResource;
    // std::cout << "Resource available" << std::endl;
    for(auto& item : request->resource)
    {
        std::string name = item.first;
        double qty = item.second;
        double remain = qty;
        //for each vehicle in the pool
        for(auto& item : this->pool)
        {
            Vehicle *vehicle = &(item.second);
             std::cout << "DBG: vehicleID=" << vehicle->vehicleID << std::endl;
            remain = vehicle->assign(name, remain);
             std::cout << "DBG assigned " <<std::endl;
            if(remain == 0) break;
        }
        if(remain != 0){
            remainResource.insert({name, remain});
        }

    }
    Request remainReq(&remainResource);
    return remainReq;
}

Request ResourcePool::releaseResource(Request *request)
{
    std::unordered_map<std::string, double> remainResource;
    for(auto& item : request->resource)
    {
        std::string name = item.first;
        double qty = item.second;
        double remain = qty;
        //for each vehicle in the pool
        for(auto& item : this->pool)
        {
            Vehicle *vehicle = &(item.second);
            // std::cout << "DBG: vehicleID=" << vehicle->vehicleID << std::endl;
            remain = vehicle->dismiss(name, remain);
            // std::cout << "DBG: resource assigned" << std::endl;
            if(remain == 0) break;
        }
        if(remain != 0){
            remainResource.insert({name, remain});
        }

    }
    Request remainReq(&remainResource);
    return remainReq;
}

double ResourcePool::peekResource(std::string resourceName){
    double qty = 0;
    for(auto& item : this->pool)
    {
        Vehicle vehicle = item.second;
        for(auto& resource : vehicle.resource)
        {
            if(resource.first.compare(resourceName) == 0)
            {
                qty += resource.second;
            }
        }
    }
    return qty;
}

double ResourcePool::peekUsedResource(std::string resourceName){
    double qty = 0;
    for(auto& item : this->pool)
    {
        Vehicle vehicle = item.second;
        for(auto& resource : vehicle.usedResource)
        {
            if(resource.first.compare(resourceName) == 0)
            {
                qty += resource.second;
            }
        }
    }
    return qty;
}

std::set<std::string> ResourcePool::getAllNames(){
    std::set<std::string> list;
    for(auto& item : this->pool)
    {
        Vehicle vehicle = item.second;
        for(auto& resource : vehicle.resource)
        {
            list.insert(resource.first);
        }
    }
    return list;
}