# TabbleLightGame
A simple game using BBB's utensils.

# How Works #
This is a simple game of luck. Using the potentiometer, the player must choose a number in a range that is determined by the photoresist. The game will pick a random number from the same range and the goal is to find the number.

If there is little light, so the game will be easy. Otherwise, the game will become more complicated.

After choosing a position potentiometer (which will be your number), the player must press the button to register your bid. The number that corresponds to what you have determined the potentiometer will be displayed on your computer screen.

If the player passes by, a blue light will appear, indicating that the attempt is near the random number for the game, and the player loses 5 points (from a total of 100 initial).

However, if the attempt is far away, a red light will illuminate. In this case, the player loses 2 points.

When hit the random number, a light will illuminate and the final score of the player will be shown on screen. Every attempt, the player is able to see what your score and what was his last attempt, If you reach 0 points, he loses.

# How to Play (Linux) - BeableBone Black#

Você irá precisar da BeableBone Black configurada. Irá acessar o sistema operacional dela.

ADownload the executable present in the repository and send to your BBB. execute:

```Shell
    & sudo ./LightTable
``` 
