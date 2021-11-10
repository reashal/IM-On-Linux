//
// Created by masker on 2021/11/5.
//

#include "main.h"
#include "User.h"
#include "DUtil.h"
#include <iostream>
#include <string>

using namespace std;

int main(){

    User user;
    DUtil dUtil;

    string userName;
    string passWord;
    string ip;
    bool flag;
    char l_or_r;

    //选择界面
    cout << "--------*****************---------" <<endl;
    cout << "--------*****************---------" <<endl;
    cout << "|****        1 login         ****|" <<endl;
    cout << "|****        2 register      ****|" <<endl;
    cout << "--------*****************---------" <<endl;
    cout << "--------*****************---------" <<endl;
    cout << "please case : ";
    cin >> l_or_r;

    //选择界面
    if (l_or_r == '1'){
        //  login
        printf("请输入用户名：");
        cin >> userName;
        cout << endl;

        printf("请输入密码：");
        cin >> passWord;
        cout << endl;


        //连接数据库
        dUtil.OpenDB();

        //登录查询数据库内有没有对应账号密码
        flag = dUtil.queryUser(userName,passWord);
        if(flag){
            cout << "login success!" << endl;
        } else{
            cout << "login fail!" << endl;
        }
    } else{
        //  register
        cout << "-------register-------" << endl;
        printf("请输入用户名：");
        cin >> userName;
        cout << endl;

        printf("请输入密码：");
        cin >> passWord;
        cout << endl;

        while (user.sameUserName(userName)){
            cout << "请重新输入用户名：" << endl;
            cin >> userName;
        }

        flag = user.registerUser(userName,passWord);
        if (flag){
            cout << "register success!" << endl;
        }

    }

}