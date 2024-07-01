#include <iostream>
#include <string>
#include <vector>
#include "life.h"
// test script for life.h library
int main(){
    std::cout << decompress("3o2b3o!") << std::endl;
    std::vector< std::vector<int> > empty;
    std::vector< std::vector<int> > res = paste(empty, decompress("3o2b3o$o!"), 1, 1);
    res = paste(res, decompress("3o2b3o$o!"), 1, 4);
    res = paste(empty, decompress("bo$obo$b2o!"), 1, 4);
    std::cout << getrle(res, -1, -1, -1, -1) << std::endl;
    std::cout << get_compressed_rle(res, -1, -1, -1, -1) << std::endl;
    /*for(int i=0; i<res.size(); i++){
        std::cout << res[i][0] << ", " << res[i][1] << std::endl;
    }
    std::vector<int> box = getbbox(res);
    std::cout << box[0] << ", " << box[1] << ", " << box[2] << ", " << box[3] << std::endl;
    std::string rle = getrle(res, -1, -1, -1, -1);
    std::cout << rle << std::endl;
    for(int i=0; i<1000; i++){
        //std::vector< std::vector<int> > pat = {{18, 13}, {19, 14}, {17, 15}, {18, 15}, {19, 15}, {53, 15}, {52, 16}, {52, 17}, {53, 17}, {54, 17}, {22, 39}, {23, 39}, {24, 39}, {24, 40}, {23, 41}};
        std::vector< std::vector<int> > pat = {{29, 29}, {29, 30}, {30, 28}, {30, 31}, {31, 29}, {31, 30}, {31, 31}};
        std::cout << getrle(pat, -1, -1, -1, -1) << std::endl;
        std::vector< std::vector<int> > newpat = run(pat, 100);
        std::vector<int> box = getbbox(newpat);
        //std::cout << box[0] << ", " << box[1] << std::endl;
        int pop = getpop(newpat);
        //std::cout << pop << std::endl;
    }
    //right now it does about 1000 iterations per second, which is way too slow but can be improved.*/
}
