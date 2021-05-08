#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WORLD_SIZE 100

static int worldSize = WORLD_SIZE;

char state[WORLD_SIZE];

char tempState[WORLD_SIZE];

int ruleset = 0;

int runtime = 0;

char randomFlag;

int main (int argsc, char **argv);
 
void initializeAutomaton (int size);

void printState (int size);

char neighborhoodDetection (int position);

void updateState (int size, char ruleset[]);

char *ruleTranslation (int rule);

int binExp (int base, int exponent);

int argumentTest (int argsc, char **argv);

int stringcmp(char *str1, char *str2);

int main (int argsc, char **argv)
{ 

	randomFlag = 0;

	if (argumentTest (argsc, argv) != 0) return 1;	 
 
	initializeAutomaton (worldSize);
	char *translatedRule = ruleTranslation(ruleset);
	if (runtime > 0) {
		while (runtime >= 0)
		{
			updateState(worldSize, translatedRule);
			runtime--;
		}

		printState(worldSize);
	}
	else {
		while (runtime >= 0)
		{
			printState(worldSize);

			updateState(worldSize, translatedRule);
		}
	} 
	free(translatedRule);
	return 0;
}

void initializeAutomaton (int size)
{
	if (randomFlag) {
		for (int i = 0; i < worldSize; i++)
		{

			if (rand() % 2 == 0) state[i] = 1;

			else state[i] = 0;

			tempState[i] = 0;
		}
	}
	else {
		for (int i = 0; i < worldSize; i++)
		{
			state[i] = 0;

			tempState[i] = 0;
		}
		state[worldSize / 2] = 1;
	}
}

void printState (int size) 
{  
 
	for (int i = 0; i < size; i++)
	{
		if (state[i] == 1) printf ("*");
		
		else printf (" ");
	}

	printf ("\n");
}

void updateState (int size, char rule[])
{ 
	int neighborhood = 0;

	for (int i = 0; i < size; i++)
	{
		neighborhood = neighborhoodDetection (i);

		tempState[i] = rule[neighborhood];
	}

	for (int i = 0; i < worldSize; i++)
	{
		state[i] = tempState[i];
		
		tempState[i] = 0;
	}    
} 
 
int argumentTest (int argsc, char **argv)
{
	if (argsc < 2)
	{
		printf ("Not enough arguments. Please specify rule.\n");
       
		return 1;
	}
  
	if (atoi(argv[1]) > 255 || atoi(argv[1]) < 0)
	{
		printf("Selected rule %d ", atoi(argv[1]));

		printf("Valid rules 0 - 255.\n");

		return 1;
	}

	ruleset = atoi(argv[1]);

	if (argsc < 3) 
	{
		return 0;
	} 

	for (int i = 2; i < argsc; i++) 
	{
		if (!stringcmp(argv[i],"-s")) 
		{
			if (atoi(argv[i+1]) > WORLD_SIZE) 
			{
				printf("Selected world size exceeds maximum %d\n", WORLD_SIZE);

				return 1;
			}			
			worldSize = atoi(argv[i+1]);
		}
		else if (randomFlag == 0 && !stringcmp(argv[i], "-r")) 
		{
			randomFlag = 1;
			srand(time(NULL));
		}
		else if (runtime == 0 && !stringcmp(argv[i], "-t"))
		{
			runtime = atoi(argv[i + 1]);
		}
	}

	return 0;
}

char *ruleTranslation (int rule)
{
	char *translatedRule = malloc (8);  
 
	if (!translatedRule) return NULL;  
 
	for (int i = 0; i <= 7; i++)
	{
		if (rule > 0)
		{
			translatedRule[i] = rule % 2;

			rule = rule / 2;
		}      
		else
		{
			translatedRule[i] = 0;
		}    
	}

	return translatedRule;
}
 
char neighborhoodDetection (int position)
{  
	char result = 0;
  
	char neighborhoodIterator = 2;
  
	position--;  
 
	while (neighborhoodIterator >= 0)
	{
		result += state[position % worldSize] * binExp (2, neighborhoodIterator);

		position++;

		neighborhoodIterator--;
	}
	
	return result;
}

int binExp (int base, int exponent)
{
	int result = 1;

	while (exponent > 0)
	{
		result *= base;
		
		exponent--;    
	}

	return result;
}

int stringcmp(char *str1, char *str2) {

	if (sizeof(str1) != sizeof(str2)) return 1;

	for (int i = 0; i < 2; i++) 
	{
		if (str1[i] != str2[i] ) return 1;
	}

	return 0;
}