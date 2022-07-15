CC = g++
CFLAGS = -Wall -std=c++14
OBJECTS = *.cpp

main: $(OBJECTS)
	$(CC) $(OBJECTS) -o main $(CFLAGS)

run: main
	./main -nr
	make clean

test: main
	./main -e
	make clean

clean:
	rm main