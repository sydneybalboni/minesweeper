 # @file Makefile
 # @brief Builds the files for the minesweeper final project
 # 
 # Course: CPE2600
 # Section: 131
 # Assignment: Final Project
 # Name: Sydney Balboni 
 # Description: This final project is a minesweeper console game

CC = gcc
CFLAGS = -c -Wall
LDFLAGS = -lncurses
SOURCES = minesweeper.c field.c main.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = minesweeper

all: $(SOURCES) $(EXECUTABLE)

-include $(OBJECTS:.o=.d)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@
	$(CC) -MM $< > $*.d

clean:
	rm -rf $(OBJECTS) $(EXECUTABLE) *.d
