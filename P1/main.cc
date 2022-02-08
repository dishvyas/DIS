
#include <iostream>
#include "Record.h"
#include "File.h"
#include <stdlib.h>
using namespace std;

extern "C" {
	int yyparse(void);   // defined in y.tab.c
}

extern struct AndList *final;

int main () {

	//try to parse the CNF
	// cout << "Enter in your CNF: ";
  	// if (yyparse() != 0) {
	// 	cout << "Can't parse your CNF.\n";
	// 	exit (1);
	// }

	// suck up the schema from the file
	Schema lineitem ("catalog", "lineitem");
	Schema customer ("catalog","customer");

	// grow the CNF expression from the parse tree 
	CNF myComparison;
	Record literal;
	Page mid;
	File j;
	int t;
	myComparison.GrowFromParseTree (final, &lineitem, literal);
	
	// print out the comparison to the screen
	myComparison.Print ();

	// now open up the text file and start procesing it
        FILE *tableFile = fopen ("/root/DIS/P1/lineitem.tbl", "r");

        Record temp;
        Schema mySchema ("catalog", "customer");
		Schema line ("catalog", "lineitem");

	//char *bits = literal.GetBits ();
	//cout << " numbytes in rec " << ((int *) bits)[0] << endl;
	//literal.Print (&supplier);

        // read in all of the records from the text file and see if they match
	// the CNF expression that was typed in
	// int counter = 0;
	// ComparisonEngine comp;
        while (temp.SuckNextRecord (&line, tableFile) == 1) {
		// counter++;
		// if (counter % 10000 == 0) {
		// 	cerr << counter << "\n";
		// }
			// t = mid.Append(&temp);
			if(mid.Append(&temp))
				cout<<"1"<<" "<<endl;
			j.AddPage(&mid,0);
			// temp.Print(&line);
			
	// 	// if (comp.Compare (&temp, &literal, &myComparison))
    //             	temp.Print (&mySchema);

        }

}


