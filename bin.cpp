
/*
* Implementare un Garbage Collector appena hai tempo
* Ciao
*/
#include <iostream> 
#include <stdlib.h>
#include <vector>
#include <random>
#include <fstream>
using namespace std;

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

        vector<pair<int, int>> takePossibility(int x, int y){
            vector<pair<int, int>> possibilities;
            if(x - 1 >= 0 && maze[x - 1][y].visited == false)
                possibilities.push_back({x - 1, y});
            if(y - 1 >= 0 && maze[x][y - 1].visited == false)
                possibilities.push_back({x, y - 1});
            if(x + 1 < n && maze[x + 1][y].visited == false)
                possibilities.push_back({x + 1, y});
            if(y + 1 < n && maze[x][y + 1].visited == false)
                possibilities.push_back({x, y + 1});
            return possibilities;
        }   

    public: 
        vector<vector<Cella>> maze;
        
        labirinto(int n){
            this -> n = n; 
            maze.resize(n);
            fill(maze.begin(), maze.end(), vector<Cella>(n, Cella()));
        }

        void destroywall(int x, int y, int newX, int newY){
            if(maze[newX][newY].visited)
                return;
            if(newY - y == -1){
                maze[newX][newY].wallRight = false;
                maze[x][y].wallLeft = false;
            }
            else if((newY - y) == 1){
                maze[newX][newY].wallLeft = false;
                maze[x][y].wallRight = false;
            }
            else if(newX - x == 1){
                maze[newX][newY].wallUp = false;
                maze[x][y].wallDown = false;
            } else {
                maze[newX][newY].wallDown = false;
                maze[x][y].wallUp = false;
            }
            
        }

        void makemaze(int x, int y){
            maze[x][y].visited = true;
            
            vector<pair<int, int>> possibilities = takePossibility(x, y);
            if(possibilities.size() == 0)
                return; 
            while(possibilities.size() > 0){
                const int choose = rand() % possibilities.size();                
                destroywall(x, y, possibilities[choose].first, possibilities[choose].second);
                makemaze(possibilities[choose].first, possibilities[choose].second);
                possibilities.erase(possibilities.begin() + choose); 
            }
        }

        void write(){
            string Informations = to_string(n) + "\n";
            ofstream linux_maze_info;
            linux_maze_info.open("source/linux-amd64/MazeInfo.txt");
            
            for(vector<Cella> riga : maze)
                for(Cella cella : riga){
                    if(!cella.visited) continue;
                    Informations += cella.write();
                } 
            linux_maze_info << Informations;
            linux_maze_info.close();
            ofstream testing;
            testing.open("source/MazeInfo.txt");
            testing << Informations;
            testing.close();
            return;
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
    return 0; 
}
