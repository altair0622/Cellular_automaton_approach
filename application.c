#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>

//#define DENSITY 0.2
#define P_REDUCE 0.25
#define MAX_SPEED 3
#define ROAD_LENGTH 100
#define CELL_LENGTH 1
#define MAX_SPACE (int)(ROAD_LENGTH / CELL_LENGTH)
#define MAX_TIME 500
//#define ACCIDENT_PROB 0.000100  //Probability of accident occurence of each car
#define MAX_ACCIDENT_PERIOD 50
#define MIN_ACCIDENT_PERIOD 20

//////////////////////////////////////////////
// structs
//////////////////////////////////////////////
struct Car
{
    int speed;
    //int space; // i-th cell
    int front_space;
	int accident_or_not;  //If this car come across accident, the value is -1  !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int accident_start_time;
	int accident_end_time;
};

///////////////////////////////////////////////
// Global variables
///////////////////////////////////////////////
double DENSITY = 0;
double ACCIDENT_PROB = 0;

struct Car *lane1[MAX_SPACE];
struct Car *lane2[MAX_SPACE];
struct Car *lane3[MAX_SPACE];
struct Car *lane4[MAX_SPACE];
struct Car *lane5[MAX_SPACE];

int* l1_to_l2;
int* l2_to_l1;
int* l2_to_l3;
int* l3_to_l2;
int* l3_to_l4;
int* l4_to_l3;
int* l4_to_l5;
int* l5_to_l4;


////////////////////////////////////////////////
// functions
////////////////////////////////////////////////

//firstly run the time seed only once at the beginning
void TimeSeed(){
    srand(time(NULL));
}

//generate random numbers within a range without duplication and with ascending order
void RandomGenerator(int* r){
    //static int r[(int)(MAX_SPACE*DENSITY)];
    int arr[MAX_SPACE]={0};
    for(int i=0; i<(int)(MAX_SPACE*DENSITY); i++){
        r[i] = rand()%MAX_SPACE;
        while(arr[r[i]] != 0){
            r[i] = rand()%MAX_SPACE;
        }
        arr[r[i]] = 1;
    }
    //sort array
    for(int i=0; i<(int)(MAX_SPACE*DENSITY); i++){
        for(int j=i+1; j<(int)(MAX_SPACE*DENSITY); j++){
            if(r[i]>r[j]){
                int temp = r[i];
                r[i] = r[j];
                r[j] = temp;
            }
        }
    }
}

