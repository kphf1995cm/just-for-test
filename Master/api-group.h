# ifndef _API_GROUP_H_
# define _API_GROUP_H_

# include<string>
# include"storage.h"
# include"manager.h"

class ApiGroup {
    private:
        Storage*p_storage;
        Manager manager;
    public:
        ApiGroup(){};
        int put(const std::string &key, const std::string &value);
        int get(const std::string &key, std::string &value);
        int remove(const std::string &key);
        void init();
        void run();
};

# endif