CC = gcc
CDFLAGS = -Wall -I.
LDFLAGS =
OBJFILES = main.o parser.o
TARGET = main

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CDFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)

clean:
	rm -f $(OBJFILES) %(TARGET) *~
	