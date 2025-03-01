CXX = g++
CXXFLAGS = -Wall

proj3: Strand.o Sequencer.o proj3.cpp
	$(CXX) $(CXXFLAGS) Strand.o Sequencer.o proj3.cpp -o proj3

Strand.o: Strand.h Strand.cpp
	$(CXX) $(CXXFLAGS) -c Strand.cpp

Sequencer.o: Strand.o Sequencer.h Sequencer.cpp
	$(CXX) $(CXXFLAGS) -c Sequencer.cpp

clean:
	rm *.o*
	rm *~

run:
	./proj3

val:
	valgrind ./proj3

