#include <iostream>
#include <cstring>

using namespace std;

int main() {
    int a[20];
    // memset(a, -1, sizeof(a));
    // for (int i = 0; i < 20; i ++) {
    //     cout << a[i] << endl;
    // }

    string buf;
    getline(cin, buf);

    int pos = buf.find(':');
    string speaker = buf.substr(0, pos);
    string statement = buf.substr(pos + 2);
    cout << speaker <<":"<< endl;
    cout << statement << endl;
    cout << statement.substr(0, sizeof("Today is")) << "|" << endl;
    if (statement.size() > sizeof("is guilty.") && statement.substr(statement.size() - sizeof("is guilty.") + 1) == "is guilty.") {
        cout << "guilty state" << endl;
        cout << statement.substr(0, statement.size() - sizeof("is guilty.")) << "|" << endl;
    }else if (statement.size() > sizeof("is not guilty.") && 
        statement.substr(statement.size() - sizeof("is not guilty.") + 1) == "is not guilty.") {
        // XXX is not guilty
        string subj = statement.substr(0, statement.size() - sizeof("is not guilty."));
        cout << "not guilty state" << endl;
        cout << subj << "|" << endl;
    } else if (statement.size() > sizeof("Today is XXX.") && statement.substr(0, sizeof("Today is") - 1) == "Today is") {
        cout << "flag" << endl;
        cout << statement.substr(sizeof("Today is"), statement.size() - sizeof("Today is ")) << endl;
    }
    return 0;
}