//generate cars
void CarsGenerator(){
    TimeSeed();

    //lane1
    int* random_nums;
    if((random_nums = (int*)malloc((int)(MAX_SPACE*DENSITY) * sizeof(int))) == NULL) {printf("malloc error\n"); exit(1);}
    RandomGenerator(random_nums);
    int random_nums_index = 0;
    for(int i=0; i<(int)(MAX_SPACE); i++){
        // malloc
        if((lane1[i] = (struct Car*)malloc (sizeof(struct Car))) == NULL) {printf("malloc error\n"); exit(1);}
        // allocate cars
        if(random_nums_index<(int)MAX_SPACE*DENSITY && i == random_nums[random_nums_index]){
            lane1[i]->speed = rand()%(MAX_SPEED+1);
            if(random_nums_index < (int)MAX_SPACE*DENSITY - 1) lane1[i]->front_space = random_nums[random_nums_index+1] - random_nums[random_nums_index] - 1;
            else lane1[i]->front_space = MAX_SPEED+1;
            random_nums_index++;
        }else{
            lane1[i]->speed = -1;
        }
    }

    //lane2
    RandomGenerator(random_nums);
    random_nums_index = 0;
    for(int i=0; i<(int)(MAX_SPACE); i++){
        // malloc
        if((lane2[i] = (struct Car*)malloc (sizeof(struct Car))) == NULL) {printf("malloc error\n"); exit(1);}
        // allocate cars
        if(random_nums_index<(int)MAX_SPACE*DENSITY && i == random_nums[random_nums_index]){
            lane2[i]->speed = rand()%(MAX_SPEED+1);
            if(random_nums_index < (int)MAX_SPACE*DENSITY - 1) lane2[i]->front_space = random_nums[random_nums_index+1] - random_nums[random_nums_index] - 1;
            else lane2[i]->front_space = MAX_SPEED+1;
            random_nums_index++;
        }else{
            lane2[i]->speed = -1;
        }
    }

    //lane3
    RandomGenerator(random_nums);
    random_nums_index = 0;
    for(int i=0; i<(int)(MAX_SPACE); i++){
        // malloc
        if((lane3[i] = (struct Car*)malloc (sizeof(struct Car))) == NULL) {printf("malloc error\n"); exit(1);}
        // allocate cars
        if(random_nums_index<(int)MAX_SPACE*DENSITY && i == random_nums[random_nums_index]){
            lane3[i]->speed = rand()%(MAX_SPEED+1);
            if(random_nums_index < (int)MAX_SPACE*DENSITY - 1) lane3[i]->front_space = random_nums[random_nums_index+1] - random_nums[random_nums_index] - 1;
            else lane3[i]->front_space = MAX_SPEED+1;
            random_nums_index++;
        }else{
            lane3[i]->speed = -1;
        }
    }

    //lane4
    RandomGenerator(random_nums);
    random_nums_index = 0;
    for(int i=0; i<(int)(MAX_SPACE); i++){
        // malloc
        if((lane4[i] = (struct Car*)malloc (sizeof(struct Car))) == NULL) {printf("malloc error\n"); exit(1);}
        // allocate cars
        if(random_nums_index<(int)MAX_SPACE*DENSITY && i == random_nums[random_nums_index]){
            lane4[i]->speed = rand()%(MAX_SPEED+1);
            if(random_nums_index < (int)MAX_SPACE*DENSITY - 1) lane4[i]->front_space = random_nums[random_nums_index+1] - random_nums[random_nums_index] - 1;
            else lane4[i]->front_space = MAX_SPEED+1;
            random_nums_index++;
        }else{
            lane4[i]->speed = -1;
        }
    }

    //lane5
    RandomGenerator(random_nums);
    random_nums_index = 0;
    for(int i=0; i<(int)(MAX_SPACE); i++){
        // malloc
        if((lane5[i] = (struct Car*)malloc (sizeof(struct Car))) == NULL) {printf("malloc error\n"); exit(1);}
        // allocate cars
        if(random_nums_index<(int)MAX_SPACE*DENSITY && i == random_nums[random_nums_index]){
            lane5[i]->speed = rand()%(MAX_SPEED+1);
            if(random_nums_index < (int)MAX_SPACE*DENSITY - 1) lane5[i]->front_space = random_nums[random_nums_index+1] - random_nums[random_nums_index] - 1;
            else lane5[i]->front_space = MAX_SPEED+1;
            random_nums_index++;
        }else{
            lane5[i]->speed = -1;
        }
    }
}

// generate a new car
int NewCarGenerator(struct Car *lane[]){
    int i = 0;
    while(lane[i]->speed != -1) i++;
    return i;
}

//update front space
void UpdateFrontSpace(struct Car* lane[]){
    int n = MAX_SPACE + MAX_SPEED;
    for(int i=MAX_SPACE-1; i>=0; i--){
        if(lane[i]->speed != -1){
            lane[i]->front_space = n - i - 1;
            n = i;
        }
    }
}

//Keep the speed of accident car at 0
//if it is in accident and have not reached the accident end time
void hold_accidental_car(struct Car* lane_X[], int current_time, int index) {
	if (lane_X[index] != NULL && lane_X[index]->accident_or_not == -1 && lane_X[index]->accident_end_time >= current_time) {
		lane_X[index]->speed = 0;
	}
}

