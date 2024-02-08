// a simple b3s23 iterator based on cell lists
// used for preprocessing patterns before piping into more complicated programs like apgsearch
#include <iostream>
#include <string>
#include <vector>
std::string decompress(std::string rle){
    std::string res;
    int buffer = 0;
    for (int i=0; i<rle.size(); i++){
        //std::cout << rle[i] << std::endl;
        if (isdigit(rle[i])){
            if (buffer == 0){
                int k = rle[i] - 48; // for some reason we need to subtract 48 (by empirical testing)
                buffer = k;
                //std::cout << buffer << std::endl;
            } else {
                int k = rle[i] - 48; // same here, probably
                buffer = 10 * buffer + k;
            }
        } else {
            if (buffer != 0){
                for (int j=0; j<buffer; j++){
                    res += rle[i];
                }
            } else {
                res += rle[i];
            }
            buffer = 0;
        }
    }
    return res;
}
std::vector< std::vector<int> > paste(std::vector< std::vector<int> > res, std::string rle, int x, int y){
    // generates a cell list based on decompressed rle
    int x_original = x;
    std::string dollar = "$";
    std::string exc = "!";
    std::string on = "o";
    for (int i=0; i<rle.size(); i++){
        std::string cur(1, rle[i]);
        if (cur == dollar){
            y += 1;
            x = x_original;
        } else if (cur != exc){
            if (cur == on){
                res.push_back({x, y});
            }
            x += 1;
        }
    }
    return res;
}
std::vector< std::vector<int> > paste_list(std::vector< std::vector<int> > res, std::vector< std::vector<int> > pat, int x, int y){
    for (int i=0; i<pat.size(); i++){
        res.push_back({pat[i][0] + x, pat[i][1] + y});
    }
    return res;
}
std::vector< std::vector<int> > run(std::vector< std::vector<int> > pat, int gens){
    //this iterator is very simple, and does not have any optimization over escaping spaceships
    //step_size must be a divisor of gens, or the program might not work properly.
    //limits pattern size to at most 64x64
    //works weirdly when values of the cell list gets close to zero
    for(int i=0; i<gens; i++){
        int xmin=2147483647; int ymin=2147483647; int xmax=0; int ymax=0;
        bool cells[64][64] = {{false}};
        for(int i=0; i<pat.size(); i++){
            cells[pat[i][0]][pat[i][1]] = true;
            if (xmin > pat[i][0]){
                xmin = pat[i][0];
            } else if (xmax < pat[i][0]){
                xmax = pat[i][0];
            }
            if (ymin > pat[i][1]){
                ymin = pat[i][1];
            } else if (ymax < pat[i][1]){
                ymax = pat[i][1];
            }
        }
        //run the pattern for 1 generation
        bool newcells[64][64] = {{false}};
        std::vector< std::vector<int> > newpat;
        for(int i=xmin-1; i<xmax+2; i++){
            for(int j=ymin-1; j<ymax+2; j++){
                std::vector<bool> neighbors;
                neighbors = {cells[i-1][j-1], cells[i][j-1], cells[i+1][j-1], cells[i-1][j], cells[i+1][j], cells[i-1][j+1], cells[i][j+1], cells[i+1][j+1]};
                if (cells[i][j] == false){
                    if (std::count(neighbors.begin(), neighbors.end(), true) == 3){
                        newcells[i][j] = true;
                        newpat.push_back({i, j});
                    }
                } else {
                    int cnt = std::count(neighbors.begin(), neighbors.end(), true);
                    if (cnt == 2 or cnt == 3){
                        newcells[i][j] = true;
                        newpat.push_back({i, j});
                    }
                }
            }
        }
        if (pat == newpat){
            return pat;
        }
        pat = newpat;
        if (pat.size() == 0){
            return pat;
        }
    }
    return pat;
}
int getpop(std::vector< std::vector<int> > pat){
    return pat.size();
}
std::vector<int> getbbox(std::vector< std::vector<int> > pat){
    int xmin=2147483647; int ymin=2147483647; int xmax=0; int ymax=0;
    for(int i=0; i<pat.size(); i++){
        if (xmin > pat[i][0]){
            xmin = pat[i][0];
        } else if (xmax < pat[i][0]){
            xmax = pat[i][0];
        }
        if (ymin > pat[i][1]){
            ymin = pat[i][1];
        } else if (ymax < pat[i][1]){
            ymax = pat[i][1];
        }
    }
    return {xmin, ymin, xmax - xmin + 1, ymax - ymin + 1};
}
/*std::string getrle(std::vector< std::vector<int> > pat){
    // TODO: sort the celllist vector so that it becomes less expensive to generate the rle
    std::vector<int> bbox = getbbox(pat);
    std::string rle = "x = 0, y = 0, rule = B3/S23\n";
    std::cout << bbox[0] << ", " << bbox[1] << ", " << bbox[2] << ", " << bbox[3] << std::endl;
    for (int y=bbox[1]; y<(bbox[1]+bbox[3]); y++){
        for (int x=bbox[0]; x<(bbox[0]+bbox[2]); x++){
            std::vector<int> val = {x, y};
            if(std::find(pat.begin(), pat.end(), val)!=pat.end()){
                // Found the item
                rle += "o";
                std::cout << x << ", " << y << std::endl;
            } else {
                rle += "b";
            }
        }
        rle += "$";
    }
    rle += "!";
    return rle;
}*/

