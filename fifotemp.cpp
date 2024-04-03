#include <iostream>
#include "FQueue.h"
using namespace std;

int main() {
    FQueue<char> q;

    char elem1 = 'A';
    char elem2 = 'B';
    char elem3 = 'C';
    char elem4 = 'D';
    char elem5 = 'E';

    cout << "Current Queue:" << "\n";

    cout << "ADDED " << elem1 << endl;
    q.FQEnqueue( &elem1 );
    q.printQUEUE();

    cout << "ADDED " << elem2 << endl;
    q.FQEnqueue( &elem2 );
    q.printQUEUE();

    cout << "ADDED " << elem3 << endl;
    q.FQEnqueue( &elem3 );
    q.printQUEUE();

    cout << "ADDED " << elem4 << endl;
    q.FQEnqueue( &elem4 );
    q.printQUEUE();

    cout << "ADDED " << elem5 << endl;
    q.FQEnqueue( &elem5 );
    q.printQUEUE();

    cout << "\nRemoved elements:" << endl;
    while (!q.FQEmpty()) {
        char* temp = q.FQDequeue();
        cout << "Removed " << *temp << endl;
        q.printQUEUE();
    }

    return 0;
}
