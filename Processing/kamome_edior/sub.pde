class EqTriangle { // equilateral triangle
  PImage img1, img2, img3;
  float x, y, n;
  int angle;
  public EqTriangle(int x, int y, int n, int a) {
    this.x = x;
    this.y = y;
    this.n = n;
    this.angle = a;
    img1 = loadImage("TRI_CORNER1.png");
    img2 = loadImage("TRI_CORNER2.png");
    img3 = loadImage("TRI_CORNER3.png");
  }

  public void drawImg(color col1, color col2, color col3) {

    float b = this.n * sqrt(3) / 4.0;
    float c = this.n / 4.0;
    float d = c * tan(radians(30));

    float x1 = 0;
    float y1 = -(b + d);

    pushMatrix();
    imageMode(CENTER);
    translate(this.x, this.y);
    rotate(radians(angle));
    tint(col1,200);
    image(img1, x1, y1);
    tint(col2,200);
    image(img2, x1, y1);
    tint(col3,200);
    image(img3, x1, y1);
    popMatrix();
  }
}

boolean overRect(int x, int y, int width, int height) {
  if (mouseX >= x && mouseX <= x+width && 
    mouseY >= y && mouseY <= y+height) {
    return true;
  } 
  else {
    return false;
  }
}