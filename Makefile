OBJS = \
	DispatcherBase.o \
	Dispatcher.o \
	ExampleTask.o \
	InitialExampleTask.o \
	ITask.o \
	Pool.o \
	PoolsArray.o \
	ProtectedCounter.o \
	samcode.o \
	Worker.o \
	WorkRequest.o

EXE = samcode

CXX = c++ -c
CC  = cc -c
LD  = c++

CFLAGS   = -std=c++11 -O0 -g3 -Wall -fmessage-length=0 -pthread
CCFLAGS  =
CPPFLAGS = -D__cplusplus=201103L
LDFLAGS = -pthread

all:	samcode

$(EXE):	$(OBJS)
	@echo "Linking $@ ..."
	$(LD) $(LDFLAGS) -o $@ $^

%.o:	src/%.cpp
	@echo "Compiling $@ ..."
	$(CXX) $(CFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	src/%.c
	@echo "Compiling $@ ..."
	$(CC) $(CFLAGS) $(CCFLAGS) -o $@ $<

clean:
	rm $(EXE) $(OBJS)
