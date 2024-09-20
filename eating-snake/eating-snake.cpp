#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <conio.h>
#include <chrono>

using namespace std;

//蛇
struct eatingSnake
{
    int dir; //移动方向
    int x,y;  //位置
}snake[225];

bool running = true;  //控制游戏是否继续运行
bool over = false,win = false;  //判断游戏胜负
int mapLength;  //地图大小
int map[17][17];  //地图
int snakeSpeed;  //游戏速度设置
int snakeLength;  //蛇的长度
int foodX,foodY;  //食物的位置

void Draw();  //绘制游戏区域
void Logic();  //处理游戏逻辑
void Food();  // 生成食物
void Setting();  //游戏的初始化
void Settlement();  //游戏结算

int main()
{
    while(running)
    {
        system("cls");
        Setting();
        Draw();
        _sleep(snakeSpeed);
        while(!over && !win)
        {
            Logic();
            Draw();
            _sleep(snakeSpeed);
        }
        Settlement();
    }
    return 0;
}

void Setting()
{
    int choice; 

    over = win = false;

    //设置地图大小
    cout << "请选择地图大小...\n1:小 2:中 3:大\n";
    cin >> choice;
    switch (choice)
    {
        case 1:
            mapLength = 5;
            break;
        case 2:
            mapLength = 10;
            break;
        case 3:
            mapLength = 15;
            break;
        default:
            over = true;
            return;
    }

    //设置蛇的移动速度
    cout << "请选择游戏难度...\n1:休闲 2:正常 3:困难 4:地狱 5:啊？\n";
    cin >> choice;
    switch (choice)
    {
        case 1:
            snakeSpeed = 500;
            break;
        case 2:
            snakeSpeed = 250;
            break;
        case 3:
            snakeSpeed = 100;
            break;
        case 4:
            snakeSpeed = 40;
            break;
        case 5:
            snakeSpeed = 0;
            break;
        default:
            over = true;
            return;
    }
    
    // 蛇的初始设置 1:上 2:下 3:左 4:右
    snake[0].x = snake[0].y = (mapLength + 1) / 2;
    snake[0].dir = 4;
    snakeLength = 1;

    //地图的初始化 0:地图边界 1:空地 2:蛇头 3:蛇身 4:食物
    for(int i = 0;i <= mapLength + 1;i++)
        for(int j = 0;j <= mapLength + 1;j++)
            map[i][j] = 0;
    for(int i = 1;i <= mapLength;i++)
        for(int j = 1;j <= mapLength;j++)
            map[i][j] = 1;
    map[(mapLength + 1) / 2][(mapLength + 1) / 2] = 2;
    Food();
}

void Draw()
{
    //控制台清屏
    system("cls");

    //绘制地图
    for(int i = 1;i <= mapLength;i++)
    {
        for(int j = 1;j <= mapLength;j++)
            switch (map[i][j])
            {
                case 1:
                    cout << "·";
                    break;
                case 2:
                    switch (snake[0].dir)
                    {
                        case 1:
                            cout << "Λ";
                            break;
                        case 2:
                            cout << "V";
                            break;
                        case 3:
                            cout << "<";
                            break;
                        case 4:
                            cout << ">";
                            break;
                    }
                    break;
                case 3:
                    cout << "*";
                    break;
                case 4:
                    cout << "▇";
                    break;
            }
        cout << endl;
    }
}

void Logic()
{
    int dir = snake[snakeLength-1].dir;
    //蛇身移动方向更新
    for(int i = snakeLength - 1;i > 0;i--)
        snake[i].dir = snake[i-1].dir;
    //检测输入
    int key = 0;
    for(int i = 0;i < 100;i++)
    {
        if(kbhit())
        {
            getch();
            key = getch();
        }
    }
    switch (key)
    {
        case 72:
            snake[0].dir = 1;
            break;
        case 80:
            snake[0].dir = 2;
            break;
        case 75:
            snake[0].dir = 3;
            break;
        case 77:
            snake[0].dir = 4;
            break;
    }
    //蛇头移动
    switch (snake[0].dir)
    {
        case 1:
            snake[0].x--;
            break;
        case 2:
            snake[0].x++;
            break;
        case 3:
            snake[0].y--;
            break;
        case 4:
            snake[0].y++;
            break;
    }
    //判断蛇头是否撞上边界
    if(map[snake[0].x][snake[0].y] == 0)
    {
        over = true;
        return;
    }
    //蛇身移动
    for(int i = 1;i < snakeLength;i++)
    {
        switch (snake[i].dir)
        {
            case 1:
                snake[i].x--;
                break;
            case 2:
                snake[i].x++;
                break;
            case 3:
                snake[i].y--;
                break;
            case 4:
                snake[i].y++;
                break;
        }
        if(snake[i].x == snake[0].x && snake[i].y == snake[0].y)
        {
            over = true;
            return;
        }  //判断蛇身是否撞上蛇头
    }
    //判断是否吃到食物
    if(snake[0].x == foodX && snake[0].y == foodY)
    {
        snakeLength++;
        switch (snake[snakeLength-2].dir)
        {
        case 1:
            snake[snakeLength-1].x = snake[snakeLength-2].x + 1;
            snake[snakeLength-1].y = snake[snakeLength-2].y;
            break;
        case 2:
            snake[snakeLength-1].x = snake[snakeLength-2].x - 1;
            snake[snakeLength-1].y = snake[snakeLength-2].y;
            break;
        case 3:
            snake[snakeLength-1].x = snake[snakeLength-2].x;
            snake[snakeLength-1].y = snake[snakeLength-2].y + 1;
            break;
        case 4:
            snake[snakeLength-1].x = snake[snakeLength-2].x;
            snake[snakeLength-1].y = snake[snakeLength-2].y - 1;
            break;
        }
        snake[snakeLength-1].dir = dir;
        Food();
    }
    //地图更新
    for(int i = 1;i <= mapLength;i++)
        for(int j = 1;j <= mapLength;j++)
            map[i][j] = 1;
    map[snake[0].x][snake[0].y] = 2;
    for(int i = 1;i < snakeLength;i++)
        map[snake[i].x][snake[i].y] = 3;
    map[foodX][foodY] = 4;
}

void Food()
{
    srand(time(NULL));
    do
    {
       foodX = (rand() % mapLength) + 1;
       foodY = (rand() % mapLength) + 1;
    } while (map[foodX][foodY] != 1);
    map[foodX][foodY] = 4;
    
}

void Settlement()
{
    if(over)
        cout << "游戏结束！\n";
    else 
        cout << "你胜利了！\n";
    cout << "你是否想再来一局(y/N):";
    char again[10];
    cin.ignore();
    cin.clear();  //清除输入缓缓存区
    cin.getline(again,10);
    if(again[0] != 'y' && again[0] != 'Y')
        running = false;
}
