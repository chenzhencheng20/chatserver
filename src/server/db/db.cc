#include "db.h"
#include <muduo/base/Logging.h>


// 数据库配置信息
static string server = "127.0.0.1";
static string user = "root";
static string password = "123456";
static string dbname = "chat";

MySQL::MySQL()
{
    _conn = mysql_init(nullptr);
}

// 释放数据库连接资源
MySQL::~MySQL()
{
    if (_conn != nullptr)
        mysql_close(_conn);
}

// 连接数据库
bool MySQL::connect()
{
    MYSQL *p = mysql_real_connect(_conn, server.c_str(), user.c_str(),
                                  password.c_str(), dbname.c_str(), 3306, nullptr, 0);
    if (p != nullptr)
    {
        //mysql_query(_conn, "set names gbk");
        if(mysql_query(_conn, "set names gbk"))
            {
                LOG_INFO << "mysql_query fail";
            }
        LOG_INFO << "connect mysql success!";
    }
    else
    {
        LOG_INFO << "connect mysql fail!";
    }
    return p;
}
// 更新操作
bool MySQL::update(string sql)
{
    
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "更新失败!";
        return false;
    }
    // int i = mysql_query(_conn, sql.c_str());
    // if(i=CR_COMMANDS_OUT_OF_SYNC)
    // {
    //     LOG_INFO << "以不恰当的顺序执行了命令";
    // }
    // else if(CR_SERVER_GONE_ERROR)
    // {
    //     LOG_INFO << "MYSQL服务器不可用";
    // }
    // else if(CR_SERVER_LOST)
    // {
    //     LOG_INFO << "查询过程中与服务器连接丢失";
    // }
    // else if(CR_UNKNOWN_ERROR)
    // {
    //     LOG_INFO << "未知错误";
    // }
    // return false;
    return true;
}
// 查询操作
MYSQL_RES *MySQL::query(string sql)
{
    if (mysql_query(_conn, sql.c_str()))
    {
        LOG_INFO << __FILE__ << ":" << __LINE__ << ":"
                 << sql << "查询失败!";
        return nullptr;
    }
    return mysql_use_result(_conn);
}

MYSQL* MySQL::getConnection()
{
    return _conn;
}