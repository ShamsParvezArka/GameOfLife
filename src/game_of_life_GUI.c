#include <stdio.h>
#include <raylib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

#define ROW	50 
#define COL	50 

const int cell_width = SCREEN_WIDTH / COL;
const int cell_height = SCREEN_WIDTH / ROW;

int main() {
	int field[ROW][COL];
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			field[i][j] = 0;
		}
	}

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life");
	SetTargetFPS(60);

	Vector2 cursor_position;
	int position_x, position_y;

	while (!WindowShouldClose()) {
		if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			cursor_position = GetMousePosition();
			position_x = cursor_position.x / cell_width; 
			position_y = cursor_position.y / cell_height; 
			field[position_x][position_y] = 1;
		}
		else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
			cursor_position = GetMousePosition();
			position_x = cursor_position.x / cell_width; 
			position_y = cursor_position.y / cell_height; 
			field[position_x][position_y] = 0;
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);

		for (int i = 0; i < COL; i++) {
			for (int j = 0; j < ROW; j++) {
				DrawRectangleLines(
						cell_width * j, 
						cell_height * i, 
						cell_width,
						cell_height,
						BLACK);
			}
		}

		for (int i = 0; i < COL; i++) {
			for (int j = 0; j < ROW; j++) {
				if (field[i][j] == true) {
					DrawRectangle(
							cell_height * i, 
							cell_height * j, 
							cell_width, 
							cell_height, 
							BLACK);
				}
			}
		}

		EndDrawing();
	}
	return 0;
}
