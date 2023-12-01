main: init set check destroy
	./init
	./set
	./check $(num)
	./destroy

init: init.cpp
	g++ init.cpp -o init -lrt

set: set.cpp
	g++ set.cpp -o set -lrt

check: check.cpp
	g++ check.cpp -o check -lrt

destroy: destroy.cpp
	g++ destroy.cpp -o destroy -lrt


clean:
	rm -f init destroy set check