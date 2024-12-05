CC = gcc
CDFLAGS = -Wall -I.
LDFLAGS =
OBJFILES = main.o parser.o symtable.o error.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CDFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	del -f $(OBJFILES) %(TARGET) *~
	