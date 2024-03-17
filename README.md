"# TicTacToe"

Description:
The game is based on text input. It has 2 game modes (defined in modes.cpp). Singleplayer features unbeatable minimax algorithm. Game loop consists of 2 while loops (one for a session of games and one for one game).

Command to compile and link (MinGW_w64): 
g++ core_functions.cpp execution_functions.cpp modes.cpp main.cpp -o program 

To run:
1. install a compiler with the libraries (I used MinGW_w64 compiler and stdio, string and stdib (standard C) libraries)
2. set up enviroment PATH variable variable (\MinGW\bin)
3. download files (all the .cpp files and the include folder (with .h files))
4. compile with following command:
    g++ core_functions.cpp execution_functions.cpp modes.cpp main.cpp -o name_of_executable
    
1.1 or just download the executable (program.exe, should work on x86_64 bit (x64) machines)

Credits:

base structure for minimax:
    https://github.com/Cledersonbc/tic-tac-toe-minimax

introduction to header files:
    https://www.youtube.com/watch?v=9RJTQmK0YPI

introduction to multidimensional arrays:
    https://www.youtube.com/watch?v=gNgUMA_Ur0U
    
