all: main Plugin1.so Plugin2.so
main: main.cpp
	g++ main.cpp -o main -ldl
Plugin1.so: WorldPlugin.cpp
	g++ -shared -fPIC -o Plugin1.so WorldPlugin.cpp -ldl
Plugin2.so: ChinaPlugin.cpp
	g++ -shared -fPIC -o Plugin2.so ChinaPlugin.cpp -ldl
