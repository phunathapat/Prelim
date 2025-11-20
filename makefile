DEPS = test
compile : main.cpp
	clear 
	g++ main.cpp WasteBin.cpp -o $(DEPS)
	
run : $(DEPS)
	./$(DEPS)

clean : $(DEPS)
	rm$(DEPS)