# ifndef _DBCLI_H_
# define _DBCLI_H_

# include<string>
# include<mysql/mysql.h>

// https://blog.csdn.net/Leo_csdn_/article/details/82682839

class DbCli{
    private:
        std::string IP;
        std::string userName;
        std::string passwd;
        std::string dbName;
        int port;
        MYSQL dbMeta;
    public:
        DBCLI(){

        }
        void connect(){
            if(mysql_library_init(0,NULL,NULL)!=0){

            }
            if(mysql_init(&dbMeta)==NULL){

            }
            if(mysql_real_connect(&dbMeta,IP,userName,passwd,dbName,port,NULL,0)==NULL){
            }
        }
}

# endif 