# FIDELTA
FIDELTA (FPGA-based Incremental DELaunay Triangulation Acceleration) is a project competing in Xilinx Open Hardware 2020.  
It's a parallelized **Delaunay Triangulation builder** which exploits the reconfigurable hardware provided by Xilinx Alveo cards for Data Center acceleration.

## The algorithm
We're implementing the algorithm proposed by [[Blelloch, Gu, Shun, Sun]](https://arxiv.org/pdf/1810.05303.pdf) which is an incremental approach  
that lowers iteration dependency, improving the degree of **parallelization** reached, with respect to traditional methods.

## Directory layout
    .
    ├── hardware                        # Hardware implementation
    │   ├── bitstream
    │   └── fidelta_archive_ide.zip     # Vitis Project compressed archive
    ├── showme                          # Tool for triangulation visualization
    │   ├── src
    │   └── Makefile
    ├── software                        # Software implementation
    │   ├── src
    │   └── Makefile
    ├── LICENSE
    └── README.md

## Use
### Vitis Project
Inside Vitis, import fidelta_archive_ide.zip.  
Then you can perform a SW-Emulation of the project, or build the Hardware from scratch.  
To avoid doing a complete synthesis, when deploying on the FPGA (Xilinx Alveo U200),  
use directly the xclbin located in hardware/bitstream, along with the host produced by SW-Emulation.

### Computing a triangulation
- Random triangulation

        ./fidelta <path_to_.xclbin> -r <n_pts> <max_abs_coord>

- From a .node file
    
        ./fidelta <path_to_.xclbin> <path_to_.node>

> For software execution the syntax is the same, just omit the xclbin as argument
> I/O files follow the format used by [Triangle](https://www.cs.cmu.edu/~quake/triangle.html)

#### Input: .node
    <n_pts> 2 0 0
    0 <x> <y>
    1 <x> <y>
    ...
    <n_pts-1> <x> <y>

#### Output: .ele
    <n_tri> 3 0
    0 <pt1> <pt2> <pt3>
    1 <pt1> <pt2> <pt3>
    ...
    <n_tri-1> <pt1> <pt2> <pt3>

### Display a triangulation
    cd showme
    make
    ./showme <path_to_.ele>

> showme was only tested on Ubuntu, compatibility with other distros is not granted

## Contacts
- Alberto Giusti - BSc student, Politecnico di Milano - albertogiusti.alberto@gmail.com
- Supervisor - Marco D. Santambrogio - Associate professor, Politecnico di Milano - marco.santambrogio@polimi.it
- [FIDELTA Youtube page](https://www.youtube.com/channel/UCLUakpV9wrvTy_oycEr1Blw)
- NECSTLab 
      - [necst.it](www.necst.it) 
      - [Youtube](https://www.youtube.com/channel/UCaovqRpUc7D_Uf2WJHL0rvA)
      - [Facebook](https://www.facebook.com/NECSTLab) 
  
## Tools
- [Vitis](https://www.xilinx.com/products/design-tools/vitis.html)
- [Show Me](https://www.cs.cmu.edu/~quake/showme.html)
- [uthash](https://troydhanson.github.io/uthash/)

## Acknowledgments
- Saverio Ricci - PhD student, Politecnico di Milano - for his contribution in the first stages of the design
- Emanuele Del Sozzo and Davide Conficconi, for their valuable advice and their patience

## Status
|                |Log                                             |
|----------------|------------------------------------------------|
|14/04/20        |`v0.1 - serial works fine`                      |
|30/04/20        |`v0.2 - random and from file modes integrated`  |
|15/05/20        |`v0.3 - algorithm adapted for FPGA acceleration`|
|08/06/20        |`v0.4 - developed kernel`                       |
|26/06/20        |`v1.0 - deployed on FPGA`                       |
