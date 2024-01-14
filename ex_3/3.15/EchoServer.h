#include"IServer.h"

// 该类继承IServer接口，实现的功能是接收客户发送的消息并回送给客户
class EchoServer: public IServer
{
    public:
        EchoServer();
        // 没有重载Bind()函数，因为该服务器就是Ipv4+TCP，与接口中相同
        void Start(); // 实现Echo功能
};
