#include"chatserver.hpp"
#include"chatservice.hpp"
#include"public.hpp"

#include<iostream>
#include<string>
#include<functional>
#include"json.hpp"
using namespace std;
using json = nlohmann::json;
using namespace placeholders;

ChatServer::ChatServer(EventLoop *loop,
               const InetAddress &listenAddr,
               const string &nameArg)
               :server_(loop,listenAddr,nameArg)
{
    server_.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

    server_.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

    server_.setThreadNum(4);
}
void ChatServer::start()
{
    server_.start();
}

void ChatServer::onConnection(const TcpConnectionPtr &conn)
{
    //客户端断开链接
    if(!conn->connected())
    {
        ChatService::instance()->clientCloseException(conn);
        conn->shutdown();
    }
}

    //上报读写事件相关信息的回调函数
void ChatServer::onMessage(const TcpConnectionPtr &conn,
                        Buffer*buffer,
                        Timestamp time)
{
    string buf = buffer->retrieveAllAsString();
    //数据的反序列化
    json js = json::parse(buf);

    auto msgHanlder = ChatService::instance()->getHandler(js["msgid"].get<int>());

    msgHanlder(conn, js, time);
}