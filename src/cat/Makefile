CC = gcc
CFLAGS = -std=c11 -Wall -Werror -Wextra
SOURCES_1 = cat.c
SOURCES_2 = cat.o
SOURCES_3 = test/test_cat.c
SOURCES_4 = test_cat.o
EXECUTABLE = test_cat

all: cat

cat: clean 
	$(CC) $(CFLAGS) -c $(SOURCES_1)
	ar rc cat.a $(SOURCES_2)
	rm -rf cat.o
	ranlib cat.a

test: clean cat
	$(CC) $(CFLAGS) -c $(SOURCES_3)
	$(CC) $(CFLAGS) -o  $(EXECUTABLE) $(SOURCES_4) cat.a
	rm -rf $(SOURCES_2) $(SOURCES_4)
	bash test/test.sh
	rm -rf $(EXECUTABLE)

clean: 
	rm -rf $(EXECUTABLE) cat.o cat.a
