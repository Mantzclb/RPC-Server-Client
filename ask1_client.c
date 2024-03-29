/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "ask1.h"
#include <pthread.h>	//Thread use for multiple clients


struct struct_arg {		//using the struct_arg we can run threads for prog1
    char * hostname;	
    int client_name;
};

void
ask1_prog1_1(void *arguments){
	
	struct struct_arg *args = arguments;
	CLIENT *clnt;
	int  *result_1; //used for the result of the selection 1
	XY_array  inner_product_1_arg;
	float  *result_2; //used to save the average result of the X array
	X_array  averagex_1_arg;
	float  *result_3; //used to save the average result of the Y array
	Y_array  averagey_1_arg;
	rXY  *result_4; //used for the result of the selection 3
	r_times_X_Y  product_1_arg;

#ifndef	DEBUG
	clnt = clnt_create ((char *)args->hostname, ASK1_PROG1, ASK1_VERS, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (args->hostname);
		exit (1);
	}
#endif	/* DEBUG */
//==========================================================//

	
	int choice, i, n;
	int *X, *Y;		//Array X & Array Y
	int flag=1;	//When flag=0 our programm stops
	float r;	//r number for the third selection
	int socket_client=(int) args->client_name;	
	
	do{ //our programm is covered inside a do while statement for the flag choice when user wants to leave
	
		recv(socket_client,&choice,sizeof(int),0);	//here we are receiving the clients choice
		
		printf("The  Client's choice is: %d \n", choice);
		
		if(choice==1){
			
			//Inner product of array X and array Y (Selection 1)
			
			recv(socket_client,&n,sizeof(int),0);		//receiving the size of the arrays
			
			inner_product_1_arg.XY.XY_len=n;	//parse the size for the rpc_server
			inner_product_1_arg.XY_size=n;
			inner_product_1_arg.XY.XY_val=(int *) malloc(n*sizeof(int));
			X = (int *) malloc(n*sizeof(int));
			
			recv(socket_client,X,n*sizeof(int),0);		//receive the array X
			
			for(i=0;i<n;i++){
				inner_product_1_arg.XY.XY_val[i] = X[i];	//parse the array X to the rpc_server
			}
						
			result_1 = inner_product_1(&inner_product_1_arg, clnt);		//calculating the inner product of the 2 arrays in the rpc_server
			
			if (result_1 == (int *) NULL){ //safety check for call failed
				clnt_perror (clnt, "call failed");
			}
			else{
				send(socket_client,result_1,sizeof(int),0);		//otherwise send the results to the socket client
			}
			
		}		
		else if(choice==2){
			
			//average of array X and array Y[]
			
			recv(socket_client,&n,sizeof(int),0);		//receiving the size of the arrays
			
			averagex_1_arg.X.X_len=n;			//parse the size of array X for the rpc_server
			averagex_1_arg.X_size=n;
			averagex_1_arg.X.X_val=(int *) malloc(n*sizeof(int));
			X = (int *) malloc(n*sizeof(int));
			
			averagey_1_arg.Y.Y_len=n;			//parse the size of array Y for the rpc_server
			averagey_1_arg.Y_size=n;
			averagey_1_arg.Y.Y_val=(int *) malloc(n*sizeof(int));
			Y = (int *) malloc(n*sizeof(int));
			
			recv(socket_client,X,n*sizeof(int),0);		//receive the array X
			recv(socket_client,Y,n*sizeof(int),0);		//receive the array Y
			
			for(i=0;i<n;i++){ //parse array X to the rpc_server
				averagex_1_arg.X.X_val[i] = X[i];		
			}
			
			for(i=0;i<n;i++){ //parse array Y to the rpc_server
				averagey_1_arg.Y.Y_val[i] = Y[i];
			}
				
			result_2 = averagex_1(&averagex_1_arg, clnt);		//Average calculation for the array X
			result_3 = averagey_1(&averagey_1_arg, clnt);		//Average calculation for the array Y
			
			if (result_2 == (float *) NULL || result_3 == (float *) NULL){ //safety check for call failed
				clnt_perror (clnt, "call failed");
			}
			else{												//else send the results to the socket client
				send(socket_client,result_2,sizeof(float),0);		
				send(socket_client,result_3,sizeof(float),0);		
			}
			
		}
		else if (choice==3){
			//r*(X+Y)
			
			recv(socket_client,&n,sizeof(int),0);		//receiving the size of the arrays
		
			product_1_arg.X_Y.X_Y_len=n;		//parse the size of the 2 arrays to the rpc_server
			product_1_arg.X_Y_size=n;
			product_1_arg.X_Y.X_Y_val=(int *) malloc(n*sizeof(int));
			X = (int *) malloc(n*sizeof(int));
			
			recv(socket_client,X,n*sizeof(int),0);		//receive the X+Y calculation
			
			for(i=0;i<n;i++){
				product_1_arg.X_Y.X_Y_val[i] = X[i];		//parse the X+Y to the rpc_server
			}
			
			recv(socket_client,&r,sizeof(float),0);		//receive the r number
			
			product_1_arg.r=r;						//parse the r number to the rpc_server
			
			result_4 = product_1(&product_1_arg, clnt);		//calculate the r(X+Y)
			
			if (result_4 == (rXY *) NULL){ //safety check for call failed
				clnt_perror (clnt, "call failed");
			}
			else{	//else send the results to the socket client
				send(socket_client,result_4->prod.prod_val,n*sizeof(float),0);	
			}
		}
		else if(choice==4){ //Quit
			flag=0;
		}
		else{
			printf("Invalid Choice. Please try Again.\n\n");
		}
	}while(flag);
	
	
//==========================================================//
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[]){
	struct struct_arg arguments;	// arguments for passing in thread
	int socket_input, socket_accepted, portno, clientlen;
	int i=0;
	
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	
	
	pthread_t thread[50];
	
	if (argc < 3) {
        printf("usage %s hostname port\n", argv[0]);
        exit(1);
    }
	
	//socket
	
	socket_input = socket(AF_INET, SOCK_STREAM, 0);	
	
	bzero((char *) &server_addr, sizeof(server_addr));
	
	
	portno = atoi(argv[2]);
	server_addr.sin_family=AF_INET;
	server_addr.sin_port=htons(portno);
	server_addr.sin_addr.s_addr=INADDR_ANY;
	
	bind(socket_input, (struct sockaddr *) &server_addr, sizeof(server_addr));
	listen(socket_input,5);
	
	
	while(1){
		
		printf("Waiting for connection...\n");
		clientlen=sizeof(client_addr);
		socket_accepted=accept(socket_input, (struct sockaddr *) &client_addr, &clientlen);	//new client
		
		arguments.client_name = socket_accepted;
		arguments.hostname = argv[1];
		
		pthread_create(&(thread[i++]), NULL, (void *)ask1_prog1_1, (void *) &arguments);	//calling via thread 
	}


	return 0;
	
	exit (0);
}
