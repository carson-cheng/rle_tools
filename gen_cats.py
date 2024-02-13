import lifelib
sess = lifelib.load_rules('b3s23')
lt = sess.lifetree(n_layers=1)
#pats = ["xs4_33", "xs6_696", "xs7_2596", "xs5_253", "xs6_356", "xs6_bd", "xs6_39c"]
pats = ["xs4_33", "xs6_696", "xs7_2596"]
#pats = ["xs4_33", "xs7_2596", "xs6_696", "xs7_25ac", "xs7_178c", "xs8_6996", "xs6_39c", "xs7_3lo", "xs6_356", "xs5_253", "xs8_3pm", "xs4_33", "xs4_33", "xs6_696", "xs6_bd", "xs6_25a4", "xs8_35ac", "xs9_178ko", "xs9_4aar", "xs12_raar", "xs10_32qr", "xs12_178br", "xs8_32qk", "xs9_31ego"]
pats = [lt.pattern(rle) for rle in pats]
def generate_transformations(pat):
    # use a phase difference of up to 8 generations, and use all 8 transformations
    patterns = []
    patterns += [pat, pat("rot270"), pat("rot180"), pat("rot90"), pat("flip_x"), pat("flip_y"), pat("swap_xy"), pat("swap_xy_flip")]
    return patterns
patterns = []
for item in pats:
    patterns += generate_transformations(item)
string = "std::vector<std::string> cats_comp = {"
for item in patterns:
    finalrle = ""
    rlepart = item.rle_string().split("\n")[2:]
    for item in rlepart:
        finalrle += item
        if "!" in item:
            break
    string += ('"' + finalrle + '", ')
string = string[:-2]
string += "};"
print(string)
