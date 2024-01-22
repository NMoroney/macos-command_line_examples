# © 2024 : github.com/NMoroney
# MIT License 
#

import cv2
import torch
import numpy
import sys
from PIL import Image

model_type = "DPT_Large"
midas = torch.hub.load("intel-isl/MiDaS", model_type)

device = torch.device("cuda") if torch.cuda.is_available() else torch.device("cpu")
midas.to(device)
midas.eval()

midas_transforms = torch.hub.load("intel-isl/MiDaS", "transforms")
transform = midas_transforms.dpt_transform

name = sys.argv[1]

img = cv2.imread(name)
img = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)

input_batch = transform(img).to(device)

with torch.no_grad():
  prediction = midas(input_batch)
  
  prediction = torch.nn.functional.interpolate(
    prediction.unsqueeze(1),
    size=img.shape[:2],
    mode="bicubic",
    align_corners=False,
  ).squeeze()

depth = prediction.cpu().numpy()

numpy.shape(depth)

size = len(name)
depth_name = name[:size - 4] + "_depth.jpg"

d_min = numpy.amin(depth)
d_max = numpy.amax(depth)
d_range = d_max - d_min

grays = 255 * ((depth - d_min) / d_range)

ns = grays.astype(numpy.uint8)
img = Image.fromarray(ns, 'L')

img.save(depth_name, "JPEG")

