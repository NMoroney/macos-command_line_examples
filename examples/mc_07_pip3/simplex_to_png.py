# © 2024 : github.com/NMoroney
# MIT License 
#

from PIL import Image
import opensimplex as simplex
import sys, getopt


def main(argv) :
  output_png = 'simplex_noise_2d.png'
  wide = 300
  high = 200
  feature_size = 25.0
  opts, args = getopt.getopt(argv,"ho:x:y:f:",["ofile=","wide=","high=","size="])
  for opt, arg in opts :
    if opt == '-h':
      print ('\npython3 simplex_to_png.py -o <output.png> -x wide -y high -f feature_size \n')
      sys.exit()
    elif opt in ("-o", "--ofile"):
      output_png = arg
    elif opt in ("-x", "--wide"):
      wide = int(arg)
    elif opt in ("-y", "--high"):
      high = int(arg)
    elif opt in ("-f", "--size"):
      feature_size = float(arg)

  im = Image.new('L', (wide, high))
  for y in range(0, high):
    for x in range(0, wide):
      value = simplex.noise2(x / feature_size, y / feature_size)
      color = int((value + 1) * 128)
      im.putpixel((x, y), color)
  im.save(output_png)


if __name__ == "__main__":
  main(sys.argv[1:])

