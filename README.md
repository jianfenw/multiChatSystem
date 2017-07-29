# multiChatSystem

The project is aimed to implement a online chat system which can support multi-user chat room. In a single chat room, each user can type his words and receive messages from all other users.

# Tips
## Test your server

Use telnet to communicate with the host at a certain IP addr and port number.

1. $ ping + ip

This will tell you whether the host at the IP addr is accessible or not

2. $ telnet ip port

This command allows you to communicate with the server at the host defined by ip/port

3. $ ctrl + ] -> q

Type ctrl + ] to enter the telnet configuration page and type 'q' to quit the telnet program

4. Manage the port number

lsof -i:"port-number"

This commend will list the process which uses the port number

kill -9 PID

You can kill the program with your hand!

# Please Star this project if you find it interesting and helpful
copyright@jwangee