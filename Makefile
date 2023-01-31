FLAGS= -Wall
CC= gcc
LIBS= -lpthread -lws -pthread -lcjson -ldb-utils
OBJECTS=objects
BUILD=build
SRC=src
INCLUDE=include


all: $(OBJECTS)/main.o $(BUILD)/main 


$(BUILD)/main: $(OBJECTS)/main.o
	mkdir -p $(BUILD)
	$(CC) $(FLAGS) -o $(BUILD)/main $(OBJECTS)/main.o  $(LIBS)

$(OBJECTS)/main.o: $(SRC)/*.c $(INCLUDE)/*.h
	mkdir -p $(OBJECTS)
	$(CC) $(FLAGS) -c $< -o $@ $(LIBS)

clean:
	rm -f $(OBJECTS)/*
	rm -f $(BUILD)/*