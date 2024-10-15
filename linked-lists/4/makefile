.PHONY: clean dist

dist: clean
	tar -hzcf "$(CURDIR).tar.gz" lslower/* slower/*  makefile

clean:
	$(MAKE) -C lslower clean
	$(MAKE) -C slower clean
