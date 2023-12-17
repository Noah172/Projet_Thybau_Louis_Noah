CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

SOURCES = main.c uninominale.c condorcet_minimax.c modules/lecture_csv.c modules/csv_votes.c jugement_majoritaire.c creation_graphe.c list.c


EXECUTABLE = scrutin

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)

mrproper: clean
	rm -f *~
	rm -f *.txt
	rm -f $(EXECUTABLE)
	rm -f -r html latex


doc:
	doxygen documentation

.PHONY: all clean mrproper doc
