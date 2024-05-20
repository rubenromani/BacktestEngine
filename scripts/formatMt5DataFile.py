import os 
import datetime
import time

def parse(inpath, outpath):
    in_path = inpath
    out_path = outpath
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
        try:
            tmp[1] = str(int(time.mktime(datetime.datetime.strptime(tmp[0].strip() + " " + tmp[1].strip(),"%Y.%m.%d %H:%M:%S").timetuple())))
        except:
            tmp[1] = str(int(time.mktime(datetime.datetime.strptime(tmp[0].strip(),"%Y.%m.%d").timetuple())))
        tmp = tmp[1:]
        result.append(','.join(tmp))
    with open(out_path, "w") as text_file:
        text_file.write('\n'.join(result))

def main():
    timeframes = [
        "M1",
        "M5",
        "M10",
        "M15",
        "M30",
        "H1",
        "H4",
        "Daily",
        "Weekly",
        "Monthly"
    ]

    symbols = [
        "AUDUSD",
        "EURUSD",
        "GBPUSD",
        "USDCAD",
        "USDCHF",
        "USDJPY",
    ]

    for timeframe in timeframes:
        for symbol in symbols:
            inpath = '../data/'+ symbol + '_' + timeframe + '.csv'
            outpath = '../data/'+ symbol + '_' + timeframe + '_pars.csv'
            parse(inpath,outpath)


if __name__=="__main__":
    main()