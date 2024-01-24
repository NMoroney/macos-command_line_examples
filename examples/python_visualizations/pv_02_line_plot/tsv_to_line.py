# © 2024 : github.com/NMoroney
# MIT License 
#

import matplotlib.pyplot as plot
import csv, sys, getopt

def main(argv) :
  input_tsv = 'data.tsv'
  output_png = 'line_plot.png'
  opts, args = getopt.getopt(argv,"hi:o:",["ifile=","ofile="])
  for opt, arg in opts :
    if opt == '-h':
      print ('\npython3 tsv_to_line.py -i <input.tsv> -o <output.png>\n')
      sys.exit()
    elif opt in ("-i", "--ifile"):
      input_tsv = arg
    elif opt in ("-o", "--ofile"):
      output_png = arg
  print ('input tsv  : ', input_tsv)
  print ('output png : ', output_png)

  file = open(input_tsv, "r")
  data = list(csv.reader(file, delimiter="\t"))
  file.close()

  tdata = list(zip(*data[1:]))

  if (False) :
    print(tdata)

  tdata = list(zip(*data[1:]))

  ys = [float(s) for s in tdata[0]]
  xs = list(range(1, len(ys)+1));

  plot.plot(xs, ys)
  plot.ylabel(data[0][0])
  plot.savefig(output_png)

#  xs = [float(s) for s in tdata[1]]

#  plot.bar(tdata[0], xs)
#  plot.xlabel(data[0][0])
#  plot.ylabel(data[0][1])
#  plot.xticks(rotation=90)
#  plot.tight_layout()
#  plot.savefig(output_png)


if __name__ == "__main__":
  main(sys.argv[1:])

