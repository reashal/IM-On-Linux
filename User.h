//
// Created by masker on 2021/11/3.
//

#ifndef IM_FOR_LINUX_USER_H
#define IM_FOR_LINUX_USER_H
#include <string>

using namespace std;

class User {
public:
    string username;
    string password;
    string ip;

    User();

    string getUsername() const;

    void setUsername(string username);

    string getPassword() const;

    void setPassword(string password);

    string getIp() const;

    void setIp(string ip);
};


#endif //IM_FOR_LINUX_USER_H
