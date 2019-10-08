# Pointy Blue (My first rice)
![presentation picture](https://github.com/oxabz/spiky-blue-rice/blob/master/Spiky%20Blue.png)
## Introduction
Point Blue is my first i3 rice. 
It was mainly made to train my scripting*. 
Wich mean that the rice might not be the cleanest.
It might also be broken.
## Content
### Controls
|key|action|
|--|--|
|mod+shift+q|kill program|
|alt+q|kill program|
|alt+F4|kill program|
|mod+return|launch term|
|mod+d|dmenu|

moving between windows can be done by pression mod+[UP/DOWN/LEFT/RIGHT/i/k/j/l] or by swiping three finger up/down/left/right
moving windows can be done by pression mod+shift+[UP/DOWN/LEFT/RIGHT/i/k/j/l] or by swiping four finger up/down/left/right

The cursor should follow the focussed window.
### Bar 
#### Info Menu 
allow you to choose between seeing particion space, coretemp and bluetooth (more comming later).
#### Wifi Indicator
show the current wifi and show a wifi menu on click
#### Update Indicator
Number of unupdated package of arch
#### Systeme Monitor
Show the core usage and memory usage (format can be modified by editing the python scripr)
#### Volume and Backlight
pretty self explanatory
#### Battery indicator
self explenatory but goes yellow when the battery is under 15
## dependencies 
- wm : i3-gaps(obviously)
- app launcher : rofi
- bar : polybar
- Terminal : urxvt
- A wallpaper manager : feh, variety ...
- touchpad gesture : libinput-gesture
- backlight gestion : light
- file explorer : ranger 
- shell : ZSH
- text editor : vim (spacevim)
- cursor centering : xdotool
- bluetooth : bluez bluez-utils
## Install
copy the content of the git directly into your home folder
