
## macOS : Command Line Examples - *PCL Viewer (Depth GIFs)*

This example builds directly on the previous [Point Cloud Library (PCL) example ](../mc_22_pcl/).

By installing PCL the [Visualization Toolkit (VTK)](https://vtk.org) is also installed.

Unlike previous examples, having VTK installed allows the creation of interactive examples or a basic UI.

The following example creates a color point cloud viewer for MiDaS depth estimated images.

The image below (["Hello" by XU ZHEN®](https://news.stanford.edu/2022/02/04/new-sculpture-lip-meyer-green-greets-passersby/), photo by n8) is used as the input :

<img src="IMG_7884-hello-640px.jpg" width=400px> 

The PyTorch [MiDaS edpth estimation example](../mc_19_pytorch_midas/) yields the depth estimates below :

<img src="IMG_7884-hello-640px_depth.jpg" width=400px>

OpenCV is used to read the color and depth images for this example.

An XYZRGB point cloud is created and a corresponding viewer yields the following :

<img src="pcl-color_cloud_viewer-midas_depth_estimated.jpg" width=400px>

Cool! But can we get a GIF to demo the depth effect?



