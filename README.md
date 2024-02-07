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

The program takes a single argument, the path to the input ROOT file containing simulated data.  To run:
```
./opticsMatrix /path/to/input_file.root
```
