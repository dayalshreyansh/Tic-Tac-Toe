==============================================
            Tic-Tac-Toe Game (C++)
==============================================

Welcome to Tic-Tac-Toe, a fun and interactive console-based game developed in C++!
Play against a friend or challenge the computer with smart AI using the Minimax algorithm.

==============================================
                FEATURES
==============================================
- Two Game Modes:
    * Player vs Player
    * Player vs Computer (AI)
- Computer AI using Minimax algorithm.
- Move validation to prevent illegal moves.
- Automatic detection of wins, losses, and draws.
- Clean and clear console-based board graphics.

==============================================
              HOW TO RUN
==============================================
1. Compile the source code using any C++ compiler:

    g++ -o tictactoe main.cpp

2. Run the executable:

    ./tictactoe

3. Follow the prompts and enjoy the game!

==============================================
             PROJECT STRUCTURE
==============================================
- main.cpp : Contains all classes (Player, Board, TicTacToe) and game logic.

==============================================
              HOW IT WORKS
==============================================
- Players are initialized with a symbol ('X' or 'O').
- Board is a 3x3 grid managed by the Board class.
- In Player vs Computer mode, the AI uses Minimax to determine optimal moves.
- The game loop handles:
    * Drawing the board
    * Accepting and validating player moves
    * Checking for a win/draw
    * Switching turns

==============================================
            DEMO 
==============================================

    --------------
    |   |   |   | 
    --------------
    |   |   |   | 
    --------------
    |   |   |   | 
    --------------
    Player X (X), enter row(1-3) and col(1-3):

(Computer also plays automatically in PvC mode!)

==============================================
          FUTURE IMPROVEMENTS
==============================================
- Implement graphical UI using libraries like SFML or Qt.
- Add difficulty levels for AI.
- Add sound effects and animations.

==============================================
              AUTHOR
==============================================
- Developed by: Shreyasnsh Dayal
- Built with C++ and lots of love!

==============================================
             LICENSE
==============================================
- Open Source project. Feel free to modify and share!!
