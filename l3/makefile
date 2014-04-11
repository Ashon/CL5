# suffixes
.SUFFIXES : .c .o

## predefined macros.
# c compiler
CC = gcc

# include & lib path
INCLUDE = ./
LIBS = ./

# files
OBJECT = main.o
SOURCE = main.c
TARGET = main


## make procedures
# generate exacute file
$(TARGET) : $(OBJECT)
	$(CC) -o $(TARGET) $(OBJECT)

# generate object file
$(OBJECT) : $(SOURCE)
	$(CC) -c $(SOURCE)

# clean
clean :
	rm -rf $(OBJECT) $(TARGET) core
