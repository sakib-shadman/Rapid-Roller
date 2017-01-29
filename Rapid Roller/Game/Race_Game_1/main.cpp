#include <GL/glut.h>
#include <stdlib.h>
#include "SOIL_Lib/SOIL.h"
#include <stdio.h>
#include<iostream>
#include<windows.h>
#include<bits/stdc++.h>

using namespace std;

GLuint Textures[100];
int power_flag=0,neg=0;
int time_of_game=0;
float speed_multi=0.0002;

float game_speed = 5;
//int retry_check = 0;
int score = 0;
int best = 0;

float x_of_car=0;

float car_size_x = 0.50;
float car_size_y = 0.50;
float car_position_x = 0;
float car_position_y = 2;
float car_center_x = car_size_x/2;
float car_center_y = car_size_y/2;

float road_size_x = 5;
float road_size_y = 5;
float road_center_x = road_size_x/2;
float road_center_y = road_size_y/2;

float road_position_x = 0;
float road_position_y = 0;

float road_texture_u = 1;
float road_texture_v = 5;

int number_of_cars = 0,number_of_spike=0,neg_number_of_spike=0;
float opponent_x[100];
float opponent_y[100];
float opponent_texture_id[100];

float spike_x[5];
float spike_y[5];
float spike_texture_id[5];

float neg_spike_x[3];
float neg_spike_y[3];
float neg_spike_texture_id[6];

float opponent_size_x = 0.8;
float opponent_size_y = 0.3;
float opponent_center_x = opponent_size_x/2;
float opponent_center_y = opponent_size_y/2;

int time_to_come = 5,time_to_come_spike=1000,neg_time_to_come_spike=500;
float fixed_x[] = {-2,-1.5,-1,0,1,1.5,2};

bool game_running = true;

void update_ball_up()
{
    if (game_running == false)
        return;

    else
    {
         car_position_y = car_position_y + 0.0009 * game_speed;
    }
}

void update_ball()
{
    if (game_running == false)
        return;

    else
    {
         car_position_y = car_position_y - 0.0002 * game_speed;
    }
}

void Is_Collision()
{
    for (int i = 0; i < number_of_cars; i++)
    {
        float x1 = opponent_x[i] - opponent_size_x/2;
        float y1 = opponent_y[i] - opponent_size_y/2;
        float x2 = opponent_x[i] + opponent_size_x/2;
        float y2 = opponent_y[i] + opponent_size_y/2;

        float x3 = car_position_x - car_size_x/2;
        float y3 = car_position_y - car_size_y/2;
        float x4 = car_position_x + car_size_x/2;
        float y4 = car_position_y + car_size_y/2;

        if (x2 >= x3 && x1 <= x4)
        {
            if (y2 >= y3 && y1 <= y4)
            {
                power_flag=0;
                neg=0;
                //return false;
                update_ball_up();
            }
        }
    }
    update_ball();
    //return false;
}

//-----------------------Power bar-----------------------

bool Is_bar_Collision()
{


    for (int i = 0; i < number_of_spike; i++)
    {
        float x1 = spike_x[i] - opponent_size_x/2;
        float y1 = spike_y[i] - opponent_size_y/2;
        float x2 = spike_x[i] + opponent_size_x/2;
        float y2 = spike_y[i] + opponent_size_y/2;

        float x3 = car_position_x - car_size_x/2;
        float y3 = car_position_y - car_size_y/2;
        float x4 = car_position_x + car_size_x/2;
        float y4 = car_position_y + car_size_y/2;

        if (x2 >= x3 && x1 <= x4)
        {
            if (y2 >= y3 && y1 <= y4)
            {
                update_ball_up();
                neg=0;
                if(power_flag==0)
                {
                    power_flag=1;
                    score=score+50;
                }
               // spike_y[i]=3;
                return true;
            }
        }
    }
    //return false;
    update_ball();
    //return true;
}


void Add_bar(float starting_x, float starting_y, int tex_id)
{
    if (number_of_spike < 5)
    {
        spike_x[number_of_spike] = starting_x;
        spike_y[number_of_spike] = starting_y;
        spike_texture_id[number_of_spike] = tex_id;
        number_of_spike++;
    }
}

