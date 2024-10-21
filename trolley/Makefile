CC=gcc
CFLAGS=-O0 -m32 -Wall -Wextra -Werror -pedantic -std=c99
BIN=trolley
BUILDIR=.build

all: $(BIN) bench

$(BIN): $(BUILDIR)/trolley.o | $(BUILDIR)
	$(CC) $(CFLAGS) -o $(BIN) $^

$(BUILDIR)/%.o: src/%.c | $(BUILDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDIR):
	mkdir -p $(BUILDIR)

clean:
	rm -r $(BUILDIR) $(BIN)

bench:
	  time shuf -i 0-1000000000000000000 -n 20000 | $(PWD)/$(BIN)

