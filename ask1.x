/* Angelos Vasileios Mantzoukas 19390128 */

/* Our Arrays */
struct X_array{
	int X <100>;
	int X_size;
};

struct Y_array{
	int Y <100>;
	int Y_size;
};

/* OPTION 1 */
struct XY_array{
	int XY <200>;
	int XY_size;
};

/* OPTION 2 */
struct average{
	float average[2];	
};

/* OPTION 3 */
struct r_times_X_Y{
	int X_Y <100>;	
	int X_Y_size;
	float r;
};

struct rXY{
	float prod <100>;
};

program ASK1_PROG1 {
		version ASK1_VERS {
			int inner_product(XY_array) = 1;
			float averageX(X_array) = 2;
			float averageY(Y_array) = 3;
			rXY product(r_times_X_Y) = 4;
			
	} = 1;
} = 0x12341234;
