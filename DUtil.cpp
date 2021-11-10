//
// Created by masker on 2021/11/3.
// 数据库连接
//

#include "DUtil.h"
#include <mysql/mysql.h>
#include <vector>

DUtil::DUtil() {
    DBUsername = "root";
    DBPasswd = "joker468";
    host = "127.0.0.1";
    database = "IM";
    port = 3306;
    isOpen = false;
}

DUtil::~DUtil() {
    CloseDB();
}

//连接数据库
bool DUtil::OpenDB() {
    mysql_init(reinterpret_cast<MYSQL *>(&connect));
    if (mysql_real_connect(reinterpret_cast<MYSQL *>(&connect), host.c_str(), DBUsername.c_str(), DBPasswd.c_str(),
                           database.c_str(), port, nullptr, 0)) {
        isOpen = true;
        return true;
    }
    cout << "mysql connect fail" << endl;
    return false;
}

//关闭数据库
bool DUtil::CloseDB() {
    mysql_close(reinterpret_cast<MYSQL *>(&connect));
    return false;
}

//查询用户进行登录
bool DUtil::queryUser(string &username, string &password) {
    bool flag = false;
    if (isOpen) {
        string sql = "select UserName,PassWord from User where UserName = '" + username + "' and PassWord = '" + password + "'";
        int res = mysql_query(reinterpret_cast<MYSQL *>(&connect), sql.c_str());
        if (!res) {
            result = mysql_store_result(reinterpret_cast<MYSQL *>(&connect));
            if (result && mysql_num_rows(result)) {
                flag = true;
            }
        } else {
            cout << "queryUser sql failed!" << endl;
        }
    } else {
        cout << "connect failed!" << endl;
    }
    mysql_free_result(result);//释放结果资源
    return flag;
}

//注册用户
bool DUtil::insertUser(string &username, string &password) {
    bool flag = false;
    if (isOpen){
        string sql = "insert into `User` values ( null,'" + username + "','" + password + "')";
        mysql_query(reinterpret_cast<MYSQL *>(&connect), sql.c_str());
        flag = true;
    } else{
        cout << "connect failed!" << endl;
    }
    return flag;
}

//查询是否有相同用户名,有则返回true
bool DUtil::queryUserName(string &username) {
    bool flag = false;
    if (isOpen) {
        string sql = "select UserName from User where UserName = '" + username +"'";
        int res = mysql_query(reinterpret_cast<MYSQL *>(&connect), sql.c_str());
        if (!res) {
            result = mysql_store_result(reinterpret_cast<MYSQL *>(&connect));
            if (result && mysql_num_rows(result)) {
                flag = true;
            }
        } else {
            cout << "queryUsername sql failed!" << endl;
        }
        mysql_free_result(result);//释放结果资源
    } else {
        cout << "connect username failed!" << endl;
    }

    return flag;
}





