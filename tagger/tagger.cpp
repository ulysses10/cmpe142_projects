#include <iostream>
#include <string>

using namespace std;
int main(int argc, char *args[])
{
    string tag(args[1]);
    string message;

    cout << "Node " << tag << " started." << endl;
    cout.flush();

    while(getline(cin, message))
    {
        cout << "[" << tag << ":" << message << "]" << endl;
        cout.flush();
    }
    cout << "Node " << tag << " done!" << endl;
    return 0;
}