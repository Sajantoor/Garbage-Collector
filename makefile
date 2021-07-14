tgc: main.cpp
	g++ -Wall -std=c++11 -o tgc.out main.cpp overrides.cpp garbageCollector.cpp
leak:
	g++ -Wall -std=c++11 -o tgc.out main.cpp overrides.cpp garbageCollector.cpp -D LEAK
debug:
	g++ -Wall -std=c++11 -o tgc.out main.cpp overrides.cpp garbageCollector.cpp -D DEBUG
example: 
	g++ -Wall -std=c++11 -o basic.out examples/basic.cpp overrides.cpp garbageCollector.cpp
example_debug: 
	g++ -Wall -std=c++11 -o basic.out examples/basic.cpp overrides.cpp garbageCollector.cpp -D DEBUG
clean:
	rm -rf *.out