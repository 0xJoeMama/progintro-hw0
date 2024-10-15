CC=gcc
CFLAGS=-O0 -m32 -Wall -Wextra -Werror -pedantic 
BIN=trolley
BUILDIR=.build

all: $(BIN)

$(BIN): $(BUILDIR)/trolley.o | $(BUILDIR)
	$(CC) $(CFLAGS) -o $(BIN) $<

$(BUILDIR)/trolley.o: src/trolley.c | $(BUILDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDIR):
	mkdir -p $(BUILDIR)

clean:
	rm -r $(BUILDIR) $(BIN)
