#include "isOdd.h"

#include <stdio.h>

int isOdd(int num)
{
	if (num % 2 != 0){
		 printf("%d is even.\n", num);
	}
	return 0;
}
