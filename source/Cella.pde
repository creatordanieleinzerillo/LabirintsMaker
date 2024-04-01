class Cella {
   public boolean wallUp, wallDown, wallLeft, wallRight, player = false, active = false, obj = false;
   public Cella(String up, String down, String left, String right){
      this.wallUp = up.equals("true");
      this.wallDown = down.equals("true");
      this.wallLeft = left.equals("true");
      this.wallRight = right.equals("true");
   }
   
   
   public void draw(float startY,float startX,float dimension){
     stroke(255);
     if(active)
       fill(0, 100, 200); 
     else if(player)
       fill(100, 200, 0);  
     else if(obj)
       fill(240, 100, 120); 
     else 
       fill(255);
     noStroke();
     square(startX, startY, dimension);
     stroke(0, 0, 0);
     if(this.wallUp)
       line(startX, startY, startX + dimension, startY);
     
     if(this.wallDown)
       line(startX, startY + dimension, startX + dimension, startY + dimension);
     
     if(this.wallLeft)
       line(startX, startY, startX, startY + dimension);
     
     if(this.wallRight)
       line(startX + dimension, startY, startX + dimension, startY + dimension);
   }
   
}
