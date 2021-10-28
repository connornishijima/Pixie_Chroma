# This hacky script finds functions not currently covered by keywords.txt, which will not get nice syntax highlighting.

from pathlib import Path
import json

types = [
    "void",
    "bool",
    "uint8_t",
    "uint16_t",
    "uint32_t",
    "int8_t",
    "int16_t",
    "int32_t",
    "float",
    "double",
    "char",
]

keywords = {}
ignore = {}

with open("extras/scripts/ignore_keywords.json","r+") as f:
    ignore = json.loads(f.read())

for path in Path('src').rglob('*.h'):
    hfile = path
    with open(str(hfile),"r") as f:
        data = f.read().split("\n")
                
        for line in range(len(data)):
            line = data[line].split(" ")
            for word in range(len(line)):
                item = line[word]
                if "(" in item:
                    type = line[word-1]
                    if type in types:
                        keyword = item.split("(")[0]
                        if len(keyword) >= 2:
                            if not keyword in ignore["ignore"]:
                                keywords[keyword] = {}

output = ""
bad_keywords = []

with open("keywords.txt","r+") as f:
    kw = f.read()
    for item in keywords:
        if not item in kw:
            output += "- :x: "
            output += "***" + str(item) + "*** not in keywords.txt!"
            bad_keywords.append(str(item))
            output += "\n"

final_output = output.split("\n")
            
output_string = "### Keyword coverage report: \n#### Any undocumented keywords currently seen will appear here after every CI test!\n---------------------------------------------------------\n"

if len(output) == 0:
    output_string += ":heavy_check_mark: **All checks passed, nothing left undocumented!**"
else:
    output_string += ("\n".join(final_output))
    output_string += "\n\nTo fix, append the following to the KEYWORD2 section of keywords.txt:\n\n"

    for item in bad_keywords:
        output_string += "    "+item + "\t" + "KEYWORD2\n"

with open("extras/reports/keywords/README.md","w+") as f:
    f.write(output_string)

   
print("--- Report saved in extras/reports/keywords/README.md")
