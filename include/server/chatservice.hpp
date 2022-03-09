#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
#include <mutex>
using namespace std;
using namespace muduo;
using namespace muduo::net;

#include "redis.hpp"
#include "usermodel.hpp"
#include "offlinemessagemodel.hpp"
#include "friendmodel.hpp"
#include "groupmodel.hpp"
#include "json.hpp"
using json = nlohmann::json;

using MsgHandler = std::function<void(const TcpConnectionPtr &conn, json &js, Timestamp)>;

//聊天服务业务类
class ChatService
{
public:
    //获取单例对象的接口函数
    static ChatService *instance();
    //处理登录业务
    void login(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //处理注册业务
    void reg(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //一对一聊天
    void oneChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //添加好友
    void addFriend(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //获取消息对应的处理器
    MsgHandler getHandler(int msgid);
    //处理用户异常退出
    void clientCloseException(const TcpConnectionPtr &conn);
    //用户注销操作
    void loginout(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //处理服务器断开时修改用户登录状态
    void reset();
    //创建群组业务
    void createGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //加入群组业务
    void addGroup(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //群组聊天业务
    void groupChat(const TcpConnectionPtr &conn, json &js, Timestamp time);
    //从redis消息队列中获取订阅的消息
    void handleRedisSubscribeMessage(int userid, string msg);

private :
    //获取单例对象的接口函数
    ChatService();

    //存储消息id和其对应的业务处理方法
    unordered_map<int, MsgHandler> _msgHandlerMap;

    //存储在线用户的通信连接
    unordered_map<int, TcpConnectionPtr> _userConnMap;

    //定义互斥锁，保证_userConnMap的线程安全
    mutex _connMutex;

    UserModel _userModel;

    offlineMsgModel _offlineMsgModel;

    FriendModel _friendModel;

    GroupModel _groupModel;

    Redis _redis;
};

#endif