void Update_bar()
{
    if (game_running == false)
        return;

    if (number_of_spike > 0)
    {
        for (int i = number_of_spike - 1; i >= 0; i--)
        {
            spike_y[i] = spike_y[i] + speed_multi * game_speed;
            if (spike_y[i] > 3)
            {
                for (int j = i+1; j < number_of_spike; j++)
                {
                    spike_x[j-1] = spike_x[j];
                    spike_y[j-1] = spike_y[j];
                    spike_texture_id[j-1] = spike_texture_id[j];
                }
                number_of_spike--;
               // score+=2;
            }
        }
    }
}

//-----------------Power Bar------------------------------//

//-----------------power bar neg---------------------------
bool Is_bar_Collision2()
{


    for (int i = 0; i < neg_number_of_spike; i++)
    {
        float x1 = neg_spike_x[i] - opponent_size_x/2;
        float y1 = neg_spike_y[i] - opponent_size_y/2;
        float x2 = neg_spike_x[i] + opponent_size_x/2;
        float y2 = neg_spike_y[i] + opponent_size_y/2;

        float x3 = car_position_x - car_size_x/2;
        float y3 = car_position_y - car_size_y/2;
        float x4 = car_position_x + car_size_x/2;
        float y4 = car_position_y + car_size_y/2;

        if (x2 >= x3 && x1 <= x4)
        {
            if (y2 >= y3 && y1 <= y4)
            {
                update_ball_up();
                power_flag=0;
                if(neg==0)
                {
                    neg=1;
                    score=score-10;
                }
                return true;
            }
        }
    }
    //return false;
    update_ball();
    //return true;
}


void Add_bar2(float starting_x, float starting_y, int tex_id)
{
    if (neg_number_of_spike < 3)
    {
        neg_spike_x[neg_number_of_spike] = starting_x;
        neg_spike_y[neg_number_of_spike] = starting_y;
        neg_spike_texture_id[neg_number_of_spike] = tex_id;
        neg_number_of_spike++;
    }
}

void Update_bar2()
{
    if (game_running == false)
        return;

    if (neg_number_of_spike > 0)
    {
        for (int i = neg_number_of_spike - 1; i >= 0; i--)
        {
            neg_spike_y[i] = neg_spike_y[i] + speed_multi * game_speed;
            if (neg_spike_y[i] > 3)
            {
                for (int j = i+1; j < neg_number_of_spike; j++)
                {
                    neg_spike_x[j-1] = neg_spike_x[j];
                    neg_spike_y[j-1] = neg_spike_y[j];
                    neg_spike_texture_id[j-1] = neg_spike_texture_id[j];
                }
                neg_number_of_spike--;
               // score+=2;
            }
        }
    }
}
//--------------------power bar neg---------------------//

void Add_Opponent(float starting_x, float starting_y, int tex_id)
{
    if (number_of_cars < 100)
    {
        opponent_x[number_of_cars] = starting_x;
        opponent_y[number_of_cars] = starting_y;
        opponent_texture_id[number_of_cars] = tex_id;
        number_of_cars++;
    }
}


void Update_Opponents()
{
    if (game_running == false)
        return;

    if (number_of_cars > 0)
    {
        for (int i = number_of_cars - 1; i >= 0; i--)
        {
            opponent_y[i] = opponent_y[i] + 0.0002 * game_speed;
            if (opponent_y[i] > 3)
            {
                for (int j = i+1; j < number_of_cars; j++)
                {
                    opponent_x[j-1] = opponent_x[j];
                    opponent_y[j-1] = opponent_y[j];
                    opponent_texture_id[j-1] = opponent_texture_id[j];
                }
                number_of_cars--;
                score++;
            }
        }
    }
}

static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
    gluPerspective(60,ar,0.001,1000); //viewing angle,aspect ratio,near,far

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0,0,5, 0, 0 , 0, 0, 1, 0); //eye, center , up
}

