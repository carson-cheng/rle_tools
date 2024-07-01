#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cstring>
#include <cstdio>
#include "life.h"
#include <random>
#include "../apgmera/lifelib/pattern2.h"
std::string lifelib_getrle(apg::pattern pat){
    std::ostringstream ss;
    pat.write_rle(ss);
    std::string s = ss.str();
    return s;
}
int main(){
    apg::lifetree<uint32_t, 1> lt(1000);
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
            std::string patrle = getrle(board, 1, 27, 1, 27, false);
            apg::pattern pat(&lt, patrle, "b3s23");
            // detect tandem gliders
            // let it evolve for some generations
            apg::pattern pat2 = pat[200];
            if (pat2[2] != pat2){
                //std::cout << patrle << std::endl;
                // detect whether that is a spaceship
                // TODO: implement bounding box check
                // for now, just use rles
                if (lifelib_getrle(pat2[4]) == lifelib_getrle(pat2)){
                    if (pat2.totalPopulation() != 5){
                        std::cout << pat2.apgcode() << std::endl;
                        pat.write_rle(std::cout);
                    }
                }
            }
            //pat2.write_rle(std::cout);
        }
    }
}