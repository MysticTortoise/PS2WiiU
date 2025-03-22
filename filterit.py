
with open("filteredwiiulogsrc.txt", "r") as file:
    lines = [line.rstrip() for line in file]

with open("filteredwiiulog.txt", "w") as file:
    for line in lines:
        if line[15:27] == "[OSConsole] ":
            file.write(line[27:] + "\n")
        
