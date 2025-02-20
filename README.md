<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>C++ Game - README</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 40px;
            line-height: 1.6;
        }
        h1, h2 {
            color: #333;
        }
        code {
            background: #f4f4f4;
            padding: 3px 6px;
            border-radius: 4px;
        }
        pre {
            background: #f4f4f4;
            padding: 10px;
            border-radius: 4px;
            overflow-x: auto;
        }
    </style>
</head>
<body>
    <h1>C++ Game: Rolling Ball on an Infinite Slope</h1>
    <p>This is a C++ program that implements a simple game using the <code>graphics.h</code> library. The game features a ball rolling down an inclined plane (infinity slope) while avoiding obstacles.</p>

    <h2>Game Features</h2>
    <h3>1. Ball Movement and Jumping</h3>
    <ul>
        <li>The ball rolls down the slope while moving along a calculated ground level.</li>
        <li>The ball can jump when the spacebar is pressed.</li>
        <li>The physics for jumping includes velocity updates to simulate gravity.</li>
    </ul>

    <h3>2. Obstacle Generation and Movement</h3>
    <ul>
        <li>Obstacles move from right to left.</li>
        <li>Their height and width change randomly to increase difficulty.</li>
        <li>Collision detection checks if the ball hits an obstacle.</li>
    </ul>

    <h3>3. Graphics and Animation</h3>
    <ul>
        <li>A crescent moon is drawn in the background.</li>
        <li>Stars appear in the sky using randomly generated coordinates.</li>
        <li>The ball contains a rotating line inside it to simulate rolling.</li>
    </ul>

    <h3>4. Score System and Difficulty Adjustment</h3>
    <ul>
        <li>The score increases when the ball successfully avoids an obstacle.</li>
        <li>Obstacle speed increases every few successful jumps to make the game harder.</li>
        <li>After a certain threshold, speed decreases slightly to prevent excessive difficulty.</li>
    </ul>

    <h3>5. Game Loop and Restart Mechanism</h3>
    <ul>
        <li>The game runs in a loop, restarting upon collision with an obstacle.</li>
        <li>A "GAME OVER" message appears along with the score.</li>
        <li>Pressing any key will restart the game.</li>
    </ul>

   
</body>
</html>
