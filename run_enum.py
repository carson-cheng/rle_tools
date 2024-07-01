# a script to 
# 1) generate the enumeration rles, (from still lifes, maybe even oscillators in the future)
# 2) add the rles into the c++ file and compile, and 
# 3) run apgsearch on the enumeration
import lifelib, os, requests
sess = lifelib.load_rules('b3s23')
lt = sess.lifetree(n_layers=1)
# first, get apgcodes from the glider syntheses textcensus (note: only works for 21 bits or below, request apgcodes from someone else for higher bit counts)
# for pseudo still lifes and constellations, run through the synthesis costs without the cost filter; but impose a bounding box limit(?)
pats2 = []
for item in range(23, 24):
    url = "https://catagolue.hatsya.com/textcensus/b3s23/synthesis-costs/xs" + str(item)
    contents = requests.get(url).text
    for item in contents.split("\n")[1:-1]:
        cost = int(item.split('","')[1].split('"')[0])
        if cost > 100000000000000000:
            # true object
            apgcode = item.split('","')[0].split('"')[1]
            pats2.append(apgcode)
            #print(apgcode)
#pats = [lt.pattern(rle) for rle in pats]
pats = []
for item in pats2:
    print(item)
    pats.append(lt.pattern(item))
print("Lst comprehension")
def generate_transformations(pat):
    # use a phase difference of up to 8 generations, and use all 8 transformations
    patterns = []
    patterns += [pat, pat("rot270"), pat("rot180"), pat("rot90"), pat("flip_x"), pat("flip_y"), pat("swap_xy"), pat("swap_xy_flip")]
    return patterns
patterns = []
for item in pats:
    patterns += generate_transformations(item)
    print("Gen transformations")
string = ""
print(len(patterns))
count = 0
for item in patterns:
    finalrle = ""
    rlepart = item.rle_string().split("\n")[2:]
    for item in rlepart:
        finalrle += item
        if "!" in item:
            break
    string += (finalrle + "\n")
    count += 1
    print(count)
string = string[:-1]
with open("rles2.txt", "w") as wf:
    wf.write(string)
# construct c++ file based on the resultant string
# read c++ file
cmd = "g++ -o genseed_enum genseed_enum.cpp -O3 -std=c++11"
print(cmd)
os.system(cmd)
# run apgsearch
newdir = "../test/apgmera_clean_universal"
print(newdir)
os.chdir(newdir)
cmd = "../../rle_tools/genseed_enum | ./apgluxe -n 1000000 -L 1 -i 100 -t 1"
print(cmd)
os.system(cmd)