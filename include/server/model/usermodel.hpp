#ifndef USERMODEL_H
#define USERMODEL_H

#include"user.hpp"

class UserModel
{
public:
    //User表的增加方法
    bool insert(User &user);

    //根据用户号码查询id
    User query(int id);

    //更新用户状态
    bool updateState(User user);

    //服务器断开时，重置用户登录状态
    void resetState();

private:
};

#endif