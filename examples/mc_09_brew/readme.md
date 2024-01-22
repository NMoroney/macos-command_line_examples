
## macOS : Command Line Examples - *brew (iceberg surface)*

[Homebrew](https://en.wikipedia.org/wiki/Homebrew_(package_manager)) is a package manager that can be used with macOS.

Installation instructions are on the [homebrew webpage](https://brew.sh). The main program to manage packages is ```brew```.

The ```brew``` tool can be used in a manner similar to the [apt-get](https://en.wikipedia.org/wiki/APT_(software)) program for linux.

Once installed, the version number can be checked using :

```
% brew --version
Homebrew 4.1.24
```

To install a package, for example [wget](https://en.wikipedia.org/wiki/Wget), simply use :

```
brew install wget
```

Once ```wget``` (1.21.4) is installed you can test using it to download an image file given a url.

```
get https://upload.wikimedia.org/wikipedia/commons/thumb/a/a0/The_underwater_surface_structures_of_an_iceberg_in_Svalbard.jpg/440px-The_underwater_surface_structures_of_an_iceberg_in_Svalbard.jpg
```

<img src="440px-The_underwater_surface_structures_of_an_iceberg_in_Svalbard.jpg">

To see all the installed packages use :

```
% brew list
```

Information about the versions can be obtained using the ```list --version``` option.

---

Homebrew can streamline more complex library installations. 

For example, instead of building opencv from scratch like was done in an earlier example the following could have been used :

```
% brew install opencv
```

Details about the installation can be found on the corresponding [webpage](https://formulae.brew.sh/formula/opencv). Note the **Depends** table lists additional packages that will be installed with opencv.






