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
    std::vector<std::string> cats_comp = {"2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "bo$obo$obo$bo!", "b2o$o2bo$b2o!", "bo$obo$obo$bo!", "b2o$o2bo$b2o!", "bo$obo$obo$bo!", "bo$obo$obo$bo!", "b2o$o2bo$b2o!", "b2o$o2bo$b2o!", "b2o$o2bo$bobo$2bo!", "2bo$bobo$o2bo$b2o!", "bo$obo$o2bo$b2o!", "b2o$o2bo$obo$bo!", "b2o$o2bo$obo$bo!", "2bo$bobo$o2bo$b2o!", "bo$obo$o2bo$b2o!", "b2o$o2bo$bobo$2bo!", "b2o$obo$bo!", "bo$obo$b2o!", "bo$obo$2o!", "2o$obo$bo!", "2o$obo$bo!", "bo$obo$b2o!", "bo$obo$2o!", "b2o$obo$bo!", "2o$obo$b2o!", "b2o$obo$2o!", "2o$obo$b2o!", "b2o$obo$2o!", "b2o$obo$2o!", "b2o$obo$2o!", "2o$obo$b2o!", "2o$obo$b2o!", "2o$o$bo$2o!", "ob2o$2obo!", "2o$o$bo$2o!", "ob2o$2obo!", "2o$bo$o$2o!", "2o$bo$o$2o!", "2obo$ob2o!", "2obo$ob2o!", "2o$o$2bo$b2o!", "2b2o$o2bo$2o!", "2o$o$2bo$b2o!", "2b2o$o2bo$2o!", "b2o$2bo$o$2o!", "b2o$2bo$o$2o!", "2o$o2bo$2b2o!", "2o$o2bo$2b2o!"};
    std::vector<std::string> cats;
    for (int i=0; i<cats_comp.size(); i++){
        cats.push_back(decompress(cats_comp[i]));
    }
    //std::cout << "Welcome!" << std::endl;
    int num = cats.size();
    int x = 15;
    int y = 15;
    int apple = -1;
    std::string glider = decompress("b2o$2o$2bo!");
    int acc = 0;
    int rej = 0;
    while (apple--){
        std::vector< std::vector<int> > board;
        // place block at specific location to enhance results
        board = paste(board, "oo$oo!", 10, 14);
        for (int i=0; i<3; i++){
            board = paste(board, cats[rng()%num], rng()%x+1, rng()%y+1);
        }
        //std::sort(board.begin(), board.end(), std::greater< std::vector<int> >());
        //std::vector< std::vector<int> > nextgen = run(board, 1);
        //std::sort(nextgen.begin(), nextgen.end(), std::greater< std::vector<int> >());
        //if (nextgen == board){
        if (is_stable(board)){
            board = paste(board, glider, 24, 24);
            std::cout << getrle(board, 1, 27, 1, 27, true) << std::endl;
            acc += 1;
            if (acc % 1000 == 0){
                //float accrate = (float)
                std::cerr << "Acceptance rate: " << (float)acc / ((float)acc + (float)rej) << std::endl;
            }
        } else {
            rej += 1;
        }
    }
}