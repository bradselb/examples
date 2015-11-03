#include <ncurses.h>

int main(int argc, char* argv[])
{
    initscr();
    addstr("hello world!");
    refresh();
    getch();
    endwin();


    return 0;
}
