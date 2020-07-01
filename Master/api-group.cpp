# include <vector>
# include "api-group.h"
# include "util.h"

void ApiGroup::init(){
    p_storage=Storage::getInstance();
    manager.init();
}

void ApiGroup::run(){

}

int ApiGroup::put(const std::string &key, const std::string &value){
    if(p_storage->keys.count(key)==0){
        p_storage->keys.insert(key);
    }
    std::vector<std::string> vals=split(value,p_storage->dataNodeNum);
    // Call EC to Encode
    

    return 0;
}

int ApiGroup::get(const std::string &key, std::string &value){
    return 0;
}

int ApiGroup::remove(const std::string &key){
    return 0;
}
