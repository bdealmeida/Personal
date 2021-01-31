import re

file = open('/mnt/c/words/english-words/words.txt', 'r')
filelines = file.readlines()

toFind = re.compile('.*stat$')

count = 1
for line in filelines:
    if(toFind.match(line)):
        print(str(count) + '. ' + line, end='')
        count += 1