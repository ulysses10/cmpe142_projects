#include <iostream>
#include <string>

using namespace std;

int main(int arc, char *args[])
{
    string progname(args[0]);
    string buffer;

    while(getline(cin, buffer))
    {
        cout << progname << ": " << buffer <<endl;
    }
    
    cout << "Done!" << endl;
    return 0;
}