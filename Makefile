CXX = g++
CXXFLAGS = -I/usr/include/SDL2
LDFLAGS = -lSDL2

TARGET = application
SRCS =   main.cpp perlin.cpp  utilitaires.cpp

$(TARGET): $(SRCS)
	$(CXX) -o $(TARGET) $(SRCS) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGET)
