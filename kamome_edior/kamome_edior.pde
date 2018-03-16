PImage[] image = new PImage[5];
int cellSize=1;
EqTriangle[] tri = new EqTriangle[40];


int myX, myY;
int tWidth=58;

int[] now_r = new int[120];
int[] now_g = new int[120];
int[] now_b = new int[120];

int[] next_r = new int[120];
int[] next_g = new int[120];
int[] next_b = new int[120];

int[] diff_r = new int[120];
int[] diff_g = new int[120];
int[] diff_b = new int[120];

int[] set_r = new int[120];
int[] set_g = new int[120];
int[] set_b = new int[120];

int[] pixelColor = new int[120];


int count=0;
int nextCount = count+1;
int framePreScale;
float maxPreScale=30;
float lineCount;

int sendCount=-1;

void setup() {
//  noCursor();
  size(640, 600); 
  colorMode(RGB);
  //image[0] = loadImage("tsuta_L.png");
  //image[0] = loadImage("dia.png");
  //image[0] = loadImage("hane_L.png");
  //image[0] = loadImage("tsuta.png");
  //image[0] = loadImage("tsuta_6.png");
  //image[0] = loadImage("tsutaL32_120_002.png");
  //image[0] = loadImage("dia32_120_003.png");
  image[0] = loadImage("haneL32_120_004.png");

  noSmooth();
  frameRate(60);

  myX = width/2;
  myY = 350;//height/4*2;

  tri[8] = new EqTriangle(myX, myY, tWidth, 0);

  tri[7] = new EqTriangle(myX-30, myY-67, tWidth, 180);
  tri[6] = new EqTriangle(myX-(30+28), myY, tWidth, 0);
  tri[5] = new EqTriangle(myX-(30+28*2+2), myY-67, tWidth, 180);
  tri[4] = new EqTriangle(myX-(30+28*3+2), myY, tWidth, 0);
  tri[3] = new EqTriangle(myX-(30+28*4+4), myY-67, tWidth, 180);
  tri[2] = new EqTriangle(myX-(30+28*5+4), myY, tWidth, 0);
  tri[1] = new EqTriangle(myX-(30+28*5+4), myY-18, tWidth, 180);
  tri[0] = new EqTriangle(myX-(30+28*6+4), myY+67-18, tWidth, 0);

  tri[9] = new EqTriangle(myX+28, myY-67, tWidth, 180);
  tri[10] = new EqTriangle(myX+(30+28), myY, tWidth, 0);
  tri[11] = new EqTriangle(myX+(30+28*2), myY-67, tWidth, 180);
  tri[12] = new EqTriangle(myX+(30+28*3+2), myY, tWidth, 0);
  tri[13] = new EqTriangle(myX+(30+28*4+2), myY-67, tWidth, 180);
  tri[14] = new EqTriangle(myX+(30+28*5+4), myY, tWidth, 0);
  tri[15] = new EqTriangle(myX+(30+28*5+4), myY-18, tWidth, 180);
  tri[16] = new EqTriangle(myX+(30+28*6+6), myY+67-18, tWidth, 0);

  tri[18] = new EqTriangle(myX, myY-18, tWidth, 180);
  tri[17] = new EqTriangle(myX-28, myY+34+16, tWidth, 0);
  tri[19] = new EqTriangle(myX+30, myY+34+16, tWidth, 0);


  // 
  myX = width/2;
  myY = 480;//(int)(height/4*3);
  tri[28] = new EqTriangle(myX, myY, tWidth, 0);

  tri[27] = new EqTriangle(myX-30, myY-67, tWidth, 180);
  tri[26] = new EqTriangle(myX-(30+28), myY, tWidth, 0);
  tri[25] = new EqTriangle(myX-(30+28*2+2), myY-67, tWidth, 180);
  tri[24] = new EqTriangle(myX-(30+28*3+2), myY, tWidth, 0);
  tri[23] = new EqTriangle(myX-(30+28*4+4), myY-67, tWidth, 180);
  tri[22] = new EqTriangle(myX-(30+28*5+4), myY, tWidth, 0);
  tri[21] = new EqTriangle(myX-(30+28*5+4), myY-18, tWidth, 180);
  tri[20] = new EqTriangle(myX-(30+28*6+4), myY+67-18, tWidth, 0);

  tri[29] = new EqTriangle(myX+28, myY-67, tWidth, 180);
  tri[30] = new EqTriangle(myX+(30+28), myY, tWidth, 0);
  tri[31] = new EqTriangle(myX+(30+28*2), myY-67, tWidth, 180);
  tri[32] = new EqTriangle(myX+(30+28*3+2), myY, tWidth, 0);
  tri[33] = new EqTriangle(myX+(30+28*4+2), myY-67, tWidth, 180);
  tri[34] = new EqTriangle(myX+(30+28*5+4), myY, tWidth, 0);
  tri[35] = new EqTriangle(myX+(30+28*5+4), myY-18, tWidth, 180);
  tri[36] = new EqTriangle(myX+(30+28*6+6), myY+67-18, tWidth, 0);

  tri[38] = new EqTriangle(myX, myY-18, tWidth, 180);
  tri[37] = new EqTriangle(myX-28, myY+34+16, tWidth, 0);
  tri[39] = new EqTriangle(myX+30, myY+34+16, tWidth, 0);
  noStroke();

  image[0].loadPixels();
  for (int i=0; i<image[0].height; i++) {
    pixelColor[i] = image[0].pixels[i*image[0].width+count];

    now_r[i]=(pixelColor[i]>>16)&0xFF;
    now_g[i]=(pixelColor[i]>>8)&0xFF;
    now_b[i]=(pixelColor[i])&0xFF;

    pixelColor[i] = image[0].pixels[i*image[0].width+nextCount];
    next_r[i]=(pixelColor[i]>>16)&0xFF;
    next_g[i]=(pixelColor[i]>>8)&0xFF;
    next_b[i]=(pixelColor[i])&0xFF;


    if (now_r[i]>=255)now_r[i]=254;
    if (now_g[i]>=255)now_g[i]=254;
    if (now_b[i]>=255)now_b[i]=254;

    if (next_r[i]>=255)next_r[i]=254;
    if (next_g[i]>=255)next_g[i]=254;
    if (next_b[i]>=255)next_b[i]=254;
  }
}



