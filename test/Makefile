all: server client FileStatPlugin.so WorldPlugin.so
server: Server.cpp TestStatus.cpp
	g++ -o server Server.cpp TestStatus.cpp -ldl
client: Client.cpp TestStatus.cpp
	g++ -o client Client.cpp TestStatus.cpp
FileStatPlugin.so: plugin/FileStatTestPlugin.cpp
	g++ -shared -fPIC -o plugin/FileStatPlugin.so plugin/FileStatTestPlugin.cpp -ldl
WorldPlugin.so: plugin/WorldTestPlugin.cpp
	g++ -shared -fPIC -o plugin/WorldPlugin.so plugin/WorldTestPlugin.cpp -ldl
OtherPlugin.so: plugin/OtherPlugin.cpp
	g++ -shared -fPIC -o plugin/OtherPlugin.so plugin/OtherPlugin.cpp -ldl
