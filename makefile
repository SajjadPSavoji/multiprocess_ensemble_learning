CC = g++
CFLAGS = -I
STD = -std=c++11

all: EnsembleClassifier.out linear_clf.o voter.o

EnsembleClassifier.out : ensemble.cpp  utils.hpp  Dir.hpp  CSV.hpp
	$(CC) $(CFLAGS) $(STD) ensemble.cpp  -o EnsembleClassifier.out

linear_clf.o: linear_clf.cpp lc_utils.hpp CSV.hpp LC.hpp
	$(CC) $(CFLAGS) $(STD) linear_clf.cpp -o linear_clf.o

voter.o: voter.cpp voter_utils.hpp lc_utils.hpp LC.hpp  CSV.hpp
	$(CC) $(CFLAGS) $(STD) voter.cpp -o voter.o

clean:
	rm *.o
	rm *.out