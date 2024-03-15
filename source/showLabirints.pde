import java.io.File;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.IOException;

//Remove anti-aliasing 

File file;
FileReader fin;
BufferedReader bfin;
int a;
float cellHeight, cellWidth;
Cella[][] maze;
void setup() {
  size(800, 800);
  strokeWeight(1);
  try{
    file = new File("MazeInfo.txt");
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
  }catch(Exception e){
    System.out.println(e.toString());
  }
}
