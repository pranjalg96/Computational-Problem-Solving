#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define CAPACITY 18
#define FLOORS 20
#define STOPTIME 15
#define movePerFloorTime 3

// Elevator structure
struct elevator
{
	int num_passengers; // Number of passengers in the elevator
	int passenger_dest[CAPACITY]; // Destination floor of each passenger
	int elevator_floor[FLOORS]; // Number of passengers assigned to each floor of the elevator
	int current_floor; // Current floor of the elevator
	int total_time;	 // Total time elapsed
};

//initialize values of the object according to constraints
void initialize(struct elevator * pointer_ele); // scenario 1
void initialize_two(struct elevator * pointer_ele1, struct elevator * pointer_ele2); // scenario 2
void initialize_three(struct elevator * pointer_ele1, struct elevator * pointer_ele2, int maxFloor1); // scenario 3
void initialize_four(struct elevator * pointer_ele1, struct elevator * pointer_ele2, struct elevator * pointer_ele3,int maxFloor1, int maxFloor2); // scenario 4

void operate_elevator(struct elevator * pointer_ele); // operate the elevator
int calc_top_floor(int dest[], int num_passengers); // calculate the top floor of the elevator

//int main(int argc,char **argv)
int main()
{
	srand(time(NULL)); // different seed every run

// SCENARIO 1
	int num_iterations_1 = 1000; // Number of iterations over which to repeat the experiment
	double avg_time_1 = 0.0; // Average elevator time over iterations
	int min_time_1 = 400; // Min elevator time over iterations, initialized to large value
	int max_time_1 = 0; // Max elevator time over iterations
	double avg_per_passenger_global = 0.0; // Average time per passenger, calculated over all iterations

	printf("-----SCENARIO 1-----\n\n");

	for(int i = 0; i < num_iterations_1; i++)
	{

		struct elevator elevator_1; // Create elevator_1 object
		initialize(&elevator_1); // Initialize members
		operate_elevator(&elevator_1); // Operate the elevator_1

		int total_time_ele_1 = elevator_1.total_time; // Total time taken by elevator in current iteration
		avg_time_1 += total_time_ele_1;

		// find minimum time
		if (total_time_ele_1 < min_time_1)
			min_time_1 = total_time_ele_1;
		
		// find max. time
		if (total_time_ele_1 > max_time_1)
			max_time_1 = total_time_ele_1;
	}

	avg_time_1 /= num_iterations_1;

	// print the results of the scenario
	printf("Number of iterations: %d\n", num_iterations_1);
	printf("Average elevator time: %f\n", avg_time_1);
	printf("Minimum elevator time: %d\n", min_time_1);
	printf("Maximum elevator time: %d\n\n", max_time_1);
	


// SCENARIO 2
	int num_iterations_2 = 1000; // Number of iterations over which to repeat the experiment
	double avg_time_2; // Average elevator time over iterations
	int min_time_2 = 400; // Min elevator time over iterations, initialized to large value
	int max_time_2 = 0; // Max elevator time over iterations


	printf("-----SCENARIO 2-----\n\n");
	
	for(int i = 0; i < num_iterations_2; i++)
	{
		struct elevator elevator_21; // Create elevator_21 object
		struct elevator elevator_22; // Create elevator_22 object
		initialize_two(&elevator_21,&elevator_22); // Initialize members
		operate_elevator(&elevator_21); // Operate the elevator_21
		operate_elevator(&elevator_22); // Operate the elevator_22
	
		int total_time_ele_2;
		if (elevator_21.total_time > elevator_22.total_time) // Determine the total time (the max between both elevators) taken 
		{
			total_time_ele_2 = elevator_21.total_time; // Time taken by elevator in current iteration
		}
		else
		{
			total_time_ele_2 = elevator_22.total_time; // Time taken by elevator in current iteration
		}
		avg_time_2 += total_time_ele_2;


		// find minimum time
		if (total_time_ele_2 < min_time_2)
			min_time_2 = total_time_ele_2;
		
		// find max. time
		if (total_time_ele_2 > max_time_2)
			max_time_2 = total_time_ele_2;

	}

	avg_time_2 /= num_iterations_2;

	// Print the results of scenario 2
	printf("Number of iterations: %d\n", num_iterations_2);
	printf("Average elevator time: %f\n", avg_time_2);
	printf("Minimum elevator time: %d\n", min_time_2);
	printf("Maximum elevator time: %d\n\n", max_time_2);

// SCENARIO 3
	int num_iterations_3 = 1000; // Number of iterations over which to repeat the experiment
	double avg_time_3; // Average elevator time over iterations
	int min_time_3 = 400; // Min elevator time over iterations, initialized to large value
	int max_time_3 = 0; // Max elevator time over iterations
	int maxFloor1 = 11; // Max floor for elevator_31

	printf("-----SCENARIO 3-----\n\n");
	
	for(int i = 0; i < num_iterations_3; i++)
	{
		struct elevator elevator_31; // Create elevator_31 object
		struct elevator elevator_32; // Create elevator_32 object
		initialize_three(&elevator_31,&elevator_32,maxFloor1); // Initialize members
		operate_elevator(&elevator_31); // Operate the elevator_31
		operate_elevator(&elevator_32); // Operate the elevator_32
	
		int total_time_ele_3;
		if (elevator_31.total_time > elevator_32.total_time) // Determine the total time (the max between both elevators) taken 
		{
			total_time_ele_3 = elevator_31.total_time; // Time taken by elevator in current iteration
		}
		else
		{
			total_time_ele_3 = elevator_32.total_time; // Time taken by elevator in current iteration
		}
		avg_time_3 += total_time_ele_3;


		// find minimum time
		if (total_time_ele_3 < min_time_3)
			min_time_3 = total_time_ele_3;
		
		// find max. time
		if (total_time_ele_3 > max_time_3)
			max_time_3 = total_time_ele_3;

	}

	avg_time_3 /= num_iterations_3;

	// Print the results of scenario 3
	printf("Number of iterations: %d\n", num_iterations_3);
	printf("Average elevator time: %f\n", avg_time_3);
	printf("Minimum elevator time: %d\n", min_time_3);
	printf("Maximum elevator time: %d\n", max_time_3);
	printf("Best maxFloor1: %d\n\n",maxFloor1);

// SCENARIO 4
	int num_iterations_4 = 1000; // Number of iterations over which to repeat the experiment
	double avg_time_4; // Average elevator time over iterations
	int min_time_4 = 400; // Min elevator time over iterations, initialized to large value
	int max_time_4 = 0; // Max elevator time over iterations
	int maxFloor41 = 7; // Max floor for elevator_41
	int maxFloor42 = 15; // Max floor for elevator_42

	printf("-----SCENARIO 4-----\n\n");
	
	for(int i = 0; i < num_iterations_4; i++)
	{
		
		struct elevator elevator_41; // Create elevator_41 object
		struct elevator elevator_42; // Create elevator_42 object
		struct elevator elevator_43; // Create elevator_43 object
		initialize_four(&elevator_41,&elevator_42,&elevator_43,maxFloor41,maxFloor42);
		operate_elevator(&elevator_41); // Operate the elevator_41
		operate_elevator(&elevator_42); // Operate the elevator_42
		operate_elevator(&elevator_43); // Operate the elevator_43
	
		int total_time_ele_4;
		if (elevator_41.total_time > elevator_42.total_time && elevator_41.total_time > elevator_43.total_time) // Determine the total time (the max between three elevators) taken 
		{
			total_time_ele_4 = elevator_41.total_time; // Time taken by elevator in current iteration
		}
		else if (elevator_42.total_time > elevator_43.total_time)
		{
			total_time_ele_4 = elevator_42.total_time; // Time taken by elevator in current iteration
		}
		else
		{
			total_time_ele_4 = elevator_43.total_time; // Time taken by elevator in current iteration
		}
			
		avg_time_4 += total_time_ele_4;


		// find minimum time
		if (total_time_ele_4 < min_time_4)
			min_time_4 = total_time_ele_4;
		
		// find max. time
		if (total_time_ele_4 > max_time_4)
			max_time_4 = total_time_ele_4;
	
	}

	avg_time_4 /= num_iterations_4;

	// Print the results of scenario 4
	printf("Number of iterations: %d\n", num_iterations_4);
	printf("Average elevator time: %f\n", avg_time_4);
	printf("Minimum elevator time: %d\n", min_time_4);
	printf("Maximum elevator time: %d\n", max_time_4);
	printf("Best maxFloor1: %d\n",maxFloor41);
	printf("Best maxFloor2: %d\n\n",maxFloor42);
	

	return 0;
}

