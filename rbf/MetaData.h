//
// Created by paul on 9/29/16.
//

#ifndef ARGO_DB_METADATA_H
#define ARGO_DB_METADATA_H

#include <string>
#include <unordered_map>
#include <iostream>

class MetaData{

public:
    std::string name;
    size_t size;
    size_t offset;

    std::unordered_map<std::string, size_t> table;

    MetaData deserialize(void* ptr){

    }

    void serialize(void* buffer)
    {

    }
    friend std::ostream& operator <<(std::ostream& out, const MetaData& data);


};

std::ostream& operator<<(std::ostream& out, const MetaData& data)
{
    out << data.name << std::endl <<  data.size << data.offset << data.table;
    return out;

}

std::istream& operator <<(std::istream& in, MetaData& data)
{
    in >> data.name >>  data.size >> data.offset >> data.table;
    return in;

}



#endif //ARGO_DB_METADATA_H
