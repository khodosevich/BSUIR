CC=gcc

all:
	$(CC) parent.c -o parent
	$(CC) child.c -o child
	export CHILD_PATH=/home/matvey/CLionProjects/labs_osisp/lab2/child
	export ENV_PATH=/home/matvey/CLionProjects/labs_osisp/lab2/env.txt
	export LC_COLLATE=C
clean:
	rm -rf *.o parent
	rm -rf *.o child
