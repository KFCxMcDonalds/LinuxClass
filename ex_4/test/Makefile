all: main Plugin1.so Plugin2.so
main: main.cpp
	g++ main.cpp -o main -ldl
Plugin1.so: LineCountPlugin.cpp
	g++ -shared -fPIC -o Plugin1.so LineCountPlugin.cpp -ldl
Plugin2.so: ByteCountPlugin.cpp
	g++ -shared -fPIC -o Plugin2.so ByteCountPlugin.cpp -ldl
