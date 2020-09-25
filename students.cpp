#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <bits/stdc++.h> 

using namespace std;

map<string, string> parseRow(string row){
    string s = "";  
    map<string,string> res;
    int count = 0;
    for (int i=0; i<row.size(); i++){
        if (row[i] == ','){
            switch (count){
                case 0:
                    res["first"] = s;
                    s = "";                
                case 1:
                    res["last"] = s;
                    s = "";  
                case 2:
                    res["department"] = s;
                    s = "";              
                }
            count++;
        }
        else s+=row[i];
    }
    res["section"] = s;
    return res;
}

bool match(string row, string first, string last, string department, string section){
    map<string,string> r = parseRow(row);
    if (first == r["first"] && last == r["last"] && department == r["department"] && section == r["section"] ) return true;
    else return false;
}

string modifyField(string row , string field, string desired){
        string res = "";
        map<string,string> r = parseRow(row);
        r[field] = desired;
        res += r["first"] + ",";
        res += r["last"] + ",";
        res += r["department"] + ",";
        res += r["section"];
        return res;
}

void modifyStudent(const string filename){
    // record data to modify
    string first,last,department,section;
    // temporary file
    ofstream outfile("temp.txt", ios_base::trunc);
    // students file
    ifstream infile(filename);
    // Skip line
    while ((getchar()) != '\n'); 
    cout << "\nEnter First Name: ";
    getline(cin, first);
    cout << "Enter Last Name: ";
    getline(cin, last);
    cout << "Enter Department: ";
    getline(cin, department);
    cout << "Enter Section: ";
    getline(cin, section);
    string line;
    // Read from infile and write to temp ( = outfile because addStudent is a modify operation)
    if (infile.is_open()){
        while ( getline (infile,line) )
        {
            if (match(line,first,last,department,section)){
               string field;
               string desired;
               cout << "\nfirst , last , department, section" << endl; 
               cout << "Which field do you want to modify: ";
               cin >> field;
               if (field != "first" && field != "last" && field != "department" && field != "section" ){
                   cout << "Invalid Field! Try again" << endl;
                   outfile << line << "\n";
               }
               else{
                   
                   cout << "Enter desired new value for " << field << ": ";
                   cin >> desired;
                   outfile << modifyField(line,field,desired) << "\n";
               }
               
            }
            else {
                outfile << line << "\n";
            }
            
        }
        infile.close();
    }
    else cout << "Unable to open file to read from";
    // Temp.txt --> new students.txt
    if( remove( filename.c_str() ) != 0 ) perror( "Error deleting file" );
    int result = rename("temp.txt", filename.c_str());
    if ( result != 0 ){
        outfile.close();
        perror("Error renaming file");
    }
    outfile.close();

    cout << "\n";
}

void deleteStudent(const string filename){
    bool found = false;
    // record data to modify
    string first,last,department,section;
    // temporary file
    ofstream outfile("temp.txt", ios_base::trunc);
    // students file
    ifstream infile(filename);
    // Skip line
    while ((getchar()) != '\n'); 
    cout << "\nEnter First Name: ";
    getline(cin, first);
    cout << "Enter Last Name: ";
    getline(cin, last);
    cout << "Enter Department: ";
    getline(cin, department);
    cout << "Enter Section: ";
    getline(cin, section);
    string line;
    // Read from infile and write to temp ( = outfile because addStudent is a modify operation)
    if (infile.is_open()){
        while ( getline (infile,line) )
        {
            if (!match(line,first,last,department,section)){
                outfile << line << "\n";
            }
            else found = true;
            
        }
        infile.close();
    }
    else cout << "Unable to open file to read from";
    // Temp.txt --> new students.txt
    if( remove( filename.c_str() ) != 0 ) perror( "Error deleting file" );
    int result = rename("temp.txt", filename.c_str());
    if ( result != 0 ){
        outfile.close();
        perror("Error renaming file");
    }
    outfile.close();
    found ? cout << "Deleted succesfully!\n" : cout << "Record not found\n\n";
    // cout << "\n";
}





void addStudent(const string filename){
    // record data to add
    string first,last,department,section;
    // temporary file
    ofstream outfile("temp.txt", ios_base::trunc);
    // students file
    ifstream infile(filename);

    cout << "Enter First Name: ";
    cin >> first; 
    cout << "Enter Last Name: ";
    cin >> last; 
    cout << "Enter Department: ";
    cin >> department; 
    cout << "Enter Section: ";
    cin >> section; 
    string line;
   
    // Read from infile and write to temp ( = outfile because addStudent is a modify operation)
    if (infile.is_open()){
        while ( getline (infile,line) )
        {
        outfile << line << '\n';
        }
        infile.close();
    }
    else cout << "Unable to open file to read from";

    // Write new record at temp
    outfile << first << "," << last << "," << department << "," << section << "\n";
    
    // Temp.txt --> new students.txt
    if( remove( filename.c_str() ) != 0 ) perror( "Error deleting file" );
    int result = rename("temp.txt", filename.c_str());
    if ( result != 0 ){
        outfile.close();
        perror("Error renaming file");
    }
    outfile.close();

    cout << "\n";
}


// function to list students
void listStudents(const string filename){
    // variables
    string line;
    ifstream myfile(filename);
    
    cout  << "\n\n";
    cout  << "First Name | Last Name | Department | Section\n";
    cout  << "=============================================\n\n";
    // main logic
    if (myfile.is_open()){
        while ( getline (myfile,line) )
        {
        cout << "  " << line << '\n';
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    cout  << "\n=============================================\n\n";
}


int main(){
    const string filename = "students.txt";
    cout << "===== STUDENT DATABASE MANAGEMENT SYSTEM =====\n\n\n\n";
    int x = 0;
    while (x != 5){
        cout << "       1. Add Student Record\n"; 
        cout << "       2. List Student Records\n"; 
        cout << "       3. Modify Student Record\n"; 
        cout << "       4. Delete Student Record\n"; 
        cout << "       5. Exit Program\n\n"; 
        cout << "       Select Option: ";
        cin >> x;
        switch(x) {
        case 1:
            addStudent(filename);
            break;
        case 2:
            listStudents(filename);
            break;
        case 3:
            modifyStudent(filename);
            break;
        case 4:
            deleteStudent(filename);
            break;
        case 5:
            cout << "       Goodbye!\n ";
            break;
        default:
           cout << "       Please enter one of the following options: ";
        } 
    }
    return 0;  
}