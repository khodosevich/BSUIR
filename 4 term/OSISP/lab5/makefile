CC = gcc


SRC = main.c

main: $(SRC)
	$(CC) -o $@ $^

.PHONY: run
run:
	make main
	./main
	make clean

.PHONY: clean
clean:
	rm main
