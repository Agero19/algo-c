.PHONY: clean dist

dist: clean
	tar -hzcf "$(CURDIR).tar.gz" set/* makefile

clean:
	$(MAKE) -C set clean
