all: out.exe

out.exe: main.o framework.o declarations.o cube.o
	g++ main.o framework.o declarations.o cube.o -o out.exe -lopengl32 -lgdi32 -static -ggdb -mwindows
	
main.o: main.cpp framework.h common.h
	g++ -c -std=c++0x main.cpp declarations.cpp -lopengl32 -static -ggdb
	
framework.o: framework.h common.h framework.cpp
	g++ -c -std=c++0x framework.cpp -ggdb
	
declarations.o: framework.h
	g++ -c -std=c++0x declarations.cpp -ggdb
	
cube.o: cube.h
	g++ -c -std=c++0x cube.cpp -ggdb
	
clean:
	rm *.o