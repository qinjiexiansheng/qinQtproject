OBJS=irinfo.cpp.o readcfgfile.cpp.o table.cpp.o  calactmp.cpp.o temp.cpp.o 

%.cpp.o:%.cpp
	g++ -fpic -c $< -o $@


all:$(OBJS)
	g++ -shared -fpic -o libtemp.so $(OBJS)
clean:
	rm *.o  *.so
