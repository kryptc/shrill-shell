TARGETS = SHRILL

all: $(TARGETS)

%o: %.c
	gcc -g -c -o  $@ $<
SHRILL: input.o cd.o echo.o pwd.o pinfo.o ls.o execute.o main.o remindme.o clock.o jobs.o killing.o bfg.o env.o
	gcc -o SHRILL input.o cd.o echo.o pwd.o pinfo.o ls.o execute.o main.o remindme.o clock.o jobs.o killing.o bfg.o env.o

.PHONY: clean
clean:
	rm -f $(TARGETS) *.o