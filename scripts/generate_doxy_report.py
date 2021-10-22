import time
import os

print("Generating report from Doxygen log contents...")

doxy_data = ""
with open("docs/doxy.log","r+") as f:
    doxy_data = f.read().split("\n")

output = "### Doxygen coverage report: \n#### Any undocumented objects currently seen by Doxygen will appear here after every CI test!\n\n"

for item in doxy_data:
    print(item)
    if "parameter '" in item:
        log_string = item.split("parameter ")[1]
        output += "  "
        output += log_string
        output += "\n"
        
    elif "warning" in item:
        if "is not documented" in item:
            if not "ICON_" in item:
                log_string = item.split("warning: ")[1]
                output += "- "
                output += log_string
                output += "\n"

with open("reports/doxygen/README.md","w+") as f:
    f.write(output)
   
print("--- Report saved in reports/doxygen/README.md")