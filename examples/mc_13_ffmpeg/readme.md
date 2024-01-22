
## macOS : Command Line Examples - *FFmpeg (boomerang gifs)*

[FFmpeg](https://ffmpeg.org) is a multimedia framework that provides a range of tools for working with videos.

To [install FFmpeg](https://formulae.brew.sh/formula/ffmpeg) the following can be used : ```brew install ffmpeg```.

First can check the version :

```
ffmpeg -version
ffmpeg version 6.0
```

Then download a gif, for example [a rotating earth](https://commons.wikimedia.org/wiki/File:Rotating_earth_(large).gif) from wikipedia.

A boomerang effect can then be applied :

```
GIF=rotating_earth.gif

boomerang :
        ffmpeg -i $(GIF) -filter_complex "[0]fps=12,scale=128:-1:flags=lanczos,split[main][reverse];[reverse]reverse[r];[main][r]concat=n=2:v=1:a=0,split[s0][s1];[s0]palettegen[p];[s1][p]paletteuse" rotating_earth_boomerang.gif
```

<img src="rotating_earth_boomerang.gif">

---

* a [FFmpeg cheat sheet](https://gist.github.com/steven2358/ba153c642fe2bb1e47485962df07c730) for more ideas.


