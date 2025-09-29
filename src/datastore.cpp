#include "datastore.h"

using namespace std;

void DataStore::set(const string& key, const string& value){
    
    //uses hashmap
    store_[key] = value;


}

string DataStore::get(const string& key) const{

    auto it = store_.find(key);
    if(it != store_.end()) {
        return it ->second;
    }

    //redis shows nil when key not found

    return "(nil)";
}