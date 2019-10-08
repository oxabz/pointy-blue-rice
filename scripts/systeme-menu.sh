#!/bin/bash

confirm() {
    echo -e "Yes\nNo" | rofi -dmenu -i -format d -selected-row 1 -p "${1:-Confirm: }"
}

lock="Lock"
suspend="Suspend"
hibernate="Hibernate"
logout="Logout"
reboot="Reboot"
shutdown="Shutdown"


content="$lock\n$suspend\n$hibernate\n$logout\n$reboot\n$shutdown"

selection=$(echo -e $content | rofi -dmenu -i -markup-rows -p "Action: ")
case $selection in
    $lock)
        i3lock-fancy ;;
    $suspend)
        i3lock-fancy && systemctl suspend ;;
    $hibernate)
        i3lock-fancy && systemctl hibernate ;;
    $logout)
        [[ $(confirm) = 1 ]] && (i3-msg exit) ;;
    $reboot)
        [[ $(confirm) = 1 ]] && (systemctl reboot -i) ;;
    $shutdown)
        [[ $(confirm) = 1 ]] && (systemctl poweroff -i) ;;
esac