/*
Function to initialize elevator members
input: 
dest - destinations of passengers

returns:
top_floor - top floor selected among passengers
*/
int calc_top_floor(int dest[], int num_passengers)
{
	int top_floor = 0;

	for(int j = 0 ; j < num_passengers ; j++)
	{
		if(dest[j] > top_floor)
		{
			top_floor = dest[j];
		}
	}
	
	return top_floor;
}


/*
Function to initialize elevator members
input: 
pointer_ele - Pointer to elevator object

returns:
void
*/
void initialize(struct elevator * pointer_ele)
{
	pointer_ele->num_passengers = rand() % CAPACITY + 1; // number of passengers assigned randomly between 1 and capacity

	// Destination of each passenger (index of array is passenger id)
	
	// printf("\nPassenger destinations: ");
	for( int j = 0; j < pointer_ele->num_passengers ; j++)
	{
		pointer_ele->passenger_dest[j] = rand() % FLOORS + 1; // Destination for each passenger assigned randomly between 1 and FLOORS
		// printf("%d ", pointer_ele->passenger_dest[j]);
	}

	// Initialize zeros to elevator_floor array
	for(int j = 0; j < FLOORS ; j++)
		pointer_ele->elevator_floor[j] = 0;

	// Based on destinations, assign values to elevator_floor
	for (int j = 0; j < pointer_ele->num_passengers; j++)
	{
		int dest_j = pointer_ele->passenger_dest[j];
		pointer_ele->elevator_floor[dest_j - 1] += 1;
	}
	// printf("\n");

	// print elevator floor to check
	/*
	for (int j = 0; j < FLOORS; j++)
	{
		printf("Floor %d: %d\n", j+1, pointer_ele->elevator_floor[j]);
	}
	*/

	pointer_ele->current_floor = 0; // elevator starts at the bottom
	pointer_ele->total_time = 0; // Accumalator for total time
}

