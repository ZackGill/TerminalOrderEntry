/*
 * Author : Zachary Gill
 * Program 1: Terminal/Order Entry system
 */

#include <curses.h>
#include <term.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
int main()
{

	int temp = 5;
	int *errret = &temp;
	setupterm((char *)0, fileno(stdout), errret);
	
	// Clearing the screen with terminfo escape string

	// Getting the escape string 'clear_screen'
	char *cmd = tigetstr("clear");
	
	//sending escape to terminal
	putp(cmd);
	
	// Getting the number of columns and rows.
	int cols = tigetnum("cols");
	int rows = tigetnum("lines");

	// Cursor moving
	// Getting escape string
	cmd = tigetstr("cup");

	// Changing parameters of escape string
	cmd = tparm(cmd, 5, 30);

	// Sending to terminal
	putp(cmd);
	printf("The cursor was here!\n");

	// Displaying Cols and Rows at cursor location.
	// For fun, changing the cursor location before printing each time.

	cmd = tigetstr("cup");
	cmd = tparm(cmd, 5, 5);
	putp(cmd);
	printf("Cols: %d \n", cols);

	cmd = tigetstr("cup");
	cmd = tparm(cmd, 8, 20);
	putp(cmd);
	printf("Rows: %d \n", rows);
	

	// Reading user input from stdin. Breaks on entering quit.
	// Outputs at same location, overwriting data.
	// reset cursor to home to get input, then put cursor elsewhere to print
	char *data = malloc(sizeof(char) * 512);
	while(1)
	{
		cmd = tigetstr("home");
		putp(cmd);
		printf("Enter data (quit quits):");
		fgets(data, 512, stdin);

		// Didn't like strcmp, so going character by character
		// if input is quit\n, quit.
		if (data[0] == 'q' && data[1] == 'u' && data[2] == 'i' && data[3] == 't' && data[4] == '\n'){
			break;
		}
		cmd = tigetstr("cup");
		cmd = tiparm(cmd, 10, 7);
		putp(cmd);
		printf("Data: %s\n", data);
		memset(data, '\0', 512);
	}
	free(data);
	return 0;
}
