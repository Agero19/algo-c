.PHONY: clean dist

dist: clean
	tar -hzcf "$(CURDIR).tar.gz" nat/* natio/* natop/* makefile

clean:
	$(MAKE) -C natio clean
	$(MAKE) -C natop clean
