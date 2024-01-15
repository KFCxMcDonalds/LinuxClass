#include"IClient.h"

// 该类继承IClient接口，实现的功能是向服务器发送消息，接收服务器的消息并显示
class SendClient: public IClient
{
    public:
        SendClient(); // 构造函数
        // 不重载Connect方法，因为不需要更改接口中的设置
        void Start();
};
