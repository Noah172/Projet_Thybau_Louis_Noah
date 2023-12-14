CC = gcc
CFLAGS = -Wall -Wextra -std=c99
LDFLAGS = -lm

# Listez vos fichiers source ici
SOURCES = main.c uninominale.c condorcet.c condorcet_minimax.c modules/lecture_csv.c

# Remplacez 'executable' par le nom que vous souhaitez pour votre exécutable
EXECUTABLE = Executable

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(EXECUTABLE) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)

mrproper: clean
	rm -f *~
	rm -f *.txt
	rm -f $(EXECUTABLE)