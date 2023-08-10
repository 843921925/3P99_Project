#include <iostream>
#include <unordered_map>
#include "ResourcePool.h"
#include "Vehicle.h"
#include "Request.h"
#include <string>
#include <random>
#include <ctime>
#include <fstream>

//*****************************************************
/// jiahao pang
/// for complie: g++ -std=c++11 *.cpp
//*****************************************************
int main(){
    std::mt19937 generator(time(0));
    for(int exp = 1; exp <= 40; ++exp) {
        std::string filename = "exp_02_" + std::string(exp < 41 ? "0" : "") + std::to_string(exp) + ".txt";
        std::ofstream outfile(filename);

        std::streambuf* coutbuf = std::cout.rdbuf();
        std::cout.rdbuf(outfile.rdbuf());

    ResourcePool pool;

    std::unordered_map<std::string, double> resources[30];
    std::unordered_map<std::string, double> usedResources[30];
    Vehicle* vehicles[30];  

   // std::mt19937 generator(time(0));
    std::uniform_int_distribution<int> resourceDistribution(0, 100);
    std::uniform_int_distribution<int> coordinateDistribution(0, 2500);
    std::uniform_int_distribution<int> vehicleDistribution(1, 10);

    for(int i = 0; i < 30; ++i) {
        resources[i].insert({"cpu", resourceDistribution(generator)});
        resources[i].insert({"memory", resourceDistribution(generator)});
        resources[i].insert({"bandwidth", resourceDistribution(generator)});

        usedResources[i].insert({"cpu", 0});
        usedResources[i].insert({"memory", 0});
        usedResources[i].insert({"bandwidth", 0});

        vehicles[i] = new Vehicle(std::to_string(i+1), &resources[i], &usedResources[i]);
        vehicles[i]->x = coordinateDistribution(generator);
        vehicles[i]->y = coordinateDistribution(generator);

        pool.addVehicle(vehicles[i]);
    }
    // std::unordered_map<std::string, double> resource1;
    // std::unordered_map<std::string, double> usedResource1;
    // std::unordered_map<std::string, double> resource2;
    // std::unordered_map<std::string, double> usedResource2;
    // std::unordered_map<std::string, double> resource3;
    // std::unordered_map<std::string, double> usedResource3;
    // std::unordered_map<std::string, double> resource4;
    // std::unordered_map<std::string, double> usedResource4;

    // resource1.insert({"cpu", 6});
    // resource1.insert({"memory", 11});
    // resource1.insert({"bandwidth", 300});

    // usedResource1.insert({"cpu", 0});
    // usedResource1.insert({"memory", 0});
    // usedResource1.insert({"bandwidth", 0});

    // resource2.insert({"cpu", 5});
    // resource2.insert({"memory", 10});
    // resource2.insert({"bandwidth", 300});

    // usedResource2.insert({"cpu", 0});
    // usedResource2.insert({"memory", 0});
    // usedResource2.insert({"bandwidth", 0});

    // resource3.insert({"cpu", 7});
    // resource3.insert({"memory", 12});
    // resource3.insert({"bandwidth", 0});

    // usedResource3.insert({"cpu", 0});
    // usedResource3.insert({"memory", 0});
    // usedResource3.insert({"bandwidth", 0});

    // resource4.insert({"cpu", 10});
    // resource4.insert({"memory", 100});
    // resource4.insert({"bandwidth", 150});

    // usedResource4.insert({"cpu", 10});
    // usedResource4.insert({"memory", 100});
    // usedResource4.insert({"bandwidth", 150});

    // Vehicle vehicle1("111", &resource1, &usedResource1);
    // Vehicle vehicle2("222", &resource2, &usedResource2);
    // Vehicle vehicle3("333", &resource3, &usedResource3);
    // Vehicle vehicle4("444", &resource4, &usedResource4);

    // vehicle1.x = 30;
    // vehicle1.y = 30;

    // vehicle2.x = 3;
    // vehicle2.y = 3;

    // vehicle3.x = 300;
    // vehicle3.y = 300;

    // vehicle4.x = 1;
    // vehicle4.y = 1;

    // pool.addVehicle(&vehicle1);
    // pool.addVehicle(&vehicle2);
    // pool.addVehicle(&vehicle3);
    // pool.addVehicle(&vehicle4);


    std::unordered_map<std::string, double> reqResource;

    reqResource.insert({"cpu", resourceDistribution(generator)});
    reqResource.insert({"memory", resourceDistribution(generator)});
    reqResource.insert({"bandwidth", resourceDistribution(generator)});

    Request request(std::to_string(vehicleDistribution(generator)), &reqResource);



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
    Request release("1", &releaseResource);

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

    for(int i = 0; i < 10; ++i) {
        delete vehicles[i];
    }

    std::cout.rdbuf(coutbuf);
        outfile.close();
    }
    return 0;

}