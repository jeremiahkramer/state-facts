CC = g++
exe_file = run_facts
$(exe_file): run_facts.cpp state_facts.cpp
	$(CC) run_facts.cpp state_facts.cpp -o $(exe_file)
clean:
	rm -f *.out *.o $(exe_file)
