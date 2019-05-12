# Cross Platform Makefile
# Compatible with MSYS2/MINGW, Ubuntu 14.04.1 and Mac OS X


#CXX = g++
#CXX = clang++

EXE = FalseCompiler
SOURCES = lexic.cpp syntax.cpp generator.cpp main.cpp 

OBJS = $(addsuffix .o, $(basename $(notdir $(SOURCES))))

LIBS = -lmingw32

CXXFLAGS = -Wall -Wformat -static-libgcc -static-libstdc++ -g
#-mwindows
CFLAGS = $(CXXFLAGS)


%.o:%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:../%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.o:../../%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

all: $(EXE)
	@echo Build complete for $(ECHO_MESSAGE)

$(EXE): $(OBJS)
	$(CXX) -o $@ $^ $(CXXFLAGS) $(LIBS)

clean:
	rm -f $(EXE) $(OBJS)
