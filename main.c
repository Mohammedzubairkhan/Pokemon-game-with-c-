#include<stdio.h>
#include<GL/glut.h>
#include<Windows.h>
#include<MMSystem.h>
#include<SOIL.h>

int count=0,slide=0,c=0,ch=3,prev=0,flag1=0,flag2=0,v=0;
int cy1=-10,cx=20,score=0,inc=10,ashx[1][2]={0};
int x[12][2]={0},y[12][2]={0},defaulty[12][2]={0},life[12]={0};

void initialise()
{
   slide=0,c=0,ch=3,prev=0;
 cy1=-10,cx=20,score=0,inc=10;
    int i;

for(i=0;i<12;i++)
    life[i]=0;

life[0]=1;life[3]=1;
ashx[0][0]=400;
ashx[0][1]=600;
for(i=0;i<12;i++)
    {
    y[i][0]=0;
    y[i][1]=100;
    defaulty[i][0]=0;
    defaulty[i][1]=100;
    }
    x[0][0]=50;x[0][1]=150;x[1][0]=250;x[1][1]=350;x[2][0]=450;x[2][1]=550;x[3][0]=650;x[3][1]=750;x[4][0]=850;x[4][1]=950;
    x[5][0]=50;x[5][1]=150;x[6][0]=250;x[6][1]=350;x[7][0]=450;x[7][1]=550;x[8][0]=650;x[8][1]=750;x[9][0]=850;x[9][1]=950;
    x[10][0]=200; x[10][1]=300; x[11][0]=700; x[11][1]=800;
}

void survive()
{

if(score<(prev + 60))
    ch--;
prev = score;
 if(ch==0)
    {
    count++;
    PlaySound("end2.wav", NULL, SND_FILENAME| SND_SYNC);
    }
}


void create(int img)
{

    if(img==0 && y[0][0]==-150)
    {
        if(c!=0)
            survive();
        life[1]=1;life[4]=1;
        c++;
    }
    if(img==1 && y[1][0]==-150)
        life[2]=1;
    if(img==2 && y[2][0]==-150)
    {
        life[5]=1;life[6]=1;
    }

    if(img==5 && y[5][0]==-150)
    {
        life[8]=1;life[9]=1;
    }
    if(img==8 && y[8][0]==-150)
        life[7]=1;

if(img==7 && y[7][0]==-150)
{
    life[11]=1;life[10]=1;
}

if(img==11 && y[11][0]==-150)
{
    life[0]=1;life[3]=1;
}

}

void refresh(int img)
{
y[img][0]=0;y[img][1]=100;
}

void check(int img)
{
if(y[img][0]==-800)
    {
    if((x[img][0]>ashx[0][0] && x[img][0]<ashx[0][1]) || x[img][1]>ashx[0][0] && x[img][1]<ashx[0][1]){
        score+=inc;
        PlaySound("sound1.wav", NULL, SND_FILENAME| SND_SYNC);
        life[img]=0;
          refresh(img);
    }

}
if(y[img][1]==-900){
    life[img]=0;
          refresh(img);
}
}

void ImageLoader(char *file,int a,int b,int c,int d)
{
	glEnable(GL_TEXTURE_2D);

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);    //what if the s,t are > 1.0
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);    //expanded to fit .., then how'll u adjust the smoothness
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	GLuint tex = SOIL_load_OGL_texture
	(
		file,
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);

	glBindTexture(GL_TEXTURE_2D,tex);
    glBegin(GL_QUADS);
    	glTexCoord2f(0.0,1.0);glVertex2f(a,d);
    	glTexCoord2f(1.0,1.0);glVertex2f(c,d);
    	glTexCoord2f(1.0,0.0);glVertex2f(c,b);
    	glTexCoord2f(0.0,0.0);glVertex2f(a,b);
    glEnd();

    glFlush();

	glDisable(GL_TEXTURE_2D);
}

void lifeball()
{
switch(ch){
case 3:
ImageLoader("life1.png",110,-50,160,0);
case 2:
    ImageLoader("life1.png",55,-50,105,0);
case 1:
    ImageLoader("life1.png",0,-50,50,0);
}
}

void Write(char *string,int x,int y)
{

	glRasterPos2f(x,y);
    while(*string)    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}


