CXX = g++
CXXFLAGS = -std=c++20 -Wall -Wextra

TARGET = zzz
OBJ = simple_sorts.o shell_sort.o merge_sort.o heap_sort.o quick_sort.o \
3way_partit_sort.o counting_sort.o tests.o main.o

.PHONY: all clean  # prevent make from confusing the phony target with a file name

all: $(TARGET)

clean:
	rm -rf $(TARGET) *.o

re: clean all

simple_sorts.o: simple_sorts.cpp
	$(CXX) $(CXXFLAGS) -c simple_sorts.cpp

shell_sort.o: shell_sort.cpp
	$(CXX) $(CXXFLAGS) -c shell_sort.cpp

merge_sort.o: merge_sort.cpp
	$(CXX) $(CXXFLAGS) -c merge_sort.cpp

heap_sort.o: heap_sort.cpp
	$(CXX) $(CXXFLAGS) -c heap_sort.cpp

quick_sort.o: quick_sort.cpp
	$(CXX) $(CXXFLAGS) -c quick_sort.cpp

3way_partit_sort.o: 3way_partit_sort.cpp
	$(CXX) $(CXXFLAGS) -c tests.cpp 3way_partit_sort.cpp

counting_sort.o: counting_sort.cpp
	$(CXX) $(CXXFLAGS) -c counting_sort.cpp

tests.o: sorts.h tests.cpp
	$(CXX) $(CXXFLAGS) -c tests.cpp

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(TARGET)
