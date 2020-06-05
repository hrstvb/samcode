OBJS = DispatcherBase.cpp Dispatcher.cpp ExampleTask.cpp InitialExampleTask.cpp ITask.cpp Pool.cpp PoolsArray.cpp ProtectedCounter.cpp samcode.cpp Worker.cpp WorkRequest.cpp

CXX = c++
CC  = cc
LD  = c++

CFLAGS   = -std=c++11 -O0 -g3 -Wall -fmessage-length=0 -pthread
CCFLAGS  =
CPPFLAGS = -D__cplusplus=201103L
LDFLAGS = -pthread

all:	samcode

samcode:	$(OBJS)
	$(LD) $(LDFLAGS) -o $@ $^

%.o:	%.cpp
	@echo "Compiling $@..."
	@echo "$(CXX) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<"
	# $(CXX) -c $(CFLAGS) $(CPPFLAGS) -o $@ $<

%.o:	%.c
	# $(CC) -c $(CFLAGS) $(CCFLAGS) -o $@ $<

clean:
	rm samcode $(OBJS)
