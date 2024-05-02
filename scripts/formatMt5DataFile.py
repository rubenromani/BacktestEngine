import os 
import datetime
import time

def main():
    in_path = '../data/AUDUSD_M1.csv'
    out_path = '../data/AUDUSD_M1_pars.csv'
    data=''
    with open(in_path) as f:
        data = f.read()
    data = data.split('\n')[1:]
    result = []
    nline = 0
    for line in data:
        if line == '':
            continue
        nline+=1
        tmp = line.split('\t')
        tmp[1] = str(int(time.mktime(datetime.datetime.strptime(tmp[0].strip() + " " + tmp[1].strip(),"%Y.%m.%d %H:%M:%S").timetuple())))
        tmp = tmp[1:]
        result.append(','.join(tmp))
    with open(out_path, "w") as text_file:
        text_file.write('\n'.join(result))

if __name__=="__main__":
    main()