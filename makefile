all: out.exe

out.exe: object/main.o object/framework.o object/cube.o object/texture.o
	g++ object/main.o object/framework.o object/cube.o -o out.exe -lopengl32 -lgdi32 -static -ggdb
	
object/main.o: header/common.h source/main.cpp
	g++ -Iheader -c -std=c++0x source/main.cpp -lopengl32 -static -ggdb
	mv main.o object
	
object/framework.o: header/framework.h header/common.h source/framework.cpp
	g++ -Iheader -c -std=c++0x source/framework.cpp -ggdb
	mv framework.o object
	
object/cube.o: header/cube.h header/common.h source/cube.cpp
	g++ -Iheader -c -std=c++0x source/cube.cpp -ggdb
	mv cube.o object

object/texture.o: header/texture.h header/common.h source/texture.cpp
	g++ -Iheader -c -std=c++0x source/texture.cpp -ggdb
	mv texture.o object 
clean:
	rm object/*.o