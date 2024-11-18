
# cub3D

Cub3D is a C graphic project from the 42 school. The goal is to create a minigame 
using raycasting and the minilibx (the 42 school graphic library).

# How to use 

You can use you cub3D by following tho step. 
First we developped and coded the project for linux, so it won't be working on Mac and Window (for now). You can git clone the repo using :

    git clone git@github.com:Eiixela/Cub3D.git

You need to compile using the command :

    make

Congrats, you compiled our code ! We've included all kinds of map for you to be able to walk around. To execute just use :

    ./cub3D ./maps/good/good.cub

You can check out other map by changing the 'good.cub' file.

# Raycasting

Raycasting is a fast rendering technique used to create 3D perspective in a 2D map.
The idea is the following :

The raycasting algorithm is given a map that looks like this :

    111111111111111111111111
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    100000000000N00000000001
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    111111111111111111111111

'1' reprensents wall, and '0' reprensents walkable spaces. The 'N' is the spot the player spawns. The goal of the raycasting algorithm is to 'draw' invisible rays from the player to the distance in order to calculate the distance between every wall in the player POV to the player.
The ray are fictonal and are not actually visible by the player. From the top it look like this :

    ![ray](raycasting-map.jpg?raw=true)

Once the distance from the player to the wall is computed, we now have the needed information to 'draw' a wall. The height of said wall will depend on the distance from the player i.e the futher away the wall, the smaller and vise-versa.

For our Cub3D project, we choose to use the DDA algorithm. This algorithm computed the wall distance using non linear step, which makes it very efficient and precise.
Some ressources we use for the raycasting :

DDA: 
    
    https://www.geeksforgeeks.org/dda-line-generation-algorithm-computer-graphics/ 
    
General raycasting:
    
    https://lodev.org/cgtutor/raycasting.html
    https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/
    https://www.youtube.com/@thehelloworldguyofficial/playlists

MLX ressources :

    https://harm-smits.github.io/42docs/libs/minilibx/events.html

# Make your own maps

If you want to get reactive and use your own map, make sure they follow those requirements :

 **No other lines that the one specified here.**

∗ **North texture:**

    NO ./path_to_the_north_texture
· identifier: NO

· path to the north texure

∗ **South texture:**
    
    SO ./path_to_the_south_texture
· identifier: SO

· path to the south texure

∗ **West texture:**

    WE ./path_to_the_west_texture
· identifier: WE

· path to the west texure

∗ **East texture:**

    EA ./path_to_the_east_texture
· identifier: EA

· path to the east texure

∗ **Floor color:**

    F 220,100,0
· identifier: F
· R,G,B colors in range [0,255]: 0, 255, 255

∗ **Ceilling color:**

    C 225,30,0
· identifier: C
· R,G,B colors in range [0,255]: 0, 255, 255

∗ **Map**

    111111111111111111111111
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    100000000000N00000000001
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    100000000000000000000001
    111111111111111111111111

Must be closed by '1' all around

The identifier for the player must be present and one of the following letter : **'N', 'S', 'E', 'W'** (the orientation of the player when spawning).

Nothing below the map 

# Messing your our code

If you wish to changed the compiler or the flags used during compiling, you can go to the Makefile and check out those line :

For compiler :

    CC = cc (line 13)

Please keep in mind that the project might not compile is you change the compiler and have unexpected behavior.

For flags :

    CFLAGS = -Wall -Wextra -Werror -g3 -Ofast  (line 19) 

-g3 is used for debugging

-Ofast is a optimization

The project should compile even is all the flags are removed.
