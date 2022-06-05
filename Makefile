# apologies for this, one day I'll find how to do it correctly
dumbest_makefile_ever:
	python3 setup.py install
	cp build/lib.linux*/* perlin.so
