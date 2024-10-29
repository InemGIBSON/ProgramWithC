#include <stdio.h>

int main() {
char name[50]; //This will store username

printf("Enter your name: ");

// scanf("%49s", name); This will limit the user input to ensure that there is not overflow.

fgets(name, sizeof(name), stdin); // this takes the username in full
printf("Welcome , %s!\n", name);

return 0;
}