/*
Function to initialize 2 elevators members
input: 
pointer_ele1 - Pointer to elevator_21 object
pointer_ele2 - Pointer to elevator_22 object

returns:
void
*/
void initialize_two(struct elevator * pointer_ele1, struct elevator * pointer_ele2)
{
	
	pointer_ele1->num_passengers = rand() % CAPACITY + 1; // number of passengers assigned randomly between 1 and capacity to elevator_21
	pointer_ele2->num_passengers = rand() % CAPACITY + 1; // number of passengers assigned randomly between 1 and capacity to elevator_22
	
	// Check that the total number of passengers is inferior to CAPACITY
	while (pointer_ele1->num_passengers + pointer_ele2->num_passengers > CAPACITY)
	{
		pointer_ele1->num_passengers = rand() % CAPACITY + 1;
		pointer_ele2->num_passengers = rand() % CAPACITY + 1;
	}

	// Destination of each passenger (index of array is passenger id)
	
	// printf("\nPassenger destinations elevator_21: ");
	for( int j = 0; j < pointer_ele1->num_passengers ; j++)
	{
		pointer_ele1->passenger_dest[j] = rand() % FLOORS + 1; // Destination for each passenger assigned randomly between 1 and FLOORS
		// printf("%d ", pointer_ele1->passenger_dest[j]);
	}
	
	// printf("\nPassenger destinations elevator_22: ");
	for( int j = 0; j < pointer_ele2->num_passengers ; j++)
	{
		pointer_ele2->passenger_dest[j] = rand() % FLOORS + 1; // Destination for each passenger assigned randomly between 1 and FLOORS
		// printf("%d ", pointer_ele2->passenger_dest[j]);
	}

	// Initialize zeros to elevator_floor array
	for(int j = 0; j < FLOORS ; j++)
	{
		pointer_ele1->elevator_floor[j] = 0;
		pointer_ele2->elevator_floor[j] = 0;
	}

	// Based on destinations, assign values to elevator_floor for elevator_21
	for (int j = 0; j < pointer_ele1->num_passengers; j++)
	{
		int dest_j = pointer_ele1->passenger_dest[j];
		pointer_ele1->elevator_floor[dest_j - 1] += 1;
	}
	// printf("\n");
	
	// Based on destinations, assign values to elevator_floor for elevator_22
	for (int j = 0; j < pointer_ele2->num_passengers; j++)
	{
		int dest_j = pointer_ele2->passenger_dest[j];
		pointer_ele2->elevator_floor[dest_j - 1] += 1;
	}
	// printf("\n");


	// print elevator floor to check
	/*
	printf("Elevator_21\n\n");
	for (int j = 0; j < FLOORS; j++)
	{
		printf("Floor %d: %d\n", j+1, pointer_ele1->elevator_floor[j]);
	}
	
	printf("\n");
	printf("Elevator_22\n\n");
	for (int j = 0; j < FLOORS; j++)
	{
		printf("Floor %d: %d\n", j+1, pointer_ele2->elevator_floor[j]);
	}
	*/

	pointer_ele1->current_floor = 0; // elevator_21 starts at the bottom
	pointer_ele1->total_time = 0; // Accumalator for total time
	
	pointer_ele2->current_floor = 0; // elevator_22 starts at the bottom
	pointer_ele2->total_time = 0; // Accumalator for total time

}

