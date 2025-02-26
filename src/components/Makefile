TESTTARGET = test.out


all: run

run:
	g++ test.cpp -o $(TESTTARGET)
	./$(TESTTARGET)

test:
	g++ test2.cpp -o $(TESTTARGET)
	./$(TESTTARGET)


clean:
	rm -rf $(TESTTARGET)