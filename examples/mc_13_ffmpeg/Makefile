# © 2024 : github.com/NMoroney
# MIT License 
#

#
# * https://commons.wikimedia.org/wiki/File:Rotating_earth_(large).gif
#

copy_gif :
	curl -o rotating_earth.gif https://upload.wikimedia.org/wikipedia/commons/2/2c/Rotating_earth_%28large%29.gif

version :
	ffmpeg -version

GIF=rotating_earth.gif

boomerang :
	ffmpeg -i $(GIF) -filter_complex "[0]fps=12,scale=128:-1:flags=lanczos,split[main][reverse];[reverse]reverse[r];[main][r]concat=n=2:v=1:a=0,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse" rotating_earth_boomerang.gif


