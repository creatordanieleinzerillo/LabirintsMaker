class Cella {
   public boolean wallUp, wallDown, wallLeft, wallRight;
   public Cella(String up, String down, String left, String right){
      this.wallUp = up.equals("true");
      this.wallDown = down.equals("true");
      this.wallLeft = left.equals("true");
      this.wallRight = right.equals("true");
   }
   
   public void draw(float startY,float startX,float dimension){
     stroke(255);
     fill(255);
     if(startX == 0.0 && startY == 0.0)
       fill(100, 200, 0);
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
