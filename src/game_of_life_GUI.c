#include <stdio.h>
#include <raylib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

#define ROW	30 
#define COL 30	

const int cell_width = SCREEN_WIDTH / COL;
const int cell_height = SCREEN_WIDTH / ROW;

const int offset_row[8] = {-1, -1, -1, 0, 1, 1,  1,  0};
const int offset_col[8] = {-1,  0,  1, 1, 1, 0, -1, -1};

void draw_cell() {
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
}

void draw_block(int field[ROW][COL]) {
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
}

void scan_neighbours(int field[ROW][COL]) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			int alive = 0;
			for (int k = 0; k < 8; k++) {
				if (((i - offset_row[k]) < 0) || ((j - offset_row[k] < 0))) {
					continue;
				}
				else if (field[i - offset_row[k]][j - offset_col[k]] == 1) {
					alive++;
				}
			}
			if ((field[i][j] == 1) && (alive == 2 || alive == 3)) {
				field[i][j] = 1;
			}
			else if((field[i][j] == 0) && (alive == 3)) {
				field[i][j] = 1;
			}
			else {
				field[i][j] = 0;
			}
			draw_block(field);
		}
	}
}

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
		else if (IsKeyDown(KEY_ENTER)) {
			while (true) {
				BeginDrawing();
				ClearBackground(RAYWHITE);
				draw_cell();
				scan_neighbours(field);
				EndDrawing();
			}
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);
		draw_cell();
		draw_block(field);
		EndDrawing();
	}
}
