all:
	python3 setup.py build
	cp build/lib*/*.so .
	python3 test.py