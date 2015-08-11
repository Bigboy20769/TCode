#include <stm32f10x.h>
#include <stdio.h>
#include <math.h>

void DecimalToString(double fnumber, char *fnumbertext, int place)
{
	int32_t intpart;
	int32_t fracpartint;
	double fracpart;
	double nplace;
	int i;
	nplace = 10;
	for (i = 1; i < place; i++)
	{
		nplace *= 10; 
	}
	intpart = (int)fnumber;
	fracpartint = (int)((fnumber - intpart) * nplace);
	switch (place)
	{
		
	case 1:
		sprintf(fnumbertext, "%d.%01d", intpart, fracpartint);
		break;
	case 2:
		sprintf(fnumbertext, "%d.%02d", intpart, fracpartint);
		break;
	case 3:
		sprintf(fnumbertext, "%d.%03d", intpart, fracpartint);
		break;
	case 4:
		sprintf(fnumbertext, "%d.%04d", intpart, fracpartint);
		break;
	case 5:
		sprintf(fnumbertext, "%d.%05d", intpart, fracpartint);
		break;
	case 6:
		sprintf(fnumbertext, "%d.%06d", intpart, fracpartint);
		break;
	}
}
