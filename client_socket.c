#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

//function for error handling
void error(char * msg) {
    perror(msg);
    exit(0);
}

int main(int argc, char * argv[]) {
    int clientSocket, portno;
    
    struct sockaddr_in serverAddr;
    struct hostent * server;

    if (argc < 3) {	
        printf("usage %s hostname port\n", argv[0]);
        exit(1);
    }

    portno = atoi(argv[2]);	//port
    clientSocket = socket(AF_INET, SOCK_STREAM, 0); //TCP socket opening

    if (clientSocket < 0){
    	error("ERROR opening socket");	
	}

    server = gethostbyname(argv[1]);		//get host
    if (server == NULL) {
        printf("ERROR!, no such host\n");
        exit(0);
    }
	
    bzero((char * ) & serverAddr, sizeof(serverAddr));	
    serverAddr.sin_family = AF_INET;
    bcopy((char * ) server -> h_addr, (char * ) & serverAddr.sin_addr.s_addr, server -> h_length);
    serverAddr.sin_port = htons(portno);

    printf("Trying to connect...\n");

    if (connect(clientSocket, (struct sockaddr * ) & serverAddr, sizeof(serverAddr)) < 0){
    	error("ERROR while connecting");	
	}

    printf("Connected!\n");

	int flag=1;			//flag to quit 
	int choice, i, n;
	int *X, *Y;
	int inner_prod;		//selection 1
	float r;
	float average[2];		//average[0] == average of array X, average[1] == average of array Y
	float *res;		//selection 3
	
    do { //our programm is inside a do while loop for the flag check
		
		printf("\n");
        printf("Please select your action. \n");
		printf("1. Multiplication of the 2 Arrays. \n");
		printf("2. Average for each array. \n");
		printf("3. Multiplication of r*(X=Y). \n");
		printf("4. Quit. \n");
        scanf("%d", & choice);

        send(clientSocket, & choice, sizeof(int), 0);

        if (choice == 1) { //inner product calculation for the arrays X and Y

            printf("Enter the size of the arrays: ");
            scanf("%d", & n);
            n *= 2;
            
            X=(int *)malloc(n*sizeof(int)); 	//array X
			
			send(clientSocket, &n, sizeof(int), 0);		//send the arrays size *2

            for (i = 0; i < n / 2; i++) { // read the array X values
                printf("X[%d] = ", i);			
                scanf("%d", &X[i]);
            }
            
            int j = 0;
            
            for (i; i < n; i++) { // read the array Y values
                printf("Y[%d] = ", j);			
                scanf("%d", & X[i]);
                j++;
            }

            send(clientSocket,X,n*sizeof(int),0);		//Send the array X and array Y in one table (this is why we made n*2
			
			recv(clientSocket,&inner_prod,sizeof(int),0); 	//receive the result

			printf("Inner product of array X and array Y : %d\n", inner_prod);
            

        } else if (choice == 2) {  //Average calculation of array X and array Y

            printf("Enter the size of the arrays: ");
            scanf("%d", & n);

            X=(int *)malloc(n*sizeof(int));
			Y=(int *)malloc(n*sizeof(int));
			
			send(clientSocket, &n, sizeof(int), 0);	//send the arrays size

            for (i = 0; i < n; i++) { // read the array X values
                printf("X[%d] = ", i);
                scanf("%d", & X[i]);
            }

            for (i = 0; i < n; i++) {	// read the array Y values
                printf("Y[%d] = ", i);	
                scanf("%d", & Y[i]);
            }

            send(clientSocket,X,n*sizeof(int),0);	//send the array X
            send(clientSocket,Y,n*sizeof(int),0);	//send the array Y

			recv(clientSocket,&average[0],sizeof(float),0); 	//receive the average of the array X
			recv(clientSocket,&average[1],sizeof(float),0);		//receive the average of the array Y

           
			printf("Average of array X is == %.2f\n", average[0]);
			printf("Average of array Y is == %.2f\n", average[1]);
            

        } else if (choice == 3) { //r*(X+Y) calculation

            printf("Enter the size of the arrays: ");
            scanf("%d", & n);

            send(clientSocket, &n, sizeof(int), 0);	//send the arrays size
			
			X=(int *)malloc(n*sizeof(int));
            
            for (i = 0; i < n; i++) {
                printf("X[%d] = ", i);		//d??ßase t?? t?µ?? t?? ?
                scanf("%d", & X[i]);
            }

            int dummy;
            for (i = 0; i < n; i++) { // read the array X values
                printf("Y[%d] = ", i); //the calculation of the X+Y is done inside the client, thats why we used the dummy variable
                scanf("%d", & dummy);
                X[i] += dummy; 				//add X[i] and Y[i] in X[i] \ (x[i] = x[i]+Y[i])
            }
			
			send(clientSocket,X,n*sizeof(int),0); 	//send the X+Y array 
			
            printf("Give the number r: ");		//read the r value
            scanf("%f", &r);

            send(clientSocket, &r, sizeof(float), 0);	// send the r value

            printf("\n");
			
			res=(float *)malloc(n*sizeof(float));	
            recv(clientSocket,res,n*sizeof(float),0);	//receive result

            
			for (i = 0; i < n; i++){
				printf("The calculation of %.2f*(X[%d]+Y[%d]) is == %.2f\n", r, i, i, res[i]);	
			}
            
        } else if (choice == 4) {		//client wants to quit
            flag = 0;
        } else { //check for wrong input
            printf("Invalid Choice. Try Again.\n\n");
        }
    } while (flag);

    close(clientSocket);

    return 0;
}
