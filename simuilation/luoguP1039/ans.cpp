#include <iostream>
#include <vector>
#include <map>
#include <cstring>

#define P_MAX 102
#define M_MAX 22
#define N_MAX 22

using namespace std;

int m, n, p;

vector<string> ItoN;    // int to name
map<string, int> NtoI;  // name to int
vector<string> ItoW;    // int to weekday
map<string, int> WtoI;  // weekday to int

class Claim {
public:
    Claim(int speaker, bool affirmative, int subject, bool week, bool guilt) : 
    speaker(speaker), affirmative(affirmative), subject(subject), week(week), guilt(guilt) {}
    int speaker;
    bool affirmative;
    int subject;
    bool week;
    bool guilt;
};

vector<Claim> claims;

void init_input() {
    ItoW = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    for (int i = 0; i < ItoW.size(); i++) {
        WtoI[ItoW[i]] = i;
    }
    cin >> m >> n >> p;
    for (int i = 0; i < m; i ++) {
        string name;
        cin >> name;
        // cout << name << endl;
        ItoN.push_back(name);
        NtoI[name] = i;
    }
    string buf;
    getline(cin, buf);
    for (int i = 0; i < p; i ++) {
        string buf;
        getline(cin, buf);
        // cout << "flag" << endl;
        int pos = buf.find(':');
        if (pos == string::npos) continue;

        string speaker = buf.substr(0, pos);
        string statement = buf.substr(pos + 2);
        // cout << statement << endl;
        if (NtoI.find(speaker) == NtoI.end()) continue;
        int speaker_id = NtoI[speaker];

        if (statement == "I am guilty.") {
            // cout << "state 1"<< endl;
            claims.push_back(Claim(speaker_id, true, speaker_id, false, true));
        } else if (statement == "I am not guilty.") {
            // cout << "state 2"<< endl;
            claims.push_back(Claim(speaker_id, false, speaker_id, false, true));
        } else {
            if (statement.size() > sizeof("is guilty.") && 
                statement.substr(statement.size() - sizeof("is guilty.") + 1) == "is guilty.") {
                // XXX is guilty
                // cout << "state 3"<< endl;
                string subj = statement.substr(0, statement.size() - sizeof("is guilty."));
                if (NtoI.find(subj) == NtoI.end()) continue;
                int subj_id = NtoI[subj];
                claims.push_back(Claim(speaker_id, true, subj_id, false, true));
            } else if (statement.size() > sizeof("is not guilty.") && 
                statement.substr(statement.size() - sizeof("is not guilty.") + 1) == "is not guilty.") {
                // XXX is not guilty
                // cout << "state 4"<< endl;
                string subj = statement.substr(0, statement.size() - sizeof("is not guilty."));
                if (NtoI.find(subj) == NtoI.end()) continue;
                int subj_id = NtoI[subj];
                claims.push_back(Claim(speaker_id, false, subj_id, false, true));
            } else if (statement.size() > sizeof("Today is XXX.") && statement.substr(0, sizeof("Today is") - 1) == "Today is") {
                // cout << "flag" << endl;
                // cout << "state 5"<< endl;
                string weekday = statement.substr(sizeof("Today is"), statement.size() - sizeof("Today is "));
                if (WtoI.find(weekday) == WtoI.end()) continue;
                int weekday_id = WtoI[weekday];
                claims.push_back(Claim(speaker_id, true, weekday_id, true, false));
            }
        }
    }
}

bool enumerate(int criminal, int week) {
    int liar[N_MAX];   // 1:liar   0: not liar  -1: unknown
    int honest_cnt = 0;
    int liar_cnt = 0;
    memset(liar, -1, sizeof(liar));

    for (Claim c : claims) {
        if (liar[c.speaker] == -1) {
            if (c.week) {
                if (c.affirmative){
                    // today is week subject
                    liar[c.speaker] = c.subject == week ? 0 : 1;
                } else {
                    // today is not week subject
                    liar[c.speaker] = c.subject == week ? 1 : 0;
                }
            }
            if (c.guilt) {
                if (c.affirmative) {
                    // subject is criminal
                    liar[c.speaker] = c.subject == criminal ? 0 : 1;
                } else {
                    // subject is not criminal
                    liar[c.speaker] = c.subject == criminal ? 1 : 0;
                }
            }
            if (liar[c.speaker] == 0) honest_cnt ++;
            if (liar[c.speaker] == 1) liar_cnt ++;
        } else if (liar[c.speaker] == 1) {
            if (c.week) {
                if ((c.affirmative && c.subject == week) ||
                    (!c.affirmative && c.subject != week)) {
                        // liar tells truth
                        return false;
                    }
            }
            if (c.guilt) {
                if ((c.affirmative && c.subject == criminal) || 
                    (!c.affirmative && c.subject != criminal)) {
                        // liar tells truth
                        return false;
                    }
            }
        } else if (liar[c.speaker] == 0) {
            if (c.week) {
                if ((c.affirmative && c.subject != week) ||
                    (!c.affirmative && c.subject == week)) {
                        // honest tells lie
                        return false;
                    }
            }
            if (c.guilt) {
                if ((c.affirmative && c.subject != criminal) || 
                    (!c.affirmative && c.subject == criminal)) {
                        // honest tells lie
                        return false;
                    }
            }
        }
    }
    // all claims checked
    return m - honest_cnt >= n && n >= liar_cnt;
}

int main() {

    init_input();

    int criminal = -1;

    // enumerate every possible weekday and criminal
    for (int i = 0; i < m; i ++) {
        for (int j = 0; j < 7; j ++) {
            // cout << "checking " << ItoN[i] << " " << ItoW[j] << endl;
            if (enumerate(i, j)) {
                if (criminal != -1 && criminal != i) {
                    cout << "Cannot determine" << endl;
                    return 0;
                }
                criminal = i;
            }
        }
    }
    if (criminal == -1) {
        cout << "Impossible" << endl;
    } else {
        cout << ItoN[criminal] << endl;
    }


    return 0;
}