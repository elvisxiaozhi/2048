#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <conio.h>
#include <fstream>
#include <windows.h>

using namespace std;

/** ���궨λ **/
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

int grid[4][4];

void show_grid(); //��ʾ����
void welcome_interface(); //��ӭ����
void new_game(); //��ʼ����Ϸ
void up_merge();
void down_merge();
void left_merge();
void right_merge();
void all_go_up();
void all_go_down();
void all_go_left();
void all_go_right();
void get_direction();
bool add_new_number(int); //�����Ƿ���������������
int check_empty();
void get_highest_score();
void get_total_score();
bool is_full(int, int);
bool no_same_number_around(int, int);
bool check_fail();
bool play_again();
void record_game();
void clear_file_data();
void read_file_data();
void set_position(int, int);
void tutorial();
void description();
bool is_file_empty();
int count_file_lines();
void return_previous_grid(int);

int main()
{
    srand(time(NULL));
    if(is_file_empty() == false) {
        welcome_interface();
        read_file_data();
        show_grid();
    }
    else {
        welcome_interface();
        new_game();
    }
    while(true) {
        record_game();
        get_direction();
        get_total_score();
        get_highest_score();
        if(check_fail() == true) {
            set_position(32, 17);
            cout << "Game Over!" << endl;
            if(play_again() == true) {
                for(int i = 0; i < 4; i++) {
                    for(int j = 0; j < 4; j++) {
                        grid[i][j] = 0;
                    }
                }
                system("cls");
                clear_file_data();
                new_game();
            }
            else {
                cout << "\nThanks for playing." << endl;
                cout << "See you next time." << endl;
                remove("2048_data.tmp");
                break;
            }
        }
    }

    getch();
    return 0;
}

void welcome_interface()
{

    system("cls");
    set_position(25, 7);
    cout << "Welcome to 2048 game!" << endl;
    set_position(25, 8);
    cout << "Created by Theodore." << endl;
    set_position(25, 9);
    cout << "Press (t/T) to see the tutorial." << endl;
    set_position(25, 10);
    cout << "Press (d/D) to see the description." << endl;
    set_position(25, 11);
    cout << "Press any other key to play..." << endl;
    char ch = getch();
    if(ch == 't' || ch == 'T') {
        tutorial();
    }
    if(ch == 'd' || ch == 'D') {
        description();
    }
    else {
        system("cls");
    }
}

void tutorial()
{
    system("cls");
    cout << "Use arrow (��, ��, ��, ��) to play." << endl;
    cout << "Press (n/N) to restart the game." << endl;
    cout << "Press (r/R) to return to the previous move." << endl;
    cout << endl;
    cout << "Press (b/B) to go back." << endl;
    cout << "Press any other key to play..." << endl;
    char ch = getch();
    if(ch == 'b' || ch == 'B') {
        system("cls");
        welcome_interface();
    }
    else {
        system("cls");
    }
}

void description()
{
    system("cls");
    cout << "The 2048 game is the developer's first project coded in C++, which the developerput a lot of efforts to it." << endl;
    cout << "Due to the limited coding level of the developer, there may still remain some   bugs unnoticed." << endl;
    cout << "If some glitches happen, try restarting the game or deleting the temporary file (2048_data.tmp)." << endl;
    cout << "You can also report the bugs to let the developer patch those." << endl;
    cout << "Hope you enjoy the game!" << endl;
    cout << endl;
    cout << "Press (b/B) to go back." << endl;
    cout << "Press any other key to play..." << endl;
    set_position(60, 12);
    cout << "Theodore Tang" << endl;
    set_position(60, 13);
    cout << "9/11/17" << endl;
    char ch = getch();
    if(ch == 'b' || ch == 'B') {
        system("cls");
        welcome_interface();
    }
    else {
        system("cls");
    }
}

