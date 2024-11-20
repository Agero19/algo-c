.PHONY: clean dist

dist: clean
	tar -hzcf "$(CURDIR).tar.gz" mset/* makefile

clean:
	$(MAKE) -C mset clean
