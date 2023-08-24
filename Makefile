CC := clang

all: mp3

mp3: driver.o ptrs.o
	$(CC) -g -z noexecstack -o $@ driver.o ptrs.o

clean:
	rm -f mp3 driver.o ptrs.o

