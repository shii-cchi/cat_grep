CC = gcc
CFLAGS = -std=c11 -D_GNU_SOURCE -Wall -Werror -Wextra
SOURCES_1 = grep.c
SOURCES_2 = grep.o
SOURCES_3 = test/test_grep.c
SOURCES_4 = test_grep.o
EXECUTABLE = test_grep

all: grep

grep: clean 
	$(CC) $(CFLAGS) -c $(SOURCES_1)
	ar rc grep.a $(SOURCES_2)
	rm -rf grep.o
	ranlib grep.a

test: clean grep
	$(CC) $(CFLAGS) -c $(SOURCES_3)
	$(CC) $(CFLAGS) -o  $(EXECUTABLE) $(SOURCES_4) grep.a
	rm -rf $(SOURCES_2) $(SOURCES_4)
	bash test/test.sh
	rm -rf $(EXECUTABLE)

clean: 
	rm -rf $(EXECUTABLE) grep.o grep.a