/*
Function to initialize 2 elevators members with maxFloor1
input: 
pointer_ele1 - Pointer to elevator_31 object
pointer_ele2 - Pointer to elevator_32 object
maxFloor1 - maximum floor for one of the elevator

returns:
void
*/
void initialize_three(struct elevator * pointer_ele1, struct elevator * pointer_ele2, int maxFloor1)
{
	
	pointer_ele1->num_passengers = rand() % CAPACITY + 1; // number of passengers assigned randomly between 1 and capacity to elevator_31
	pointer_ele2->num_passengers = rand() % CAPACITY + 1; // number of passengers assigned randomly between 1 and capacity to elevator_32
	
	// Check that the total number of passengers is inferior to CAPACITY
	while (pointer_ele1->num_passengers + pointer_ele2->num_passengers > CAPACITY)
	{
		pointer_ele1->num_passengers = rand() % CAPACITY + 1;
		pointer_ele2->num_passengers = rand() % CAPACITY + 1;
	}

	// Destination of each passenger (index of array is passenger id)
	
	// printf("\nPassenger destinations elevator_31: ");
	for( int j = 0; j < pointer_ele1->num_passengers ; j++)
	{
		pointer_ele1->passenger_dest[j] = rand() % maxFloor1 + 1; // Destination for each passenger assigned randomly between 1 and maxFloor1
		// printf("%d ", pointer_ele1->passenger_dest[j]);
	}
	
	// printf("\nPassenger destinations elevator_32: ");
	for( int j = 0; j < pointer_ele2->num_passengers ; j++)
	{
		pointer_ele2->passenger_dest[j] = rand() % (FLOORS-maxFloor1) + (maxFloor1+1); // Destination for each passenger assigned randomly between maxFloor1+1 and FLOORS
		// printf("%d ", pointer_ele2->passenger_dest[j]);
	}

	// Initialize zeros to elevator_floor array
	for(int j = 0; j < FLOORS ; j++)
	{
		pointer_ele1->elevator_floor[j] = 0;
		pointer_ele2->elevator_floor[j] = 0;
	}

	// Based on destinations, assign values to elevator_floor for elevator_31
	for (int j = 0; j < pointer_ele1->num_passengers; j++)
	{
		int dest_j = pointer_ele1->passenger_dest[j];
		pointer_ele1->elevator_floor[dest_j - 1] += 1;
	}
	// printf("\n");
	
	// Based on destinations, assign values to elevator_floor for elevator_32
	for (int j = 0; j < pointer_ele2->num_passengers; j++)
	{
		int dest_j = pointer_ele2->passenger_dest[j];
		pointer_ele2->elevator_floor[dest_j - 1] += 1;
	}
	// printf("\n");


	// print elevator floor to check
	/*
	printf("Elevator_31\n\n");
	for (int j = 0; j < FLOORS; j++)
	{
		printf("Floor %d: %d\n", j+1, pointer_ele1->elevator_floor[j]);
	}
	
	printf("\n");
	printf("Elevator_32\n\n");
	for (int j = 0; j < FLOORS; j++)
	{
		printf("Floor %d: %d\n", j+1, pointer_ele2->elevator_floor[j]);
	}
	*/

	pointer_ele1->current_floor = 0; // elevator_31 starts at the bottom
	pointer_ele1->total_time = 0; // Accumalator for total time
	
	pointer_ele2->current_floor = 0; // elevator_32 starts at the bottom
	pointer_ele2->total_time = 0; // Accumalator for total time

}

