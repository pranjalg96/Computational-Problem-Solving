#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define CAPACITY 18
#define FLOORS 20
#define STOPTIME 15
#define movePerFloorTime 3

/*
ASSUMPTIONS:

1. Elevator starts at floor 0 in all scenarios, so we add the time the elevator stops for at floor 0, which is STOPTIME to every scenario.
2. The passenger exits the elevator after STOPTIME seconds, upon arrival to their destination floor. 
3. For scenario 2, average time per passenger is computed as the average of cumulative time taken by passengers in elevator 1 and cumulative time taken by passengers in elevator 2.
4. For scenario 3 & 4, only average time per passenger is used in determining best maxFloor1 (and best maxFloor2).
5. For scenario 4, maxFloor2 varies from maxFloor1 + 1 to (FLOORS - 1).
6. For scenario 4, average time per passenger is computed as the average of cumulative time taken by passengers in elevator 1, cumulative time taken by passengers in elevator 2 and cumulative time taken by passengers in elevator 3.
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

void initialize_1(struct elevator * pointer_ele); 
void initialize_2(struct elevator * pointer_ele1, struct elevator * pointer_ele2);
void initialize_3(struct elevator * pointer_ele1, struct elevator * pointer_ele2, int maxFloor1);
void initialize_4(struct elevator * pointer_ele1, struct elevator * pointer_ele2, struct elevator * pointer_ele3, int maxFloor1, int maxFloor2);

void operate_elevator_1(struct elevator * pointer_ele);

int calc_top_floor(int dest[], int num_passengers);
int max_ele_time(int time_ele_1, int time_ele_2);
int max_ele_time_3(int time_ele_1, int time_ele_2, int time_ele_3);

void scenario_1();
void scenario_2();
void scenario_3();
void scenario_4();

//int main(int argc,char **argv)
int main()
{
	srand(time(NULL)); // different seed every run

	scenario_1();
	scenario_2();
	scenario_3();
	scenario_4();

	return 0;
}

// Function to perform scenario 1
void scenario_1()
{
	int num_iterations = 1000000; // Number of iterations over which to repeat the experiment
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
	int num_iterations = 1000000; // Number of iterations over which to repeat the experiment
	double avg_time = 0.0; // Average elevator time over iterations
	int min_time = 400; // Min elevator time over iterations, initialized to large value
	int max_time = 0; // Max elevator time over iterations
	double avg_time_per_pass_all = 0.0; // Average time to destination per passenger over all iterations

	printf("\n\n-----SCENARIO 2-----\n\n");

	for(int i = 0; i < num_iterations; i++)
	{

		struct elevator elevator_1, elevator_2; // Create two elevator objects
		initialize_2(&elevator_1, &elevator_2); // Initialize members of both elevators according to the procedure mentioned
		operate_elevator_1(&elevator_1); // Operate the elevator 1
		operate_elevator_1(&elevator_2); // Operate the elevator 2

		int max_elev_time = max_ele_time(elevator_1.total_time, elevator_2.total_time); // Get max time of the two elevators
		avg_time += max_elev_time;
		
		double avg_time_pass = (elevator_1.avg_time_per_passenger*elevator_1.num_passengers + elevator_2.avg_time_per_passenger*elevator_2.num_passengers)/(elevator_1.num_passengers + elevator_2.num_passengers); // Assumption 3

		avg_time_per_pass_all += avg_time_pass;

		// find minimum time
		if (max_elev_time < min_time)
			min_time = max_elev_time;
		
		// find max. time
		if (max_elev_time > max_time)
			max_time = max_elev_time;
	}

	avg_time /= num_iterations;
	avg_time_per_pass_all /= num_iterations;

	printf("Number of iterations: %d\n", num_iterations);
	printf("Average elevator time: %f\n", avg_time);
	printf("Minimum elevator time: %d\n", min_time);
	printf("Maximum elevator time: %d\n", max_time);
	printf("Average passenger time: %f\n", avg_time_per_pass_all);
}


// Function to perform scenario 3
void scenario_3()
{
	int best_floor1;

	// Define variables to store best values over the range of maxFloor1 values
	int num_iterations = 1000000; // Number of iterations over which to repeat the experiment
	double best_avg_time = 0.0;
	int best_min_time = 400;
	int best_max_time = 0;
	double best_avg_per_passenger = 400;

	int min_floor = FLOORS/3; // Minimum value of maxFloor1
	int max_floor = 2*min_floor; // Maximum value of maxFloor1

	for (int floor = min_floor; floor <= max_floor; floor++)
	{
		double avg_time = 0.0; // Average elevator time over iterations
		int min_time = 400; // Min elevator time over iterations, initialized to large value
		int max_time = 0; // Max elevator time over iterations
		double avg_time_per_pass_all = 0.0; // Average time to destination per passenger over all iterations

		int maxFloor1 = floor; // Top floor serviced by elevator 1

		for(int i = 0; i < num_iterations; i++)
		{

			struct elevator elevator_1, elevator_2; // Create two elevator objects
			initialize_3(&elevator_1, &elevator_2, maxFloor1); // Initialize members of both elevators according to the procedure mentioned
			operate_elevator_1(&elevator_1); // Operate the elevator 1
			operate_elevator_1(&elevator_2); // Operate the elevator 2

			int max_elev_time = max_ele_time(elevator_1.total_time, elevator_2.total_time); // Get max time of the two elevators
			avg_time += max_elev_time;
			
			double avg_time_pass = (elevator_1.avg_time_per_passenger*elevator_1.num_passengers + elevator_2.avg_time_per_passenger*elevator_2.num_passengers)/(elevator_1.num_passengers + elevator_2.num_passengers); // Assumption 3

			avg_time_per_pass_all += avg_time_pass;

			// find minimum time
			if (max_elev_time < min_time)
				min_time = max_elev_time;
			
			// find max. time
			if (max_elev_time > max_time)
				max_time = max_elev_time;
		}

		avg_time /= num_iterations;
		avg_time_per_pass_all /= num_iterations;

		// Determine the best value for maxFloor1 based on the best_avg_per_passenger
		if(avg_time_per_pass_all < best_avg_per_passenger) 
		{
			best_floor1 = floor;

			best_avg_time = avg_time;
			best_min_time = min_time;
			best_max_time = max_time;
			best_avg_per_passenger = avg_time_per_pass_all;
		}
	}

	printf("\n\n-----SCENARIO 3-----\n\n");

	printf("Number of iterations: %d\n", num_iterations);
	printf("Best Average elevator time: %f\n", best_avg_time);
	printf("Best Minimum elevator time: %d\n", best_min_time);
	printf("Best Maximum elevator time: %d\n", best_max_time);
	printf("Best Average passenger time: %f\n", best_avg_per_passenger);
	printf("Best maxFloor1 value: %d\n", best_floor1);
}

// Function to perform scenario 4
void scenario_4()
{
	int best_floor1;
	int best_floor2;

	// Define variables to store best values over the range of maxFloor1 values
	int num_iterations = 1000000; // Number of iterations over which to repeat the experiment
	double best_avg_time = 0.0;
	int best_min_time = 400;
	int best_max_time = 0;
	double best_avg_per_passenger = 400;

	int min_floor_1 = FLOORS/3; // Minimum value of maxFloor1
	int max_floor_1 = 2*min_floor_1; // Maximum value of maxFloor1

	for (int floor1 = min_floor_1; floor1 <= max_floor_1; floor1++)
	{
		int min_floor_2 = floor1 + 1;
		int max_floor_2 = FLOORS - 1; // Assumption 5

		for(int floor2 = min_floor_2; floor2 <= max_floor_2; floor2++)
		{
			double avg_time = 0.0; // Average elevator time over iterations
			int min_time = 400; // Min elevator time over iterations, initialized to large value
			int max_time = 0; // Max elevator time over iterations
			double avg_time_per_pass_all = 0.0; // Average time to destination per passenger over all iterations

			int maxFloor1 = floor1; // Top floor serviced by elevator 1
			int maxFloor2 = floor2; // Top floor serviced by elevator 2

			for(int i = 0; i < num_iterations; i++)
			{

				struct elevator elevator_1, elevator_2, elevator_3; // Create three elevator objects
				initialize_4(&elevator_1, &elevator_2, &elevator_3, maxFloor1, maxFloor2); // Initialize members of elevators according to the procedure mentioned for scenario 4
				operate_elevator_1(&elevator_1); // Operate the elevator 1
				operate_elevator_1(&elevator_2); // Operate the elevator 2
				operate_elevator_1(&elevator_3); // Operate the elevator 3

				int max_elev_time = max_ele_time_3(elevator_1.total_time, elevator_2.total_time, elevator_3.total_time); // Get max time of the three elevators
				avg_time += max_elev_time;
				
				double avg_time_pass = (elevator_1.avg_time_per_passenger*elevator_1.num_passengers + elevator_2.avg_time_per_passenger*elevator_2.num_passengers + elevator_3.avg_time_per_passenger*elevator_3.num_passengers)/(elevator_1.num_passengers + elevator_2.num_passengers + elevator_3.num_passengers); // Assumption 6

				avg_time_per_pass_all += avg_time_pass;

				// find minimum time
				if (max_elev_time < min_time)
					min_time = max_elev_time;
				
				// find max. time
				if (max_elev_time > max_time)
					max_time = max_elev_time;				
			}

			avg_time /= num_iterations;
			avg_time_per_pass_all /= num_iterations;


			if(avg_time_per_pass_all < best_avg_per_passenger) // Assumption 4
			{
				best_floor1 = floor1;
				best_floor2 = floor2;

				best_avg_time = avg_time;
				best_min_time = min_time;
				best_max_time = max_time;
				best_avg_per_passenger = avg_time_per_pass_all;
			}
		}
	}

	printf("\n\n-----SCENARIO 4-----\n\n");

	printf("Number of iterations: %d\n", num_iterations);
	printf("Best Average elevator time: %f\n", best_avg_time);
	printf("Best Minimum elevator time: %d\n", best_min_time);
	printf("Best Maximum elevator time: %d\n", best_max_time);
	printf("Best Average passenger time: %f\n", best_avg_per_passenger);
	printf("Best maxFloor1 value: %d\n", best_floor1);
	printf("Best maxFloor2 value: %d\n", best_floor2);
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
Function to return max of the two elevator times
input: 
time_ele_1 - Time taken by ele 1
time_ele_2 - Time taken by ele 2

returns:
max_time - max of the two arguments
*/
int max_ele_time(int time_ele_1, int time_ele_2)
{
	int max_time;

	if(time_ele_1 > time_ele_2)
		max_time = time_ele_1;
	else
		max_time = time_ele_2;
	
	return max_time;
}

