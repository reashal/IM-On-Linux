//
// Created by masker on 2021/11/3.
//

#include "DUtil.h"
#include <string>
using namespace std;

class User {
public:
    string username;
    string password;
    string ip;
    DUtil dUtil;

    User();

    string getUsername() const;

    void setUsername(string username);

    string getPassword() const;

    void setPassword(string password);

    string getIp() const;

    void setIp(string ip);

    bool sameUserName(string username);

    bool registerUser(string username,string passwd);

};
