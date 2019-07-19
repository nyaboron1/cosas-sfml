all:
	g++ -c doodlejump.cpp -ISFML/include
	g++ doodlejump.o -o doodlejump-sfml -LSFML/lib -lsfml-graphics -lsfml-window -lsfml-system
run: all
	export LD_LIBRARY_PATH=SFML/lib && ./doodlejump-sfml
clean:
	rm -f doodlejump.o doodlejump-sfml
