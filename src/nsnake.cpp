#include <cstdlib>
#include <ctime>
#include <fcntl.h>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <vector>

using namespace std;

bool gameOver;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
vector<int> tailX, tailY;
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

// 针对 Linux 发行版的非阻塞按键监听实现
int kbhit() {
  struct termios oldt, newt;
  int ch, oldf;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
  ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
  if (ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}

void Setup() {
  srand(time(NULL));
  gameOver = false;
  dir = RIGHT; // 启动直接向右开局，没有菜单
  x = width / 2;
  y = height / 2;
  fruitX = rand() % width;
  fruitY = rand() % height;
  score = 0;
  nTail = 2; // 初始两条尾巴
  tailX.resize(width * height);
  tailY.resize(width * height);
}

void Draw() {
  cout
      << "\033[H\033[J"; // 使用 ANSI 逃逸码清屏，替代闪烁明显的 system("clear")
  for (int i = 0; i < width + 2; i++)
    cout << "■";
  cout << endl;

  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      if (j == 0)
        cout << "■";
      if (i == y && j == x)
        cout << "O"; // 蛇头
      else if (i == fruitY && j == fruitX)
        cout << "F"; // 食物
      else {
        bool print = false;
        for (int k = 0; k < nTail; k++) {
          if (tailX[k] == j && tailY[k] == i) {
            cout << "o"; // 蛇身
            print = true;
          }
        }
        if (!print)
          cout << " ";
      }
      if (j == width - 1)
        cout << "■";
    }
    cout << endl;
  }

  for (int i = 0; i < width + 2; i++)
    cout << "■";
  cout << endl;
  cout << "SCORE: " << score << endl;
}

void Input() {
  if (kbhit()) {
    switch (getchar()) {
    case 'a':
      if (dir != RIGHT)
        dir = LEFT;
      break;
    case 'd':
      if (dir != LEFT)
        dir = RIGHT;
      break;
    case 'w':
      if (dir != DOWN)
        dir = UP;
      break;
    case 's':
      if (dir != UP)
        dir = DOWN;
      break;
    case 'q':
      gameOver = true;
      break; // 按 x 键直接结束
    }
  }
}

void Logic() {
  int prevX = tailX[0];
  int prevY = tailY[0];
  int prev2X, prev2Y;
  tailX[0] = x;
  tailY[0] = y;
  for (int i = 1; i < nTail; i++) {
    prev2X = tailX[i];
    prev2Y = tailY[i];
    tailX[i] = prevX;
    tailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }
  switch (dir) {
  case LEFT:
    x--;
    break;
  case RIGHT:
    x++;
    break;
  case UP:
    y--;
    break;
  case DOWN:
    y++;
    break;
  default:
    break;
  }
  if (x >= width || x < 0 || y >= height || y < 0)
    gameOver = true;
  for (int i = 0; i < nTail; i++)
    if (tailX[i] == x && tailY[i] == y)
      gameOver = true;

  if (x == fruitX && y == fruitY) {
    score += 10;
    fruitX = rand() % width;
    fruitY = rand() % height;
    nTail++;
  }
}

int main() {
  Setup();
  while (!gameOver) {
    Draw();
    Input();
    Logic();
    usleep(100000); // 100 毫秒刷新一帧
  }
  cout << "GAME OVER! Final Score: " << score << endl;
  return 0;
}