void scene2(){
glColor3f(1.0,1.0,1.0);

if(life[0]==1)
{
y[0][0]+=cy1;y[0][1]+=cy1;
ImageLoader("poke1.png",x[0][0],y[0][0],x[0][1],y[0][1]);
check(0);
create(0);
}
if(life[1]==1)
{
y[1][0]+=cy1;y[1][1]+=cy1;
ImageLoader("poke2.png",x[1][0],y[1][0],x[1][1],y[1][1]);
check(1);
create(1);

}
if(life[2]==1)
{
y[2][0]+=cy1;y[2][1]+=cy1;
ImageLoader("poke3.png",x[2][0],y[2][0],x[2][1],y[2][1]);
check(2);
create(2);
}
if(life[3]==1)
{
y[3][0]+=cy1;y[3][1]+=cy1;
ImageLoader("poke4.png",x[3][0],y[3][0],x[3][1],y[3][1]);
check(3);
create(3);
}
if(life[4]==1)
{
y[4][0]+=cy1;y[4][1]+=cy1;
ImageLoader("poke5.png",x[4][0],y[4][0],x[4][1],y[4][1]);
check(4);
create(4);
}
if(life[5]==1)
{
y[5][0]+=cy1;y[5][1]+=cy1;
ImageLoader("poke6.png",x[5][0],y[5][0],x[5][1],y[5][1]);
check(5);
create(5);
}
if(life[6]==1)
{
y[6][0]+=cy1;y[6][1]+=cy1;
ImageLoader("poke7.png",x[6][0],y[6][0],x[6][1],y[6][1]);
check(6);
create(6);
}
if(life[7]==1)
{
y[7][0]+=cy1;y[7][1]+=cy1;
ImageLoader("poke8.png",x[7][0],y[7][0],x[7][1],y[7][1]);
check(7);
create(7);
}
if(life[8]==1)
{
y[8][0]+=cy1;y[8][1]+=cy1;
ImageLoader("poke9.png",x[8][0],y[8][0],x[8][1],y[8][1]);
check(8);
create(8);
}
if(life[9]==1)
{
y[9][0]+=cy1;y[9][1]+=cy1;
ImageLoader("poke10.png",x[9][0],y[9][0],x[9][1],y[9][1]);
check(9);
create(9);
}

if(life[10]==1)
{
y[10][0]+=cy1;y[10][1]+=cy1;
ImageLoader("pokea.png",x[10][0],y[10][0],x[10][1],y[10][1]);
check(10);
create(10);
}

if(life[11]==1)
{
y[11][0]+=cy1;y[11][1]+=cy1;
ImageLoader("pokeb.png",x[11][0],y[11][0],x[11][1],y[11][1]);
check(11);
create(11);
}
lifeball();
//ash
ImageLoader("ash.png",ashx[0][0],-1000,ashx[0][1],-800);
char buffer[10]={'\0'};
sprintf(buffer,"%d",score);
glColor3f(1.0,0.0,0.0);
Write("SCORE : ",850,-30);
Write(buffer,950,-30);
glPointSize(10.0);
	glColor3f(1.0,0.0,0.0);
glBegin(GL_LINE_LOOP);
glVertex2i(840,-5);
glVertex2i(990,-5);
glVertex2i(990,-35);
glVertex2i(840,-35);
glEnd();

glFlush();
glColor3f(1.0,1.0,1.0);
Sleep(50);
glutSwapBuffers();
}


void scene1(){
    if(v==0){
    if(flag1==0 && flag2==0){
ImageLoader("pic0.png",0,-1000,1000,0);
glColor3f(0.0,0.0,0.0);
ImageLoader("play.png",450,-850,550,-750);
ImageLoader("about.png",425,-745,575,-645);
ImageLoader("help-1.png",425,-955,575,-855);
}
    }

if(flag2==1 && v==1){

    ImageLoader("pic6.png",0,-1000,1000,0);
glColor3f(1.0,1.0,1.0);
ImageLoader("back.png",0,-950,200,-750);
glColor3f(0.0,0.0,0.0);
Write("This game is based on the popular cartoon series POKEMON. ",0,-30);
Write("It has been developed in such a way that it is true to the concept of the cartoon.",0,-60);
Write("It is designed and developed by MOHAMMED ZUBAIR KHAN. Who is a Computer Science & ",0,-90);

Write("Engineering student at U.V.C.E",0,-120);
Write("Under the guidance of Mr.SREYAS, who is a research scholar in C.S.E dept. at U.V.C.E ",0,-150);
Write("Version : 2.2",0,-180);
Write("     12/01/2018     ",0,-210);
Write("Copyright (c) 2018",0,-240);
Write("All rights reserved",0,-270);
Write("For more info visit - https://pokemon_game_mzk.com ",0,-300);

}
if(flag1==1 && v==1){

    ImageLoader("pic6.png",0,-1000,1000,0);
glColor3f(1.0,1.0,1.0);
ImageLoader("back.png",0,-950,200,-750);
glColor3f(0.0,0.0,0.0);
Write("The game is very easy to play. From the top of the screen, pokemons transcend down.",0,-30);
Write("There is a man at the bottom of the screen, you have to move this man and align it ",0,-60);

Write("along the pokemon you want to catch. You can move this man by pressing",0,-90);
Write("-> key : to move right",0,-120);
Write("<- key : to move left",0,-150);
Write("For every pokemon you catch your score, your score increases by 10.",0,-180);
Write("You have three chances to survive in the game, you will lose a chance when your unable",0,-210);
Write("to catch atleast 6 pokemons, out of 12. When you lose all your chances your game ",0,-240);

Write("will end. You can also end the game forcefully by pressing 'q'",0,-270);
}

glFlush();

glutSwapBuffers();

}


