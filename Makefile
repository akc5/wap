cc=gcc
cflags = -Wall -Werror
ldflags = -lpthread
bin = tlsclient
srcs = tlsclient.c

all: $(bin)

$(bin): $(srcs)
	$(cc) $(cflags) $^ -o $@

.PHONY: clean

clean:
	@rm -f ./*.o $(bin)

