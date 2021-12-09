CC=gcc
CFLAGS=-I.

# Dépendances pour le programme normal
ODIR=obj
DEPS = compression.h liste_chainée.h arbre.h
MAIN = main.o 
_OBJ_NO_MAIN = compression.o liste_chainée.o arbre.o
OBJ_NO_MAIN = $(patsubst %,$(ODIR)/%,$(_OBJ_NO_MAIN))
_OBJ = $(MAIN) $(_OBJ_NO_MAIN)
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))
$(ODIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

# Dépendances pour le programme de test
TEST_DIR=test
TEST_ODIR=test_obj
_TEST_DEPS = test_framework.h test_arbre.h test_liste_chainee.h
TEST_DEPS = $(patsubst %,$(TEST_DIR)/%,$(_DEPS))
_TEST_OBJ = main_test.o test_framework.o test_arbre.o test_liste_chainee.o
TEST_OBJ = $(patsubst %,$(TEST_ODIR)/%,$(_TEST_OBJ))
$(TEST_ODIR)/%.o: $(TEST_DIR)/%.c $(TEST_DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

huffman: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

tests: $(OBJ_NO_MAIN) $(TEST_OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
	./tests

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(TEST_ODIR)/*.o