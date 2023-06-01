#include <iostream>
#include <algorithm>
#include "ResourcePool.h"
#include "Vehicle.h"
#include "Request.h"

//*****************************************************
/// jiahao pang
/// for complie: g++ -std=c++11 *.cpp
//*****************************************************

ResourcePool::ResourcePool()
{

}

ResourcePool::~ResourcePool()
{

}

void ResourcePool::addVehicle(Vehicle *vehicle)
{
    this->pool.push_back({vehicle->vehicleID, *vehicle});
    this->dictionary.insert({vehicle->vehicleID, *vehicle});
}

void ResourcePool::removeVehicle(Vehicle *vehicle)
{
    this->dictionary.erase(vehicle->vehicleID);
    int n = 0;
    for(auto& item : this->pool)
    {
        Vehicle* v = &(item.second);
        if(v == vehicle) break;
        n++;
    }
    this->pool.erase(this->pool.begin()+n);
}

void ResourcePool::sortVehicleByRequest(Request *request)
{
    std::unordered_map<std::string, int> vehicleScore;
    //Sort vehicle by resource
    //std::vector<std::pair<std::string, Vehicle>> resourceElements(this->pool.begin(), this->pool.end());
    
    for(auto& item : this->pool)
    {
        Vehicle *vehicle = &(item.second);
        vehicle->getResourceScore(*request);
    }
    std::vector<std::pair<std::string, Vehicle>> resourceElements(this->pool.begin(), this->pool.end());
    std::sort(resourceElements.begin(), resourceElements.end(), ResourcePool::sortByResourceScore);

    int n = 1;
    for(auto&item : resourceElements){
        std::string vehicleID = item.first;
        vehicleScore.insert({vehicleID, n});
        std::cout <<"vehicle score#1:" << vehicleScore[vehicleID] << "  ID:" << vehicleID<< std::endl;
        n++;
    }

    //Sort vehicle by distance
    //std::vector<std::pair<std::string, Vehicle>> distanceElements(this->pool.begin(), this->pool.end());
    for(auto& item : this->pool)
    {
        Vehicle *vehicle = &(item.second);
        //std::cout << "request->vehicleID="<<request->vehicleID<<std::endl;
        Vehicle requestVehicle = this->dictionary.at(request->vehicleID);
        vehicle->distance(requestVehicle);
    }

    std::vector<std::pair<std::string, Vehicle>> distanceElements(this->pool.begin(), this->pool.end());
    std::sort(distanceElements.begin(), distanceElements.end(), ResourcePool::sortByDistance);

    n = 1;
    for(auto& item : distanceElements)
    {
        std::string vehicleID = item.first;
        vehicleScore[vehicleID] += n; 
                std::cout <<"vehicle score#2:" << vehicleScore[vehicleID] << "  ID:" << vehicleID<< std::endl;

        n++;
    }

    //sort vehicleScore
    std::vector<std::pair<std::string, int>> vehicleScoreElements(vehicleScore.begin(), vehicleScore.end());
    std::sort(vehicleScoreElements.begin(), vehicleScoreElements.end(), ResourcePool::sortVehicleScore);
    //re-arrange this->pool
    std::vector<std::pair<std::string, Vehicle>> newPool;
    for(auto& item : vehicleScoreElements)
    {
        std::string vehicleID = item.first;
        std::cout << "Vehicle ID: " << vehicleID << " - " << item.second << std::endl;
        Vehicle v = this->dictionary.at(vehicleID);
        newPool.push_back({vehicleID, v});
    }
    this->pool = newPool;
    for(auto& item : this->pool)
    {
        Vehicle *vehicle = &(item.second);
        std::cout << "RE-ARRANGE: vehicleID=" << vehicle->vehicleID << std::endl;
    }


}

bool ResourcePool::sortByResourceScore(std::pair<std::string, Vehicle> v1, std::pair<std::string, Vehicle> v2)
{
    return (v1.second.resourceScore < v2.second.resourceScore);
}

bool ResourcePool::sortByDistance(std::pair<std::string, Vehicle> v1, std::pair<std::string, Vehicle> v2)
{
    return (v1.second.dist < v2.second.dist);
}

bool ResourcePool::sortVehicleScore(std::pair<std::string, int> v1, std::pair<std::string, int> v2)
{
    return (v1.second < v2.second);
}

Request ResourcePool::requestResource(Request *request)
{
    std::unordered_map<std::string, double> remainResource;
    // std::cout << "Resource available" << std::endl;
    this->sortVehicleByRequest(request);
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
            std::cout << "DBG: resource assigned" << std::endl;
            if(remain == 0) break;
        }
        if(remain != 0){
            remainResource.insert({name, remain});
        }

    }
    Request remainReq(request->vehicleID, &remainResource);
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
            std::cout << "DBG: vehicleID=" << vehicle->vehicleID << std::endl;
            remain = vehicle->dismiss(name, remain);
            std::cout << "DBG: resource released" << std::endl;
            if(remain == 0) break;
        }
        if(remain != 0){
            remainResource.insert({name, remain});
        }

    }
    Request remainReq(request->vehicleID,&remainResource);
    return remainReq;
}

double ResourcePool::peekResource(std::string resourceName)
{
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

double ResourcePool::peekUsedResource(std::string resourceName)
{
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

std::set<std::string> ResourcePool::getAllNames()
{
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

Vehicle ResourcePool::getVehicleByID(std::string vehicleID)
{
    return this->dictionary.at(vehicleID);
}