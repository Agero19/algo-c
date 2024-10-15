.PHONY: clean dist

dist: clean
	tar -hzcf "$(CURDIR).tar.gz" balpar/* quicksort/* str_rec/* makefile

clean:
	$(MAKE) -C balpar clean
	$(MAKE) -C quicksort clean
	$(MAKE) -C str_rec clean
