// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
* Defect Classification
* ---------------------
* Defect Type: Resource management defects
* Defect Sub-type: Double free
*
*/

#include <stdlib.h>

/*
* Types of defects: Double free
* Complexity: Basic type where pointer is "freed" in a if condition in a loop
*/

void double_free_002_bad()
{
	char* ptr= (char*) malloc(10*sizeof(char));
	if (ptr == NULL) return;
	int i;

	for(i=0;i<10;i++)
	{
		ptr[i]='a';
		if(i==9)
		{
			free(ptr);
		}
	}
	free(ptr); /*Tool should detect this line as error*/ /*ERROR:Double free*/
}

/*
* Types of defects: Double free
* Complexity: Basic type where pointer is "freed" in a if condition in a loop
*/

void double_free_002_good()
{
	char* ptr= (char*) malloc(10*sizeof(char));
	if (ptr == NULL) return;
	int i;

	for(i=0;i<10;i++)
	{
		ptr[i]='a';
		if(i==10)
		free(ptr);
	}
	free(ptr); /*Tool should Not detect this line as error*/ /*No ERROR:Double free*/
}

/*
* Types of defects: Double free
* double free main function
*/

int main ()
{
	double_free_002_good();
	double_free_002_bad();
	return 0;
}
