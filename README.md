# DIS


## Project 1 

### Commands to setup and run the program

make main <br />
./main    <br />
You will be asked to enter a CNF phrase. You can use this to understand the output : "(l_orderkey > 27) AND (l_orderkey < 45)"  <br />

You can find my DBfile implementation in DBFile.h and DBFile.cc which is built on top of classes File, Page and Record. <br />

To run the tests I have written, follow the steps below : <br />
make test.out <br />
./test.out           ( if you have your own test cases) <br />
OTHERWISE run <br />
./test.out < test3.txt | tail -n15000  > output3.txt   ( To test the other two cases simply replace 3 in output and test file with 1 and 2) <br />


You can generate .bin files for other tables by running ./test.out. Choose option 1 in the first prompt and then select the table you want test the query on. <br />

Queries on remaining tables can be carried out only if you generate the .bin files first. You can find schema of the database inside P1/Catalog file. 

