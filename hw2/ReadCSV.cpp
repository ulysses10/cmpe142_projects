#include <iostream>
#include <string>
using namespace std;

int main()
{

    //string text;
    for(string text; getline(cin,text);){
    cin >> text;
    int n=text.length();
    cout << "<tr>\n\t<td>";
    for(int i=0; i<n; i++)
    {
        while(text[i]==',')
        {
            i++;
            cout << "</td><td>";
        }
        cout << text[i];
    }
    cout << "</td>\n</tr>\n";    
    }
    //cin >> text;

    return 0;
}