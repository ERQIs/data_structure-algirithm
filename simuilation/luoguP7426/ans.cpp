#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;
typedef enum gender {MALE, FEMALE} gender;

class Student {
public:
    string id;
    int score;
    int validRecords;
    int classTrain;
    gender gend;
    string level;
    Student(string& id, int classTrain, gender gend, int initScore) : 
        id(id), classTrain(classTrain), gend(gend), score(initScore) {
            validRecords = 0;
            lastFinish = 0;
        };
    time_t lastFinish;
};

vector<Student*> students;
map<string, Student*> idToStu_p;

int n, m;

int minSecToSec(string time) {
    int min = 0, sec = 0;
    size_t minPos = time.find('\''), secPos = time.find('\"');
    if (minPos == string::npos || secPos== string::npos) {
        cout << "invalid min and sec format!" << endl;
        return -1;
    }
    min = stoi(time.substr(0, minPos));
    sec = stoi(time.substr(minPos + 1, secPos - minPos - 1));
    return min * 60 + sec;
}

int longRunScore(int sec, gender gend) {
    int maleBar[10] = {750, 780, 810, 840, 870, 910, 950, 990, 1030, 1080};
    int femaleBar[10] = {400, 417, 434, 451, 470, 485, 500, 515, 530, 540};
    int* array = (gend == MALE) ? maleBar : femaleBar;
    int i;
    for (i = 0; i < 10; i ++) {
        if (sec <= array[i]) break;
    }
    return 20 - 2 * i;
}

typedef struct record {
    string id;
    string date;
    string begin;
    string end;
    double distance;
    string pauseTime;
    int steps;
} record;

int hmsToSec(string hms) {
    size_t colon1 = hms.find(':');
    size_t colon2 = hms.find(':', colon1 + 1);

    if (colon1 == string::npos || colon2 == string::npos) {
        cout << "invalid hms time format!" << endl;
        return -1;
    }

    int hh = stoi( hms.substr(0, colon1) );
    int mm = stoi( hms.substr(colon1 + 1, colon2 - colon1 - 1));
    int ss = stoi( hms.substr(colon2 + 1));

    return (hh * 60 + mm) * 60 + ss;
}

bool recordIsValid(record* rec_p) {
    int pauseTime = minSecToSec(rec_p->pauseTime);
    if (pauseTime > 4*60 + 30) return false;

    gender gend = idToStu_p[rec_p->id]->gend;
    if (gend == MALE) {
        if (rec_p->distance < 3) return false;
    } else {
        if (rec_p->distance < 1.5) return false;
    }

    Student* stu_p = idToStu_p[rec_p->id]; 
    int yy = stoi((rec_p->date).substr(0, 4));
    int mm = stoi((rec_p->date).substr(4, 2));
    int dd = stoi((rec_p->date).substr(6, 2));
    int begin_h = stoi((rec_p->begin).substr(0, 2));
    int begin_m = stoi((rec_p->begin).substr(3, 2));
    int begin_s = stoi((rec_p->begin).substr(6, 2));
    int end_h = stoi((rec_p->end).substr(0, 2));
    int end_m = stoi((rec_p->end).substr(3, 2));
    int end_s = stoi((rec_p->end).substr(6, 2));
    struct tm t;
    t.tm_year = yy;
    t.tm_mon = mm;
    t.tm_mday = dd;
    t.tm_year -= 1900;
    t.tm_mon -= 1;

    t.tm_hour = begin_h;
    t.tm_min = begin_m;
    t.tm_sec = begin_s;
    time_t beginTimeAsSec = mktime(&t);

    t.tm_hour = end_h;
    t.tm_min = end_m;
    t.tm_sec = end_s;
    time_t endTimeAsSec = mktime(&t);

    if (endTimeAsSec < beginTimeAsSec) endTimeAsSec += 24*60*60;

    if (beginTimeAsSec - stu_p->lastFinish < 6*60*60){
        return false;
    }

    int totalTime = hmsToSec(rec_p->end) - hmsToSec(rec_p->begin);
    if (totalTime < 0) totalTime += 24*60*60;

    // totalTime -= pauseTime;

    double speed = 1000 * rec_p->distance / (double)totalTime;
    double stepLen = 1000 *rec_p->distance / (double)rec_p->steps;

    if (speed < 2 || speed > 5 || stepLen > 1.5) return false;

    stu_p->lastFinish = endTimeAsSec;
    return true;
}

