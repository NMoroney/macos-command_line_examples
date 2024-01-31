
## macOS : Command Line Examples - *Point Cloud Library (Filter Outliers)*

This example reads the vertices of an input mesh using [happly](https://github.com/nmwsharp/happly).

The [Point Cloud Library](https://pointclouds.org) or PCL (version 1.13.1) is used to find the bounding box of the vertices.

Random points are then generated within this box and added to the vertices point cloud.

Finally, the PCL [outliers filter](https://pointclouds.org/documentation/tutorials/statistical_outlier.html) is applied.

The result below shows the outliers as orange.

<img src="pcl-filter_outliers.jpg" width=500px>

Note that with the filter settings, some of the tricerotops horn tips are also selected as outliers.

---

PCL was installed with ```brew install pcl``` - this also installs ```qt``` and ```VTK```.

