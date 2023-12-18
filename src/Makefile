CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm
SOURCES = main.c uninominale.c condorcet_minimax.c modules/lecture_csv.c modules/csv_votes.c jugement_majoritaire.c condorcet_paires.c creation_graphe.c list.c
EXECUTABLE = scrutin
TEST_SOURCES = fich_tests/tests.c
MODULE_SOURCES = modules/lecture_csv.c jugement_majoritaire.c  uninominale.c condorcet_minimax.c list.c

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)
	rm -f $(EXECUTABLE) tests

mrproper: clean
	rm -f *~
	rm -f *.txt
	rm -f $(EXECUTABLE)
	rm -f -r html latex

doc:
	doxygen config

tests: $(TEST_SOURCES) $(MODULE_SOURCES) $(SOURCES)
	$(CC) $(CFLAGS) $(TEST_SOURCES) $(MODULE_SOURCES) -o tests $(LDFLAGS)
	./tests

.PHONY: all clean mrproper doc
