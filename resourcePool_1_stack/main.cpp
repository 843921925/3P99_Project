#include <iostream>
#include <unordered_map>
#include "ResourcePool.h"
#include "Vehicle.h"
#include "Request.h"

int main(){
    ResourcePool pool;
    std::unordered_map<std::string, double> resource1;
    std::unordered_map<std::string, double> usedResource1;
    std::unordered_map<std::string, double> resource2;
    std::unordered_map<std::string, double> usedResource2;
    resource1.insert({"cpu", 4});
    resource1.insert({"memory", 200});
    resource1.insert({"bandwidth", 50});

    // usedResource1.insert({"cpu", 2});
    // usedResource1.insert({"memory", 50});
    // usedResource1.insert({"bandwidth", 10});

    resource2.insert({"cpu", 2});
    resource2.insert({"memory", 300});
    resource2.insert({"bandwidth", 150});

    Vehicle vehicle1("111", &resource1, &usedResource1);
    Vehicle vehicle2("222", &resource2, &usedResource2);

    pool.addVehicle(&vehicle1);
    pool.addVehicle(&vehicle2);

    std::unordered_map<std::string, double> reqResource;
    reqResource.insert({"cpu", 3});
    reqResource.insert({"memory", 250});
    Request request(&reqResource);

    Request remainReq = pool.requestResource(&request);
    if(!remainReq.resource.empty()){
        std::cout << "There is some remaining for another pool." << std::endl;
        std::cout << "Remaining unassigned request: " << std::endl;
        for(auto& item : remainReq.resource)
        {
            std::cout << item.first << ": " << item.second << std::endl;
        }
        std::cout << "==============================" << std::endl;
        // Request remainReq2 = pool2.requestResource(&remainReq);
    
    }else{
        std::cout << "All requested resources are assigned successfully." << std::endl;
    }

    std::unordered_map<std::string, double> releaseResource;
    releaseResource.insert({"cpu", 0});
    releaseResource.insert({"memory", 0});
    Request release(&releaseResource);

    Request remainRelease = pool.releaseResource(&release);

    if(!remainRelease.resource.empty()){
        std::cout << "There is some remaining for another pool." << std::endl;
        std::cout << "Remaining unreleased request: " << std::endl;
        for(auto& item : remainRelease.resource)
        {
            std::cout << item.first << ": " << item.second << std::endl;
        }
        std::cout << "==============================" << std::endl;
        // Request remainRelease2 = pool2.releaseResource(&remainRelease);
    
    }else{
        std::cout << "All requested resources are released successfully." << std::endl;
    }

    std::set<std::string> names = pool.getAllNames();
    std::cout << "Resource: " << std::endl;
    for(std::string name : names)
    {
        std::cout << name <<": " << pool.peekResource(name) << std::endl;
    }

    std::cout << "Used Resource: " << std::endl;
    for(std::string name : names)
    {
        std::cout << name <<": " << pool.peekUsedResource(name) << std::endl;
    }

}