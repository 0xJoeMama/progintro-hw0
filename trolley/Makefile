CC=gcc
CFLAGS=-O0 -m32 -Wall -Wextra -Werror -pedantic -std=c99
BIN=trolley trolley_new
BUILDIR=build

all: $(BIN)

%: $(BUILDIR)/%.o | $(BUILDIR)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDIR)/%.o: src/%.c | $(BUILDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

$(BUILDIR):
	mkdir -p $(BUILDIR)

clean:
	rm -r $(BUILDIR) $(BIN)

bench:
	time $(PWD)/$(BIN) < $(PWD)/trolley.txt

