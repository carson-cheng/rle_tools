#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include "life.h"
#include <fstream>
int main(){
    std::vector< std::vector<int> > example;
    //std::cout << "Made example vector" << std::endl;
    std::vector<std::string> cats_comp = {};
    //std::cout << "Initialized Empty List" << std::endl;
    std::string line;
    //std::cout << "Initialized empty line" << std::endl;
    std::ifstream rf("rles.txt");
    //std::cout << "Opened ifstream" << std::endl;
    while (std::getline(rf, line)){
        //std::cout << "Got it" << std::endl;
        cats_comp.push_back(line);
    }
    //std::cout << "Ok" << std::endl;
    std::vector< std::vector< std::vector<int> > > cats;
    for (int i=0; i<cats_comp.size(); i++){
        cats.push_back(paste(example, decompress(cats_comp[i]), 0, 0));
    }
    //std::cout << "Welcome!" << std::endl;
    int g_coords = 28;
    std::vector< std::vector<int> > glider = paste(example, decompress("b2o$2o$2bo!"), 0, 0);
    // preplacing cache
    //std::vector< std::vector<int> > eater = paste(example, decompress("2o$bo$bobo$2b2o!"), 0, 0);
    //int acc = 0;
    //int rej = 0;
    for (int i=0; i<cats.size(); i++){
        std::vector< std::vector<int> > board;
        board = paste_list(board, cats[i], 10, 12);
        std::vector< std::vector<int> > result;
        int gx_coords = 18;
        for (int i=0; i<20; i++){
            result = paste_list(board, glider, gx_coords, g_coords);
            //std::cout << getrle(result, 1, gx_coords+3, 1, g_coords+3) << std::endl;
            std::cout << get_compressed_rle(result, 1, gx_coords+3, 1, g_coords+3) << std::endl;
            gx_coords += 1;
        }
    }
}