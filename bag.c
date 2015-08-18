#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define EMPTY 0
#define PRIZE 1
#define OUTOFPLAY 2

unsigned int rand_interval(unsigned int min, unsigned int max)
{
    int r;
    const unsigned int range = 1 + max - min;
    const unsigned int buckets = RAND_MAX / range;
    const unsigned int limit = buckets * range;

    /* Create equal size buckets all in a row, then fire randomly towards
     * the buckets until you land in one of them. All buckets are equally
     * likely. If you land off the end of the line of buckets, try again. */
    do
    {
        r = rand();
    } while (r >= limit);

    return min + (r / buckets);
}

int findEmpty(int bags[3]){
	for(int i = 0; i < 3; i++){
		if(bags[i] == EMPTY){
			return i;
		}
	}
	return -1;
}

void printHelp(){
	printf("\tUsage: ./bag Iterations RandSeed\n");
}
int main(int argc, char *argv[]){
	if(argc != 3){
		printHelp();
		exit(1);
	}
	char *itP;
	char *seedP;
	int iterations = strtol(argv[1],&itP,10);
	int seed = strtol(argv[2],&seedP,10);
	if(*itP == '\0' && *seedP == '\0'){}
	else{
		printHelp();
		exit(1);
	}
	srand(seed);
	int switchBagCount = 0; //this will keep track of how often the bag ends up in the hosts hand
	for(int j = 0; j < iterations; j++){
		//declare 3 "bags".
		// 0 - bag is EMPTY
		// 1 - bag contains PRIZE
		// 2 - bag is OUT OF PLAY
		int bags[3] = {EMPTY,EMPTY,EMPTY}; //initially all bags are empty
		int prizeBag = rand_interval(0,2); //randomly decide which bag the prize goes in
		bags[prizeBag] = PRIZE; //put the prize in the bag
		bags[rand_interval(0,2)] = OUTOFPLAY; //contestant picks a bag
		bags[findEmpty(bags)] = OUTOFPLAY; //host turns back and discards empty bag
		//printf("The current status of the bags are: [%d , %d , %d]\n",bags[0], bags[1], bags[2]);
		for(int i = 0; i < 3; i++){
			if(bags[i] == 1){
				switchBagCount++;
				break;
			}
		}
	 }
	printf("The prize was in the Host's hand %f %% of the time.\n", (float)switchBagCount/(float)iterations*100);
}