void scene3()
{
    int i;
    for(i=0;i<10;i++)
        life[i]=0;
    glClearColor(1.0,1.0,1.0,1.0);
   glClear(GL_COLOR_BUFFER_BIT);

glColor3f(1.0,1.0,1.0);
ImageLoader("end.png",0,-1000,1000,0);
glColor3f(0.234,1.0,0.5670);
Write("Well pl@yed & better LUCK next time :) !!!",300,-80);
glColor3f(1.0,0.0,0.0);
Write("Your Score : ",450,-170);
char buffer[10]={'\0'};
sprintf(buffer,"%d",score);
glColor3f(1.0,0.0,0.0);
Write(buffer,580,-170);
//front line
glBegin(GL_QUADS);
			glPointSize(120.0);
			glColor3f(0.4,0.4,0.4);
			glVertex2i(200,-90);
			glVertex2i(602,-90);
			glVertex2i(602,-95);
			glVertex2i(200,-95);
		glEnd();

		glBegin(GL_QUADS);
			glPointSize(120.0);
			glColor3f(1.0,0.5,0.0);
			glVertex2i(602,-90);
			glVertex2i(620,-90);
			glVertex2i(620,-95);
			glVertex2i(602,-95);
		glEnd();
//end line
		glBegin(GL_QUADS);
			glPointSize(120.0);
			glColor3f(0.4,0.4,0.4);
			glVertex2i(850,-105);
			glVertex2i(452,-105);
			glVertex2i(452,-100);
			glVertex2i(850,-100);
		glEnd();

		glBegin(GL_QUADS);
			glPointSize(120.0);
			glColor3f(1.0,0.5,0.0);
			glVertex2i(430,-105);
			glVertex2i(452,-105);
			glVertex2i(452,-100);
			glVertex2i(430,-100);
		glEnd();

//surroundedLoop
glPointSize(10.0);
	glColor3f(1.0,0.0,0.0);
glBegin(GL_LINE_LOOP);
glVertex2i(440,-140);
glVertex2i(625,-140);
glVertex2i(625,-180);
glVertex2i(440,-180);
glEnd();

glFlush();


glColor3f(1.0,1.0,1.0);
ImageLoader("logout.png",200,-950,350,-800);
glColor3f(0.0,0.0,0.0);
Write("REPLAY",252,-805);
glColor3f(1.0,1.0,1.0);
ImageLoader("login.png",700,-950,850,-800);
glColor3f(0.0,0.0,0.0);
Write("EXIT",772,-805);
glutSwapBuffers();

}

void special(int key,int x,int y)
{
if(count==1)
    {
        if(key==GLUT_KEY_LEFT)
  if(ashx[0][0]>0){
    ashx[0][0]-=cx;
    ashx[0][1]-=cx;
}
if(key==GLUT_KEY_RIGHT)
   if(ashx[0][1]<1000){
    ashx[0][1]+=cx;
    ashx[0][0]+=cx;
}
}
}

void myinit()
{
    initialise();
glClearColor(1.0,1.0,1.0,1.0);

glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluOrtho2D(0.0,1000.0,-1000.0,0.0);
}


void display()
{

glClear(GL_COLOR_BUFFER_BIT);
if(count==0)
    scene1();
if(count==1)
scene2();
if(count==2)
    scene3();
glFlush();

glutPostRedisplay();
}

void trackpad(int btn,int state,int xz,int yz)
{
if(btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
printf("%d %d\n",xz,yz);
    if(count==0 && (flag1==0 && flag2==0))
        {
            if((xz>=456) && (xz<=533) && (yz>=567) && (yz<=625))
                {
                count++;
               PlaySound("startPika.wav", NULL, SND_FILENAME| SND_SYNC);
            }
           if((xz>=428) && (xz<=566) && (yz>=484) && (yz<=548)){
                flag2=1;v=1;printf("bye");
            }
            if((xz>=428) && (xz<=569) && (yz>=642) && (yz<=692))
            {
                flag1=1;v=1;
            }
}
if(count==0 && (flag2==1)){
        if(((xz>=1) && (xz<=200)) && ((yz>=560) && (yz<=700))){
    flag2=0;v=0;
    printf("hi");
    xz=0;yz=0;}
}
if(count==0 && (flag1==1)){
      if((xz>=1) && (xz<=200) && (yz>=560) && (yz<=700)){
    flag1=0;v=0;}
}


if(count==2 && (xz>=704) && (xz<=860) && (yz>=585) && (yz<=688))
    {
    PlaySound("close.wav", NULL, SND_FILENAME| SND_SYNC);
    glutDestroyWindow(glutGetWindow());
}
if(count==2 && (xz>=205) && (xz<=365) && (yz>=585) && (yz<=688))
{
    initialise();
    PlaySound("startPika.wav", NULL, SND_FILENAME| SND_SYNC);
    count=1;

}
}

void keys(unsigned char key,int x,int y)
{
if(key == 'q')
    {
    count++;
PlaySound("end2.wav", NULL, SND_FILENAME| SND_SYNC);
    }
}

int main(int argc,char** argv)
{
glutInit(&argc,argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
glutInitWindowPosition(200,0);
glutInitWindowSize(1000,1000);
glutCreateWindow("story");
myinit();
glutDisplayFunc(display);
glutKeyboardFunc(keys);
glutMouseFunc(trackpad);
glutSpecialFunc(special);
glutMainLoop();
return 0;
}
