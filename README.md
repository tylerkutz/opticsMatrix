Program to fit the MOLLER spectrometer optics matrix from simulated data.

To compile, create directory where you would like to build:
```
mkdir build
cd build
cmake ../opticsMatrix
make
```


Note that on a Mac with an M1 chip, you must switch to `x86_64` architecture before compiling:
```
env /usr/bin/arch -x86_64 /bin/bash --login
```

The program takes two arguments: the path to the input ROOT file containing simulated data, and the index of the variable being fit (0 = theta, 1 = phi).  Note that this assumes that hole identification has already been performed on the simulated data, and the ROOT file contains a branch `hole_id`.  To run:
```
./opticsMatrix /path/to/input_file.root <0 = fit theta, 1 = fit phi>
```
