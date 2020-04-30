# FIDELTA
FIDELTA (FPGA-based Incremental DELaunay Triangulation Acceleration) is a project competing in Xilinx Open Hardware 2020.
It's a higly parallelized **Delaunay Triangulation builder** which exploits the reconfigurable hardware provided by Xilinx Alveo cards for Data Center acceleration.

## The algorithm
We're implementing the algorithm proposed by [[Belloch, Gu, Shun, Sun]](https://arxiv.org/pdf/1810.05303.pdf) which is an incremental approach 
that lowers iteration dependency, improving the degree of **parallelization** reached, with respect to traditional methods.

## Serial version
### Installation
    
    cd serial
    make

### Computing a triangulation
- From a .node file
    
        ./serial [.node_PATH]

- Random triangulation

        ./serial -r [N_PTS] [MAX_COORDINATE]

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
General: **Work in Progress**
|                |Log                                   |
|----------------|--------------------------------------|
|28/02/20        |`Start           `                    |
|04/03/20        |`Main structures implemented`         |
|02/04/20        |`InCircle and Counterclockwise`       |
|04/04/20        |`Added merge encroaching points lists`|
|14/04/20        |`Version 0.1 - Works Fine`            |
|30/04/20        |`Version 0.2 - 2 input modes avaiable`|

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
