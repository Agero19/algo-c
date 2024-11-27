.PHONY: clean dist

dist: clean
	tar -hzcf "$(CURDIR).tar.gz" printlines/* sortwords/* stack/* makefile

clean:
	$(MAKE) -C printlines clean
	$(MAKE) -C sortwords clean
