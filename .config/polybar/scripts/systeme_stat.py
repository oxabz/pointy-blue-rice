import psutil
import math


usage_bars = '▁▂▃▄▅▆▇'
forma = ' cpu %Pcpu %Bcpus |  memory %Pmem %Bmem'

def getCPUUsage():
    t = psutil.cpu_percent(interval=0.1, percpu=True)
    le = len(t)
    res = 0
    for i in range(0,le):
        res += t[i]
    return res/le


def getCPUUsages():
    return psutil.cpu_percent(interval=0.1, percpu=True)

def getRAMUsagePercent():
    return psutil.virtual_memory().percent


def getSWAPUsagePercent():
    return psutil.swap_memory().percent


def getMemoryUsagePercent():
    return (psutil.virtual_memory().percent+psutil.swap_memory().percent)/2


def getBars(percent):
    return usage_bars[math.trunc((len(usage_bars)-1) * percent / 100)]


def getMultiCoreBar():
    res = ''
    val = getCPUUsages()
    for i in val :
        res += getBars(i)
    return res


def format(forma):
    forma = forma.replace('%Pcpu', str(int(getCPUUsage()))+'%')
    forma = forma.replace('%Bcpus', getMultiCoreBar())
    forma = forma.replace('%Bcpu', "%{T3}"+getBars(getCPUUsage())+"%{T-}")
    forma = forma.replace('%Bmem', "%{T3}"+getBars(getMemoryUsagePercent())+"%{T-}")
    forma = forma.replace('%Pmem', str(int(getMemoryUsagePercent()))+'%')
    forma = forma.replace('%Bram', "%{T3}"+getBars(getRAMUsagePercent())+"%{T-}")
    forma = forma.replace('%Pram', str(int(getRAMUsagePercent()))+'%')
    forma = forma.replace('%Bswap', "%{T3}"+getBars(getSWAPUsagePercent())+"%{T-}")
    forma = forma.replace('%Pswap', str(int(getSWAPUsagePercent())) + '%')
    return forma


print(format(forma))
