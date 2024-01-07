# RPC-Server-Client-communication

This is an assignment based on Distributed Systems lecture.
There is a concurrent server (server process) which will perform the following calculations:
1. The inner product of the two vectors X ∙ Y (return: integer).
2. The average value of each vector: AVX, AVY (return: array of 2 float numbers).
3. The product r*(X+Y) (return: a vector-array of float numbers of n length).

Client after succesfull communication will enter: 1 float number r, 2 arrays X (x1,x2,...,xn) & Y (y1,y2,…,yn)
and the size of the arrays named: n

Communication is done via TCP AF_INET (Internet Domain) sockets. Each one
socket-Client process will read from the keyboard (repeatedly, until it declares
the user that he does not wish to continue).

<h2>How to run</h2>

1. Save all files in the same folder.
2. Open a terminal directed in the folder.
3. Input ```make``` and press **Enter** (executables are now created).
4. Input ```./ask1_server``` and press **Enter** (Server will start running).
5. Open a new terminal directed again in the folder.
6. Input ```./ask1_client localhost 5000```(Client will start running).
7. Open a new terminal directed again in the folder.
8. Input ```gcc –o client client_socket.c``` and press **Enter**.
9. Input ```./client localhost 5000``` and press **Enter**. (Client socket will start running).

