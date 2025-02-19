#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <ctime>
#include <cmath>
#define PI 3.14159265
using namespace std;

const int screenWidth = 800;
const int screenHeight = 800;
const int slopeStartY = 200; // Starting Y-coordinate of slope (higher)
const int slopeEndY = 550;   // Ending Y-coordinate of slope(lower)
const int jumpStrength = -18; //initial y velocity(upwards) when going up// initial y velocity(downwards) when coming down
const int ballRadius = 15;
const int thickness=2; // degree of thickness of lines or circles
int extra_h=0; //to increase height of obstacle
int extra_w=0; //to increase width of obstacle
int ballX = 200;//x-coordinate of ball's center// this is fixed
int ballY;//y-coordinate of ball's center// changes when jumping or not jumping
int velocityY = 0;// initially, when not jumping
bool isJumping = false;// initially, ball is not jumping
int score = 0;// initial score = 0
int obstacleSpeed = 5; // Initial obstacle speed
int a=0;// color parameter for lines and circles
int theta =0;
int oscount=0;
int getGroundLevel(int x) {
    // Calculate the Y position based on the x-coordinate
    return slopeStartY + ((slopeEndY - slopeStartY) * x / screenWidth) ;// y=y1+((y2-y1)/(x2-x1))*(x-x1)
}                                                                       // (x1,y1)=(0, slopeStartY) /Left corner
                                                                        // (x2,y2)=(screenWidth, slopeEndY) /Left corner

// Function to draw a thicker line using Bresenham's algorithm
void drawBresenhamLine(int x1, int y1, int x2, int y2, int thickness, int a) {
    int COLOR1;
    if(a==1)
        COLOR1=BLACK;
    if(a==0)
        COLOR1=WHITE;
    if(a==2)
        COLOR1=RED;
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int lx = (x2 > x1) ? 1 : -1;
    int ly = (y2 > y1) ? 1 : -1;

    int x = x1, y = y1;

    if (dx > dy) {
        int p = 2 * dy - dx;
        for (int i = 0; i <= dx; i++) {
            // Draw a thicker line by adding pixels around the center point
            for (int j = 0; j <= thickness; j++) {
                putpixel(x, y + j, COLOR1);  // Adjust in the y-direction for thickness
            }
            x += lx;
            if (p < 0) {
                p += 2 * dy;
            } else {
                y += ly;
                p += 2 * (dy - dx);
            }
        }
    } else {
        int p = 2 * dx - dy;
        for (int i = 0; i <= dy; i++) {
            for (int j = 0; j <=thickness; j++) {
                putpixel(x + j, y, COLOR1);  // Adjust in the x-direction for thickness
            }
            y += ly;
            if (p < 0) {
                p += 2 * dx;
            } else {
                x += lx;
                p += 2 * (dx - dy);
            }
        }
    }
}


int b;
void rotateLine(int x1, int y1, int x2, int y2, float angle, int b) {

    // Compute midpoint
    int midX = (x1 + x2) / 2;
    int midY;
    if(b==1)
    midY = (y1 + y2) / 2 +2;
    if(b==0)
    midY = (y1 + y2) / 2 -2;


    // Convert angle to radians
    float rad = angle * (PI / 180.0);

    // Translate points to origin (relative to midpoint)
    int x1Rel = x1 - midX;
    int y1Rel = y1 - midY;
    int x2Rel = x2 - midX;
    int y2Rel = y2 - midY;

    // Apply rotation
    int newX1 = midX + (x1Rel * cos(rad) - y1Rel * sin(rad));
    int newY1 = midY + (x1Rel * sin(rad) + y1Rel * cos(rad));
    int newX2 = midX + (x2Rel * cos(rad) - y2Rel * sin(rad));
    int newY2 = midY + (x2Rel * sin(rad) + y2Rel * cos(rad));

    // Draw rotated line
    drawBresenhamLine(newX1, newY1, newX2, newY2,1,2);

}