/*
Function to return max of the three elevator times
input: 
time_ele_1 - Time taken by ele 1
time_ele_2 - Time taken by ele 2
time_ele_3 - Time taken by ele 3

returns:
max_time - max of the three arguments
*/
int max_ele_time_3(int time_ele_1, int time_ele_2, int time_ele_3)
{
	int max_time;

	if(time_ele_1 > time_ele_2 && time_ele_1 > time_ele_3)
	{
		max_time = time_ele_1;
	}
	else if(time_ele_2 > time_ele_1 && time_ele_2 > time_ele_3)
	{
		max_time = time_ele_2;
	}
	else
	{
		max_time = time_ele_3;
	}

	return max_time;
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
Function to initialize elevator members in scenario 2
input: 
pointer_ele1 - Pointer to elevator object 1
pointer_ele2 - Pointer to elevator object 2

returns:
void
*/
void initialize_2(struct elevator * pointer_ele1, struct elevator * pointer_ele2)
{
	int random_num_pass = rand() % CAPACITY + 1; // number of passengers assigned randomly between 1 and capacity
	int random_dest[CAPACITY]; // Array to store random destination for each passenger
	int rand_idx[CAPACITY]; // Array to store random index indicating elevator assignment

	pointer_ele1->num_passengers = 0;
	pointer_ele2->num_passengers = 0;

	for( int j = 0; j < random_num_pass ; j++)
	{
		random_dest[j] = rand() % FLOORS + 1; // Destination for each passenger assigned randomly between 1 and FLOORS
		rand_idx[j] = rand() % 2; // Each passenger assigned randomly to one of the two elevators
		// printf("%d ", pointer_ele->passenger_dest[j]);
	}
	
	// Initialize zeros to elevator_floor array of both objects
	for(int j = 0; j < FLOORS ; j++)
	{
		pointer_ele1->elevator_floor[j] = 0;
		pointer_ele2->elevator_floor[j] = 0;
	}

	// Based on destinations, assign values to elevator_floor
	for (int j = 0; j < random_num_pass; j++)
	{
		int dest_j = random_dest[j];
		int idx_j = rand_idx[j];

		if(idx_j == 0)
		{
			pointer_ele1->passenger_dest[pointer_ele1->num_passengers] = dest_j;
			pointer_ele1->elevator_floor[dest_j - 1] += 1;
			pointer_ele1->num_passengers += 1;
		}
		else
		{
			pointer_ele2->passenger_dest[pointer_ele2->num_passengers] = dest_j;
			pointer_ele2->elevator_floor[dest_j - 1] += 1;
			pointer_ele2->num_passengers += 1;
		}
	}

	// elevator 1
	pointer_ele1->current_floor = 0; // elevator starts at the bottom
	pointer_ele1->total_time = 0; // Accumalator for total time
	pointer_ele1->avg_time_per_passenger = 0.0; // Accumulator for time per passenger

	// elevator 2
	pointer_ele2->current_floor = 0; // elevator starts at the bottom
	pointer_ele2->total_time = 0; // Accumalator for total time
	pointer_ele2->avg_time_per_passenger = 0.0; // Accumulator for time per passenger
}

/*
Function to initialize elevator members in scenario 3
input: 
pointer_ele1 - Pointer to elevator object 1
pointer_ele2 - Pointer to elevator object 2
maxFloor1 - Top floor elevator 1 services

returns:
void
*/
void initialize_3(struct elevator * pointer_ele1, struct elevator * pointer_ele2, int maxFloor1)
{
	int random_num_pass = rand() % CAPACITY + 1; // number of passengers assigned randomly between 1 and capacity
	int random_dest[CAPACITY]; // Array to store random destination for each passenger

	pointer_ele1->num_passengers = 0;
	pointer_ele2->num_passengers = 0;

	for( int j = 0; j < random_num_pass ; j++)
	{
		random_dest[j] = rand() % FLOORS + 1; // Destination for each passenger assigned randomly between 1 and FLOORS
		// printf("%d ", pointer_ele->passenger_dest[j]);
	}
	
	// Initialize zeros to elevator_floor array of both objects
	for(int j = 0; j < FLOORS ; j++)
	{
		pointer_ele1->elevator_floor[j] = 0;
		pointer_ele2->elevator_floor[j] = 0;
	}

	// Based on floor, assign destinations to each elevator
	for (int j = 0; j < random_num_pass; j++)
	{
		int dest_j = random_dest[j];

		if(dest_j <= maxFloor1)
		{
			pointer_ele1->passenger_dest[pointer_ele1->num_passengers] = dest_j;
			pointer_ele1->elevator_floor[dest_j - 1] += 1;
			pointer_ele1->num_passengers += 1;
		}
		else
		{
			pointer_ele2->passenger_dest[pointer_ele2->num_passengers] = dest_j;
			pointer_ele2->elevator_floor[dest_j - 1] += 1;
			pointer_ele2->num_passengers += 1;
		}
	}

	// elevator 1
	pointer_ele1->current_floor = 0; // elevator starts at the bottom
	pointer_ele1->total_time = 0; // Accumalator for total time
	pointer_ele1->avg_time_per_passenger = 0.0; // Accumulator for time per passenger

	// elevator 2
	pointer_ele2->current_floor = 0; // elevator starts at the bottom
	pointer_ele2->total_time = 0; // Accumalator for total time
	pointer_ele2->avg_time_per_passenger = 0.0; // Accumulator for time per passenger
}

/*
Function to initialize elevator members in scenario 4
input: 
pointer_ele1 - Pointer to elevator object 1
pointer_ele2 - Pointer to elevator object 2
pointer_ele3 - Pointer to elevator object 2
maxFloor1 - Top floor elevator 1 services
maxFloor2 - Top floor elevator 2 services

returns:
void
*/
void initialize_4(struct elevator * pointer_ele1, struct elevator * pointer_ele2, struct elevator * pointer_ele3, int maxFloor1, int maxFloor2)
{
	int random_num_pass = rand() % CAPACITY + 1; // number of passengers assigned randomly between 1 and capacity
	int random_dest[CAPACITY]; // Array to store random destination for each passenger

	pointer_ele1->num_passengers = 0;
	pointer_ele2->num_passengers = 0;
	pointer_ele3->num_passengers = 0;

	for( int j = 0; j < random_num_pass ; j++)
	{
		random_dest[j] = rand() % FLOORS + 1; // Destination for each passenger assigned randomly between 1 and FLOORS
		// printf("%d ", pointer_ele->passenger_dest[j]);
	}
	
	// Initialize zeros to elevator_floor array of both objects
	for(int j = 0; j < FLOORS ; j++)
	{
		pointer_ele1->elevator_floor[j] = 0;
		pointer_ele2->elevator_floor[j] = 0;
		pointer_ele3->elevator_floor[j] = 0;
	}

	// Based on floor, assign destinations to each elevator
	for (int j = 0; j < random_num_pass; j++)
	{
		int dest_j = random_dest[j];

		if(dest_j <= maxFloor1)
		{
			pointer_ele1->passenger_dest[pointer_ele1->num_passengers] = dest_j;
			pointer_ele1->elevator_floor[dest_j - 1] += 1;
			pointer_ele1->num_passengers += 1;
		}
		else if(dest_j > maxFloor1 && dest_j <= maxFloor2)
		{
			pointer_ele2->passenger_dest[pointer_ele2->num_passengers] = dest_j;
			pointer_ele2->elevator_floor[dest_j - 1] += 1;
			pointer_ele2->num_passengers += 1;
		}
		else
		{
			pointer_ele3->passenger_dest[pointer_ele3->num_passengers] = dest_j;
			pointer_ele3->elevator_floor[dest_j - 1] += 1;
			pointer_ele3->num_passengers += 1;
		}
	}

	// elevator 1
	pointer_ele1->current_floor = 0; // elevator starts at the bottom
	pointer_ele1->total_time = 0; // Accumalator for total time
	pointer_ele1->avg_time_per_passenger = 0.0; // Accumulator for time per passenger

	// elevator 2
	pointer_ele2->current_floor = 0; // elevator starts at the bottom
	pointer_ele2->total_time = 0; // Accumalator for total time
	pointer_ele2->avg_time_per_passenger = 0.0; // Accumulator for time per passenger
	
	// elevator 3
	pointer_ele3->current_floor = 0; // elevator starts at the bottom
	pointer_ele3->total_time = 0; // Accumalator for total time
	pointer_ele3->avg_time_per_passenger = 0.0; // Accumulator for time per passenger
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

	if( pointer_ele->num_passengers != 0)
		pointer_ele->avg_time_per_passenger /= pointer_ele->num_passengers;
	else
		pointer_ele->avg_time_per_passenger = 0.0;

	// printf("Total time: %d\n", pointer_ele->total_time);
}