void draw() {

  background(10);
  tint(255);

  framePreScale++;

  if (framePreScale>maxPreScale) {
    framePreScale=0;

    image[0].loadPixels();

    count++;

    if (count<(image[0].width-1)) {
      nextCount = count+1;
    } else if (count>(image[0].width-1)) {
      count=0;
      nextCount = count+1;
    } else if (count==(image[0].width-1)) {
      nextCount = 0;
    }




    for (int i=0; i<image[0].height; i++) {
      pixelColor[i] = image[0].pixels[i*image[0].width+count];

      now_r[i]=(pixelColor[i]>>16)&0xFF;
      now_g[i]=(pixelColor[i]>>8)&0xFF;
      now_b[i]=(pixelColor[i])&0xFF;

      pixelColor[i] = image[0].pixels[i*image[0].width+nextCount];
      next_r[i]=(pixelColor[i]>>16)&0xFF;
      next_g[i]=(pixelColor[i]>>8)&0xFF;
      next_b[i]=(pixelColor[i])&0xFF;


      if (now_r[i]>=255)now_r[i]=254;
      if (now_g[i]>=255)now_g[i]=254;
      if (now_b[i]>=255)now_b[i]=254;

      if (next_r[i]>=255)next_r[i]=254;
      if (next_g[i]>=255)next_g[i]=254;
      if (next_b[i]>=255)next_b[i]=254;
    }
  }

  imageMode(CORNER);
  tint(255);
  image(image[0], 0, 0, 640, 240);

  //  noFill();//(255,100);
  //  stroke(255, 0, 0);
  //  rect(count*(640/20), 0, (640/20), 120);
  //  text("now", count*(640/20)+5, 130);
  //
  //  noFill();//fill(255,100);
  //  stroke(255, 0, 0);
  //  rect(nextCount*(640/20), 0, (640/20), 120);
  //  text("next", nextCount*(640/20)+3, 130);


  lineCount = framePreScale*((nextCount*(640/image[0].width)-count*(640/image[0].width))/maxPreScale);
  stroke(255, 0, 0);
  line(count*(640/image[0].width)+lineCount, 0, count*(640/image[0].width)+lineCount, 240);
  stroke(0);
  line(0,120,640,120);
  for (int i=0; i<image[0].height; i++) {
    diff_r[i] = next_r[i] - now_r[i];
    diff_g[i] = next_g[i] - now_g[i];
    diff_b[i] = next_b[i] - now_b[i];

    set_r[i] = (int)(now_r[i] + framePreScale*(diff_r[i]/maxPreScale));
    set_g[i] = (int)(now_g[i] + framePreScale*(diff_g[i]/maxPreScale));
    set_b[i] = (int)(now_b[i] + framePreScale*(diff_b[i]/maxPreScale));
  }

  colorPreview();
}

void mousePressed() {
  saveData();
}


void colorPreview() {
  for (int i=39; i>=0; i--) {
    
    tri[i].drawImg( 
    color(set_r[i*3+1], set_g[i*3+1], set_b[i*3+1]), 
    color(set_r[i*3], set_g[i*3], set_b[i*3]), 
    color(set_r[i*3+2], set_g[i*3+2], set_b[i*3+2]));
    
  }
}

void saveData() {
  String[] lines = new String[image[0].height];

  int r;
  int g;
  int b;
  color pcolor;

  for (int j=0; j<image[0].width; j++) {
    for (int i=0; i<image[0].height; i++) {
      pcolor = image[0].pixels[i*image[0].width+j];

      r=(pcolor>>16)&0xFF;
      g=(pcolor>>8)&0xFF;
      b=(pcolor)&0xFF;

      if (r>=255)r=254;
      if (g>=255)g=254;
      if (b>=255)b=254;

      if (j==0) {
        lines[i] = (r<<16) + (g<<8) + b + "\t,";
      } else {
        lines[i] += (r<<16) + (g<<8) + b + "\t,";
      }
    }
  }

  saveStrings("data/points.txt", lines);
  ;
}