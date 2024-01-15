# LinuxCourse
电子科技大学研究生课程：Linux高级编程实验源代码

## 实验要求及运行方法
### 1 ex_1
#### 1.1 Make的使用
`ex_1/make/`
##### 实验要求
自己编写一个程序，再编写其Makefile文件。注意，在Makefile文件对应的依赖关系树，必须是3层的完全二叉树。给出程序代码、Makefile文件。

##### 运行方法
```shell
make
```
#### 1.2 GDB的使用
`ex_1/GdbMultiProcess/`
##### 实验要求
自己编写一个多进程的程序，通过截图和文字，说明如何调试多进程。

##### 运行方法
```shell
gcc -o test -g twoWayPipe.c
gdb test # 开始调试
```

#### 1.3 Googletest的使用
`ex_1/googletest/`
##### 实验要求
自己编写一个程序，然后使用googletest对其进行测试。至少要包含三个测试用例。需要给出程序代码，测试代码，并进行适当分析。

##### 运行方法
```shell
make
./calculator_test
```
#### 1.4 Valgrind的使用
`ex_1/valgrind/`
##### 实验要求
自己编写一个程序，然后使用valgrind检测其有无内存泄露、指针访问违规。需要给出程序代码，截图和文字说明。
##### 运行方法
```shell
g++ -o example example.cpp
valgrind ./example
```
### 2 ex_2
#### 2.1 将一个类的一个对象序列化到文件
`ex_2/v1/`
##### 运行方法
```shell
g++ -c Person.cpp
g++ Person.o main.cpp -o main
./main
```

#### 2.2 将一个类的多个对象序列化到文件
`ex_2/v2/`
##### 运行方法
```shell
make
./main
```

#### 2.3 将两个类的多个对象序列化到文件 
`ex_2/v3/`
##### 运行方法
```shell
make
./main
```

#### 2.4 将一个类的对象序列化到文件
`ex_2/v4/`
##### 实验要求
按照面向对象的方法，解决类的多个对象序列化到文件的问题
##### 运行方法
```shell
make
./main
```
#### 2.5 将一个类的对象序列化到文件
`ex_2/v4/`
##### 实验要求
序列化的目的地不仅可以是文件，还可以是其他，即可配置性
在config.txt配置
##### 运行方法
```shell
make
./main
```
### 3 ex_3
对基本TCP套接口通信机制进行封装。要求使用以下五种编程范式，封装通信库；并使用五种封装后通信库，实现echo服务器和客户端。

<font color="#e67e22">运行方法相同</font>
##### 运行方法
```shell
make

# terminal1
./server

# terminal2
./client
Hello # 输入发送给服务器的信息
##... 其他信息
exit # 退出连接
```

#### 3.1 传统C的结构化程序设计思想
`ex_3/3.12`  <font size=1>鬼知道老师为啥命名3.12/14/..</font>
#### 3.2 面向对象程序设计思想
`ex_3/3.14`
#### 3.3 基于接口的程序设计思想
`ex_3/3.15`
#### 3.4 静态的面向对象程序
没懂，不是自己写的，直接运行的示例代码
`ex_3/3.16`
#### 3.5 面向方法的程序设计思想
`ex_3/3.17`

### 4 ex_4
#### 4.1 插件的更新
##### 实验要求
- 开发一个程序，向屏幕打印“Hello World”
- 在不重新编译链接原程序的前提下，将打印的文字改为“Hello China”
##### 运行方法
```shell
g++ -shared -fPIC -o Plugin.so WorldPlugin.cpp -ldl
g++ -o main main.cpp -ldl
./main

# 更新插件：编译ChinaPlugin.cpp -> Plugin.so
g++ -shared -fPIC -o Plugin.so ChinaPlugin.cpp -ldl
./main
```
#### 4.2 多插件的使用
##### 实验要求
- 同时要打印“Hello World”，打印“Hello China”，甚至同时打印未来才会增加的其他打印信息
- 打印未来的这些信息，也不能重新编译链接原程序
##### 运行方法
```shell
make
./main
```

如果要加新的插件：
1. 在plugin里面新增文件：`newPlugin.cpp`
2. Makefile里修改：
    ```shell
    # 修改：
    all: main WorldPlugin.so ChinaPlugin.so OtherPlugin.so NewPlugin.so
    # 中间不变，文件最后增加：
    NewPlugin.so: plugin/newPlugin.cpp
        g++ -shared -fPIC -o plugin/NewPlugin.so plugin/newPlugin.cpp -ldl
    ```
3. 运行
#### 4.3 多插件的选择和使用
`ex_4/4.3`
##### 实验要求
- 版本2是同时调用所有插件的打印功能，现在要求一次只调用一种功能
- 插件导出一个Help接口，向屏幕输出信息，使用户知道该插件实现了何种打印功能，以及该功能对应的ID
##### 运行方法
```shell
make
./main
./main help
./main 1
./main 2
```
#### 4.4 插件设计优化--减少接口
略
> 要求用接口统一上面的所有Plugin，但我一开始就用了接口，所以这个要求已经满足了，就是4.3的代码。

#### 4.5 综合练习
`ex_4/test`
##### 实验要求
现在需要实现一个软件系统，该系统可对文件进行统计分析。究竟对文件进行什么样的统计分析，最终用户自己也不是很清楚，目前只知道需要统计文件的行数。也就是说，本软件系统将会随时面临，增加文件统计新功能的难题。请结合本实验内容，设计并实现这样一个面向文件统计功能的插件系统。（需要实现的插件包括：统计某个文件的行数，统计某个文件的字节数）
##### 运行方法
```shell
make
./main
./main 1 testfile.txt
./main 2 testfile.txt
```

### 5 考察实验
`test/`
##### 实验要求
开发一套分布式测试平台。具有以下功能：
1. 测试任务由测试中心统一管理，当有测试任务时，由管理中心服务器向远端若干测试机进行任务分发；
2. 测试中心需要跟踪远端测试机的测试任务执行情况，待远端测试机任务执行完成后，回收所有测试结果并进行分析；
3. 支持测试中心对远端测试机的测试功能模块的动态更新；
4. 支持测试中心对远端测试机测试任务的指定迁移。
##### 运行方法
主要是做了一些测试来展示功能，这里把一些主要命令说一下，实验的顺序和效果请同学们自己设置一下，可以运行多个client。

```shell
make
```
make之后会在plugin文件夹里编译出插件的动态链接库.so文件，文件的名字就是插件的名字，比如`FileStatPlugin.so`插件的名字为`FileStatPlugin`
```
# server
./server

# client
./client

# client2
./client
```
运行服务器和客户机之后命令行会输出提示，根据提示进行：
- exit：退出当前连接的客户端
- migrate：客户端数据迁移（到文件）
    - migrate之后指定迁移文件的地址
- load: 客户端数据载入（从文件）
    - load之后指定载入的文件地址
- plugin name：客户端执行插件

> 客户端的迁移数据只包含了执行过的任务和任务状态：running、finished，比较简单，想要做的更复杂可以考虑数据的迁移
