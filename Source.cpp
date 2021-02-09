#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
#include <ctime>

// ��� �������� ������� ���������� ����
#define HEIGHT 28
#define WIDTH 16

// ����� ��� ������ ��������
char buf_cur[HEIGHT][WIDTH];

// ����� ��� ����� ��������
char buf_next[HEIGHT][WIDTH];

using namespace std;

// ���������� ������� ��������� �� ������������ ������
// �� ������������
// int count;

// �� ������������
// bool work;

// ����������� ������� �����
int slaw;
// ��� �������� �������
#define STANDART_SLOW 130

int score; //���������� �����
// ���� ��������?
bool gameOver;

// ��� ������
int typeFigure;
int turnFigure;
int oldTurnFigure;
// ������
int width;

// ������
int height;

// ���������� ����� � ������, �� ������� ����� ��������� ������
int x, y;

int x1, y11;


// ��������� �� ����������� ������ ����� ��� ������
bool direcL, direcR;

// �� ������������
// vector <int>zam;

// �������� � ��������
enum eDirection { RIGHT = 0, LEFT, DOWN, lowDOWN, STOP, NON, TURN };

eDirection dir;

// ���������� �����, ������� ����������
vector <int> downX;
vector <int> downY;

// ������� ������, ������� ��������
vector <int> Vx;
vector <int> Vy;


vector <int> oldVx; //���������� ���������� ������� Vx,Vy, ����� ��������� ���� �heckDown()
vector <int> oldVy;



void checkDown()    //�������� �� ����������� �������� ������ ����� �������
{
    for (int i = 0; i < Vx.size(); i++)
    {
        for (int j = 0; j < downX.size(); j++)
        {
            if (Vx[i] == downX[j] && Vy[i] == downY[j])
            {
                Vx = oldVx;
                Vy = oldVy;
            }
        }
    }
}

// ������ ���������� ������ � ���������� (x,y) �� �������� ���� ��� system("cls") ���������� ������ � �������� ����������
void setcur(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void Setup()
{
    srand(time(NULL));
    slaw = STANDART_SLOW;
    gameOver = false;
    typeFigure = rand() % 7;
    width = WIDTH;
    height = HEIGHT;
    dir = STOP;
    x = rand() % (width - 4) + 2;
    y = 0;
    score = 0;
    turnFigure = 0;
    oldTurnFigure = 0;
    Vx.resize(4);
    Vy.resize(4);
    // ��������� ������ � ����� ������� �������
    system("cls");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if ((j == 0) || (j == (width - 1))) {
                buf_cur[i][j] = buf_next[i][j] = '*';
                cout << '*';
            }
            else {
                buf_cur[i][j] = buf_next[i][j] = ' ';
                cout << ' ';
            }
        }
        cout << '\n';
    }

    // ������ ������ ������
    for (int i = 0; i < width; i++)
    {
        cout << '*';
    }

    // ��������� ��������� �����
    cout.flush();
}

void Draw() {
    Sleep(slaw);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // ������ ������� ������
            if (j == 0 || j == width - 1)
            {
                // cout << "*";
                continue;
            }
            else
            {
                bool print = false;
                bool printD = false;

                // ������ �������� ������
                for (int q = 0; q < Vx.size(); q++)
                {
                    if (Vx[q] == j && Vy[q] == i)
                    {
                        buf_next[i][j] = '#';
                        //cout << "#";
                        print = true;
                    }
                }

                // ������ ��� ������� ������
                for (int q = 0; q < downX.size(); q++)
                {
                    if (i == downY[q] && j == downX[q])
                    {
                        buf_next[i][j] = '#';
                        //cout << "#";
                        printD = true;
                    }
                }

                // ������ �������
                if (!print && !printD)
                {
                    buf_next[i][j] = ' ';
                    //cout << " ";
                }

            }

        }
        //cout << endl;
    }


    // ������������ ��������� ������
    for (int i = 0; i < height; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            if (buf_cur[i][j] != buf_next[i][j]) {
                buf_cur[i][j] = buf_next[i][j];
                setcur(j, i);
                cout << buf_next[i][j];
            }
        }
    }

    setcur(0, height);
    cout << endl << "Score = " << score;

    // ��������� ��������� �����
    cout.flush();

}

void Input()
{
    // �������� �����-�� �������?
    if (_kbhit())
    {
        // ����� ������ ������� ��������?
        switch (_getch())
        {
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 's':
            dir = DOWN;
            break;
        case'w':
            dir = TURN;
            break;

        }
    }
}

