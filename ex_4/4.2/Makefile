all: main WorldPlugin.so ChinaPlugin.so OtherPlugin.so
main: main.cpp
	g++ -o main main.cpp -ldl
ChinaPlugin.so: plugin/ChinaPlugin.cpp
	g++ -shared -fPIC -o plugin/ChinaPlugin.so plugin/ChinaPlugin.cpp -ldl
WorldPlugin.so: plugin/WorldPlugin.cpp
	g++ -shared -fPIC -o plugin/WorldPlugin.so plugin/WorldPlugin.cpp -ldl
OtherPlugin.so: plugin/OtherPlugin.cpp
	g++ -shared -fPIC -o plugin/OtherPlugin.so plugin/OtherPlugin.cpp -ldl
