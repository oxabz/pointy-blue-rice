def setColor(string, fgColor, bgColor):
    return '%{B'+str(bgColor)+'}%{F'+str(fgColor)+'}'+str(string)+'%{B- F-}'

def getSeparator(separator, fgColor, bgColor):
    return '%{T2}%{B'+str(bgColor)+'}%{F'+str(fgColor)+'}'+str(separator)+'%{B- F- T-}'