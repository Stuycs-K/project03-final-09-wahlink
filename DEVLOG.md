# Dev Log:

This document must be updated daily by EACH group member.

## Player 1

### 2024-06-02 - filled README
Whole class time spent.

### 2024-07-03 - Created files
Whole class time spent.

### 2024-08-03 - Created README, 3-way handshake
Whole class time spent. Used pipes to initiate a 3-way handshake between the server and client.

### 2024-09-03 - Started file editing
Whole class time spent. Created the file for storing game data and wrote its first gamestate. Also created code to randomly determine starting player

### 2024-10-03 - Tested file editing
Whole class time spent. Worked on figuring out how to use read, write, and lseek to recall information.

### 2024-13-03 - Started user input
Started writing code to take and process actions on the server side

### 2024 - 14 - 03- Converted to structs
Converted the previous string data storage format and used structs instead since they are way better.

### 2024-15-03 - Started the pipe structure for comms
Hadn't thought this out originally, but here's how the server and client will communicate:
  If server starts, it will generate its first turn, (maybe go straight to the loop)log it, and write it. It will then look to read -> log, and then go down to the for loop with write as the argument and read as one of the contents. If either of these fail, the loop breaks, both pipes close, and a dc message is sent. If the gamestate check declares a winner(this is at the end of the loop), a victory/defeat message is sent, both pipes close, and serverop is now allowed to view the replay.
  If client starts, server will write this as a unique message. Client will check for this, generate and write its turn, and then go into its read loop. I can have client generate its own file used to store replays(MAYBE) and have it view replays through that.

### 2024-15-03 - Started the pipe structure for comms
Worked on carrying out last devlog for server, will need to adjust the move processing func for client. MY GROUPID IS 18
