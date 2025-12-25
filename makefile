CXX := g++
CXXFLAGS := -std=c++20 -O2 -g -Wall -Wextra
INCLUDES := -Isrc
LDFLAGS := -lX11 -lGL -ldl -lpthread

SRC := $(wildcard src/*.cpp)
OBJ := $(SRC:.cpp=.o)

app: $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -f $(OBJ) app

