#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

#define WORLD_SIZE 100

static int worldSize = WORLD_SIZE;

char state[WORLD_SIZE]; //Presented world state, printed on terminal.

char tempState[WORLD_SIZE]; //Swap space for the world state

int ruleset = 0;

int runtime = 0;

char randomFlag; //Randomize the initial state

int main (int argsc, char **argv);
 
void initializeAutomaton (int size); //Set initial state of automaton

void printState (int size); //Print 'worldState'

char neighborhoodDetection (int position); //Compute neighborhood state

void updateState (int size, char ruleset[]); //Determine next state

char *ruleTranslation (int rule); //Translate Wolframcode into char array

int binExp (int base, int exponent); //Raise 'base' to the power of 'exponent'

int argumentTest (int argsc, char **argv); //Test CLI args

int stringcmp(char *str1, char *str2); //Compare strings (used by 'argumentTest').

int isRule(char *ruleStr); //Verify rule

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
/*
Set initial state of the automaton.
If the the randomization isn't turned on, set only the middle cell
to '1' and leave rest as '0'.
*/
	if (randomFlag) {
		for (int i = 0; i < size; i++)
		{

			if (rand() % 2 == 0) state[i] = 1;

			else state[i] = 0;

			tempState[i] = 0;
		}
	}
	else {
		for (int i = 0; i < size; i++)
		{
			state[i] = 0;

			tempState[i] = 0;
		}
		state[size / 2] = 1;
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
/*
Parse and test all supplied arguments.
If an invalid arg, or arg value is found, return '1'.
*/
	if (argsc < 2) //Arg number check
	{
		printf("Not enough arguments. Please specify rule.\n");
       
		return 1;
	}

	if (isRule(argv[1])) //Verify if the rule is valid.
	{
		printf("Selected rule '%s' is invalid!\n", argv[1]);

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
			srand(time(NULL)); //initialize random generator
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
/*
Translate integer Wolframcode into a size 8 char array.
Return the result.
*/
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
/*
Detect state of the neighborhood and return 
*/
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
/*
Compare two strings if they are an exact match.
Return '0' if they are and '1' otherwise.
*/
	if (sizeof(str1) != sizeof(str2)) return 1;

	for (int i = 0; i < 2; i++) 
	{
		if (str1[i] != str2[i] ) return 1;
	}

	return 0;
}

int isRule(char *ruleStr){
/*
Verify that the supplied rule is a valid Wolframcode.
Return '0' if the rule is valid and '1' otherwise.
*/
	for (int i = 0; i < strlen(ruleStr); i++){
		if (!isdigit(ruleStr[i])){
			return 1;
		}
	}

	if (atoi(ruleStr) < 0 || atoi(ruleStr) >= 255){
		return 1;
	}

	return 0;
}
