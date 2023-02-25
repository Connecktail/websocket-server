FLAGS= -Wall
CC= gcc
LIBS= -lpthread -lws -lcjson -ldb-utils
OBJECTS=objects
BUILD=build
SRC=src
INCLUDE=include

OBJECTS_FILES=$(OBJECTS)/main.o $(OBJECTS)/websocket.o $(OBJECTS)/actions.o

all: $(BUILD)/main

$(BUILD)/main: $(OBJECTS_FILES)
	mkdir -p $(BUILD)
	$(CC) $(OBJECTS_FILES) -o $(BUILD)/main $(LIBS)


$(OBJECTS)/%.o: $(SRC)/%.c $(INCLUDE)/*.h
	$(CC) $(FLAGS) -c -fPIC -o $@ $<

clean:
	rm -f $(OBJECTS)/*
	rm -f $(BUILD)/*