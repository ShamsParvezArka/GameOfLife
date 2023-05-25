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

void draw_block(int generation[ROW][COL]) {
	for (int i = 0; i < COL; i++) {
		for (int j = 0; j < ROW; j++) {
			if (generation[i][j] == true) {
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

void scan_neighbours(int generation[ROW][COL], int next_generation[ROW][COL]) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			int alive = 0;
			for (int k = 0; k < 8; k++) {
				if (((i - offset_row[k]) < 0) || ((j - offset_row[k] < 0))) {
					continue;
				}
				else if (generation[i - offset_row[k]][j - offset_col[k]] == 1) {
					alive++;
				}
			}
			if ((generation[i][j] == 1) && (alive == 2 || alive == 3)) {
				next_generation[i][j] = 1;
			}
			else if ((generation[i][j] == 0) && (alive ==3)) {
				next_generation[i][j] = 1;
			}
			else {
				next_generation[i][j] = 0;
			}
			draw_block(next_generation);
		}
	}
}

void scan_neighbours_next_generation(int generation[ROW][COL], int next_generation[ROW][COL]) {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			int alive = 0;
			for (int k = 0; k < 8; k++) {
				if (((i - offset_row[k]) < 0) || ((j - offset_row[k] < 0))) {
					continue;
				}
				else if (next_generation[i - offset_row[k]][j - offset_col[k]] == 1) {
					alive++;
				}
			}
			if ((next_generation[i][j] == 1) && (alive == 2 || alive == 3)) {
				generation[i][j] = 1;
			}
			else if ((next_generation[i][j] == 0) && (alive ==3)) {
				generation[i][j] = 1;
			}
			else {
				generation[i][j] = 0;
			}
			draw_block(generation);
		}
	}
}

int main() {
	int generation[ROW][COL];
	int next_generation[ROW][COL];
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			generation[i][j] = 0;
			next_generation[i][j] = 0;
		}
	}

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Game of Life");
	SetTargetFPS(60);

	Vector2 cursor_position;
	int position_x, position_y;

	while (!WindowShouldClose()) {
		if (IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			cursor_position = GetMousePosition();
			position_x = cursor_position.x / cell_width; 
			position_y = cursor_position.y / cell_height; 
			generation[position_x][position_y] = 1;
		}
		else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
			cursor_position = GetMousePosition();
			position_x = cursor_position.x / cell_width; 
			position_y = cursor_position.y / cell_height; 
			generation[position_x][position_y] = 0;
		}
		else if (IsKeyDown(KEY_ENTER)) {
			long int x = 1;
			while (!IsKeyDown(KEY_ESCAPE)) {
				BeginDrawing();
				ClearBackground(RAYWHITE);
				draw_cell();
				if (x % 2 != 0) {
					scan_neighbours(generation, next_generation);
				}
				else {
					scan_neighbours_next_generation(generation, next_generation);
				}
				EndDrawing();
				x++;
			}
		}

		BeginDrawing();
		ClearBackground(RAYWHITE);
		draw_cell();
		draw_block(generation);
		EndDrawing();
	}

	CloseWindow();
}
