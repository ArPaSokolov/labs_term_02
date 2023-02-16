#include <iostream>
using namespace std;

int main()
{
    string theString;
    string animatedString;
    cout << "Enter the string" << endl;
    cin >> theString;
    int Number = theString.length();
    cout << Number << endl;
    for (int count = 0; count < Number; count++)
    {
        animatedString += theString[count];
        cout << animatedString << endl;
    }
    return 0;
}