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
    std::vector< std::vector<int> > example;
    std::vector<std::string> cats_comp = {"2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "2o$2o!", "b2o$o2bo$o2bo$b2o!", "b2o$o2bo$o2bo$b2o!", "b2o$o2bo$o2bo$b2o!", "b2o$o2bo$o2bo$b2o!", "b2o$o2bo$o2bo$b2o!", "b2o$o2bo$o2bo$b2o!", "b2o$o2bo$o2bo$b2o!", "b2o$o2bo$o2bo$b2o!"};    std::vector< std::vector< std::vector<int> > > cats;
    for (int i=0; i<cats_comp.size(); i++){
        cats.push_back(paste(example, decompress(cats_comp[i]), 0, 0));
    }
    //std::cout << "Welcome!" << std::endl;
    int numSL = 4;
    int num = cats.size();
    int x = 15;
    int y = 15;
    int apple = -1;
    std::vector< std::vector<int> > glider = paste(example, decompress("b2o$2o$2bo!"), 0, 0);
    //int acc = 0;
    //int rej = 0;
    while (apple--){
        std::vector< std::vector<int> > board;
        // place block at specific location to enhance results
        for (int i=0; i<numSL; i++){
            board = paste_list(board, cats[rng()%num], rng()%x+1, rng()%y+1);
        }
        //std::sort(board.begin(), board.end(), std::greater< std::vector<int> >());
        //std::vector< std::vector<int> > nextgen = run(board, 1);
        //std::sort(nextgen.begin(), nextgen.end(), std::greater< std::vector<int> >());
        //if (nextgen == board){
        if (is_stable(board)){
            board = paste_list(board, glider, 24, 24);
            std::cout << getrle(board, 1, 27, 1, 27) << std::endl;
            //acc += 1;
            /*if (acc % 65536 == 0){
                //float accrate = (float)
                std::cerr << "Acceptance rate: " << (float)acc / ((float)acc + (float)rej) << std::endl;
            }*/
        }
    }
}