void show_grid()
{
    system("color f9");
    set_position(25, 5);
    cout << "   Created by Theodore    " << endl;
    cout << setw(50) << "|-----------------------|";
    for(int i = 0; i < 4; i++) {
        cout << setw(26) << endl;
        for(int j = 0; j < 4; j++) {
            if(grid[i][j] == 0) {
                if(j < 3) {
                    cout << "|" << setw(3) << " " << setw(3);
                }
                else {
                    cout << "|" << setw(3) << " " << setw(3) << "|";
                }
            }
            else {
                if(j < 3) {
                    cout << "|" << setw(3) << grid[i][j] << setw(3);
                }
                else {
                    cout << "|" << setw(3) << grid[i][j] << setw(3) << "|";
                }
            }
        }
        cout << endl << setw(50) << "|-----------------------|";
    }
}

void new_game()
{
    int a = rand() % 4;
    int b = rand() % 4;
    int c = rand() % 4;
    int d = rand() % 4;
    grid[a][b] = grid[c][d] = 2;
    show_grid();
}

void get_direction()
{
    switch(getch()) {
    case 224:
        switch(getch()) {
        case 72: //up
            up_merge();
            all_go_up();
            add_new_number(1);
            system("cls");
            show_grid();
            break;
        case 80: //down
            down_merge();
            all_go_down();
            add_new_number(2);
            system("cls");
            show_grid();
            break;
        case 75: //left
            left_merge();
            all_go_left();
            add_new_number(3);
            system("cls");
            show_grid();
            break;
        case 77: //right
            right_merge();
            all_go_right();
            add_new_number(4);
            system("cls");
            show_grid();
            break;
        }
        break;
    case 'n':
        {
            cout << "\nDo you want to start a new game? (y/n) ";
            char ch = getch();
            if(ch == 'y' || ch == 'Y') {
                for(int i = 0; i < 4; i++) {
                    for(int j = 0; j < 4; j++) {
                        grid[i][j] = 0;
                    }
                }
                clear_file_data();
                system("cls");
                new_game();
            }
            else {
                system("cls");
                show_grid();
            }
        }
        break;
    case 'N':
        {
            cout << "\nDo you want to start a new game? (y/n) ";
            char ch = getch();
            if(ch == 'y' || ch == 'Y') {
                for(int i = 0; i < 4; i++) {
                    for(int j = 0; j < 4; j++) {
                        grid[i][j] = 0;
                    }
                }
                clear_file_data();
                system("cls");
                new_game();
            }
            else {
                system("cls");
                show_grid();
            }
        }
        break;
    case 'r':
        {
            int return_times = 0;
            while(true) {
                if(return_times == 0) {
                    cout << "\nDo you want to return to the previous move? (y/n) ";
                }
                if(return_times > 0) {
                    cout << "\nDo you still want to return to the previous move? (y/n) ";
                }
                char ch = getch();
                if(ch == 'y' || ch == 'Y') {
                    system("cls");
                    return_times++;
                    return_previous_grid(return_times);
                    show_grid();
                }
                else {
                    system("cls");
                    show_grid();
                    break;
                }
            }
        }
        break;
    case 'R':
        {
            int return_times = 0;
            while(true) {
                if(return_times == 0) {
                    cout << "\nDo you want to return to the previous move? (y/n) ";
                }
                if(return_times > 0) {
                    cout << "\nDo you still want to return to the previous move? (y/n) ";
                }
                char ch = getch();
                if(ch == 'y' || ch == 'Y') {
                    system("cls");
                    return_times++;
                    return_previous_grid(return_times);
                    show_grid();
                }
                else {
                    system("cls");
                    show_grid();
                    break;
                }
            }
        }
        break;
    default:
        set_position(32, 17);
        cout << "Wrong input!" << endl;
        break;
    }
}

