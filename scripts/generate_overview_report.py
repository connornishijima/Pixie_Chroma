import os

report = {}

for item in os.listdir("scripts"):
    if "generate" in item and not "overview" in item:
        report_type = item.split("_")[1]
        report[report_type] = True
        
        with open("reports/"+report_type+"/README.md","r+") as f:
            if ":x:" in f.read():
                report[report_type] = False

output = ""

output += "### Library status report: \n"
output += "#### Any undocumented objects currently seen after every CI test will be marked here.\n"
output += "---------------------------------------------------------\n"

for item in report:
    pass_state = report[item]
    icon = ":x:"
    if pass_state == True:
        icon = ":heavy_check_mark:"
    item = item.title()
    output += "- "+icon+" "+item+"\n"
    
print(output)