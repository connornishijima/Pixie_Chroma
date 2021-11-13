import time
import os

data = []
with open("pixie_icons.h","r+") as f:
    data = f.read().split('\n');

for item in data:
    if "PROGMEM" in item:
        item = item.split(" ")
        name = item[3]
        
        name = name.replace("ICON_","").split("[")[0]
        columns = item[5].replace("{", "").replace("};", "")
        
        out_string = "/* [:"+name+":]"
        while len(out_string) < 24:
            out_string += " "
        out_string += " */ "

        out_string += columns
        out_string += ", 255, "
        
        for i in range(len(name)):
            out_string += "'"
            out_string += name[i]
            out_string += "',"
            
        out_string += " 0,"
        
        print(out_string);