int rand_range(int min_n, int max_n)
{
    return min_n + ( rand() % ( max_n - min_n + 1 ) );
}

void game_over_function(){
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures[3]);
        glPushMatrix();
        glTranslatef(-1, .5, 0 );

        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex2f(0,0);
        glTexCoord2f(1,0);
        glVertex2f(2,0);
        glTexCoord2f(1,1);
        glVertex2f(2,1);
        glTexCoord2f(0,1);
        glVertex2f(0,1);

        glEnd();
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void retry(){
    glEnable(GL_TEXTURE_2D);
    //glBindTexture(GL_TEXTURE_2D, Textures[4]);
        glPushMatrix();
        glTranslatef(-1, -.5, 0 );

        glBegin(GL_QUADS);
        glTexCoord2f(0,0);
        glVertex2f(0,0);
        glTexCoord2f(1,0);
        glVertex2f(2,0);
        glTexCoord2f(1,1);
        glVertex2f(2,1);
        glTexCoord2f(0,1);
        glVertex2f(0,1);

        glEnd();
        glPopMatrix();
    glDisable(GL_TEXTURE_2D);
}

void showScore(string str,float x,float y,float z)
{
    glRasterPos3f(x,y,z);
    //glColor3f(1.0,1.0,1.0);
    string s = str;
    void * font = GLUT_BITMAP_TIMES_ROMAN_24;

    for (std::string::iterator i = s.begin(); i != s.end(); ++i)
    {
        char c = *i;
        glutBitmapCharacter(font, c);
    }
}

void print_score(){
   // retry_check  = 0;
    glPushMatrix();
        glColor3f(1.0f,0.0,0.0);
    glPopMatrix();
}


static void display(void)
{
    time_of_game++;
    if(time_of_game == 1000*30)
    {
        speed_multi*=1.5;
        //time_of_game=0;
    }


    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    ///////////////////////////////////////////////////////////////////////////////////////
    //Road
    ///////////////////////////////////////////////////////////////////////////////////////
    if (game_running == true)
        road_position_y = road_position_y - 0.0005 * game_speed;

    if (road_position_y < -3)
        road_position_y = 3;

    //Road Quad 1
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures[1]);

    glPushMatrix();
    glTranslatef(road_position_x - road_center_x, road_position_y - road_center_y, 0 );
    glBegin(GL_QUADS);

    glTexCoord2f(0,0);
    glVertex2f(0,0);

    glTexCoord2f(road_texture_u,0);
    glVertex2f(road_size_x,0);

    glTexCoord2f(road_texture_u,road_texture_v);
    glVertex2f(road_size_x,road_size_y);

    glTexCoord2f(0,road_texture_v);
    glVertex2f(0,road_size_y);
    glEnd();

    glPopMatrix();

    glDisable(GL_TEXTURE_2D);

    //Road Quad 2
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures[1]);
    glPushMatrix();
    glTranslatef(road_position_x - road_center_x, road_position_y - road_center_y + road_size_y, 0 );
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(0,0);
    glTexCoord2f(road_texture_u,0);
    glVertex2f(road_size_x,0);
    glTexCoord2f(road_texture_u,road_texture_v);
    glVertex2f(road_size_x,road_size_y);
    glTexCoord2f(0,road_texture_v);
    glVertex2f(0,road_size_y);
    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);

    //Road Quad 3
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures[1]);
    glPushMatrix();
    glTranslatef(road_position_x - road_center_x, road_position_y - road_center_y - road_size_y, 0 );
    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(0,0);

    glTexCoord2f(road_texture_u,0);
    glVertex2f(road_size_x,0);

    glTexCoord2f(road_texture_u,road_texture_v);
    glVertex2f(road_size_x,road_size_y);

    glTexCoord2f(0,road_texture_v);
    glVertex2f(0,road_size_y);
    glEnd();
    glPopMatrix();

    glDisable(GL_TEXTURE_2D);



    //update_ball();

    ///////////////////////////////////////////////////////////////////////////////////////
    //Opponents
    ///////////////////////////////////////////////////////////////////////////////////////
    if (game_running == true) time_to_come = time_to_come - 1;
    if (time_to_come < 0)
    {
        time_to_come = 500 + rand_range(0,1000);
        Add_Opponent(fixed_x[rand_range(0,6)],-3,Textures[2]);
    }

    Update_Opponents();

    for (int i = number_of_cars - 1; i >= 0; i--) {
    //opponent car quad creation
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, opponent_texture_id[i]);

    glPushMatrix();
    glTranslatef(opponent_x[i] - opponent_center_x, opponent_y[i] - opponent_center_y, 0 );

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(0,0);
    glTexCoord2f(1,0);
    glVertex2f(opponent_size_x,0);
    glTexCoord2f(1,1);
    glVertex2f(opponent_size_x,opponent_size_y);
    glTexCoord2f(0,1);
    glVertex2f(0,opponent_size_y);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }
//-----------------------Power Bar-----------------------
    if (game_running == true) time_to_come_spike = time_to_come_spike - 1;
    if (time_to_come_spike < 0)
    {
        time_to_come_spike= 1500 + rand_range(0,2000);
        Add_bar(fixed_x[rand_range(0,20)],-3,Textures[5]);
    }

    Update_bar();

    for (int i = number_of_spike - 1; i >= 0; i--) {
    //opponent car quad creation
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, spike_texture_id[i]);

    glPushMatrix();
    glTranslatef(spike_x[i] - opponent_center_x, spike_y[i] - opponent_center_y, 0 );

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(0,0);
    glTexCoord2f(1,0);
    glVertex2f(opponent_size_x,0);
    glTexCoord2f(1,1);
    glVertex2f(opponent_size_x,opponent_size_y);
    glTexCoord2f(0,1);
    glVertex2f(0,opponent_size_y);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }
//-----------------Power Bar pos----------------------
//-----------------Power Bar neg-----------------------

   if (game_running == true) neg_time_to_come_spike = neg_time_to_come_spike - 1;
    if (neg_time_to_come_spike < 0)
    {
        neg_time_to_come_spike= 1500 + rand_range(0,1000);
        Add_bar2(fixed_x[rand_range(0,6)],-3,Textures[6]);
    }

    Update_bar2();

    for (int i = neg_number_of_spike - 1; i >= 0; i--) {
    //opponent car quad creation
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, neg_spike_texture_id[i]);

    glPushMatrix();
    glTranslatef(neg_spike_x[i] - opponent_center_x, neg_spike_y[i] - opponent_center_y, 0 );

    glBegin(GL_QUADS);
    glTexCoord2f(0,0);
    glVertex2f(0,0);
    glTexCoord2f(1,0);
    glVertex2f(opponent_size_x,0);
    glTexCoord2f(1,1);
    glVertex2f(opponent_size_x,opponent_size_y);
    glTexCoord2f(0,1);
    glVertex2f(0,opponent_size_y);
    glEnd();

    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    }
//--------------power bar neg---------------------//



    ///////////////////////////////////////////////////////////////////////////////////////
    //Car
    ///////////////////////////////////////////////////////////////////////////////////////

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, Textures[0]);

    glPushMatrix();
    glTranslatef(car_position_x-car_center_x, car_position_y-car_center_y, 0 );

    glBegin(GL_QUADS);

    glTexCoord2f(0,0);
    glVertex2f(0,0);
    glTexCoord2f(1,0);
    glVertex2f(car_size_x,0);
    glTexCoord2f(1,1);
    glVertex2f(car_size_x,car_size_y);
    glTexCoord2f(0,1);
    glVertex2f(0,car_size_y);

    glEnd();
    glPopMatrix();
    glDisable(GL_TEXTURE_2D);
    Is_Collision();
    //----------------------------Power Bar Collision------------------------
    if(Is_bar_Collision())
    {
       // cout<<"inn\n";
        game_running = true;
        //system("CLS");
        //printf("Collsion\n");
        //score=score+50;
       // print_score();
        //system("pause");
       //if(score>=best)
             //   best = score;
       // game_over_function();
        //retry();
    }
    if(Is_bar_Collision2())
    {
        game_running=true;
    }

    if(score<0)
    {
        game_running = false;
        system("CLS");
        printf("Collsion\n");
        print_score();
        //system("pause");
        if(score>=best)
                best = score;
        game_over_function();
       // retry();
    }

    //////////////////////////////////////////////////////////////////////////////////
    //Collision
    //////////////////////////////////////////////////////////////////////////////////
    if (car_position_y > 3 || car_position_y <-3){
        game_running = false;
        system("CLS");
        printf("Collsion\n");
        print_score();
        //system("pause");
        if(score>=best)
                best = score;
        game_over_function();
       // retry();
    }
    //if(retry_check ==  1)
         //   glColor3f(1.0,1.0,1.0);

    stringstream ss,ss1;
    ss<<score;
    string str = ss.str();
    showScore("Score is : "+str,.5,1.07,3);
    ss1<<best;
    string st1 = ss1.str();
    showScore("Best : "+st1,.5,1,3);

    glutSwapBuffers();
}