void Logic()
{
    // ���� ������ ������ ������ ������ ������, �� �������� ����� ������ ������ ������������
    
    if (y == 0)
    {
        // ����� ��� ������ ����� � �������?
       
        switch (typeFigure)
        {
        case 0:
            for (int i = 0; i < Vx.size(); i++)
            {
                Vx[i] = x;
                Vy[i] = y - i;
            }
            break;
        case 1:
            Vx[0] = Vx[1] = x;
            Vx[2] = Vx[3] = x + 1;

            Vy[0] = Vy[3] = y;
            Vy[1] = Vy[2] = y - 1;
            break;
        case 2:
            Vx[0] = Vx[1] = x;
            Vx[2] = x - 1;
            Vx[3] = x + 1;

            Vy[0] = Vy[3] = y;
            Vy[1] = Vy[2] = y - 1;
            break;
        case 3:
            Vx[0] = Vx[1] = Vx[2] = x;
            Vx[3] = x + 1;

            Vy[0] = Vy[3] = y;
            Vy[1] = y - 1;
            Vy[2] = y - 2;
            break;
        case 4:
            Vx[3] = Vx[1] = Vx[2] = x + 1;
            Vx[0] = x;

            Vy[0] = Vy[3] = y;
            Vy[1] = y - 2;
            Vy[2] = y - 1;
            break;
        case 5:
            Vx[0] = Vx[2] = x;
            Vx[1] = x - 1;
            Vx[3] = x + 1;

            Vy[0] = Vy[1] = y;
            Vy[2] = Vy[3] = y - 1;
            break;
        case 6:
            Vx[0] = Vx[2] = x;
            Vx[1] = x - 1;
            Vx[3] = x + 1;

            Vy[0] = Vy[1] = Vy[3] = y;
            Vy[2] = y - 1;
            break;
        }
        y++;


    }
    

    // ����������� ������
    switch (dir)
    {
        // �����
    case LEFT:
        slaw = STANDART_SLOW;
        direcL = true;

        // �������� �� ����������� ������
        for (int i = 0; i < Vx.size(); i++)
        {
            // �� ��������� � ����� ������?
            if (Vx[i] > 1)
            {
                // �� ��������� � ������� ������?
                for (int k = 0; k < downX.size(); k++)
                {
                    if (Vx[i] - 1 == downX[k] && Vy[i] == downY[k])
                    {
                        direcL = false;
                        break;
                    }
                }
            }
            else
            {
                direcL = false;
            }
        }

        // ���� ��� ����, �� ����������
        if (direcL)
        {
            for (int i = 0; i < Vx.size(); i++)
            {
                Vx[i]--;
            }
        }
        // ��������� ���������� �����������, ����� ������ ������������ ������ �� 1 ����������
        dir = NON;
        // ��� ����� �������� ������, ����� ������ ��������
        
        return;

    // ������
    case RIGHT:
        slaw = STANDART_SLOW;
        direcR = true;

        // �������� �� ����������� ������
        for (int i = 0; i < Vx.size(); i++)
        {
            // �� ��������� � ������ ������?
            if (Vx[i] < width - 2)
            {
                // �� ��������� � ������� ������?
                for (int k = 0; k < downX.size(); k++)
                {
                    if (Vx[i] + 1 == downX[k] && Vy[i] == downY[k])
                    {
                        direcR = false;
                        break;
                    }
                }
            }
            else
            {
                direcR = false;
            }
        }

        // ���� ��� ����, �� ����������
        if (direcR)
        {
            for (int i = 0; i < Vx.size(); i++)
            {
                Vx[i]++;
            }
        }
        // ��������� ���������� �����������, ����� ������ ������������ ������ �� 1 ����������
        dir = NON;
        // ��� ����� �������� ������, ����� ������ ��������
        
        return;

    // �������� �������, ������� ������� Sleep()
    case DOWN:
        slaw = 10;
        dir = NON;
        break;

    case TURN:
        turnFigure++;
        switch (typeFigure)
        {
        case 0:           //l
            
                x1 = Vx[0];
                y11 = Vy[0];
                oldVx = Vx;
                oldVy = Vy;
                switch (turnFigure % 2)
                {                 
                case 0:
                   
                        Vx[0] = Vx[1] = Vx[2] = Vx[3] = x1;
                        Vy[0] = y11;
                        Vy[1] = y11 - 1;
                        Vy[2] = y11 - 2;
                        Vy[3] = y11 - 3;
                        checkDown();
                        break;
                       
                case 1:                    
                        Vx[0] = x1;
                        Vx[1] = x1 + 1;
                        Vx[2] = x1 + 2;
                        Vx[3] = x1 + 3;
                        Vy[0] = Vy[1] = Vy[2] = Vy[3] = y11;
                        checkDown();

                        break;
                }
            
            dir = NON;
            break;


        case 1:  //O
            
            dir = NON;
            break;

        case 2:              //z
            oldVx = Vx;
            oldVy = Vy;
                x1 = Vx[0];
                y11 = Vy[0];
                switch (turnFigure % 2)
                {
                    case 0:
                        Vx[0] = Vx[1]  = x1;
                        Vx[2] = x1 - 1;
                        Vx[3] = x1 + 1;
                        Vy[0] = Vy[3]= y11;
                        Vy[1] = Vy[2] = y11 - 1;
                        checkDown();
                        break;

                    case 1:
                       Vx[0] = Vx[1] = x1;
                       Vx[2] = Vx[3] = x1 + 1;
                    
                       Vy[0] = Vy[2] = y11;
                       Vy[1] =  y11 +1;
                       Vy[3] = y11 - 1;
                       checkDown();                    
                        break;
                } 
            dir = NON;
            break;

        case 3:  //L
            oldVx = Vx;
            oldVy = Vy;
            x1 = Vx[0];
            y11 = Vy[0];
            switch (turnFigure % 4)
            {
            case 0:
                Vx[0] = Vx[1] = Vx[2] = x1;
                Vx[3] = x1 + 1;

                Vy[0] = Vy[3] = y11;
                Vy[1] = y11 - 1;
                Vy[2] = y11 - 2;
                checkDown();
                break;
            case 1:
                Vx[0] = Vx[3] = x1;
                Vx[1] = x1 + 1;
                Vx[2] = x1 + 2;

                Vy[0] = Vy[1] = Vy[2] = y11;
                Vy[3] = y11 + 1;
                checkDown();
                break;
            case 2:
                Vx[0] = Vx[1] =Vx[2]= x1;
                Vx[3] = x - 1;
                
                Vy[0] = Vy[3] = y11;
                Vy[1] = y11 + 1;
                Vy[2] = y11 + 2;
                checkDown();
                break;
            case 3:
                Vx[0] = Vx[1] = x1;
                Vx[2] = x1 - 1;
                Vx[3] = x1 - 2;

                Vy[0] = Vy[2] = Vy[3] = y11;
                Vy[1] = y11 - 1;
                checkDown();
                break;
               
            }
            dir = NON;
            break;

        case 4:    //J
            oldVx = Vx;
            oldVy = Vy;
            x1 = Vx[0];
            y11 = Vy[0];
            switch (turnFigure % 4)
            {
            case 0:
                Vx[0] = Vx[1] = Vx[2] = x1;
                Vx[3] = x1 - 1;

                Vy[0] = Vy[3] = y11;
                Vy[1] = y11 - 1;
                Vy[2] = y11 - 2;
                checkDown();
                break;

            case 1:
                Vx[0] = Vx[3] = x1;
                Vx[1] = x1 + 1;
                Vx[2] = x1 + 2;

                Vy[0] = Vy[1] = Vy[2] = y11;
                Vy[3] = y11 + 1;
                checkDown();
                break;

            case 2:
                Vx[0] = Vx[1] = Vx[2] = x1;
                Vx[3] = x1 + 1;

                Vy[0] = Vy[3] = y11;
                Vy[1] = y11 + 1;
                Vy[2] = y11 + 2;
                checkDown();
                break;

            case 3:
                Vx[0] = Vx[1] = x1;
                Vx[2] = x1 - 1;
                Vx[3] = x1 - 2;

                Vy[0] = Vy[2] = Vy[3] = y11;
                Vy[1] = y11 + 1;
                checkDown();
                break;

            }
            dir = NON;
            break;

        case 5:   //s
            oldVx = Vx;
            oldVy = Vy;
            x1 = Vx[0];
            y11 = Vy[0];
            switch (turnFigure % 2)
            {
                case 0:
                    Vx[0] = Vx[2] = x1;
                    Vx[1] = x1 - 1;
                    Vx[3] = x1 + 1;
                   
                    Vy[0] = Vy[1] = y11;
                    Vy[2] = Vy[3] = y11 - 1;
                    checkDown();
                    break;

                case 1:
                    Vx[0] = Vx[3] = x1;
                    Vx[1] = Vx[2] = x1 + 1;

                    Vy[0] = Vy[1] = y11;
                    Vy[2] = y11 - 1;
                   Vy[3] = y11 + 1;
                   checkDown();
                    break;
            }

            dir = NON;
            break;
        
        case 6:     //T
            oldVx = Vx;
            oldVy = Vy;
            x1 = Vx[0];
            y11 = Vy[0];
            switch (turnFigure % 4)
            {
            case 0:
                Vx[0] = Vx[2] = x1;
                Vx[1] = x1 - 1;
                Vx[3] = x1 + 1;

                Vy[0] = Vy[1] = Vy[3] = y11;
                Vy[2] = y11 - 1;
                checkDown();
                break;

            case 1:
                Vx[0] = Vx[1]=Vx[3] = x1;
                Vx[2] = x1 + 1;

                Vy[0] = Vy[2] = y11;
                Vy[1] = y11 - 1;
                Vy[3] = y11 + 1;
                checkDown();
                break;

            case 2:
                Vx[0] = Vx[2] = x1;
                Vx[1] = x1 - 1;
                Vx[3] = x1 + 1;

                Vy[0] = Vy[1] = Vy[3] = y11;
                Vy[2] = y11 + 1;
                checkDown();
                break;

            case 3:
                Vx[0] = Vx[1] = Vx[3] = x1;
                Vx[2] = x1 - 1;

                Vy[0] = Vy[2] = y11;
                Vy[1] = y11 - 1;
                Vy[3] = y11 + 1;
                checkDown();
                break;
            }
            dir = NON;
            break;
        }
       

    default:
        for (int i = 0; i < Vy.size(); i++)
        {
            Vy[i]++;
        }
        break;

    }

    if (oldTurnFigure != turnFigure)
    {
        for (int i = 0; i < Vx.size(); i++)
        {
            while (Vx[i] <= 0)
            {
                for (int j = 0; j < Vx.size(); j++)
                {
                    Vx[j]++;
                }
                i = 0;
            }

            while (Vx[i] >= width - 1)
            {
                for (int j = 0; j < Vx.size(); j++)
                {
                    Vx[j]--;
                }
                i = 0;
            }
            while (Vy[i] >= height)
            {
                for (int j = 0; j < Vy.size(); j++)
                {
                    Vy[j]--;
                }
                i = 0;
            }
        }
    }
    oldTurnFigure = turnFigure;

  
    // �������� ����� ����
    // ���� ����� �� ������� �����
    for (int i = 0; i < downX.size(); i++)
    {
        if (downY[i] < 0)
        {
            gameOver = true;
            return;
        }

    }

    // ������ � �������� ��������
    for (int i = 0, work = false; i < downX.size(); i++)
    {
        if (work) 
        {
            return;
        }

        for (int q = 0; q < Vx.size(); q++)
        {
            // ���� ���������� �������� ����� ��������� � ������������ ������� �� (�-1), �� ������ ���� ���������� �������
            if (Vx[q] == downX[i] && Vy[q] == downY[i] - 1)
            {
                for (int j = 0; j < Vx.size(); j++)
                {
                    downX.push_back(Vx[j]);
                    downY.push_back(Vy[j]);
                }
                // ����� ������ ����� �������� ����� ������ ��������
                y = 0;
                slaw = STANDART_SLOW;
                x = rand() % (width - 4) + 2;
                typeFigure = rand() % 7;
                turnFigure = 0;
                for (int i = 0; i < Vx.size(); i++)
                {
                    Vx[i] = 0;
                    Vy[i] = 0;
                }
                work = true;
                break;
            }
        }
    }

    // ���� ����� �� ���, �� ������ �����
    for (int j = 0; j < Vy.size(); j++)
    {

        if (Vy[j] == height-1)
        {
            for (int i = 0; i < Vx.size(); i++)
            {
                downX.push_back(Vx[i]);
                downY.push_back(Vy[i]);
            }
            // �������� ����� ������
            slaw = STANDART_SLOW;
            y = 0;
            x = rand() % (width - 4) + 2;
            typeFigure = rand() % 7;
            turnFigure = 0;
            for (int i = 0; i < Vx.size(); i++)
            {
                Vx[i] = 0;
                Vy[i] = 0;
            }
            return;
        }
    }



    // �������� �� ������� ����������� ������ �����
    int lv;     // �������, (������) ��� ����� ���������� ���� ���
    int countD;//���������� ������� ������ � ����

    for (lv = 0; lv < height+1; lv++)
    {
        countD = 0;
        for (int i = 0, count = 0; i < downY.size(); i++)
        {
            // ������� ������� ����� �� ���
            if (downY[i] == lv)
            {
                countD++;
            }
            
        }
        if (countD == width - 2)     // ���� ��� ��� ���������, �� ��� ���� �������
        {
            score += 100;

            for (int k = 0; k < downX.size(); k++)
            {
                if (downY[k] == lv)
                {
                    downY.erase(downY.begin() + k);
                    downX.erase(downX.begin() + k);
                    k = 0;

                }
            }

            // ����� �������� ���� �������� ��� ������ ����
            for (int k = 0; k < downX.size(); k++)
            {
                if (downY[k] < lv)
                {
                    downY[k]++;
                }
            }

        }
    }



}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();

    }
    return 0;
}
