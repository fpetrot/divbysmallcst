il : li.c
	$(CC) -O3 -o $@ $<
li : li.c
	$(CC) -DLI -O3 -o $@ $<

N ?= 25
SYSTEMC = /opt/systemc-2.3.4/
check : divu$(N).x
	LD_LIBRARY_PATH=$(SYSTEMC)/lib-linux64 ./$<

divu$(N).x : divu$(N).cpp
	g++ -O3 -I $(SYSTEMC)/include divu$(N).cpp -o divu$(N).x -L $(SYSTEMC)/lib-linux64 -lsystemc
