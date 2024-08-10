#include <stdio.h>

int main (void)
{
	float kela = 279.4 + 674.4;
	float rent = -985;
	float subscriptions = -50;
	float food = -200;
	float shopping = -100;
	float flights = -300;
	float buffer = -100;
	float saved = 4209.7;
	float debt = 17000;
	float sign = 1;

	float total = kela + rent + food + shopping + flights + buffer;
	if (total < 0)
		sign = -1;
	int i = 7 + (saved / (total * sign));
	const char *months[] = {
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December"
	};
	
	if (i > 11)
		i -= 12;

	printf("- - - - - MONTHLY EXPENCES- - - - - \n");
	printf("Kela: %.2f\n", kela);
	printf("Rent: %.2f\n", rent);
	printf("Food: %.2f\n", food);
	printf("Buffer: %.2f\n", buffer);
	printf("Shopping: %.2f\n", shopping);
	printf("Flights: %.2f\n", flights);

	printf("- - - - - - - - - - - - - - - - - -\n");
	printf("Total: %.2f\n", total);
	printf("Saved: %.2f\n", saved);
	printf("How long will I survive without working? %.2f months\n", saved / (total * sign));
	printf(">> It is %s already, which means I'll survive until %s\n", months[7], months[i]);
	printf("- - - - - - - - - - \n");
	return (0);
}