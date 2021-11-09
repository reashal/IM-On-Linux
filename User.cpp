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



