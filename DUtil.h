//
// Created by masker on 2021/11/3.
//

#ifndef IM_FOR_LINUX_DUTIL_H
#define IM_FOR_LINUX_DUTIL_H
#include <cstring>
#include <mysql/mysql.h>
#include <iostream>
#include <vector>
#include "User.h"
#include "TimeUtil.h"

using namespace std;


class DUtil {
private:
    string DBUsername; // 数据库用户名
    string DBPasswd; //数据库密码
    string host; //主机名
    string database; //数据库名称
    int port; //端口号
    bool isOpen; //是否连接
    MYSQL *connect{};
    MYSQL_RES *result{};
    MYSQL_ROW sql_row{};
    MYSQL_FIELD *fd{};
    TimeUtil timeUtil;
public:
    DUtil();
    ~DUtil();
    bool OpenDB();
    bool CloseDB();
    bool queryUser(string &username,string &password);//登录
    bool insertUser(string &username,string &password);//注册
    bool queryUsername(string &username);
};


#endif //IM_FOR_LINUX_DUTIL_H
