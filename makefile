all: CuerdaVibrante.png

CuerdaVibrante.png: edo.dat plot.py
	python plot.py

edo.dat : ecu.x
	./ecu.x 100 90 > edo.dat

ecu.x : EcuacionDeOnda.cpp
	c++ EcuacionDeOnda.cpp -o ecu.x

clean:
	rm ecu.x edo.dat

