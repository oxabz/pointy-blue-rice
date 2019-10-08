import subprocess
import colorscheme
import polybarfunct

discharging_chars = ''
charging_char = ''
lowBaterry = 10


def getPercentage() :
    unprocessed = subprocess.check_output('acpi | cut --delimiter="," -f 2', shell=True)
    unprocessed = str(unprocessed)[2:len(unprocessed)]
    return int(unprocessed)


def isCharging() :
    try:
        unprocessed = subprocess.check_output('acpi | grep Charging', shell=True)
        return True
    except:
        return False


def format():
    if (isCharging()):
        res = charging_char+' '+str(getPercentage())+'%'
    else:
        res = discharging_chars[int(getPercentage()*len(discharging_chars)/100)-1]+' '+str(getPercentage())+'%'
    return res

def coloredFormat():
    if lowBaterry >= getPercentage() :
        return polybarfunct.setColor(format(),colorscheme.colorNope,colorscheme.colorYah)
    else:
        return polybarfunct.setColor(format(),colorscheme.colorLevel4,colorscheme.colorLevel1)


out = coloredFormat()
if getPercentage()<=lowBaterry and not isCharging():
    out = polybarfunct.getSeparator('',colorscheme.colorYah,colorscheme.colorLevel1)+out
else:
    out = polybarfunct.getSeparator('|',colorscheme.colorLevel4,colorscheme.colorLevel1)+out
print(out)

