
## macOS : Command Line Examples - *stable diffusion cpp*

The [stable-diffusion.cpp](https://github.com/leejet/stable-diffusion.cpp) repository is Stable Diffusion in pure C/C++.

First, download the source :

```
git clone --recursive https://github.com/leejet/stable-diffusion.cpp
```

Then create and enter build directory :

```
cd stable-diffusion.cpp
mkdir build
cd build
```

Had already installed openblas but for other reasons built without :

```
cmake .. -DGGML_OPENBLAS=OFF
cmake --build . --config Release
```

And download the weights, in this case version 1.4 :

```
curl -L -O https://huggingface.co/CompVis/stable-diffusion-v-1-4-original/resolve/main/sd-v1-4.ckpt
```

And then run for a given prompt :

```
% ./sd -m sd-v1-4.ckpt -p "a willow tree at sunset"
[INFO]  stable-diffusion.cpp:4295 - loading model from 'sd-v1-4.ckpt'
[INFO]  model.cpp:626  - load sd-v1-4.ckpt using checkpoint format
[INFO]  stable-diffusion.cpp:4317 - Stable Diffusion 1.x
[INFO]  stable-diffusion.cpp:4323 - Stable Diffusion weight type: f32
[INFO]  stable-diffusion.cpp:4477 - total memory buffer size = 2722.37MB (clip 470.66MB, unet 2156.24MB, vae 95.47MB)
[INFO]  stable-diffusion.cpp:4479 - loading model from 'sd-v1-4.ckpt' completed, taking 16.41s
[INFO]  stable-diffusion.cpp:4493 - running in eps-prediction mode
[INFO]  stable-diffusion.cpp:5262 - apply_loras completed, taking 0.00s
[INFO]  stable-diffusion.cpp:5291 - get_learned_condition completed, taking 369 ms
[INFO]  stable-diffusion.cpp:5301 - sampling using Euler A method
[INFO]  stable-diffusion.cpp:5305 - generating image: 1/1 - seed 42
  |==================================================| 20/20 - 49.63s/it
[INFO]  stable-diffusion.cpp:5317 - sampling completed, taking 964.10s
[INFO]  stable-diffusion.cpp:5325 - generating 1 latent images completed, taking 964.34s
[INFO]  stable-diffusion.cpp:5327 - decoding 1 latents
[INFO]  stable-diffusion.cpp:5335 - latent 1 decoded, taking 98.39s
[INFO]  stable-diffusion.cpp:5339 - decode_first_stage completed, taking 98.39s
[INFO]  stable-diffusion.cpp:5346 - txt2img completed in 1063.10s
[INFO]  main.cpp:501  - save result image to 'output.png'
```

<img src="sd-a_willow_tree_at_sunset.jpg" width=400px>

```
A willow tree at sunset : Stable Diffusion 1.4
```

---

The above steps are pretty straightforward (it will take up +1 GB of memory for the weights) but still why run stable diffusion on your laptop instead of someone else's computer?

For me one major advantage is ease of integration with other libraries and software tools.

Below shows a result for a stable diffusion sent directly to the [MiDaS depth estimation](../mc_19_pytorch_midas/) and then [FFmpeg](../mc_13_ffmpeg/) for visualization of corresponding features in the two images.

<img src="stable_diffusion_then_depth_estimation.gif" width=400px>

```
A red and green coffee mug on a cafe table : Stable Diffusion 1.4
```

The automatically animated overlay really helps me notice more details about both the stable diffusion and the depth estimation.