void up_merge()
{
    for(int i = 1; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(grid[i][j] > 0 && grid[i - 1][j] == grid[i][j]) {
                while(grid[i - 1][j] == grid[i][j]) {
                    grid[i - 1][j] *= 2;
                    grid[i][j] = 0;
                }
            }
            else if(grid[i][j] > 0 && grid[i - 1][j] == 0 && grid[i - 2][j] == grid[i][j]) {
                while(grid[i - 2][j] == grid[i][j]) {
                    grid[i - 2][j] *= 2;
                    grid[i][j] = 0;
                }
            }
            else if(grid[i][j] > 0 && grid[i - 1][j] == 0 && grid[i - 2][j] == 0 && grid[i - 3][j] == grid[i][j]) {
                while(grid[i - 3][j] == grid[i][j]) {
                    grid[i - 3][j] *= 2;
                    grid[i][j] = 0;
                }
            }
        }
    }
}

void down_merge()
{
    for(int i = 3; i > 0; i--) {
        for(int j = 0; j < 4; j++) {
            if(grid[i][j] > 0 && grid[i][j] == grid[i - 1][j]) {
                while(grid[i][j] == grid[i - 1][j]) {
                    grid[i][j] *= 2;
                    grid[i - 1][j] = 0;
                }
            }
            else if(grid[i][j] > 0 && grid[i - 1][j] == 0 && grid[i][j] == grid[i - 2][j]) {
                while(grid[i][j] == grid[i - 2][j]) {
                    grid[i][j] *= 2;
                    grid[i - 2][j] = 0;
                }
            }
            else if(grid[i][j] > 0 && grid[i - 1][j] == 0 && grid[i - 2][j] == 0 && grid[i][j] == grid[i - 3][j]) {
                while(grid[i][j] == grid[i - 3][j]) {
                    grid[i][j] *= 2;
                    grid[i - 3][j] = 0;
                }
            }
        }
    }

}

void left_merge()
{
    for(int i = 0; i < 4; i++) {
        for(int j = 1; j < 4; j++) {
            if(grid[i][j - 1] > 0 && grid[i][j - 1] == grid[i][j]) {
                while(grid[i][j - 1] == grid[i][j]) {
                    grid[i][j - 1] *= 2;
                    grid[i][j] = 0;
                }
            }
            else if(grid[i][j - 1] > 0 && grid[i][j] == 0 && grid[i][j - 1] == grid[i][j + 1]) {
                while(grid[i][j - 1] == grid[i][j + 1]) {
                    grid[i][j - 1] *= 2;
                    grid[i][j + 1] = 0;
                }
            }
            else if(grid[i][j - 1] > 0 && grid[i][j] == 0 && grid[i][j + 1] == 0 && grid[i][j - 1] == grid[i][j + 2]) {
                while(grid[i][j - 1] == grid[i][j + 2]) {
                    grid[i][j - 1] *= 2;
                    grid[i][j + 2] = 0;
                }
            }
        }
    }
}

void right_merge()
{
    for(int i = 0; i < 4; i++) {
        for(int j = 3; j > 0; j--) {
            if(grid[i][j] > 0 && grid[i][j] == grid[i][j - 1]) {
                while(grid[i][j] == grid[i][j - 1]) {
                    grid[i][j] *= 2;
                    grid[i][j - 1] = 0;
                }
            }
            else if(grid[i][j] > 0 && grid[i][j - 1] == 0 && grid[i][j] == grid[i][j - 2]) {
                while(grid[i][j] == grid[i][j - 2]) {
                    grid[i][j] *= 2;
                    grid[i][j - 2] = 0;
                }
            }
            else if(grid[i][j] > 0 && grid[i][j - 1] == 0 && grid[i][j - 2] == 0 && grid[i][j] == grid[i][j - 3]) {
                while(grid[i][j] == grid[i][j - 3]) {
                    grid[i][j] *= 2;
                    grid[i][j - 3] = 0;
                }
            }
        }
    }
}

