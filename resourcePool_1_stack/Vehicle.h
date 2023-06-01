#ifndef VEHICLE_H
#define VEHICLE_H

#include <unordered_map>
#include <string>
#include <vector>
struct Vehicle
{
    std::string vehicleID;
    std::unordered_map<std::string, double> resource;
    std::unordered_map<std::string, double> usedResource;
    Vehicle(std::string vehicleID, std::unordered_map<std::string, double> *resource, std::unordered_map<std::string, double> *usedResource)
    {
        this->vehicleID = vehicleID;
        this->resource = *resource;
        this->usedResource = *usedResource;
    }

    //return the remaining qty after assign to this vehicle
    double assign(std::string name, double qty)
    {
        double total = 0;
        auto totalItem = resource.find(name);
        if(totalItem != resource.end()){
            total = totalItem->second;
        }

        double used = 0;
        auto usedItem = usedResource.find(name);
        if(usedItem != usedResource.end()){
            used = usedItem->second;
        }else{
            usedResource.insert({name, 0});
        }

        double available = total - used;
        // std::cout << "DBG: available=" << available << std::endl; 
        // std::cout << "DBG: qty=" << qty << std::endl; 
        usedItem = usedResource.find(name);
        if(available >= qty){
            // std::cout << "DBG: usedItem->second=" << usedItem->second << std::endl; 
            usedItem->second += qty;
            return 0;
        }else{
            usedItem->second += available;
            return qty-available;
        }

    }

    double dismiss(std::string name, double qty)
    {
        auto usedItem = usedResource.find(name);
        if(usedItem != usedResource.end())
        {
            if(usedItem->second >= qty){
                usedItem->second -= qty;
            }else{
                double remain = qty - usedItem->second;
                usedItem->second = 0;
                return remain;
            }
            
        }else{
            std::cerr << "No used resource to dismiss on vehicle " << this->vehicleID << std::endl;
            return qty;
        }
        return 0;
    }

};
#endif