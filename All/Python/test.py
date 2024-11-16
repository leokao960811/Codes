import json
import csv

with open('D:\Programmed Files\Python\\test2.json', mode='w', encoding='utf-8') as file:
    data = {"key": 'date', "value": 1023}
    json.dump(data, file)

with open('D:\Programmed Files\Python\\test2.json', mode='r', encoding='utf-8') as file:
    data = json.load(file)
print("test2.json data: ")
print(data)

ftext = open('D:\Programmed Files\Python\\test.txt', 'w',encoding='utf-8')
s='I HAVE COME.'
ftext.write(s)
ftext.close()

ftext = open('D:\Programmed Files\Python\\test.txt', 'r',encoding='utf-8')
s=ftext.read()
print(s)
ftext.close()

table = [ [1, 2, 3], [4, 5, 6], [7, 8, 9] ]
with open('D:\Programmed Files\Python\\test.csv', 'wt', newline='', encoding='utf-8') as csvfile:
    writer = csv.writer(csvfile, delimiter=',')
    writer.writerows(table)

with open('D:\Programmed Files\Python\\test.csv', 'r', newline='', encoding='utf-8') as csvfile:
    rows = csv.reader(csvfile)
    for row in rows:
        print(row)