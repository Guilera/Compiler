CCSOURCES = $(wildcard src/*.cc)

all: compiler clean

compiler: $(CCSOURCES:.cc=.o)
	@g++ -std=c++11 -o $@ $^ 

%.o: %.cc %.h
	@g++ -c -std=c++11 $< -o $@

%.o: %.cc
	@g++ -c -std=c++11 $< -o $@

clean:
	@-rm -f *.o *.d *~

-include $(CCSOURCES:.cc=.d)

%.d: %.cc
	@g++ -std=c++11 $< -MM -MD
