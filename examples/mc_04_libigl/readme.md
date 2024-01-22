
## macOS : Command Line Examples - *libigl (blue noise surface sampling)*

The [libigl](https://libigl.github.io) is a header only geometry processing library ([version 2.5.0](https://github.com/libigl/libigl) was used).

Like Eigen, the previous example which is required by libigl, this library can be downloaded and linked against without making from source.

For this example, the dependencies were not downloaded and the exercise was to [blue noise sample](https://libigl.github.io/tutorial/#blue-noise-surface-sampling) a mesh surface.

The image result shows a mesh with 5,000 points sampled over the surface. 

<img src="libigl_blue_noise_sample_surface.jpg" width=500px>

This [source](libigl_blue_noise.cc) was compiled with this [Makefile](Makefile) (update the paths to libigl and Eigen installation locations).

The above point cloud visualization was created using [MeshLab](https://www.meshlab.net) version 2022.02.

booyah
