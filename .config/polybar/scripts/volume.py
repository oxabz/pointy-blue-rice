import subprocess

muted_char = 'ﱝ'
volume_chars = '奄奔墳'

def getPercentage() :
    unprocessed = subprocess.check_output(' amixer get Master |  cut --delimiter="[" --only-delimited --fields=2', shell=True)
    begin = str(unprocessed).find('\'')
    end = str(unprocessed).find(']')
    return int(str(unprocessed)[begin+1:end-1])


def isMuted() :
    unprocessed = subprocess.check_output(' amixer get Master |  cut --delimiter="[" --only-delimited --fields=3', shell=True)
    begin = str(unprocessed).find('\'')
    end = str(unprocessed).find(']')
    processed =str(unprocessed)[begin+1:end]
    return processed == 'off'

def format():
    if isMuted() :
        return muted_char+' -%'
    else:
        return volume_chars[int(max(getPercentage(),100)*len(volume_chars)/100-1)] + '' + str(getPercentage()) + '%'


print(format())
print(isMuted())
print(getPercentage())