// move cars to the next position
void NextPosition(struct Car *lane[], int current_time){
    int if_new_car = 0; // judge whether it should generate a new car

    for(int i=MAX_SPACE-1; i>=0; i--){
        if(lane[i]->speed != -1){
            //Acceleration process
            lane[i]->speed = lane[i]->speed + 1;
            if(lane[i]->speed > MAX_SPEED) lane[i]->speed = MAX_SPEED;

            //Deceleration process, if there is not enough space
            if ((lane[i]->speed) > (lane[i]->front_space)) {
                lane[i]->speed = lane[i]->front_space;
            }

            //Randomization process, reduce speed with prob p
            if (lane[i]->speed > 0) {
                double prob_decelerate = (double)rand() / RAND_MAX;
                if (prob_decelerate <= P_REDUCE) lane[i]->speed = lane[i]->speed-1;
            }

			//Keep speed of accident car to 0
			hold_accidental_car(lane, current_time, i); 

            //Move this car to new position, Xi -> Xi + Vi
            int p = i + lane[i]->speed;
            if(p >= MAX_SPACE){
                if_new_car = i;
                continue;
            }
            if(lane[p]->speed == -1){
                lane[p]->speed = lane[i]->speed;
                lane[i]->speed = -1;
            }
        }
    }

    if(if_new_car != 0){
        int p = NewCarGenerator(lane);
        lane[p]->speed = lane[if_new_car]->speed;
        lane[if_new_car]->speed = -1;
    }
    UpdateFrontSpace(lane);
}

//move cars
void MoveCars(int current_time){
    NextPosition(lane1, current_time);
    NextPosition(lane2, current_time);
    NextPosition(lane3, current_time);
    NextPosition(lane4, current_time);
    NextPosition(lane5, current_time);
}

// check whether need to transfer the lane
void CheckTransfer(struct Car* l1[], struct Car* l2[], int* transfer_cars){
    for(int i=0; i<MAX_SPACE; i++){
        if(l1[i]->speed != -1){
            // 1 The distance ahead in current lane is smaller than the car speed.
            if(l1[i]->front_space < l1[i]->speed){
                // 2 The distance ahead in another lane is larger than in the current lane.
                int j=0;
                while(i+j+1<MAX_SPACE && l2[i+j+1]->speed == -1){
                    j++;
                } 
                if(i+j+1>=MAX_SPACE || j > l1[i]->front_space){
                    // 3 There exists an empty cell right in another lane.
                    if(l2[i]->speed == -1){
                        // 4 The distance ahead of the following vehicle in another lane is larger than the speed of the following vehicle.
                        j=0;
                        while(i-j-1>=0 && l2[i-j-1]->speed == -1) j++;
                        if(i-j-1<0 || l2[i-j-1]->speed <= j){
                            // the car should transfer the lane
                            transfer_cars[i] = 1;
                        }
                    }
                }
            }
        }else{
            transfer_cars[i] = 0;
        }
    }
}

//transfer the cars
void TransferOneLane(struct Car* l1[], struct Car* l2[], int* transfer_cars){
    //change status
    for(int i=0; i<MAX_SPACE; i++){
        if(l1[i]->speed!=-1 && l2[i]->speed==-1 && transfer_cars[i] == 1){
            l2[i]->speed = l1[i]->speed;
            l1[i]->speed = -1;
        }
    }
}

// if the same car can transfer to both the right lane and the left lane
// we assume that it has 1/2 possibility choosing the right lane
// and 1/2 possibility to choose the left lane.
void SolveDuplication(int* a, int* b){
    if(a == NULL || b == NULL){printf("error in solving duplication!\n"); exit(1);}
    for(int i=0; i<MAX_SPACE; i++){
        if(a[i] == 1 && b[i] == 1){
            int p = rand()%100;
            if(p<50) b[i] = 0;
            else a[i] = 0;
        }
    }
}