std::string getrle(std::vector< std::vector<int> > pat, int xmin, int xmax, int ymin, int ymax){
    // TODO: sort the celllist vector so that it becomes less expensive to generate the rle
    // to signal that the bounding box needs to be found, just specify xmin, xmax, ymin, and ymax to be -1
    std::string rle = "x = 0, y = 0, rule = B3/S23\n";
    if (xmin == -1 || xmax == -1 || ymin == -1 || ymax == -1){
        std::vector<int> bbox = getbbox(pat);
        xmin = bbox[0];
        xmax = bbox[0] + bbox[2];
        ymin = bbox[1];
        ymax = bbox[1] + bbox[3];
    }
    bool grid[64][64] = {{false}};
    for (int i=0; i<pat.size(); i++){
        grid[pat[i][0]][pat[i][1]] = true;
        //std::cout << pat[i][0] << ", " << pat[i][1] << std::endl;
    }
    for (int y=ymin; y<ymax; y++){
        for (int x=xmin; x<xmax; x++){
            std::vector<int> val = {x, y};
            if(grid[x][y] == true){
                // Found the item
                rle += "o";
                //std::cout << x << ", " << y << std::endl;
            } else {
                rle += "b";
            }
        }
        rle += "$";
    }
    rle += "!";
    return rle;
}

bool is_stable(std::vector< std::vector<int> > pat){
    //this iterator is very simple, and does not have any optimization over escaping spaceships
    //step_size must be a divisor of gens, or the program might not work properly.
    //limits pattern size to at most 64x64
    //works weirdly when values of the cell list gets close to zero
    int xmin=2147483647; int ymin=2147483647; int xmax=0; int ymax=0;
    bool cells[64][64] = {{false}};
    for(int i=0; i<pat.size(); i++){
        cells[pat[i][0]][pat[i][1]] = true;
        if (xmin > pat[i][0]){
            xmin = pat[i][0];
        } else if (xmax < pat[i][0]){
            xmax = pat[i][0];
        }
        if (ymin > pat[i][1]){
            ymin = pat[i][1];
        } else if (ymax < pat[i][1]){
            ymax = pat[i][1];
        }
    }
    //run the pattern for 1 generation
    //bool newcells[64][64] = {{false}};
    std::vector< std::vector<int> > newpat;
    for(int i=xmin-1; i<xmax+2; i++){
        for(int j=ymin-1; j<ymax+2; j++){
            std::vector<bool> neighbors;
            neighbors = {cells[i-1][j-1], cells[i][j-1], cells[i+1][j-1], cells[i-1][j], cells[i+1][j], cells[i-1][j+1], cells[i][j+1], cells[i+1][j+1]};
            if (cells[i][j] == false){
                if (std::count(neighbors.begin(), neighbors.end(), true) == 3){
                    // cell birth
                    return false;
                }
            } else {
                int cnt = std::count(neighbors.begin(), neighbors.end(), true);
                if (cnt < 2 or cnt > 3){
                    // cell death
                    return false;
                }
            }
        }
    }
    return true;
}
