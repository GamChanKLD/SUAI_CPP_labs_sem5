CXX = g++
CXXFLAGS = -std=c++98 -Wall -Wextra -Iinclude
SRC = $(wildcard src/*.cpp)

conference: $(SRC) $(wildcard include/*.h)
	$(CXX) $(CXXFLAGS) $(SRC) -o conference

clean:
	rm -f conference
