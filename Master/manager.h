# ifndef _MANAGER_H_
# define _MANAGER_H_
# include <vector>
# include <string>
# include <mutex>
# include "storage.h"
# include "kvclient.h"

// mtx.lock()
// mtx.unlock()

class KvClientStatus {
    private:
        KvClient client;
        std::mutex mux;
}

class Manager{
    private:
        Storage *p_storage;
        std::vector<KvClientStatus> clients;
    public:
        Manager(){
            p_storage=Storage::getInstance();
        }
        
        void init(){
            for(int i=0;i<p_storage->nodeIPPorts.size();i++){
                clients.push_back(KvClient(grpc::CreateChannel(
                    p_storage->nodeIPPorts[0]+":"+p_storage->nodeIPPorts[1],
                    grpc::InsecureChannelCredentials()
                )));
            }
        }
        
        int put(int i,const std::string &key, const std::string &value){
            return clients[i].put(key,value);
        }
        
        int get(int i,const std::string &key, std::string &value){
            return clients[i].get(key,value);
        }
        
        int remove(int i, const std::string &key){
            return clients[i].remove(key);
        }
        
        int modify(){

        }
}        

# endif