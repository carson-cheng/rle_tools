#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
#include "life.h"
#include <random>
int main(){
    std::mt19937 rng; std::random_device rd;
    rng.seed(rd());
    std::vector<std::string> cats_comp = {"2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "bo$obo$obo$bo!", "b2o$o2bo$b2o!", "bo$obo$obo$bo!", "b2o$o2bo$b2o!", "bo$obo$obo$bo!", "bo$obo$obo$bo!", "b2o$o2bo$b2o!", "b2o$o2bo$b2o!", "b2o$o2bo$bobo$2bo!", "2bo$bobo$o2bo$b2o!", "bo$obo$o2bo$b2o!", "b2o$o2bo$obo$bo!", "b2o$o2bo$obo$bo!", "2bo$bobo$o2bo$b2o!", "bo$obo$o2bo$b2o!", "b2o$o2bo$bobo$2bo!", "b2o$obo$bo!", "bo$obo$b2o!", "bo$obo$2o!", "2o$obo$bo!", "2o$obo$bo!", "bo$obo$b2o!", "bo$obo$2o!", "b2o$obo$bo!", "2o$obo$b2o!", "b2o$obo$2o!", "2o$obo$b2o!", "b2o$obo$2o!", "b2o$obo$2o!", "b2o$obo$2o!", "2o$obo$b2o!", "2o$obo$b2o!", "bo$obo$bo!", "bo$obo$bo!", "bo$obo$bo!", "bo$obo$bo!", "bo$obo$bo!", "bo$obo$bo!", "bo$obo$bo!", "bo$obo$bo!", "b2o$o2bo$o2bo$b2o!", "b2o$o2bo$o2bo$b2o!", "b2o$o2bo$o2bo$b2o!", "b2o$o2bo$o2bo$b2o!", "b2o$o2bo$o2bo$b2o!", "b2o$o2bo$o2bo$b2o!", "b2o$o2bo$o2bo$b2o!", "b2o$o2bo$o2bo$b2o!", "bo$obo$bobo$2b2o!", "2bo$bobo$obo$2o!", "2o$obo$bobo$2bo!", "2b2o$bobo$obo$bo!", "2bo$bobo$obo$2o!", "2b2o$bobo$obo$bo!", "bo$obo$bobo$2b2o!", "2o$obo$bobo$2bo!", "4b2o$3bobo$3b2o$b2o$obo$2o!", "2o$obo$b2o$3b2o$3bobo$4b2o!", "4b2o$3bobo$3b2o$b2o$obo$2o!", "2o$obo$b2o$3b2o$3bobo$4b2o!", "2o$obo$b2o$3b2o$3bobo$4b2o!", "2o$obo$b2o$3b2o$3bobo$4b2o!", "4b2o$3bobo$3b2o$b2o$obo$2o!", "4b2o$3bobo$3b2o$b2o$obo$2o!", "bo$obo$bobo$2bo!", "2bo$bobo$obo$bo!", "bo$obo$bobo$2bo!", "2bo$bobo$obo$bo!", "2bo$bobo$obo$bo!", "2bo$bobo$obo$bo!", "bo$obo$bobo$2bo!", "bo$obo$bobo$2bo!", "4b2o$3bo2bo$3bobo$b2obo$o2bo$obo$bo!", "b2o$o2bo$bobo$2bob2o$3bo2bo$4bobo$5bo!", "5bo$4bobo$3bo2bo$2bob2o$bobo$o2bo$b2o!", "bo$obo$o2bo$b2obo$3bobo$3bo2bo$4b2o!", "b2o$o2bo$bobo$2bob2o$3bo2bo$4bobo$5bo!", "bo$obo$o2bo$b2obo$3bobo$3bo2bo$4b2o!", "4b2o$3bo2bo$3bobo$b2obo$o2bo$obo$bo!", "5bo$4bobo$3bo2bo$2bob2o$bobo$o2bo$b2o!", "bo$obo$o2bo$bobo$2bo!", "2b2o$bo2bo$o2bo$b2o!", "bo$obo$o2bo$bobo$2bo!", "2b2o$bo2bo$o2bo$b2o!", "2bo$bobo$o2bo$obo$bo!", "2bo$bobo$o2bo$obo$bo!", "b2o$o2bo$bo2bo$2b2o!", "b2o$o2bo$bo2bo$2b2o!", "2o$bo$bobo$2b2o!", "3bo$b3o$o$2o!", "2o$obo$2bo$2b2o!", "2b2o$3bo$3o$o!", "2b2o$2bo$obo$2o!", "2b2o$bobo$bo$2o!", "o$3o$3bo$2b2o!", "2o$o$b3o$3bo!"};
    std::vector<std::string> cats;
    for (int i=0; i<cats_comp.size(); i++){
        cats.push_back(decompress(cats_comp[i]));
    }
    //std::cout << "Welcome!" << std::endl;
    int num = cats.size();
    int x = 15;
    int y = 15;
    int apple = -1;
    int its = 0;
    std::string glider = decompress("b2o$2o$2bo!");
    while (apple--){
        std::vector< std::vector<int> > board;
        for (int i=0; i<3; i++){
            board = paste(board, cats[rng()%num], rng()%x+1, rng()%y+1);
        }
        std::sort(board.begin(), board.end(), std::greater< std::vector<int> >());
        std::vector< std::vector<int> > nextgen = run(board, 1);
        std::sort(nextgen.begin(), nextgen.end(), std::greater< std::vector<int> >());
        if (nextgen == board){
            board = paste(board, glider, 24, 24);
            std::cout << getrle(board, 1, 27, 1, 27) << std::endl;
            its += 1;
            if (its % 1000 == 0){
                std::cout << its << " soups processed" << std::endl;
            }
        }
    }
}