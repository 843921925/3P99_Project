#ifndef REQUEST_H
#define REQUEST_H

#include <unordered_map>
#include <string>
#include <vector>
struct Request
{
    std::unordered_map<std::string, double> resource;
    Request(std::unordered_map<std::string, double> *resource)
    {
        this->resource = *resource;
    }
};
#endif