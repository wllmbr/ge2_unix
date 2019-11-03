#include <galactic_empires.h>

void Galactic_Empires::print_map() {
	uint8_t frame_buffer[MAP_DIMENSIONS_X][MAP_DIMENSIONS_Y];
	uint16_t r, c;
	for (r = 0; r < MAP_DIMENSIONS_Y; r++) {
		for (c = 0; c < MAP_DIMENSIONS_X; c++) {
			frame_buffer[c][r] = 0xff;
		}
	}
	uint64_t w;
	for (w = 0; w < all_worlds.size(); w++) {
		uint16_t x, y;
		x = (uint16_t)all_worlds[w].get_position().get_x();
		y = (uint16_t)all_worlds[w].get_position().get_y();

		frame_buffer[x][y] = w;
	}

	printf("\n============================================= STAR MAP =============================================\n");

	for (r = 0; r < MAP_DIMENSIONS_Y; r++) {
		printf("\n");
		for (c = 0; c < MAP_DIMENSIONS_X; c++) {
			if (frame_buffer[c][r] != 0xff) {
				printf("%3d |", frame_buffer[c][r]);
			} else {
				printf("    |");
			}
		}
	}
	printf("\n");
}