import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;
//MazeInfo.txt
//Remove anti-aliasing 
File file, source;
FileReader fin;
BufferedReader bfin;
int a;
float cellHeight, cellWidth;
Cella[][] maze;

boolean won = false; 

int playerX = 0, playerY = 0; 
void settings(){
  int canvasSize = (displayWidth > displayHeight) ? (displayHeight - 100) : (displayWidth - 100); 
  size(canvasSize, canvasSize); 
}
void setup() {
  
  strokeWeight(1);
  try{
    
    file = new File(sketchPath("") + "/MazeInfo.txt");
    fin = new FileReader(file);
    bfin = new BufferedReader(fin);
    a =  Integer.parseInt(bfin.readLine());
    
    
    cellHeight = height / Float.parseFloat("" + a);
    cellWidth = width / Float.parseFloat("" + a);
    
    maze = new Cella[a][a];
    int ct = 0;

   String newLine;
   while((newLine = bfin.readLine()) != null){
     String[] informations = newLine.split(" "); 
     
     maze[ct / a][ct % a] = new Cella(informations[0], informations[1], informations[2], informations[3]); 
     
     maze[ct/a][ct % a].draw(cellHeight * (ct / a), cellWidth * (ct % a), cellHeight);
     
     ct++;
   }
   maze[0][0].active = true;
   maze[a - 1][a - 1].obj = true;
  }catch(Exception e){
    System.out.println(e.toString());
    return; 
  }
  noLoop(); 
}

void draw(){
  int n = maze.length; 
  for(int i = 0; i < n; i++){
   for(int j = 0; j < n; ++j){
    maze[i][j].draw(i * cellHeight, j * cellWidth, cellHeight);  
   }
  }
  
  if(won){
    fill(0);
    textSize(128);
    int canvasSize = (displayWidth > displayHeight) ? (displayHeight - 100) : (displayWidth - 100); 
    textAlign(CENTER);
    text("Hai vinto", canvasSize / 2, canvasSize / 2);
    
  } 
  
  
}

void keyPressed(){
  if(won)
    return; 
  maze[playerX][playerY].active = false;
  maze[playerX][playerY].player = true; 
  if(keyCode == 'W' && !maze[playerX][playerY].wallUp)
    playerX--;
  else if(keyCode == 'S' && !maze[playerX][playerY].wallDown)
    playerX++;
  else if(keyCode == 'A' && !maze[playerX][playerY].wallLeft)
    playerY--;
  else if(keyCode == 'D' && !maze[playerX][playerY].wallRight)
    playerY++;
  if(maze[playerX][playerY].obj){
    won = true; 
  }
  maze[playerX][playerY].active = true; 
  redraw(); 
}
