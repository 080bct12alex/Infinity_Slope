Rolling Ball Game

Description

This is a simple C++ game using the graphics library (graphics.h). The game features a ball rolling down an inclined plane (infinity slope) while avoiding obstacles. The objective is to survive as long as possible while accumulating points.

Game Features

1. Ball Movement and Jumping

The ball rolls down the slope while moving along a calculated ground level.

The player can make the ball jump by pressing the spacebar.

Jump physics include velocity updates to simulate gravity.


2. Obstacle Generation and Movement

Obstacles move from right to left.

Their height and width vary randomly to increase difficulty.

Collision detection is implemented to check if the ball hits an obstacle.


3. Graphics and Animation

A crescent moon is drawn in the background.

Stars are randomly generated in the sky.

The ball features a rotating line inside it to simulate rolling motion.


4. Score System and Difficulty Adjustment

The score increases when the ball successfully avoids an obstacle.

The obstacle speed increases gradually after a few successful jumps.

After reaching a certain threshold, the speed decreases slightly to maintain balance.


5. Game Loop and Restart Mechanism

The game runs continuously until the ball collides with an obstacle.

A "GAME OVER" message is displayed along with the final score.

Pressing any key restarts the game.


