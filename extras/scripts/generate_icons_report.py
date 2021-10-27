import os

data = ""
with open("src/utility/pixie_icons.h", "r+") as f:
    data = f.read()

keywords = ""
with open("keywords.txt", "r+") as f:
    keywords = f.read()

data = data.split("\n")

miss_list = ""
bad_icons = []

for item in data:
    if "PROGMEM " in item:
        icon_name = item.split("PROGMEM ")[1].split("[")[0]
        
        if not icon_name in keywords:
            print("ICON: "+icon_name)
            miss_list += "- :x: *Icon ***"+icon_name+"*** is not documented as a LITERAL1 in keywords.txt!*\n"
            bad_icons.append(icon_name)

output_string = "### Icon coverage report: \n#### Any undocumented Icons currently seen will appear here after every CI test!\n---------------------------------------------------------\n"

if len(miss_list) == 0:
    output_string += ":heavy_check_mark: **All checks passed, nothing left undocumented!**"
else:
    output_string += miss_list
    output_string += "\n\nTo fix, append the following to the LITERAL1 section of keywords.txt:\n\n"

    for item in bad_icons:
        output_string += "    "+item + "\t" + "LITERAL1\n"

with open("extras/reports/icons/README.md","w+") as f:
    f.write(output_string)
   
print("--- Report saved in extras/reports/icons/README.md")
