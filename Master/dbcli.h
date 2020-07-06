# ifndef _DBCLI_H_
# define _DBCLI_H_

# include<iostream>
# include<string>
# include<mysql/mysql.h>

// https://blog.csdn.net/Leo_csdn_/article/details/82682839

class DbCli{
    private:
        std::string host;
        std::string user;
        std::string pwd;
        std::string db;
        MYSQL *mysql;
        MYSQL_RES *result;
        MYSQL_ROW row;
    public:
        DBCLI(){
            mysql=mysql_init(NULL);
            if(mysql==NULL)
            {
                cout<<"Error:"<<mysql_error(mysql);
                exit(1);
            }
        }
        ~DBCLI(){
            if(mysql!=NULL){
                mysql_close(mysql);
            }
        }
        void initParm(std::string _host,std::string _user,std::string _pwd,std::string db){
            host=_host;
            user=_user;
            pwd=_pwd;
            db=_db;
        }
        bool initDB(){
            mysql = mysql_real_connect(mysql, host.c_str(), user.c_str(), pwd.c_str(), db.c_str(), 0, NULL, 0);  
            if(mysql == NULL)  
            {  
                cout << "Error: " << mysql_error(mysql);  
                exit(1);  
            }  
            return true;  
        }
        bool execSQL(std::string sql)
        {
            //mysql_query()执行成功返回0,执行失败返回非0值。
            if (mysql_query(mysql, sql.c_str()))
            {
                cout << "Query Error: " << mysql_error(mysql);
                return false;
            }
            else // 查询成功
            {

                result = mysql_store_result(mysql); //获取结果集
                if (result)                         // 返回了结果集
                {
                    int num_fields = mysql_num_fields(result); //获取结果集中总共的字段数，即列数
                    int num_rows = mysql_num_rows(result);     //获取结果集中总共的行数
                    for (int i = 0; i < num_rows; i++)         //输出每一行
                    {
                        //获取下一行数据
                        row = mysql_fetch_row(result);
                        if (row < 0)
                            break;

                        for (int j = 0; j < num_fields; j++) //输出每一字段
                        {
                            cout << row[j] << "\t\t";
                        }
                        cout << endl;
                    }
                }
                else // result==NULL
                {
                    if (mysql_field_count(mysql) == 0) //代表执行的是update,insert,delete类的非查询语句
                    {
                        // (it was not a SELECT)
                        int num_rows = mysql_affected_rows(mysql); //返回update,insert,delete影响的行数
                    }
                    else // error
                    {
                        cout << "Get result error: " << mysql_error(mysql);
                        return false;
                    }
                }
            }
            return true;
        }
}

# endif 