set confirm off

target ext :3333
b base.cpp:125
monitor reset init
p us_count
exit