void tailHandles(Student* stu_p) {
    int present = stu_p->validRecords + stu_p->classTrain;

    int tailScore = 0;
    if (present >= 18) {
        tailScore += 5;
    } else if (present >= 15) {
        tailScore += 4;
    } else if (present >= 12) {
        tailScore += 3;
    } else if (present >= 9) {
        tailScore += 2;
    } else if (present >= 6) {
        tailScore += 1;
    }

    if (stu_p->validRecords >= 21) {
        tailScore += 10;
    } else if (stu_p->validRecords >= 19) {
        tailScore += 9;
    } else if (stu_p->validRecords >= 17) {
        tailScore += 8;
    } else if (stu_p->validRecords >= 14) {
        tailScore += 7;
    } else if (stu_p->validRecords >= 11) {
        tailScore += 6;
    } else if (stu_p->validRecords >= 7) {
        tailScore += 4;
    } else if (stu_p->validRecords >= 3) {
        tailScore += 2;
    }

    stu_p->score += tailScore;
    string lev = "F";
    if (stu_p->score >= 95) {
        lev = "A";
    } else if (stu_p->score >= 90) {
        lev = "A-";
    } else if (stu_p->score >= 85) {
        lev = "B+";
    } else if (stu_p->score >= 80) {
        lev = "B";
    } else if (stu_p->score >= 77) {
        lev = "B-";
    } else if (stu_p->score >= 73) {
        lev = "C+";
    } else if (stu_p->score >= 70) {
        lev = "C";
    } else if (stu_p->score >= 67) {
        lev = "C-";
    } else if (stu_p->score >= 63) {
        lev = "D+";
    } else if (stu_p->score >= 60) {
        lev = "D";
    }

    stu_p->level = lev;
}

int main() {

    cin >> n;
    for (int i = 0; i < n; i ++) {

        string id, mf, longRun, passTest;
        int classScore, firstGrade, classTrain;
        cin >> id >> mf >> classScore >> longRun >> passTest >> 
        firstGrade >> classTrain;

        gender gend = (mf == "M") ? MALE : FEMALE;
        int init_score = 0;
        init_score += classScore;
        init_score += longRunScore(minSecToSec(longRun), gend);
        init_score += passTest == "P" ? 10 : 0;
        init_score += firstGrade;

        Student* stu_p = new Student(id, classTrain, gend, init_score);

        students.push_back(stu_p);
        idToStu_p[id] = stu_p;
    }

    cin >> m;
    for (int i = 0; i < m; i ++) {
        record rec;
        cin >> rec.date >> rec.id >> rec.begin >> rec.end >> rec.distance
            >> rec.pauseTime >> rec.steps;
        if (recordIsValid(&rec)) {
            idToStu_p[rec.id]->validRecords += 1;
        }
    }

    for (Student* stu_p : students) {
        tailHandles(stu_p);
    }

    sort(students.begin(), students.end(), [](Student* a, Student*b){return a->id < b->id; });

    for (Student* stu_p : students) {
        cout << stu_p->id << " " << stu_p->score << " " << stu_p->level << endl;
        delete stu_p;
    }

    return 0;
}

// int main() {
//     vector<string> minSec = {"6\'40\"", "6\'57\"", "7\'14\"", "7\'31\"", "7\'50\"", "8\'5\"", 
//                              "8\'20\"", "8\'35\"", "8\'50\"", "9\'00\""};
//     for (string s : minSec) {
//         cout << minSecToSec(s) << ", ";
//     }
//     cout << endl;

//     for (int i = 0; i < 5; i ++) {
//         string buf;
//         cin >> buf;
//         cout << longRunScore(minSecToSec(buf), MALE) << endl;
//     }
//     return 0;
// }




    // vector<string> minSec = {"12\'30\"", "13\'00\"", "13\'30\"", "14\'00\"", "14\'30\"", 
    //                          "15\'10\"", "15\'50\"", "16\'30\"", "17\'10\"", "18\'00\""};