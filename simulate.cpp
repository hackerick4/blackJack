#ifndef _UNISTD_H
#define _UNISTD_H    1

/* This file intended to serve as a drop-in replacement for 
 *  unistd.h on Windows
 *  Please add functionality as neeeded 
 */

#include <stdlib.h>
#include <io.h>
#include <process.h> /* for getpid() and the exec..() family */
#include <direct.h> /* for _getcwd() and _chdir() */

#define srandom srand
#define random rand

/* Values for the second argument to access.
   These may be OR'd together.  */
#define R_OK    4       /* Test for read permission.  */
#define W_OK    2       /* Test for write permission.  */
//#define   X_OK    1       /* execute permission - unsupported in windows*/
#define F_OK    0       /* Test for existence.  */

#define access _access
#define dup2 _dup2
#define execve _execve
#define ftruncate _chsize
#define unlink _unlink
#define fileno _fileno
#define getcwd _getcwd
#define chdir _chdir
#define isatty _isatty
#define lseek _lseek
/* read, write, and close are NOT being #defined here, because while there are file handle specific versions for Windows, they probably don't work for sockets. You need to look at your app and consider whether to call e.g. closesocket(). */

#define ssize_t int

#define STDIN_FILENO 0
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
/* should be in some equivalent to <sys/types.h> */
typedef __int8            int8_t;
typedef __int16           int16_t; 
typedef __int32           int32_t;
typedef __int64           int64_t;
typedef unsigned __int8   uint8_t;
typedef unsigned __int16  uint16_t;
typedef unsigned __int32  uint32_t;
typedef unsigned __int64  uint64_t;

#endif /* unistd.h  */
#include<iostream>
#include <conio.h>
//#include <unistd.h>
#include "BlackjackGame.cpp"
#define NUM_OF_ROUNDS 5
using namespace std;
int main(){
    BlackjackGame game(1, 0.25, 1);
    Player p1(10, 1);
    p1.set_strategy(hard, soft, split);
    Player p2(10, 5);
    p2.set_strategy(hard, soft, split);
/*
 *Modify any stragety as you want to see the expected return
 * 
 *   hard[12][3] = STAND;
 *   soft[13][4] = D_H;
 *   split[8][10] = HIT;
 *   split[8][1] = HIT;
*/
    Player p3(10, 0);
    p3.set_strategy(hard, soft, split);

    game.add_player(p1);
    game.add_player(p2);
    game.add_player(p3);
    for(int i = 0; i < NUM_OF_ROUNDS; i++){
        game.play_round();
        game.players[0].modify_bet_by_count(game.doc.get_running_count());

    }

    cout << "1:" << game.players[0].get_money() << endl;
    cout << "2:" << game.players[1].get_money() << endl;
    cout << "3:" << game.players[2].get_money() << endl;
    cout << "1:" << game.players[0].get_sidebet_money() << endl;
    cout << "2:" << game.players[1].get_sidebet_money() << endl;
    cout << "3:" << game.players[2].get_sidebet_money() << endl;

    return 0;
}
