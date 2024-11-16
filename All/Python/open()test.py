import sys
print(sys.path)

ftext = open('123.txt', 'w',encoding='utf-8')
s='ABCDE'
ftext.write(s)
ftext.close()

ftext = open('123.txt', 'r',encoding='utf-8')
s=ftext.read()
print(s)
ftext.close()