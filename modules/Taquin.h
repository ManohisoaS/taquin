#ifndef TAQUIN_H
#define TAQUIN_H
#include "Graphe.h"
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;
enum MOVE
{
    UP = 0,
    DOWN,
    LEFT,
    RIGHT
};
const char BLANK_CASE = '0';
const string FINAL_STATE = "123456780";
const int SIZE = 3;
const string DB_NAME = "base.csv";

class Taquin
{
private:
    bool is_correct_move(string state, int move);
    string do_move(string state, int move);
    list<string> neighbords_list(string state);
    void show_list(list<string> my_list);
    void show_state(string state);

public:
    string state;
    Graphe graphe;
    list<string> story;
    void solve();
    void show_story();
    void write_inDb();
};
#endif