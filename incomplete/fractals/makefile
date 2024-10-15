.PHONY: clean dist

dist: clean
	tar -hzcf "$(CURDIR).tar.gz" fractal/* point/* sg/* makefile

clean:
	$(MAKE) -C fractal clean
	$(MAKE) -C point clean
	$(MAKE) -C sg clean
