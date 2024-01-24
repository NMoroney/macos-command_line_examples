
## macOS : Command Line Examples - *Armadillo (fit sphere)*

[Armadillo](https://arma.sourceforge.net) is a linear algebra library and is used by the [ensmallen](https://ensmallen.org) and [mlpack](https://www.mlpack.org) libraries.

This example uses armadillo to fit a 3D sphere to a set of input 3D points.

First, random points are generated on a sphere surface according to [this answer](https://math.stackexchange.com/questions/1585975/how-to-generate-random-points-on-a-sphere).

This sampling is then jittered, scaled and offset to yield a set of 3D points to fit a sphere to.

For this fitting process, [this code](https://paulbourke.net/geometry/circlesphere/spheretest.c) to fit a sphere to 4 points was combined with the [Thiel-Sen estimator](https://en.wikipedia.org/wiki/Theil–Sen_estimator).

That is for 1000 fits, randomly select 4 points and compute the corresponding center and radius of the sphere. Take the median of the fitted centers and radii as the fitted sphere.

```
samples size : 500
number fits  : 1000

center fit : 2.87249 4.05532 4.97395
radius fit : 10.6013
```

A MeshLab visualization of the 3d points and the fitted sphere is below :

<img src="armadillo-thiel-sen_fit_sphere_to_points_3d.jpg" width=500px>

---

median, upwards thumb


