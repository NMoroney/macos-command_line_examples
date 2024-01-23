# © 2024 : github.com/NMoroney
# MIT License 
#

import matplotlib.pyplot as plt
import numpy as np
import csv, sys, getopt

from matplotlib import colormaps

def main(argv) :
  input_tsv = 'data.tsv'
  output_png = 'contour.png'
  the_title = ''
  the_alpha = 1
  opts, args = getopt.getopt(argv,"hi:o:t:",["ifile=","ofile=","title="])
  for opt, arg in opts :
    if opt == '-h':
      print ('\npython3 tsv_to_contour.py -i <input.tsv> -o <output.png> -t the_title\n')
      sys.exit()
    elif opt in ("-i", "--ifile"):
      input_tsv = arg
    elif opt in ("-o", "--ofile"):
      output_png = arg
    elif opt in ("-t", "--title"):
      the_title = arg
  print ('input tsv  : ', input_tsv)
  print ('output png : ', output_png)

  file = open(input_tsv, "r")
  data = list(csv.reader(file, delimiter="\t"))
  file.close()

  tdata = list(zip(*data[1:]))

  if (False) :
    print(tdata)

  xs = [float(s) for s in tdata[0]]
  ys = [float(s) for s in tdata[1]]
  zs = [float(s) for s in tdata[2]]

  wide = len(set(xs))
  high = len(set(ys))

  X = np.array(xs)
  Y = np.array(ys)
  Z = np.array(zs)

  cols = wide
  rows = high
  X2 = X.reshape(rows, cols);
  Y2 = Y.reshape(rows, cols);
  Z2 = Z.reshape(rows, cols);

  # plt.contour(X2, Y2, Z2);
  plt.contour(X2, Y2, Z2, cmap="copper", linewidths=6);

  plt.xlabel(data[0][0])
  plt.ylabel(data[0][1])
  t = the_title.replace("_", " ");
  plt.title(t)

  plt.savefig(output_png)


if __name__ == "__main__":
  main(sys.argv[1:])