void drawCircle(int xc, int yc, int r,int a) {
    int x = 0, y = r;
    int p = 1 - r;
    int color;
    if(a==1)
        color = BLACK;
    else if(a==2)
        color = BLUE;
    else
        color = BLACK;

    while (x <= y) {
        // Plot all 8 octants
        putpixel(xc + x, yc + y, color);
        putpixel(xc - x, yc + y, color);
        putpixel(xc + x, yc - y, color);
        putpixel(xc - x, yc - y, color);
        putpixel(xc + y, yc + x, color);
        putpixel(xc - y, yc + x, color);
        putpixel(xc + y, yc - x, color);
        putpixel(xc - y, yc - x, color);

        if (p < 0) {
            p += 2 * x + 3;
        } else {
            p += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}


void drawBall() {
    int groundLevel = getGroundLevel(ballX);
    if (!isJumping) {
        ballY = groundLevel - ballRadius;  // Keep the ball on the slope when ball is not jumping
    }
    drawCircle(ballX, ballY, ballRadius,1);
    setfillstyle(SOLID_FILL,WHITE);
    floodfill(ballX, ballY, BLACK);

    rotateLine(ballX-ballRadius, ballY+2, ballX+ballRadius, ballY+2, theta,0);// a line inside the ball that is rotating every frame
                                                                        // by increasing theta angle(degree)
    rotateLine(ballX-ballRadius, ballY-2, ballX+ballRadius, ballY-2, theta,1);
}

void drawObstacle(int x) {
    int groundLevel = getGroundLevel(x);
    setfillstyle(SOLID_FILL, RED);

    drawBresenhamLine(x   , groundLevel-30-extra_h,   x+20-extra_w,       groundLevel-30-extra_h,   thickness,0);
    drawBresenhamLine(x+20-extra_w, groundLevel-30-extra_h,   x+20-extra_w,       getGroundLevel(x+20-extra_w),          thickness,0);
    drawBresenhamLine(x+20-extra_w, getGroundLevel(x+20-extra_w),          x,          groundLevel,            thickness,0);
    drawBresenhamLine(x,    groundLevel,            x,          groundLevel-30-extra_h,   thickness,0);

    floodfill(x + 3, groundLevel - 2, WHITE);
}


// Function to fill the area below the slope with green
void fillAreaBelowSlope() {
    drawBresenhamLine(0, slopeStartY, screenWidth, slopeEndY, 1,0);
    setfillstyle(SOLID_FILL,GREEN);
    floodfill(screenWidth / 2 ,screenHeight - 1 , WHITE);
}

void drawCresentMoon(){
    //setcolor(YELLOW);
    drawCircle(700,100,70,1);//YELLOw
    setfillstyle(SOLID_FILL, YELLOW);
    floodfill(700, 100, BLACK);

    //setcolor(BLUE);
    drawCircle(700+30,100-10,70,1);//BLUE
    setfillstyle(SOLID_FILL,BLUE);
    floodfill(700+20,100-10,BLACK);

    drawCircle(700,100,70,2);
    drawCircle(700+30,100-10,70,2);
}

void gameLoop() {
    int starsTL[50];//stars at top left sky
    int j=25;
    for(int i=0;i<25;i++)
        {
                starsTL[i]=rand() % 550;
                starsTL[j]=rand()% 175;
                j++;

        }

    int starsBR[50];// stars at bottom right sky
    int j1=25;
    for(int i1=0;i1<25;i1++)
        {
                starsBR[i1]=rand() % (screenWidth - 400 + 1) + 400;
                starsBR[j1]=rand() % (300 - 200 + 1) + 200;
                j1++;

        }

    int obstacleX = screenWidth;
    int currentPage = 0;  // Page flipping variable

    while (true) {


        // Switch to the non-visible page
        setactivepage(currentPage);

        cleardevice();  // Clears only the off-screen buffer


        // Draw everything on the hidden page
        drawCresentMoon();
        fillAreaBelowSlope();
        drawObstacle(obstacleX);

            setfillstyle(SOLID_FILL, WHITE);
            for(int i=0;i<25;i++)
            {
                drawCircle(starsTL[i],starsTL[i+25],3,0);
                floodfill(starsTL[i],starsTL[i+25],BLACK);
            }

            setfillstyle(SOLID_FILL, WHITE);
            for(int i1=0;i1<25;i1++)
            {
                drawCircle(starsBR[i1],starsBR[i1+25],3,0);
                floodfill(starsBR[i1],starsBR[i1+25],BLACK);
            }


            theta = theta+obstacleSpeed;
            drawBall();

        // Ball physics
        if (isJumping) {
            velocityY += 1.2;
            ballY += velocityY;
            int groundLevel = getGroundLevel(ballX);
            if (ballY >= groundLevel - ballRadius) {
                ballY = groundLevel - ballRadius;
                isJumping = false;
            }
        }

        // Move obstacle
        obstacleX -= obstacleSpeed;
        if (obstacleX < 0) {
            obstacleX = screenWidth + rand() % 200;
            score++;
            if(oscount<6){
            obstacleSpeed=obstacleSpeed+2;
            oscount++;
            }
            else if(oscount>=6 && oscount<12)
            {
            obstacleSpeed=obstacleSpeed-2;
            oscount++;
            }
            else if(oscount>=12)
            {
                oscount=0;
            }
            int values[] = {0, 10, 20, 30};
            int randomValue = values[rand() % 4];
            extra_h = randomValue;
            int values1[] = {8, 13, 17};
            int randomValue1 = values1[rand() % 3];
            extra_w = randomValue1;

        }

        // Collision detection
        int groundLevel = getGroundLevel(ballX);
        if (ballX + ballRadius-5-obstacleSpeed > obstacleX && ballX - ballRadius < obstacleX + 20 && ballY + ballRadius >= groundLevel - (25 + extra_h)) {
            setactivepage(currentPage);
            outtextxy(screenWidth / 2 - 50, screenHeight / 4, "GAME OVER");
            char scoreText[20];
            sprintf(scoreText, "Score: %d", score);
            outtextxy(screenWidth / 2 - 50, screenHeight / 4 + 30, scoreText);
            outtextxy(screenWidth / 2 - 50, screenHeight / 4 + 60, "Press Any Button To RESTART");
            if (kbhit())
                break;
            setvisualpage(currentPage);
            break;
        }

        // Display score
        char scoreText[20];
        sprintf(scoreText, "Score: %d", score);
        outtextxy(10, 10, scoreText);

        // Handle Jump
        if (kbhit()) {
            char key = getch();
            if (key == ' ' && ballY >= getGroundLevel(ballX) - ballRadius) {
                if (!isJumping) {
                    velocityY = jumpStrength;
                    isJumping = true;
                }
            }
        }

        // Page Flip: Make the drawn page visible
        setvisualpage(currentPage);

        // Switch to the other page for the next frame
        currentPage = 1 - currentPage;

        delay(10);  // Keep a small delay for smooth animation
    }

    getch();  // Keep the screen open after Game Over
}




int main() {
    while(1){
    initwindow(screenWidth, screenHeight, "Infinity Slope");
    setbkcolor(BLUE);
    gameLoop();
    closegraph();
    extra_h=0;
    extra_w=0;
    ballX = 200;
    ballY;
    velocityY = 0;
    isJumping = false;
    score = 0;
    obstacleSpeed = 5;
    oscount=0;
    }
    return 0;
}
