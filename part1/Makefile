.PHONY: all

all: pi.out

pi.out: pi.c
	gcc $< -pthread -o $@

clean: 
	rm *.out