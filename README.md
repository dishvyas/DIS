# DIS


## Project 1 

### Commands to setup and run the program

make main 
./main 
You will be asked to enter a CNF phrase. You can use this to understand the output : "(l_orderkey > 27) AND (l_orderkey < 45)"

You can find my DBfile implementation in DBFile.h and DBFile.cc which is built on top of classes File, Page and Record. 

To run the tests I have written, follow the steps below : 
make test.out
./test.out           ( if you have your own test cases)
OTHERWISE run 
./test.out < test3.txt | tail -n15000  > output3.txt   ( To test the other two cases simply replace 3 in output and test file with 1 and 2)


You can generate .bin files for other tables by running ./test.out. Choose option 1 in the first prompt and then select the table you want test the query on. 

Queries on remaining tables can be carried out only if you generate the .bin files first. You can find schema of the database inside P1/Catalog file. 

