#include "icecream.h"

int	main(void)
{
	write (1, "\n       ICECREAM\n\n", 18);
	write (1, "    [From lib base]\n\n", 21);
	base_milk();
	base_water();
	write (1, "\n    [From lib arom]\n\n", 22);
	arom_coco();
	arom_cherry();
	write (1, "\n    [From lib m]\n\n", 19);
	printf("m: pow(2,2) = %f\n\n", pow(2,2));
	return (0);
}
