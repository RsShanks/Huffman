CC=gcc
CFLAGS=-I.

DEPS = compression.h liste_chainée.h arbre.h

_OBJ = main.o compression.o liste_chainée.o arbre.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
_TEST_OBJ = 

ODIR=obj

$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

huffman: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)


# A finir 
test: huffman
	$(CC) -o 

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 