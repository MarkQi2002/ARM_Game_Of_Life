# ARM_Game_Of_Life
## Game Description
- The concept of the Game of Life was invented by Cambridge mathematician John Conway. This game consists of a grid of cells which based a few mathematical rules, can live, die or multiply. Depending on the initial conditions, the cells can evolve into many interesting patterns. <br />
- Some unique initial pattern contributed by players across the world can be found at https://conwaylife.com/ref/lexicon/lex_home.htm

## Project Description
- Using the ARMv7 architecture on the DE1-SoC board along with its capability to compile and process code written in C, I was able to implement the Game of Life. <br />
- If you owns a physical DE1-SoC board, you can implement the program and observe the output using the VGA output of the board. <br />
- If you don't have a DE1-SoC board, you can simulate the program using and online tool at https://cpulator.01xz.net/?sys=arm-de1soc

## Rule Of The Game [1]
### For a space that is populated:
*- Each cell with one or no neighbors dies, as if by solitude (Rule 1)* <br />
<p align="center">
<img src="images/Rule_One.png">  <br />
<p align="left">
*- Each cell with four or more neighbors dies, as if by overpopulation (Rule 2)* <br />
<p align="center">
<img src="images/Rule_Two.png">  <br />
<p align="left">
*- Each cell with two or three neighbors survives (Rule 3)* <br />
<p align="center">
<img src="images/Rule_Three.png">  <br />
<p align="left">

### For a space that is empty or unpopulated:
*- Each cell with three neighbors becomes populated (Rule 4)*
<p align="center">
<img src="images/Rule_Four.png">  <br />
<p align="left">

## Conclusion
- This program demonstrated how the double buffer for the VGA controller in the DE1-SoC draw the frames using the memory mapped I/O ports.
- The underlying algorithm for Game of Life isn't hard to understand.
- The time complexity of the algorithm is O(m * n) where m is the number of rows and n is the number of columns.
- The space complexity of the algorithm is O(1).
  
## Timeline
- 03/19/2022, Completed and tested the first version of the program using CPUlator.

## Reference
[1] Game of Life Explanation, https://playgameoflife.com/info
