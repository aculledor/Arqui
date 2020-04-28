CC= gcc -Wall -mavx -O0
LIBS = -msse3 -lm
HEADER_FILES_DIR = ./headerFiles
INCLUDES = -I $(HEADER_FILES_DIR)

MAIN= ejecutable

SRCS = main.c sec.c

DEPS = $(HEADER_FILES_DIR)/header.h 

OBJS = $(SRCS:.c=.o)

$(MAIN): $(OBJS)
	$(CC) -o $(MAIN) $(OBJS) $(LIBS) $(INCLUDES) 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(INCLUDES)

cleanall: clean
	rm -f $(MAIN)
clean:
	rm -f *.o *~
