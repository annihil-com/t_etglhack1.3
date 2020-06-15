# GPL License - see http://opensource.org/licenses/gpl-license.php
# Copyright 2005 eth team - don't forget to credits us
CC = gcc
LD = gcc
CFLAGS = -g -Wall -fPIC
LDFLAGS = -ldl -lz -shared

RM = /bin/rm -f

OBJS = t_etglhackII.o
PROG = t_et.so

# Main rule
all: $(PROG)

# Link
$(PROG): $(OBJS)
	$(LD) $(LDFLAGS) $(OBJS) -o $(PROG)

t_etglhackII.o: t_etglhackII.c
	$(CC) $(CFLAGS) -c t_etglhackII.c

clean:
	$(RM) $(PROG) $(OBJS)
