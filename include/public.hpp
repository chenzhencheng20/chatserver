#ifndef PUBLIC_H
#define PUBLIC_H

/*
    server和client的公共文件
*/
enum EnMsgType
{
    LOGIN_MSG = 1,//登录消息
    LOGIN_MSG_ACK,
    LOGINOUT_MSG,
    REG_MSG, //注册消息
    REG_MSG_ACK,
    ONE_CHAT_MSG,//聊天信息
    ADD_FRIEND_MSG,//添加好友信息

    CREATE_GROUP_MSG,//创建群聊
    ADD_GROUP_MSG,//加入群聊
    GROUP_CHAT_MSG//群聊天
};


#endif