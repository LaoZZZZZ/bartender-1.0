#!/usr/bin/python

f = 'table_file.txt'

l = 0;
part1 = open('barcode_1.csv','w')
part2 = open('barcode_2.csv', 'w') 
for line in open(f,'r'):
	parts = line.split()
	part1.write(parts[3] + '\n')
	part2.write(parts[4] + '\n')	
part1.close()
part2.close()