void TransferLanes(){
    int* l1_to_l2;
    int* l2_to_l1;
    int* l2_to_l3;
    int* l3_to_l2;
    int* l3_to_l4;
    int* l4_to_l3;
    int* l4_to_l5;
    int* l5_to_l4;

    if((l1_to_l2 = (int*)malloc(MAX_SPACE * sizeof(int))) == NULL) {printf("malloc error\n"); exit(1);}
    if((l2_to_l1 = (int*)malloc(MAX_SPACE * sizeof(int))) == NULL) {printf("malloc error\n"); exit(1);}
    if((l2_to_l3 = (int*)malloc(MAX_SPACE * sizeof(int))) == NULL) {printf("malloc error\n"); exit(1);}
    if((l3_to_l2 = (int*)malloc(MAX_SPACE * sizeof(int))) == NULL) {printf("malloc error\n"); exit(1);}
    if((l3_to_l4 = (int*)malloc(MAX_SPACE * sizeof(int))) == NULL) {printf("malloc error\n"); exit(1);}
    if((l4_to_l3 = (int*)malloc(MAX_SPACE * sizeof(int))) == NULL) {printf("malloc error\n"); exit(1);}
    if((l4_to_l5 = (int*)malloc(MAX_SPACE * sizeof(int))) == NULL) {printf("malloc error\n"); exit(1);}
    if((l5_to_l4 = (int*)malloc(MAX_SPACE * sizeof(int))) == NULL) {printf("malloc error\n"); exit(1);}

    CheckTransfer(lane1, lane2, l1_to_l2);
    CheckTransfer(lane2, lane1, l2_to_l1);
    CheckTransfer(lane2, lane3, l2_to_l3);
    SolveDuplication(l2_to_l1, l2_to_l3);
    CheckTransfer(lane3, lane2, l3_to_l2);
    CheckTransfer(lane3, lane4, l3_to_l4);
    SolveDuplication(l3_to_l2, l3_to_l4);
    CheckTransfer(lane4, lane3, l4_to_l3);
    CheckTransfer(lane4, lane5, l4_to_l5);
    SolveDuplication(l4_to_l3, l4_to_l5);
    CheckTransfer(lane5, lane4, l5_to_l4);

    TransferOneLane(lane1, lane2, l1_to_l2);
    TransferOneLane(lane2, lane1, l2_to_l1);
    TransferOneLane(lane2, lane3, l2_to_l3);
    TransferOneLane(lane3, lane2, l3_to_l2);
    TransferOneLane(lane3, lane4, l3_to_l4);
    TransferOneLane(lane4, lane3, l4_to_l3);
    TransferOneLane(lane4, lane5, l4_to_l5);
    TransferOneLane(lane5, lane4, l5_to_l4);

    UpdateFrontSpace(lane1);
    UpdateFrontSpace(lane2);
    UpdateFrontSpace(lane3);
    UpdateFrontSpace(lane4);
    UpdateFrontSpace(lane5);
}


//print cars
// format:
// time, lane#, i-th, speed, location, front space
void PrintCarList(FILE* ofp, struct Car *lane[], int timestamp, int lane_id){
    if(ofp == NULL) {printf("print error: car_list is NULL\n"); exit(1);}
    
    int id = 0;
    for(int i=0; i<MAX_SPACE; i++){
        if(lane[i]->speed == -1) continue;
        else{
            fprintf(ofp, "%d %d %d %d %d %d\n", timestamp, lane_id, id, lane[i]->speed, i, lane[i]->front_space);
            printf("%d %d %d %d %d %d\n", timestamp, lane_id, id, lane[i]->speed, i, lane[i]->front_space);
            id++;
        }
    }
    //fprintf(ofp, "********************* THIS LANE END *********************\n\n");
    //printf("********************* THIS LANE END *********************\n\n");
}

