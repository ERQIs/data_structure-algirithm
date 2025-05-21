#include <iostream>
#include <set>
#include <string>
#include <stack>
#include <vector>
#include <fstream>

#define MAX_DEPTH 64

// grid states   not the searching state
#define EMPTY 'o'
#define INVALID ' '
#define OCCUPIED '.'

using namespace std;

typedef string StateHash_t;
typedef pair<char, char> PCC;
typedef pair<PCC, PCC> PPCC;
int mapSize;

void hideCursor() {
    cout << "\033[?25l"; // ANSI 转义序列：隐藏光标
}

void showCursor() {
    cout << "\033[?25h"; // ANSI 转义序列：显示光标
}

class State {
public:
    PPCC path[MAX_DEPTH];
    int depth;
    int endingDepth;  //at which depth the search should end 
    string board;
    bool checkEnd();
    void printState();
    vector<State> subStates();
    StateHash_t hash();
    char getBoard(int i, int j);
    void setBoard(int i, int j, char set);
    State(string board, int endingDepth) : board(board), endingDepth(endingDepth) {
        depth = 0;
    };
};

char State::getBoard(int i, int j) {
    if (i >= 0 && i < mapSize && j >= 0 && j < mapSize) {
        return this->board[i * mapSize + j];
    } else {
        return INVALID;
    }
}

void State::setBoard(int i, int j, char set) {
    if (i >= 0 && i < mapSize && j >= 0 && j < mapSize) {
        board[i * mapSize + j] = set;
    } else {
        board[i * mapSize + j] = INVALID;
    }
}

bool State::checkEnd() {
    return this->depth == this->endingDepth 
           && board[mapSize*mapSize / 2] == OCCUPIED;
};

vector<State> State::subStates() {
    vector<State> ret;
    int direc[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    // the reverse way to look at jumping: empty slots are jumping
    for (int i = 0; i < mapSize; i ++) {
        for (int j = 0; j < mapSize; j ++) {
            if (getBoard(i, j) == EMPTY) {
            // foreach slot if empty
                
                for (int k = 0; k < 4; k ++) {
                    // on its four directions
                    int jumpPos_x = i + direc[k][0];
                    int jumpPos_y = j + direc[k][1];
                    int startPos_x = jumpPos_x + direc[k][0];
                    int startPos_y = jumpPos_y + direc[k][1];
                    if ( getBoard(jumpPos_x, jumpPos_y) == OCCUPIED &&
                         getBoard(startPos_x, startPos_y) == OCCUPIED ) {
                        // can jump, and we found a new sub state

                            State sub = *this;
                            sub.setBoard(jumpPos_x, jumpPos_y, EMPTY);
                            sub.setBoard(startPos_x, startPos_y, EMPTY);
                            sub.setBoard(i, j, OCCUPIED);
                            sub.path[sub.depth ++] = make_pair(
                                make_pair(startPos_x, startPos_y),
                                make_pair(i, j)
                            );
                            ret.push_back(sub);
                         }
                } 
            
            }
        }
    }

    return ret;
};

StateHash_t State::hash() {return this->board; };

void State::printState() {
    for (int i = 0; i < mapSize; i ++) {
        for (int j = 0; j < mapSize; j ++) {
            cout << getBoard(i, j);
        }
        cout << endl;
    }
};

class Game {
private:
    State initialState;
    vector<State> winningStates;
    set<StateHash_t> visited;
    int checkedCnt = 0;
    int solutionFound = 0;
    vector<string> gridNames;
    ostream& solutionStream;
public:
    Game(vector<string>& gridNames, ostream& solutionStream)
        : gridNames(gridNames), initialState("", -1), solutionStream(solutionStream) {
        checkedCnt = 0;
        //make initial state here
        string initialBoard = "";
        int endDepth = -1;
        for (string ss : gridNames) {
            for (char c : ss) {
                if (c == ' ') initialBoard += INVALID;
                else if (c == 'x') initialBoard += EMPTY;
                else {
                    initialBoard += OCCUPIED;
                    endDepth ++;
                }
            }
        }
        initialState = State(initialBoard, endDepth);
    };
    void run();
    string getStatePath(State& s);
    void saveSolution(int id, State& s);
};

string Game::getStatePath(State& s) {
    string ret = "";
    for (int i = 0; i < s.depth; i ++) {
        auto [from, to] = s.path[i];
        ret += string(1, gridNames[from.first][from.second])
             + " -> " + string(1, gridNames[to.first][to.second]) + "\n";
    }
    return ret;
};

void Game::saveSolution(int id, State& s) {
    solutionStream << "solution " << id << ":" << endl;
    solutionStream << getStatePath(s);
    solutionStream << endl;
    solutionStream.flush();
}

void Game::run() {
    // DFS to search the ans
    // depth should not exceed 49^2 since 49 is an upper bound
    // for final path and each state has at most 49 substates.
    hideCursor();
    stack<State> stk;
    stk.push(initialState);
    while (!stk.empty()) {
        State now = stk.top(); stk.pop();
        vector<State> subStates = now.subStates();
        for (State s : subStates) {

            StateHash_t h = s.hash();
            if (visited.find(h) != visited.end()) {
                continue;
            }
            visited.emplace(h);
            if (s.checkEnd()) {
                // exit here
                saveSolution(++ solutionFound, s);
                continue;
            }

            checkedCnt ++;
            if (checkedCnt % 2048 == 0){
                cout << "\rChecked " << checkedCnt << " states. ";
                cout << solutionFound << " solutions found.";
            }
            stk.push(s);
        }
    }
    // if (checkedCnt % 64 == 0) cout << "\rChecked " << checkedCnt << " states. ";
    cout << endl;
    showCursor();
};

int main() {

    cout << "Peg Solitire Solving Program" << endl;

    vector<string> British = {
        "  abc  ",
        "  def  ",
        "ghijklm",
        "nopxPON",
        "MLKJIHG",
        "  FED  ",
        "  CBA  "
    };

    vector<string> European = {
        "  abc  ",
        " ydefz ",
        "ghijklm",
        "nopxPON",
        "MLKJIHG",
        " ZFEDY ",
        "  CBA  "
    };

    vector<string> test = {
        "       ",
        " 12x   ",
        " abx   ",
        "   x   ",
        "       ",
        "       ",
        "       "
    };

    mapSize = 7;

    cout << "checking British game" << endl;

    ofstream fout("output.txt", ios::out | ios::trunc);

    Game game = Game(British, fout);
    game.run();

    cout << "Porgram ends successfully" << endl;

    return 0;
};

 
// love simulations 