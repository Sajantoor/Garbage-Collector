tgc: main.cpp
	g++ -Wall -std=c++11 -o tgc.out main.cpp overrides.cpp garbageCollector.cpp
clean:
	rm -rf *.out