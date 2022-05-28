import numpy as np
from time import sleep
from numba import jit

class GameOfLife():

    ANSI_COLOR_ALIVE = "\x1b[38;2;255;228;181;208m\x1b[48;2;5;5;20;208m"
    ANSI_COLOR_DEAD  = "\x1b[38;2;10;9;59;208m\x1b[48;2;5;5;20;208m"
    ANSI_COLOR_RESET = "\x1b[0m"

    def __init__(self, rows, cols, fps):
        
        self.rows = rows
        self.cols = cols
        self.fps = fps
        self.world = np.array(np.random.rand(self.rows, self.cols) > 0.5, dtype=int)

    def world_print(self):
    
        for i in range(self.rows):
            for j in range(self.cols):
                if self.world[i][j] == 0:
                    print(self.ANSI_COLOR_DEAD + "\u25A0 " + self.ANSI_COLOR_RESET, end = "")
                else:
                    print(self.ANSI_COLOR_ALIVE + "\u25A0 "  + self.ANSI_COLOR_RESET, end = "")
            print()   

        sleep((1.0/fps))

        for i in range(self.rows):
            print("\x1b[1A\r", end = "")
            
    def world_update(self):

        old_world = np.array(self.world, copy=True)
        
        for i in range(self.rows):
            for j in range(self.cols):
                state = old_world[i][j]
                neis = old_world[i % self.rows][(j + 1) % self.cols]\
                    +old_world[i % self.rows][(j - 1) % self.cols]\
                    +old_world[(i + 1) % self.rows][j % self.cols]\
                    +old_world[(i - 1) % self.rows][j % self.cols]\
                    +old_world[(i + 1) % self.rows][(j + 1) % self.cols]\
                    +old_world[(i - 1) % self.rows][(j - 1) % self.cols]\
                    +old_world[(i + 1) % self.rows][(j - 1) % self.cols]\
                    +old_world[(i - 1) % self.rows][(j + 1) % self.cols]	

                if state == 1:									
                    if (neis != 2 and neis != 3):
                        self.world[i][j] = 0
                else:
                    if neis == 3:								
                        self.world[i][j] = 1

if __name__ == "__main__":

    from argparse import ArgumentParser

    MAX_TIME = 1000000

    parser = ArgumentParser(description="Python Game of Life")
    
    parser.add_argument("--rows", "-r",
                        help="Number of rows for the grid",
                        type=int, default=50)
    
    parser.add_argument("--cols", "-c",
                        help="Number of collumns of the grid",
                        type=float, default=50)

    parser.add_argument("--fps", "-f",
                        help="Frames per second",
                        type=float, default=10)

    args = parser.parse_args()
    rows = args.rows
    cols = args.cols
    fps = args.fps

    game = GameOfLife(rows, cols, fps)
    game.world_print()

    for i in range(MAX_TIME):
        game.world_update()
        game.world_print()