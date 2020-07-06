#include<iostream>
#include"dbcli.h"

int main()
{
    DbCli db; 
    db.initParm("localhost","root","123456","eckv");
    db.initDB();
    db.execSQL("INSERT node_ip_port values(1,'192.168.1.3','2222');");
    db.execSQL("SELECT * from node_ip_port;");
    db.execSQL("INSERT `keys` values('hello');");
    db.execSQL("SELECT * from `keys`;");
    return 0;
}
