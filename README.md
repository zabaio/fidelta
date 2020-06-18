# FIDELTA
FIDELTA (FPGA-based Incremental DELaunay Triangulation Acceleration) is a project competing in Xilinx Open Hardware 2020.
It's a higly parallelized **Delaunay Triangulation builder** which exploits the reconfigurable hardware provided by Xilinx Alveo cards for Data Center acceleration.

## The algorithm
We're implementing the algorithm proposed by [[Belloch, Gu, Shun, Sun]](https://arxiv.org/pdf/1810.05303.pdf) which is an incremental approach 
that lowers iteration dependency, improving the degree of **parallelization** reached, with respect to traditional methods.

## Directory layout

 .
 ├── serial         # Sequential implementation, for general use
 ├── parallel       # Algorithm adaptation suitable for hw acceleration
 │   └── xilix      # Vivado-HLS and Vitis projects
 └── showme         # Visualization tool

## Use
### Installation
If you do that in the base folder you'll build the *serial* and *parallel* software implementations as well as the visualization tool *showme*.
Otherwise it's possible to just use make inside the desired folder.
    make
    *or* cd <dir> && make

### Computing a triangulation
- From a .node file
    
        ./fidelta [.node_PATH]

- Random triangulation

        ./fidelta -r [N_PTS] [MAX_COORDINATE]

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
    ./showme [.ele_PATH]

## Status
|                |Log                                             |
|----------------|------------------------------------------------|
|14/04/20        |`v0.1 - serial works fine`                      |
|30/04/20        |`v0.2 - random and from file modes integrated`  |
|15/05/20        |`v0.3 - algorithm adapted for FPGA acceleration`|
|08/06/20        |`v0.4 - developed kernel`                       |

## Contacts
- Alberto Giusti - BSc student, Politecnico di Milano - albertogiusti.alberto@gmail.com
- Saverio Ricci - PhD student, Politecnico di Milano - saverio.ricci95@hotmail.it
- NECSTLab 
  - [necst.it](www.necst.it) 
  - [Youtube](https://www.youtube.com/channel/UCaovqRpUc7D_Uf2WJHL0rvA)
  - [Facebook](https://www.facebook.com/NECSTLab) 
  
## Tools
- [Vitis](https://www.xilinx.com/products/design-tools/vitis.html)
- [Show Me](https://www.cs.cmu.edu/~quake/showme.html)
- [uthash](https://troydhanson.github.io/uthash/)
