#include <galactic_empires.h>

void Galactic_Empires::perform_player(uint16_t id) {
	char command;
	printf("Player %d\n", id);
	while(1){
		/* Make sure we aren't supposed to die */
		if(exit_game == true){
			return;
		}

		/* Get single key stroke */
		command = getchar();
		switch (command) {
			case '\n':
				printf("Ending Turn\n");
				return;
				break;
			case 'M':
			case 'm':
				print_map();
				break;
			case 'C':
			case 'c':
				get_command(id);
				break;
			case 'S':
			case 's':
				print_stats();
				break;
			case 'q':
			case 'Q':
				exit_game = true;
				return;
				break;
			case 'H':
			case 'h':
			default:
				printf("Valid commands are\nh: Get Help\nm: display map\ns: Display Galaxy Stats\nc: create mission\nEnter: End Turn\n");
		}
		/* Clear the newline */
		command = getchar();
	}
}