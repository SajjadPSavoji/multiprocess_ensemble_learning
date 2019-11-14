CC = g++
CFLAGS = -I
STD = -std=c++11

all: EnsembleClassifier.o linear_clf.o voter.o

EnsembleClassifier.o : ensemble.cpp  utils.hpp
	$(CC) $(CFLAGS) $(STD) ensemble.cpp  -o EnsembleClassifier.o

linear_clf.o: linear_clf.cpp
	$(CC) $(CFLAGS) $(STD) linear_clf.cpp -o linear_clf.o

voter.o: voter.cpp
	$(CC) $(CFLAGS) $(STD) voter.cpp -o voter.o

clean:
	rm *.o
	rm *.out