void all_go_up()
{
    for(int i = 3; i > 0; i--) {
        for(int j = 0; j < 4; j++) {
            if(grid[i][j] > 0 && grid[i - 1][j] == 0) {
                grid[i - 1][j] = grid[i][j];
                grid[i][j] = 0;
            }
            for(int k = 3; k > 0; k--) { //��������(0 2 2 2 )�����Ƶ���������
                if(grid[k][j] > 0 && grid[k - 1][j] == 0) {
                    grid[k - 1][j] = grid[k][j];
                    grid[k][j] = 0;
                }
            }
        }
    }
}

void all_go_down()
{
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++) {
            if(grid[i][j] > 0 && grid[i + 1][j] == 0) {
                grid[i + 1][j] = grid[i][j];
                grid[i][j] = 0;
            }
            for(int k = 0; k < 3; k++) { //��������(2 2 2 0)�����Ƶ���������
                if(grid[k][j] > 0 && grid[k + 1][j] == 0) {
                    grid[k + 1][j] = grid[k][j];
                    grid[k][j] = 0;
                }
            }
        }
    }
}

void all_go_left()
{
    int flag = 0;
    for(int j = 3; j > 0; j--) {
        for(int i = 0; i < 4; i++) {
            if(grid[i][j] > 0 && grid[i][j - 1] == 0) {
                grid[i][j - 1] = grid[i][j];
                grid[i][j] = 0;
            }
            for(int k = 3; k > 0; k--) { //�������ƶ�(0 2 2 2)�����Ƶ���������
                if(grid[i][k] > 0 && grid[i][k - 1] == 0) {
                    grid[i][k - 1] = grid[i][k];
                    grid[i][k] = 0;
                }
            }
        }
    }
}

void all_go_right()
{
    int flag = 0;
    for(int j = 0; j < 3; j++) {
        for(int i = 0; i < 4; i++) {
            if(grid[i][j] > 0 && grid[i][j + 1] == 0) {
                grid[i][j + 1] = grid[i][j];
                grid[i][j] = 0;
            }
            for(int k = 0; k < 3; k++) {
                if(grid[i][k] > 0 && grid[i][k + 1] == 0) {
                    grid[i][k + 1] = grid[i][k];
                    grid[i][k] = 0;
                }
            }
        }
    }
}

int check_empty()
{
    int flag = 0; //��Ҫ��flag����Ȼ��һֱ����ѭ����
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(grid[i][j] == 0) {
                flag = 1;
                return flag;
            }
        }
    }
}

bool add_new_number(int num)
{
    int n = rand() % 2 + 1; //range + min number
    int newnumber = 1 << n; // 1 << n = 1 * (2^n) //��<<(shift operator)��pow()����Ч
    int r, c;
    switch(num) {
    case 1: //up
        r = rand() % 2 + 2;
        c = rand() % 4;
        break;
    case 2: //down
        r = rand() % 2;
        c = rand() % 4;
        break;
    case 3: //left
        r = rand() % 4;
        c = rand() % 2 + 2;
        break;
    case 4: //right
        r = rand() % 4;
        c = rand() % 2;
        break;
    }
    do {
        if(check_empty() == 1) {
            if(grid[r][c] == 0) {
                grid[r][c] = newnumber;
                return false;
            }
            if(grid[r][c] != 0) {
                switch(num) {
                case 1: //up
                    r = rand() % 2 + 2;
                    c = rand() % 4;
                    break;
                case 2: //down
                    r = rand() % 2;
                    c = rand() % 4;
                    break;
                case 3: //left
                    r = rand() % 4;
                    c = rand() % 2 + 2;
                    break;
                case 4: //right
                    r = rand() % 4;
                    c = rand() % 2;
                    break;
                }
            }
        }
        else {
            return false;
        }

    } while(true);
}

void get_highest_score() //����Ҫ�Ľ�
{
    int maxnumber = grid[0][0];
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            if(grid[i][j] > maxnumber) {
                maxnumber = grid[i][j];
            }
        }
    }
    cout << setw(16) << "Best: " << maxnumber << endl;
}

void get_total_score()
{
    int totalnumber = 0;
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            totalnumber += grid[i][j];
        }
    }
    cout << setw(62) << "Score: " << totalnumber;
}

