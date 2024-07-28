#include <iostream> 
#include <stdlib.h>
#include <vector>
#include <random>
#include <fstream>
#include <stack>
using namespace std;

struct movement {
    int x;
    int y;
    int typeofMov;
};

typedef struct movement movement;

class Cella{
    public: 
        bool wallUp = true, wallDown = true, wallLeft = true, wallRight = true, visited = false;

        string write(){
            string result = (wallUp ? "true" : "false");
            result += " ";
            result += (wallDown ? "true" : "false");
            result += " ";
            result += (wallLeft ? "true" : "false");
            result += " ";
            result += (wallRight ? "true" : "false");
            result += "\n"; 
            return result;
        }

};

class labirinto {
    private:
        int n;

        vector<movement> takePossibility(int x, int y){
            vector<movement> possibilities;
            if(x - 1 >= 0 && maze[x - 1][y].visited == false)
                possibilities.push_back((movement){x - 1, y, 1});
            if(y - 1 >= 0 && maze[x][y - 1].visited == false)
                possibilities.push_back((movement){x, y - 1, 2});
            if(x + 1 < n && maze[x + 1][y].visited == false)
                possibilities.push_back((movement){x + 1, y, 3});
            if(y + 1 < n && maze[x][y + 1].visited == false)
                possibilities.push_back((movement){x, y + 1, 4});
            return possibilities;
        }   

    public: 
        Cella** maze;
        
        labirinto(int n){
            this -> n = n; 
            maze = (Cella**) malloc(n * sizeof(Cella*));
            for(size_t i = 0; i < n; i++){
                maze[i] = (Cella*) malloc(n * sizeof(Cella));
                for(size_t j = 0; j < n; j++){
                    maze[i][j] = Cella();
                }
            }
            //fill(maze.begin(), maze.end(), vector<Cella>(n, Cella()));
        }

        void destroywall(int x, int y, int kindOfMovement){
            if(kindOfMovement == 1){
                maze[x][y].wallDown = false;
                maze[x+1][y].wallUp = false;
            }
            else if(kindOfMovement == 2){
                maze[x][y].wallRight = false;
                maze[x][y + 1].wallLeft = false;
            }
            else if(kindOfMovement == 3){
                maze[x][y].wallUp = false;
                maze[x - 1][y].wallDown = false;
            }
            else if(kindOfMovement == 4){
                maze[x][y].wallLeft = false;
                maze[x][y - 1].wallRight = false;
            } 
            return;
        }

        void makemaze(int x, int y){
            stack<movement> moves;
            moves.push((movement){x, y, 0});
            while(!moves.empty()){
                x = moves.top().x;
                y = moves.top().y;
                size_t kindOfMovement = moves.top().typeofMov;
                moves.pop();
                if(maze[x][y].visited)
                    continue;
                destroywall(x, y, kindOfMovement);
                maze[x][y].visited = true;
                vector<movement> possibilities = takePossibility(x, y);
                if(possibilities.empty())
                    continue;
                size_t choose = rand() % possibilities.size();
                
                for(size_t i = 0; i < possibilities.size(); i++){
                    moves.push(possibilities[(choose + i) % possibilities.size()]);
                }
            }

        }

        void write(){
            string Informations = to_string(n) + "\n";
            ofstream linux_maze_info;
            linux_maze_info.open("source/linux-amd64/MazeInfo.txt");
            
            for(size_t i = 0; i < n; i++){
                Cella* riga = maze[i];
                for(size_t j = 0; j < n; ++j){
                    Cella cella = riga[j];
                    if(!cella.visited) continue;
                    Informations += cella.write();
                } 
            }
            linux_maze_info << Informations;
            linux_maze_info.close();
            ofstream testing;
            testing.open("source/MazeInfo.txt");
            testing << Informations;
            testing.close();
            return;
        }

        void freeMaze(){
            for(size_t i = 0; i < n; i++){
                free(maze[i]);
            }
            free(maze);
        }
};


int main(int argc, char** argv){
    int n;
    cout << "Dammi dimensioni del labirinto: " << endl; 
    cin >> n;
    srand(time(NULL));
    labirinto NuovoLabirinto(n);
    NuovoLabirinto.makemaze(0, 0);
    NuovoLabirinto.write();
    system("./source/linux-amd64/source");
    NuovoLabirinto.freeMaze();
    return 0; 
}
