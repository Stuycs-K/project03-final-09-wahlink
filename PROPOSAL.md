
# Final Project Proposal

## Group Members:

Kartik Wahlin
       
# Intentions:

I want to make code that allows two players on the same machine to play [chopsticks](https://en.wikipedia.org/wiki/Chopsticks_%28hand_game%29). 
# Intended usage:
Players will run the 'server' or 'client' executable to connect to each other over a set WKP. They will then be prompted to make their move via a chain of user inputs specifying what move they want to make, the hand they want to use, and the target of their move.
  
# Technical Details:

My current plan is to use pipes to relay information from client to server, where the game state is stored in a file managed by the server. I will likely use a shared integer to keep track of which player is taking their turn. A stretch goal of mine is to use forking to allow for the server to play multiple clients at once. Another potential expansion would be having games with more than two players.
I will be doing everything.
I will use an array of integers to represent the game state, with each one representing the number of fingers on each hand. I will verify the connection using a three-way handshake. 
    
# Intended pacing:

Jan 13 - 3 way handshake tested and functional
Jan 17 - Shared memory verification makes sure users do not read information too early, and wait their turn.
Jan 20 - base game functional, potentially add more than 2 players
