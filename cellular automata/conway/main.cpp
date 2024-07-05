#include <chrono>
#include <cstddef>
#include <iostream>
#include <raylib.h>


#define WRAP_AROUND // remove this line to remove wrap around

const std::size_t resolution = 10;
const double delay = 0.1; // in seconds



std::size_t width, height;
int cols, rows;

bool **game;
bool **after;
bool **temp;

bool start_game = false;

#ifdef WRAP_AROUND
int count_neighbours(int i, int j) {
    int neighbours{0};
    for (int k{-1}; k <= 1; k++) {
        for (int l{-1}; l <= 1; l++) {
            if (k == 0 && l == 0) continue;
            int row = (i + k + rows) % rows;
            int col = (j + l + cols) % cols;

            if (game[row][col]) {
                neighbours++;
            }
        }
    }
    return neighbours;
}
#else
int count_neighbours(int i, int j) {
  int neighbours{0};
  for (int k{-1}; k <= 1; k++) {
    for (int l{-1}; l <= 1; l++) {
      
      if ((i + k) < 0 || (i + k) >= rows) continue;
      if ((j + l) < 0 || (j + l) >= cols) continue;
      if (l == 0 && k == 0) continue;


      if (game[i + k][j + l]) {
          neighbours++;
      }
    }
  }
  return neighbours;
}
#endif

void gameLoop() {
  BeginDrawing();
  ClearBackground({0, 0, 0, 255});
  for (std::size_t i{0}; i < rows; i++) {
    for (std::size_t j{0}; j < cols; j++) {
      if (game[i][j]) {
        DrawRectangle(i * resolution, j * resolution, resolution - 1,
                      resolution - 1, {255, 255, 255, 255});
      }
    }
  }

  EndDrawing();

  if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
    int i = static_cast<int>(GetMouseX() / resolution);
    int j = static_cast<int>(GetMouseY() / resolution);

    game[i][j] = !game[i][j];
  }

  if (IsKeyPressed(KEY_SPACE)) {
    start_game = !start_game;
  }

  if (!start_game) {
    return;
  }

  for (int i{0}; i < rows; i++) {
    for (int j{0}; j < cols; j++) {
      bool state = game[i][j];
      if(i == 3 && j == 4) {
      }
      int neighbours = count_neighbours(i, j);

      if (state == 1 && (neighbours < 2 || neighbours > 3)) {
        after[i][j] = 0;
      } else if (state == 0 && (neighbours == 3)) {
        after[i][j] = 1;
      } else {
        after[i][j] = state;
      }
    }
  }
  temp = game;
  game = after;
  after = temp;

  WaitTime(delay);
}

int main() {
  width = 400;
  height = 400;

  cols = height / resolution;
  rows = width / resolution;

  SetRandomSeed(std::chrono::system_clock::now().time_since_epoch().count());

  game = new bool *[rows];
  after = new bool *[rows];

  for (std::size_t i{0}; i < rows; i++) {
    game[i] = new bool[cols];
    after[i] = new bool[cols];
  }

  for (std::size_t i{0}; i < rows; i++) {
    for (std::size_t j{0}; j < cols; j++) {
      //game[i][j] = GetRandomValue(0, 1);
      game[i][j] = 0;
    }
  }

  InitWindow(width, height, "Conway's Game Of Life");
  SetTargetFPS(60);

  while (!WindowShouldClose()) {

    gameLoop();
  }

  for (std::size_t i{0}; i < rows; i++) {
    delete[] game[i];
    delete[] after[i];
  }
  delete[] game;
  delete[] after;
}
