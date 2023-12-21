#!/bin/sh
# Ref: https://www.imagemagick.org/discourse-server/viewtopic.php?t=32068

# 绘制一个圆，分成8个伞形，背景white，线条black
#convert -size 100x100 xc:white -stroke black \
#    -fill gray   -draw "path 'M 50,50 L 50,0        A 50,50 0 0,1 85.36,14.64 Z'" \
#    -fill white  -draw "path 'M 50,50 L 85.36,14.64 A 50,50 0 0,1 100,50      Z'" \
#    -fill gray   -draw "path 'M 50,50 L 100,50      A 50,50 0 0,1 85.36,85.36 Z'" \
#    -fill white  -draw "path 'M 50,50 L 85.36,85.36 A 50,50 0 0,1 50,100      Z'" \
#    -fill gray   -draw "path 'M 50,50 L 50,100      A 50,50 0 0,1 14.64,85.36 Z'" \
#    -fill white  -draw "path 'M 50,50 L 14.64,84.36 A 50,50 0 0,1 0,50        Z'" \
#    -fill gray   -draw "path 'M 50,50 L 0,50        A 50,50 0 0,1 14.64,14.64 Z'" \
#    -fill white  -draw "path 'M 50,50 L 14.64,14.64 A 50,50 0 0,1 50,0        Z'" \
#    piechart_1.png

# 绘制一个圆，分成8个伞形，背景透明，无边缘线条
#convert -size 100x100 xc:none -stroke none \
#    -fill 'rgba(255, 0, 0, 0.5)'  -draw "path 'M 50,50 L 50,0        A 50,50 0 0,1 85.36,14.64 Z'" \
#    -fill 'rgba(0, 255, 0, 0.5)'  -draw "path 'M 50,50 L 85.36,14.64 A 50,50 0 0,1 100,50      Z'" \
#    -fill 'rgba(0, 0, 255, 0.5)'  -draw "path 'M 50,50 L 100,50      A 50,50 0 0,1 85.36,85.36 Z'" \
#    -fill white  -draw "path 'M 50,50 L 85.36,85.36 A 50,50 0 0,1 50,100      Z'" \
#    -fill gray   -draw "path 'M 50,50 L 50,100      A 50,50 0 0,1 14.64,85.36 Z'" \
#    -fill white  -draw "path 'M 50,50 L 14.64,84.36 A 50,50 0 0,1 0,50        Z'" \
#    -fill gray   -draw "path 'M 50,50 L 0,50        A 50,50 0 0,1 14.64,14.64 Z'" \
#    -fill white  -draw "path 'M 50,50 L 14.64,14.64 A 50,50 0 0,1 50,0        Z'" \
#    piechart_2.png

# 绘制一个圆环，分成4段，背景透明，无边缘线条
#convert -size 100x100 xc:none -stroke none \
#    -fill 'rgba(255, 0, 0, 0.5)'  -draw "path 'M 50,0       A 50,50 0 0,1 100,50 L 75,50 A 25,25 0 0,0 50,25 Z'" \
#    -fill 'rgba(0, 255, 0, 0.5)'  -draw "path 'M 100,50     A 50,50 0 0,1 50,100 L 50,75 A 25,25 0 0,0 75,50 Z'" \
#    -fill 'rgba(0, 0, 255, 0.5)'  -draw "path 'M 50,100     A 50,50 0 0,1 0,50   L 25,50 A 25,25 0 0,0 50,75 Z'" \
#    -fill 'rgba(0, 255, 0, 0.5)'  -draw "path 'M 0,50       A 50,50 0 0,1 50,0   L 50,25 A 25,25 0 0,0 25,50 Z'" \
#    piechart_3.png

# 绘制一个圆环，分成8段，背景透明，无边缘线条
convert -size 200x200 xc:none -stroke none \
    -fill 'rgba(100, 100, 100, 0.5)'  -draw "path 'M 100,0        A 100,100 0 0,1 170.71,29.29   L 135.36,64.64  A 50,50 0 0,0 100,50 Z'" \
    -fill 'rgba(50, 50, 50, 0.5)'  -draw "path 'M 170.71,29.29 A 100,100 0 0,1 200,100        L 150,100       A 50,50 0 0,0 135.36,64.64 Z'" \
    -fill 'rgba(100, 100, 100, 0.5)'  -draw "path 'M 200,100       A 100,100 0 0,1 170.71,170.71 L 135.36,135.36 A 50,50 0 0,0 150,100 Z'" \
    -fill 'rgba(50, 50, 50, 0.5)'  -draw "path 'M 170.71,170.71 A 100,100 0 0,1 100,200       L 100,150       A 50,50 0 0,0 135.36, 135.36 Z'" \
    -fill 'rgba(100, 100, 100, 0.5)'  -draw "path 'M 100,200      A 100,100 0 0,1 29.29,170.71   L 64.64,135.36  A 50,50 0 0,0 100,150 Z'" \
    -fill 'rgba(50, 50, 50, 0.5)'  -draw "path 'M 29.29,170.71 A 100,100 0 0,1 0,100          L 50,100        A 50,50 0 0,0 64.64,135.36 Z'" \
    -fill 'rgba(100, 100, 100, 0.5)'  -draw "path 'M 0,100        A 100,100 0 0,1 29.29,29.29    L 64.64,64.64   A 50,50 0 0,0 50,100 Z'" \
    -fill 'rgba(50, 50, 50, 0.5)'  -draw "path 'M 29.29,29.29  A 100,100 0 0,1 100,0          L 100,50        A 50,50 0 0,0 64.64,64.64 Z'" \
    -fill 'rgba(100, 100, 100, 0.5)'  -draw "circle 100,100 70,70" \
    weapon_wheel_2.png
