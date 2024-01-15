main: main.cpp Plugin.so
	g++ -o main main.cpp -ldl
Plugin.so: WorldPlugin.cpp # change this to use different plugin
	g++ -shared -fPIC -o plugin.so WorldPlugin.cpp -ldl
