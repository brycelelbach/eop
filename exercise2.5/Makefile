CXX=g++

ifdef DEBUG
	BOOST_ROOT=/opt/boost/1.52.0-debug
	CXXFLAGS+=-O0 -g
else
	BOOST_ROOT=/opt/boost/1.52.0-release
	CXXFLAGS+=-O3 -finline
endif

CXXFLAGS+=-std=c++0x -L$(BOOST_ROOT)/stage/lib -Wl,-rpath $(BOOST_ROOT)/stage/lib
INCLUDES=-I$(BOOST_ROOT)
LIBS=-lrt
ADDITIONAL_SOURCES=
PROGRAMS=linear_congruential
DIRECTORIES=build

all: directories $(PROGRAMS)

.PHONY: directories
directories: $(DIRECTORIES)/  

$(DIRECTORIES)/:
	mkdir -p $@ 

% : %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) $(LIBS) $(ADDITIONAL_SOURCES) $< -o build/$@

clean:
	rm -rf $(DIRECTORIES) 

