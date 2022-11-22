#include <stdio.h>
#include <cs50.h>

string get_name(void);
void say_hello(string name);

int main(void)
{
    // Get Input
    string name = get_name();
    // Print Response
    say_hello(name);
}

string get_name(void)
{
    string name = get_string("What's your name? ");
    return name;
}

void say_hello(string name)
{
    printf("Hello %s!\n", name);
}