static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;
        case 'r':
            game_running = true;
            car_position_x = 0;
            car_position_y = -2;
            number_of_cars = 0;
            time_to_come = 3000;
           // retry_check = 1;
            score = 0;
            break;
        case 'a':
            if (game_running == true){
                car_position_x = car_position_x - 0.1;
            }
            if (car_position_x < -2.0){
                car_position_x = -2.0;
            }
            break;
        case 'd':
             if (game_running == true){
                car_position_x = car_position_x + 0.1;
             }
            if (car_position_x > 2.0){
                car_position_x = 2.0;
            }
            break;
        case 'l':
             if (game_running == true)
                car_position_y = car_position_y - 0.1;
            if (car_position_y < -2)
                car_position_y = -2;
            break;
        case 'j':
             if (game_running == true)
                car_position_y = car_position_y + 0.1;
            if (car_position_y > 0)
                car_position_y = 0;
            break;
    }
    glutPostRedisplay();
}

static void idle(void)
{
    glutPostRedisplay();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(600,800);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Rapid Roll Game");

    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);

    glClearColor(1,1,1,1);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_ALPHA);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_NORMALIZE);

    glGenTextures(100,Textures);

    GLuint tex_2d = SOIL_load_OGL_texture
	(
		"E:\\Graphics\\New folder\\Rapid_Roll\\Game\\b1.png",SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	Textures[0] = tex_2d;

    tex_2d = SOIL_load_OGL_texture
	(
		"E:\\Graphics\\New folder\\Rapid_Roll\\Game\\bg.jpg",SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	Textures[1] = tex_2d;

    tex_2d = SOIL_load_OGL_texture
	(
		"E:\\Graphics\\New folder\\Rapid_Roll\\Game\\roller1.png",SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	Textures[2] = tex_2d;

	tex_2d = SOIL_load_OGL_texture
	(
		"E:\\Graphics\\New folder\\Rapid_Roll\\Game\\go.png",SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	Textures[3] = tex_2d;

	tex_2d = SOIL_load_OGL_texture
	(
		"E:\\Graphics\\New folder\\Rapid_Roll\\Game\\retry.png",SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	Textures[4] = tex_2d;


	tex_2d = SOIL_load_OGL_texture
	(
		"E:\\Graphics\\New folder\\Rapid_Roll\\Game\\pw.png",SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	Textures[5] = tex_2d;

	tex_2d = SOIL_load_OGL_texture
	(
		"E:\\Graphics\\New folder\\Rapid_Roll\\Game\\bomb.png",SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	Textures[6] = tex_2d;

    ///////////////////////////////////////////////////////////
    //Road Texture Parameter
    ///////////////////////////////////////////////////////////
    glBindTexture(GL_TEXTURE_2D, Textures[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindTexture(GL_TEXTURE_2D, Textures[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, Textures[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, Textures[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, Textures[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, Textures[5]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    game_running = true;

    glutMainLoop();

    return EXIT_SUCCESS;
}
