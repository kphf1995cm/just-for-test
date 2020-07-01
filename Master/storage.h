# ifndef _STORAGE_H_
# define _STORAGE_H_
# include<string>
# include<vector>
# include<unordered_set>
# include<unordered_map>
# include "util.h"
# include"dbcli.h"

// 未考虑线程安全性 参考https://blog.csdn.net/chenxun2009/article/details/48273723
class WorkerIPStatus{
    public:
        bool used;
        bool avaiable;
        WorkerIPStatus(){
            used=false;
            avaiable=true;
        }
};

class Storage{
    public:
        int nodeNum;
        int dataNodeNum;
        int codeNodeNum;
        std::vector<std::pair<std::string,std::string>> nodeIPPorts;
        std::unordered_set<std::string> keys;
    private:
        static Storage* p_instance;
        std::string workerIPPath;
        std::string configPath;
        std::unordered_map<std::string,WorkerIPStatus> workerIPs;
        //DBCli dbcli;
        Storage(){};
        ~Storage(){};
        Storage(const Storage&);
        Storage& operator=(const Storage&); 
        class GC{
            public:
                ~GC(){
                    if(p_instance!=NULL){
                        delete p_instance;
                    }
                }
        };
        static GC gc;
    public:
        static Storage* getInstance(){
            if(p_instance==NULL){
                p_instance=new Storage();
            }
            return p_instance;
        }
        // read config from file
        void init(){

            // attain node num
            dataNodeNum=3;
            codeNodeNum=1;
            nodeNum=dataNodeNum+codeNodeNum;

            // attain worker ip
            int ipnum=5;
            std::string ips[5]={
                "192.168.0.2",
                "192.168.0.3",
                "192.168.0.4",
                "192.168.0.5",
                "192.168.0.6",
            }; 
            for(int i=0;i<ipnum;i++){
                WorkerIPStatus wips;
                if(deteckWorkerIP(ips[i])==false){
                    wip.avaiable=false;
                }
                workerIPs[ips[i]]=wips;         
            }

            // sync nodeIPPorts and keys from DB

            // assign worker ip
            assignWorkerIP();
        };
        void assignWorkerIP(){
            // decide nodeIPPorts table

        }
        void parseJson(){};
};
Storage* Storage::p_instance = NULL;
# endif