#include<iostream>
#include"DBCLI.h"
using namespace std;


int main()
{
    DbCli db; 
    db.initParm("localhost","root","123456","eckv");
    db.initDB();
    db.exeSQL("INSERT node_ip_port values(0,'192.168.1.3','2222');");
    db.exeSQL("SELECT * from node_ip_port;");
    db.exeSQL("INSERT `keys` values('world');");
    db.exeSQL("SELECT * from `keys`;");
    return 0;
}