all: debug optimize

debug: main_debug spainmain_debug

main_debug: main.cpp
	g++ -g -o main_debug main.cpp
	./main_debug

spainmain_debug: spainmain.cpp
	g++ -g -o spainmain_debug spainmain.cpp
	./spainmain_debug

optimize: main_optimize spainmain_optimize

main_optimize: main.cpp
	g++ -O3 -o main_optimize main.cpp
#	./main_optimize

spainmain_optimize: spainmain.cpp
	g++ -O3 -o spainmain_optimize spainmain.cpp
#	./spainmain_optimize

clean:
	rm -f main_debug main_optimize spainmain_debug spainmain_optimize