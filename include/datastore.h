#ifndef DATASTORE_H
#define  DATASTORE_H

//2
#include <string>
#include <unordered_map>


//stores keys an dvalues in memoery while sever is running
//so ie set name John stores John later for Get name
class DataStore{


public:
    void set(const std::string& key, const std::string& value);
    std:: string get(const std::string&key) const;

private:
    std::unordered_map<std::string,std::string> store_;

};


#endif