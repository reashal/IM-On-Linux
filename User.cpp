//
// Created by masker on 2021/11/3.
// 用户
//
#include <iostream>
#include <string>
#include <vector>
#include "User.h"

using namespace std;

string User::getUsername() const {
    return username;
}

void User::setUsername(string username) {
    User::username = username;
}

string User::getPassword() const {
    return password;
}

void User::setPassword(string password) {
    User::password = password;
}

string User::getIp() const {
    return ip;
}

void User::setIp(string ip) {
    User::ip = ip;
}

User::User() {

}

//检测用户名是否重复,重复则true
bool User::sameUserName(string userName) {
    bool flag = false;

    //连接数据库
    dUtil.OpenDB();

    if (dUtil.queryUserName(userName)){
        flag = true;
        cout << "用户名重复！" << endl;
    }
    return flag;
}

//注册用户
bool User::registerUser(string userName,string passwd){
    bool flag = false;

    dUtil.OpenDB();

    if (dUtil.insertUser(userName,passwd)){
        flag = true;
        cout << "注册成功！" << endl;
    }
}



