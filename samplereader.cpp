#include <iostream>
#include <string>
#include"csvreader.h"

using namespace std;

int main (int argc, char* argv[])
{
    csvreader::csvreader reader;
    reader.readFile (argv[1]);
    for (int i = 0; i < reader.columns().size(); i++)
        cout << reader.columns()[i] << "  |  ";
    cout << endl;
    cout << "Select one of the above fields and enter its name." << endl;
    string field;
    getline(cin, field);
    cout << field << " values are:";
    for (int i = 0; i < reader.size(); i++)
        cout << " " << reader[i][field];
    cout << endl;
    return 0;
}