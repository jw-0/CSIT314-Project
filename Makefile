# This is just a convenience makefile that removes the need to cd into src to make then back out to run
all:
	cd src && $(MAKE)

clean:
	cd src && $(MAKE) clean
