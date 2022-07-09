#include <iostream>

const int WIDTH = 8;

int board[WIDTH][WIDTH] = {0};

// int line[WIDTH] = {0};      // 行
int col [WIDTH] = {0};      // 列
int ld[WIDTH + WIDTH - 1] = {0};    // 左斜线
int rd[WIDTH + WIDTH - 1] = {0};    // 右斜线

int count = 0;

void print() {
    std::cout << "Solution:" << count << std::endl;
    for (int i = 0; i < WIDTH; i++) {
        for (int k = 0; k < WIDTH; k++) 
            printf("%2d", board[i][k]);
        printf("\n");
    }
}

// 尝试在第i行摆放皇后
void queens(int i) {
    if (i == WIDTH) {
        count++;
        print();
    }
    else {
        // 从第i行的0列开始，到WIDTH-1列，分别尝试是否可摆放皇后
        for(int k = 0; k < WIDTH; k++) {

            // if (line[i])    continue;      // 第i行已经有皇后
            if (col[k])     continue;      // 第k列已经有皇后
            if (ld[i+k])    continue;      // [i,k]所在左斜线已经有皇后
            if (rd[i-k+WIDTH-1]) continue; // [i,k]所在右斜线已经有皇后
            
            // 第k列可以摆放皇后，则将board[i, k]置为1
            board[i][k] = 1;

            // 将[i, k]所在的行、列、左斜线、右斜线置为1
            // line[i] = 1;
            col [k] = 1;
            ld[i+k] = 1;
            rd[i-k+WIDTH-1] = 1;

            // 继续尝试下一行
            queens(i + 1);

            // 尝试完后，需要还原，以继续尝试后续的其余列是否也可以摆放皇后
            board[i][k] = 0;
            // 将[i, k]所在的行、列、左斜线、右斜线重新置为0
            // line[i] = 0;
            col [k] = 0;
            ld[i+k] = 0;
            rd[i-k+WIDTH-1] = 0;
        }
    }
}

int main()
{
    queens(0);
    std::cout << "Total solutions " << count << std::endl;
}