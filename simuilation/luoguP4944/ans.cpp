/*
main function for map:
    for each living snake (in the order):
        1.update snake state.
        2.update map.



snake state main function:
1. check the mevement of snake head.
    if there is a blocking in front of head's moving position:
        the snake is dead in next moment.
    if there is an apple in front of head's moving position:
        the snake grows.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>

// data limits
#define N_MAX 202
#define M_MAX 202
#define C_MAX 21
#define K_MAX 102

// grid states
#define BODY 0
#define APPLE 1
#define EMPTY 2
#define INVALID 3
#define TMP 5
#define SHARP 6

// snake states
#define DEAD 0
#define ALIVE 1
#define DONE 2

// directions
#define W 'W'
#define A 'A'
#define S 'S'
#define D 'D'

// #define DEBUG

using namespace std;

typedef pair<int, int> PII;

class Map;

class Snake {
private:
    queue<PII> body;
    Map* map;
    string moves;
    int move_p;
    int k;
    int state;

public:
    int id;
    Snake(PII headPos, string& in_moves, Map* m);
    void move();
    PII head() {return body.back(); };
    int getLenth() { return body.size(); };
    int getState() { return state; };
};


class Map {

private:
    vector<vector<int>> gameMap;
    int n, m;
    vector<Snake*> snakes;

public:
    void addSnake(Snake* newSnake) { snakes.push_back(newSnake); };
    int getMap(int x, int y) {
        return x >= 0 && x < n && y >= 0 && y < m ? gameMap[x][y] : INVALID;
    };
    int getMap(const PII& pos) {
        int x = pos.first, y = pos.second;
        return x >= 0 && x < n && y >= 0 && y < m ? gameMap[x][y] : INVALID;
    };
    void setMap(int x, int y, int state) {
        if ( !(x >= 0 && x < n && y >= 0 && y < m) ) {
            cout << "Invalid map setting" << endl;
            return;
        }
        gameMap[x][y] = state; 
    };
    void setMap(const PII& pos, int state) { 
        int x = pos.first, y = pos.second;
        if ( !(x >= 0 && x < n && y >= 0 && y < m) ) {
            cout << "Invalid map setting" << endl;
            return;
        }
        gameMap[x][y] = state; 
    };
    Map(int n, int m, vector<string>& rawMap);
    void run();
    void printMap();
    int countApples();
};

Map::Map(int n, int m, vector<string>& rawMap) {
    this->m = m; this->n = n;
    for (int i = 0; i < n; i ++) {
        gameMap.push_back(vector<int>(m));
        for (int j = 0; j < m; j ++) {
            switch (rawMap[i][j]) {
                case '.': 
                    gameMap[i][j] = EMPTY; break;
                case '#':
                    gameMap[i][j] = SHARP; break;
                case '@':
                    gameMap[i][j] = BODY; break;
                case '&':
                    gameMap[i][j] = APPLE; break;
                default:
                    break;
            }
        }
    }
}

void Map::run() {

    // calculate id for snakes
    int id = 1;
    map<PII, Snake*> headToSnake;
    for (Snake* s : snakes) {
        headToSnake[s->head()] = s;
    }
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            PII pos = make_pair(i, j);
            if (headToSnake.find(pos) != headToSnake.end()) {
                headToSnake[pos]->id = id ++;
            }
        }
    }

    sort(snakes.begin(), snakes.end(), [](Snake* a, Snake* b) {
        return a->id < b->id; // id assending order 
    });

    int cnt = 0;
    while(1) {
        bool done = true;

        for (Snake* pS : snakes) {
            if (pS->getState() != ALIVE) continue;
            pS->move();
            done = false;
        }
#ifdef DEBUG
        cout << "step " << cnt++ << ":" << endl;
        this->printMap();
        cout << endl;
#endif
        if (done) break;
    }
};

void Map::printMap() {
    for (int i = 0; i < n; i ++) {
        for (int j = 0; j < m; j ++) {
            switch(gameMap[i][j]) {
                case APPLE:
                    cout << '&'; break;
                case BODY:
                    cout << '#'; break;
                case EMPTY:
                    cout << '.'; break;
                default:
                    cout << ' '; break;
            }
        }
        cout << endl;
    }
};

int Map::countApples() {
    int cnt = 0;
    for (int i = 0; i < n; i ++)  {
        for (int j = 0; j < m; j ++) {
            if (gameMap[i][j] == APPLE) {
                cnt ++;
            }
        }
    }
    return cnt;
}

Snake::Snake(PII headPos, string& in_moves, Map* m) {
    // init map
    map = m;

    // init body with dfs
    stack<PII> reverseBody;
    reverseBody.push(headPos);
    map->setMap(reverseBody.top(), TMP);

    while(1) {
        bool find = false;
        PII last = reverseBody.top();
        int adjD[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
        for (int i = 0; i < 4; i ++) {
            PII adjP = make_pair(last.first + adjD[i][0], last.second + adjD[i][1]);
            if (map->getMap(adjP) == SHARP) {
                map->setMap(adjP, TMP);
                reverseBody.push(adjP);
                find = true;
                break;
            }
        }
        if (!find) break;
    }

    while(!reverseBody.empty()) {
        PII b = reverseBody.top(); reverseBody.pop();
        map->setMap(b, BODY);
        body.push(b);
    }

    // register snake
    map->addSnake(this);

    // init moves
    move_p = 0;
    moves = in_moves;
    k = moves.size();

    // init state
    state = ALIVE;
};

/*
moves another step and updates snake state and 
map state;
*/
void Snake::move() {
    if (move_p >= k){
        this->state = DONE;
        return;
    }
    PII head_pos = body.back();
    PII next_pos = head_pos;
    switch (moves[move_p ++]) {
        case W:
            next_pos.first --; break;
        case A:
            next_pos.second --; break;
        case S:
            next_pos.first ++; break;
        case D:
            next_pos.second ++; break;
        default:
            break;
    }

    switch (map->getMap(next_pos)) {
        case INVALID:
        case BODY:
            this->state = DEAD;
            while(!body.empty()) {
                PII pos = body.front(); body.pop();
                map->setMap(pos, APPLE);
            }
            break;
        case APPLE:
            body.push(next_pos);
            map->setMap(next_pos, BODY);
            break;
        case EMPTY:
            body.push(next_pos);
            // cout << "???" << endl;
            map->setMap(next_pos, BODY);
            map->setMap(body.front(), EMPTY);
            body.pop();
            break;
        default:
            break;
    };

};

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<string> rawMap;
    vector<PII> snakeHeads;
    vector<Snake*> snakes;

    for (int i = 0; i < n; i ++) {
        string row;
        cin >> row;
        rawMap.push_back(row);
        for (int j = 0; j < m; j ++) {
            if (row[j] == '@') {
                snakeHeads.push_back(make_pair(i, j));
            }
        }
    }

    Map game = Map(n, m, rawMap);

    for (PII head : snakeHeads) {
        string moves;
        cin >> moves;
        snakes.push_back(new Snake(head, moves, &game));
    }

    game.run();

    // game.printMap();

    
    // int tag = 0;

    // sort as asked
    vector<pair<int, Snake*>> priority_snake;
    for (Snake* s : snakes) {
        priority_snake.push_back(
            make_pair( -(s->getLenth() * C_MAX - s->id), s) 
        );
    }
    sort(priority_snake.begin(), priority_snake.end());

    for (auto [p, s] : priority_snake) {
        cout << s->getLenth() << " " << s->id << endl;
    }


    cout << game.countApples() << endl;

    for (Snake* s : snakes) {
        delete s;
    }
    return 0;
};
