import os

for item in os.listdir("scripts"):
    if "generate" in item and not "overview" in item:
        print(item)

#with open("reports/doxygen/README.md","r+") as f:
#    if ":x:" in f.read():
#        doxy_pass = False