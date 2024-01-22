
## macOS : Command Line Examples - *pip3 (simplex noise)*

This example is actually an extension of the first example ([hello world](../mc_01_hello_world/)).

When installing ```g++``` (and ```python3```) from the pop-up window prompt other tools, such as ```pip3```, are also installed.

To see everything installed, from the terminal list the contents of the following directory :

```
ls /Library/Developer/CommandLineTools/usr/bin/
```

Pip is a Python package manager and as an already installed tool, it is used in this and other examples.

For example, to install the [opensimplex](https://pypi.org/project/opensimplex/) package, type the following in the terminal :

```
pip3 install opensimplex
```

This should perform a user installation (as opposed to adding to site-packages). 

After installing [pillow](https://pypi.org/project/pillow/) the included [python](simplex_to_png.py) can be used to generate 2D [simplex noise](https://en.wikipedia.org/wiki/Simplex_noise).


The resulting simplex noise as a grayscale image :

<img src="simplex_noise_2d.jpg" width=500px>

---

To get the version for pip3 use this option :

```
% pip3 --version
pip 21.2.4
```
To list the installed packages and their version numbers use :

```
% pip3 list
Package             Version
------------------- ----------
the_package         0.1.2
```

