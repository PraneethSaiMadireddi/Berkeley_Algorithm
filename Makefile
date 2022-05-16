compile:
	g++ -std=c++0x -Wall -w -pthread berkeley_algorithm/berkeley.cpp -o bt.out

clean:
	rm bt.out
	ls | grep temp_.* | xargs -d"\n" rm

run_berkeley:
	bash berkeley_algorithm/shell_script.sh 2 5

