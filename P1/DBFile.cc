#include "TwoWayList.h"
#include "TwoWayList.cc"
#include "Record.h"
#include "Schema.h"
#include "File.h"
#include "Comparison.h"
#include "ComparisonEngine.h"
#include "DBFile.h"
#include "Defs.h"
#include <string.h>

// stub file .. replace it with your own DBFile.cc
//ok
//create open add movefirst

DBFile::DBFile () {
    r_current= new Record();
    r_temp = new Record();
    p_current = new Page();
    f_current = new File();
    end_of_File=0;
    p_Index=0;
    CNF mycomparison;
}

int DBFile::Create (const char *f_path, fType f_type, void *startup) {
    // if (f_type != heap)                                              
    //     return 0;
    f_current->Open(0,(char *) f_path);                              // Open function with 1st argument 0 because new file
    p_Index=0;
    end_of_File=0;
    return 1;
}

void DBFile::Load (Schema &f_schema, const char *loadpath) {
    int sum = 0;
    FILE *f_open = fopen(loadpath, "r");                        // Open file to read data from 
    // Schema temp = &f_schema;
    Record temp;
    while (temp.SuckNextRecord (&f_schema, f_open) == 1)
    {
        // p_current.Append(temp);
        sum++;
        Add(temp);
    }
    fclose(f_open);
    cout << sum << " records loaded!" << endl;
}

int DBFile::Open (const char *f_path) {
    if( f_path == NULL)
        return 0;
    f_current->Open(1,(char *) f_path);                     // File.Open requires a char path and not char * 
    p_Index=1;
    end_of_File=0;
    return 1;
}

void DBFile::MoveFirst () {
    f_current->GetPage(p_current,0);                        // Get 1st page of the file
    p_Index = 0;
    // p_current->GetFirst(r_current);                      // Get 1st record of current page which is 1st currently  
                                                            // (Will delete the record)
}

int DBFile::Close () {
    if(f_current->Close()>0)                                // Use File class function to close the file
        return 1;               
    else 
        return 0;
}

void DBFile::Add (Record &rec) {
    // end_of_File=1;                                       // to be added at the end of file
    if(p_current->Append(&rec)==0)                          // Check if page is full and
    {                                                       // Add new page in that case and update page index
        // p_Index++;
        f_current->AddPage(p_current,p_Index++);
        p_current->EmptyItOut();
        p_current->Append(&rec);
    }
    r_temp->Consume(&rec);                                  // To make sure same record is not added again 
}

int DBFile::GetNext (Record &fetchme) {
    // r_current = &fetchme;
    // check if we have reached end of page or any records left to read
    if(p_current->GetFirst(&fetchme)==0)
    {
        p_Index++;                                                  // If no records left move to next page    
        if(p_Index<f_current->GetLength()-1)
        {
            f_current->GetPage(p_current,p_Index);                  // Get the next page 
            p_current->GetFirst(&fetchme);
            // if(p_current->GetFirst(&fetchme)==0)
            // {
            //     cout<<"Page Empty \n";                           // next page is empty hence no record to read
            //     return 0;
            // }          
            // else
            // {
            //     return 1;
            // }                                       
        } 
        else
        {
            cout<<"End of File \n";
            return 0;
        }
    }
    return 1;
}

int DBFile::GetNext (Record &fetchme, CNF &cnf, Record &literal) {
    ComparisonEngine comp;
    // r_current = &fetchme;
    // if(r_current == NULL)
    //     return 0;
    while(true)                             
    {
        if(GetNext(fetchme)!=0)                             // Until we reach end of file read records to compare with CNF  
        {
            if(comp.Compare (&fetchme, &literal, &cnf))     // check for each record if it matches CNF expression
                return 1;
            // else
            //     return 0;
        }
        else
            return 0;
    }
    // return 1;
}