bool is_full(int row, int col)
{
    do {
        if(grid[row][col] != 0) {
            col++;
            while(col < 4) {
                if(is_full(row, col) != 0) {
                    col++;
                }
                else {
                    break;
                }
            }
            if(col == 4) {
                col = 1;
                row++;
                while(row < 4) {
                    if(is_full(row, col) != 0) {
                       row++;
                    }
                    else {
                        break;
                    }
                }
            }
        }
        else {
            break;
        }
    } while(row == 4);
    if(row == 4) {
        return true;
    }
}

bool no_same_number_around(int row, int col)
{
    do {
        while(col < 4) {
            if(grid[row][col] != grid[row - 1][col] &&
               grid[row][col] != grid[row + 1][col] &&
               grid[row][col] != grid[row][col - 1] &&
               grid[row][col] != grid[row][col + 1]) {
                col++;
            }
            else {
                return false;
                break;
            }
        }
        if(col == 4) {
            col = 1;
            row++;
            while(row < 4) {
            if(grid[row][col] != grid[row - 1][col] &&
               grid[row][col] != grid[row + 1][col] &&
               grid[row][col] != grid[row][col - 1] &&
               grid[row][col] != grid[row][col + 1]) {
                row++;
            }
            else {
                return false;
                break;
            }
            }
        }
    } while(row < 4);
    if(row == 4) {
        return true;
    }

}

bool check_fail()
{
    if(is_full(0, 0) == true) {
        if(no_same_number_around(0, 0) == true) {
            return true;
        }
    }
}

bool play_again()
{
    cout << "\nDo you want to play it again? (y/n) ";
    char user_input;
    cin >> user_input;
    if(user_input == 'y' || user_input == 'Y') {
        return true;
    }
    else {
        return false;
    }
}

void clear_file_data()
{
    fstream openFile;
    openFile.open("2048_data.tmp", ios::out | ios::trunc);
    openFile.close();
}

void record_game()
{
    ofstream writeFile;
    writeFile.open("2048_data.tmp", ios::out | ios::app);
    if(writeFile.is_open()) {
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                writeFile << grid[i][j] << " ";
                if(i == 3 && j == 3) {
                    writeFile << endl;
                }
            }
        }
        writeFile.close();
    }
}

void set_position(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}

int count_file_lines()
{
    ifstream openFile;
    openFile.open("2048_data.tmp", ios::in);
    char ch;
    int i = 0;
    while(openFile.get(ch)) {
        if(ch == '\n') {
            i++;
        }
        if(openFile.eof()) {
            break;
        }
    }
    openFile.close();
    return i;
}

bool is_file_empty()
{
    count_file_lines();
    if(count_file_lines() == 1) {
        return true;
    }
    else {
        return false;
    }
}

void read_file_data()
{
    int i = count_file_lines();
    int j = 0;
    ifstream openFile;
    openFile.open("2048_data.tmp");
    if(openFile.is_open()) {
        while(true) {
            char in = openFile.get();
            if(in == '\n') {
                j++;
            }
            if(j == i - 1) {
                break;
            }
        }
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                int a;
                openFile >> a;
                grid[i][j] = a;
            }
        }
    }
    openFile.close();
}

void return_previous_grid(int return_times)
{
    int i = count_file_lines(), j = 0;
    ifstream openFile;
    openFile.open("2048_data.tmp");
    if(openFile.is_open()) {
        while(true) {
            char in = openFile.get();
            if(in == '\n') {
                j++;
            }
            if(j == i - 2 - return_times) {
                break;
            }
            if(i < 2 + return_times) {
                cout << "\nCan go back anymore!" << endl;
                break;
            }
        }
        for(int i = 0; i < 4; i++) {
            for(int j = 0; j < 4; j++) {
                int a;
                openFile >> a;
                grid[i][j] = a;
            }
        }
    }
    openFile.close();
}