/*
Function to initialize 3 elevators members with maxFloor41 and maxFloor42
input: 
pointer_ele1 - Pointer to elevator_41 object
pointer_ele2 - Pointer to elevator_42 object
pointer_ele3 - Pointer to elevator_43 object

maxFloor1 - maximum floor for one of the elevator
maxFloor2 - maximum floor for one of the elevator

returns:
void
*/
void initialize_four(struct elevator * pointer_ele1, struct elevator * pointer_ele2, struct elevator * pointer_ele3, int maxFloor41, int maxFloor42)
{
	// Check that maxFloor2 is bigger than maxFloor1
	if (maxFloor42 < maxFloor41)
	{
		int temp = maxFloor41;
		maxFloor41 = maxFloor42;
		maxFloor42 = temp;
	}
	
	pointer_ele1->num_passengers = rand() % CAPACITY + 1; // number of passengers assigned randomly between 1 and capacity to elevator_41
	pointer_ele2->num_passengers = rand() % CAPACITY + 1; // number of passengers assigned randomly between 1 and capacity to elevator_42
	pointer_ele3->num_passengers = rand() % CAPACITY + 1; // number of passengers assigned randomly between 1 and capacity to elevator_43
	
	// Check that the total number of passengers is inferior to CAPACITY
	while (pointer_ele1->num_passengers + pointer_ele2->num_passengers + pointer_ele3->num_passengers > CAPACITY)
	{
		pointer_ele1->num_passengers = rand() % CAPACITY + 1;
		pointer_ele2->num_passengers = rand() % CAPACITY + 1;
		pointer_ele3->num_passengers = rand() % CAPACITY + 1;
	}

	// Destination of each passenger (index of array is passenger id)
	
	// printf("\nPassenger destinations elevator_41: ");
	for( int j = 0; j < pointer_ele1->num_passengers ; j++)
	{
		pointer_ele1->passenger_dest[j] = rand() % maxFloor41 + 1; // Destination for each passenger assigned randomly between 1 and maxFloor41
		// printf("%d ", pointer_ele1->passenger_dest[j]);
	}
	
	// printf("\nPassenger destinations elevator_42: ");
	for( int j = 0; j < pointer_ele2->num_passengers ; j++)
	{
		pointer_ele2->passenger_dest[j] = rand() % (maxFloor42-maxFloor41) + (maxFloor41+1); // Destination for each passenger assigned randomly between maxFloor41+1 and maxFloor42
		// printf("%d ", pointer_ele2->passenger_dest[j]);
	}
	
	// printf("\nPassenger destinations elevator_43: ");
	for( int j = 0; j < pointer_ele3->num_passengers ; j++)
	{
		pointer_ele3->passenger_dest[j] = rand() % (FLOORS-maxFloor42) + (maxFloor42+1); // Destination for each passenger assigned randomly between maxFloor42+1 and FLOORS
		// printf("%d ", pointer_ele3->passenger_dest[j]);
	}

	// Initialize zeros to elevator_floor array
	for(int j = 0; j < FLOORS ; j++)
	{
		pointer_ele1->elevator_floor[j] = 0;
		pointer_ele2->elevator_floor[j] = 0;
		pointer_ele3->elevator_floor[j] = 0;
	}

	// Based on destinations, assign values to elevator_floor for elevator_41
	for (int j = 0; j < pointer_ele1->num_passengers; j++)
	{
		int dest_j = pointer_ele1->passenger_dest[j];
		pointer_ele1->elevator_floor[dest_j - 1] += 1;
	}
	// printf("\n");
	
	// Based on destinations, assign values to elevator_floor for elevator_42
	for (int j = 0; j < pointer_ele2->num_passengers; j++)
	{
		int dest_j = pointer_ele2->passenger_dest[j];
		pointer_ele2->elevator_floor[dest_j - 1] += 1;
	}
	// printf("\n");
	
	// Based on destinations, assign values to elevator_floor for elevator_43
	for (int j = 0; j < pointer_ele3->num_passengers; j++)
	{
		int dest_j = pointer_ele3->passenger_dest[j];
		pointer_ele3->elevator_floor[dest_j - 1] += 1;
	}
	// printf("\n");


	// print elevator floor to check
	/*
	printf("Elevator_41\n\n");
	for (int j = 0; j < FLOORS; j++)
	{
		printf("Floor %d: %d\n", j+1, pointer_ele1->elevator_floor[j]);
	}
	
	printf("\n");
	printf("Elevator_42\n\n");
	for (int j = 0; j < FLOORS; j++)
	{
		printf("Floor %d: %d\n", j+1, pointer_ele2->elevator_floor[j]);
	}

	printf("\n");
	printf("Elevator_43\n\n");
	for (int j = 0; j < FLOORS; j++)
	{
		printf("Floor %d: %d\n", j+1, pointer_ele3->elevator_floor[j]);
	}
	*/

	pointer_ele1->current_floor = 0; // elevator_41 starts at the bottom
	pointer_ele1->total_time = 0; // Accumalator for total time
	
	pointer_ele2->current_floor = 0; // elevator_42 starts at the bottom
	pointer_ele2->total_time = 0; // Accumalator for total time
	
	pointer_ele3->current_floor = 0; // elevator_43 starts at the bottom
	pointer_ele3->total_time = 0; // Accumalator for total time


}


/*
Function to operate elevator to the top floor
input: 
pointer_ele - Pointer to elevator object

returns:
total_time -- Time taken by elevator to reach highest floor selected among passengers
*/
void operate_elevator(struct elevator * pointer_ele)
{
	int top_floor = calc_top_floor(pointer_ele->passenger_dest, pointer_ele->num_passengers);
	// printf("Top floor: %d\n", top_floor);

	pointer_ele->total_time += STOPTIME; // Elevator stopped at floor 0

	while (pointer_ele->current_floor != top_floor)
	{
		pointer_ele->total_time += movePerFloorTime; // Elevator moves to current_floor
		pointer_ele->current_floor += 1; // Increment current floor
		
		if(pointer_ele->elevator_floor[pointer_ele->current_floor-1] != 0)
		{
			pointer_ele->total_time += STOPTIME; // If there is at least 1 passenger whose destination is current floor, we wait
		}
	}

	// printf("Total time: %d\n", pointer_ele->total_time);
}