//print five lanes
void PrintFiveLanes(FILE* ofp, int timestamp){
    if(ofp == NULL) {printf("print error: car_list is NULL\n"); exit(1);}


    //fprintf(ofp, "\nlane1\n\n");
    //printf("\nlane1\n\n");
    PrintCarList(ofp, lane1, timestamp, 1);

    //fprintf(ofp, "\nlane2\n\n");
    //printf("\nlane2\n\n");
    PrintCarList(ofp, lane2, timestamp, 2);

    //fprintf(ofp, "\nlane3\n\n");
    //printf("\nlane3\n\n");
    PrintCarList(ofp, lane3, timestamp, 3);

    //fprintf(ofp, "\nlane4\n\n");
    //printf("\nlane4\n\n");
    PrintCarList(ofp, lane4, timestamp, 4);

    //fprintf(ofp, "\nlane5\n\n");
    //printf("\nlane5\n\n");
    PrintCarList(ofp, lane5, timestamp, 5);
}

//free the memory of the car list
void FreeCars(){
    for(int i=0; i<MAX_SPACE; i++) free(lane1[i]);
    for(int i=0; i<MAX_SPACE; i++) free(lane2[i]);
    for(int i=0; i<MAX_SPACE; i++) free(lane3[i]);
    for(int i=0; i<MAX_SPACE; i++) free(lane4[i]);
    for(int i=0; i<MAX_SPACE; i++) free(lane5[i]);
}

//Randomly generator a accident lasting time
int accident_period_generator() {
	int accident_lasting = (rand() % (MAX_ACCIDENT_PERIOD - MIN_ACCIDENT_PERIOD)) + MIN_ACCIDENT_PERIOD;
    //printf("\nthe accident last time is: %d \n", accident_lasting);
	return accident_lasting;
}

//produce accident for possible car, if accident happen in this function, return the accident lasting period
void one_car_accident_generator(FILE* ofp2, struct Car* lane_accident[], int current_time, int accident_period, int lane_id) {

	//decide if accident happen on this car
	for (int i = 0; i < MAX_SPACE; i++) 
	{
		double prob = (double)rand() / RAND_MAX;
		if (lane_accident[i] != NULL && lane_accident[i]->accident_or_not != -1)
		{
			if (prob<=ACCIDENT_PROB)
			{
                for(int k=0; k<accident_period+1; k++){
                    if(current_time + k >= MAX_TIME) break;
                    fprintf(ofp2, "%d %d %d\n", current_time + k,lane_id, i);
                }
				lane_accident[i]->accident_or_not = -1;
                lane_accident[i]->speed=0;
				lane_accident[i]->accident_start_time = current_time;
				lane_accident[i]->accident_end_time = accident_period + current_time;
			}
		}
	}
}

//Generate accidents for all 5 lanes
void one_car_accident(FILE* ofp2, int current_time) {
	one_car_accident_generator(ofp2, lane1, current_time, accident_period_generator(), 1);
	one_car_accident_generator(ofp2, lane2, current_time, accident_period_generator(), 2);
	one_car_accident_generator(ofp2, lane3, current_time, accident_period_generator(), 3);
	one_car_accident_generator(ofp2, lane4, current_time, accident_period_generator(), 4);
	one_car_accident_generator(ofp2, lane5, current_time, accident_period_generator(), 5);
}


////////////////////////////////////////////
// main function
////////////////////////////////////////////

int main (int argc, const char * argv[]){
    FILE* ofp;
    if ((ofp = fopen(argv[3], "w")) == NULL)  printf("Error! opening file\n");
    FILE* ofp2;
    if ((ofp2 = fopen(argv[4], "w")) == NULL)  printf("Error! opening file\n");

    DENSITY = atof(argv[1]);
    ACCIDENT_PROB = atof(argv[2]);

    /* initialize cars */
    CarsGenerator();
    printf("------ time: 0 ------");
    PrintFiveLanes(ofp, 0);

    int a_index = 0;
    
    /* start the system */
    for(int i=1; i<MAX_TIME; i++){

        MoveCars(i);
        TransferLanes();
		one_car_accident(ofp2, i);

        PrintFiveLanes(ofp, i);

    }

    /*free memory*/
    FreeCars();
}








