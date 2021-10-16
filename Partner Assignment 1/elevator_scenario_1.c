#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define CAPACITY 18
#define FLOORS 20
#define STOPTIME 15
#define movePerFloorTime 3

/*
ASSUMPTIONS:

1. Elevator starts at floor 0, so we add the time the elevator stops for at floor 0, which is STOPTIME to every scenario.
2. The passenger exits the elevator after STOPTIME seconds, upon arrival to their destination floor. 
*/

// Elevator structure
struct elevator
{
	int num_passengers; // Number of passengers in the elevator
	int passenger_dest[CAPACITY]; // Destination floor of each passenger
	int elevator_floor[FLOORS]; // Number of passengers assigned to each floor of the elevator
	int current_floor; // Current floor of the elevator
	int total_time;	 // Total time elapsed
	double avg_time_per_passenger; // Average time to destination per passenger for current iteration
};

void initialize_1(struct elevator * pointer_ele); //initialize values of the object according to constraints in scenario 1
void operate_elevator_1(struct elevator * pointer_ele);
int calc_top_floor(int dest[], int num_passengers);

void scenario_1();
void scenario_2();

//int main(int argc,char **argv)
int main()
{
	srand(time(NULL)); // different seed every run

	scenario_1();

	return 0;
}

// Function to perform scenario 1
void scenario_1()
{
	int num_iterations = 1000; // Number of iterations over which to repeat the experiment
	double avg_time = 0.0; // Average elevator time over iterations
	int min_time = 400; // Min elevator time over iterations, initialized to large value
	int max_time = 0; // Max elevator time over iterations
	double avg_time_per_pass_all = 0.0; // Average time to destination per passenger over all iterations

	printf("-----SCENARIO 1-----\n\n");

	for(int i = 0; i < num_iterations; i++)
	{

		struct elevator elevator_1; // Create elevator object
		initialize_1(&elevator_1); // Initialize members
		operate_elevator_1(&elevator_1); // Operate the elevator

		int total_time_ele = elevator_1.total_time; // Time taken by elevator in current iteration
		avg_time += total_time_ele;

		double avg_time_pass = elevator_1.avg_time_per_passenger;
		avg_time_per_pass_all += avg_time_pass;

		// find minimum time
		if (total_time_ele < min_time)
			min_time = total_time_ele;
		
		// find max. time
		if (total_time_ele > max_time)
			max_time = total_time_ele;
	}

	avg_time /= num_iterations;
	avg_time_per_pass_all /= num_iterations;

	printf("Number of iterations: %d\n", num_iterations);
	printf("Average elevator time: %f\n", avg_time);
	printf("Minimum elevator time: %d\n", min_time);
	printf("Maximum elevator time: %d\n", max_time);
	printf("Average passenger time: %f\n", avg_time_per_pass_all);
}

// Function to perform scenario 2
void scenario_2()
{
	int num_iterations = 1000; // Number of iterations over which to repeat the experiment
	double avg_time = 0.0; // Average elevator time over iterations
	int min_time = 400; // Min elevator time over iterations, initialized to large value
	int max_time = 0; // Max elevator time over iterations
	double avg_time_per_pass_all = 0.0; // Average time to destination per passenger over all iterations

	printf("\n\n-----SCENARIO 2-----\n\n");

	for(int i = 0; i < num_iterations; i++)
	{

		struct elevator elevator_1, elevator_2; // Create two elevator object
		initialize_2(&elevator_1, &elevator_2); // Initialize members of both elevators according to the procedure mentioned
		operate_elevator_1(&elevator_1); // Operate the elevator 1
		operate_elevator_1(&elevator_2); // Operate the elevator 2

		int total_time_ele = elevator_1.total_time; // Time taken by elevator in current iteration
		avg_time += total_time_ele;

		double avg_time_pass = elevator_1.avg_time_per_passenger;
		avg_time_per_pass_all += avg_time_pass;

		// find minimum time
		if (total_time_ele < min_time)
			min_time = total_time_ele;
		
		// find max. time
		if (total_time_ele > max_time)
			max_time = total_time_ele;
	}

	avg_time /= num_iterations;
	avg_time_per_pass_all /= num_iterations;

	printf("Number of iterations: %d\n", num_iterations);
	printf("Average elevator time: %f\n", avg_time);
	printf("Minimum elevator time: %d\n", min_time);
	printf("Maximum elevator time: %d\n", max_time);
	printf("Average passenger time: %f\n", avg_time_per_pass_all);
}


/*
Function to calculate top floor
input: 
dest - destinations of passengers
num_passengers - number of passengers

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
Function to initialize elevator members in scenario 1
input: 
pointer_ele - Pointer to elevator object

returns:
void
*/
void initialize_1(struct elevator * pointer_ele)
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

	// print elevator floor to check
	/*
	for (int j = 0; j < FLOORS; j++)
	{
		printf("Floor %d: %d\n", j+1, pointer_ele->elevator_floor[j]);
	}
	*/

	pointer_ele->current_floor = 0; // elevator starts at the bottom
	pointer_ele->total_time = 0; // Accumalator for total time
	pointer_ele->avg_time_per_passenger = 0.0; // Accumulator for time per passenger
}

/*
Function to operate elevator to the top floor in scenario 1
input: 
pointer_ele - Pointer to elevator object

returns:
total_time -- Time taken by elevator to reach highest floor selected among passengers
*/
void operate_elevator_1(struct elevator * pointer_ele)
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
			pointer_ele->avg_time_per_passenger += (pointer_ele->total_time * pointer_ele->elevator_floor[pointer_ele->current_floor-1]); // Time taken to reach current floor times the number of passengers who get off at the current floor
		}
	}

	pointer_ele->avg_time_per_passenger /= pointer_ele->num_passengers;

	// printf("Total time: %d\n", pointer_ele->total_time);
}