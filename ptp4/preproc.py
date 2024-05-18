import os
import re
from math import *

s = input("Введите какие данные подготовить in/out/ticks: ")
if (s == "in"):
    directory = './data/inside_data/raw_data'
    directory_preproc = './data/inside_data/preproced_data'
if (s == "out"):
    directory = './data/outside_data/raw_data'
    directory_preproc = './data/outside_data/preproced_data'
elif (s == "ticks"):
    directory = './data/inside_ticks_data/raw_data'
    directory_preproc = './data/inside_ticks_data/preproced_data'
files = os.listdir(directory)


for filename in files:
    f = open(f'{directory}/{filename}', 'r')
    average_time, low_q, middle_q, high_q = 0, 0, 0, 0
    mn, mx = inf, -inf
    temp = []
    for line in f:
        temp.append(float(line.strip()))
    temp = sorted(list(map(float, temp)))
    l = len(temp)
    for ind, time in enumerate(temp):
        average_time += time
        mn = min(mn, time)
        mx = max(mx, time)
        if (ind == int(l / 4)):
            low_q = time
        if (ind == int(l / 2)):
            middle_q = time
        if (ind == int(l * 3 / 4)):
            high_q = time
    average_time /= l
    mode = re.search(r'method={(\d+)}', filename).group(1)
    f.close()

    f1 = open(f'{directory_preproc}/{filename}', 'w')
    f1.write(str(average_time) + " " + str(mn) + " " + str(mx) + " " + str(low_q) + " " + str(middle_q) + " " + str(high_q) + " " + str(mode))
    f1.close()


    
    


