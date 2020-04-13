# FIDELTA
FIDELTA (FPGA-based Incremental DELaunay Triangulation Acceleration) is a project competing in Xilinx Open Hardware 2020.
It's a higly parallelized **Delaunay Triangulation builder** which exploits the reconfigurable hardware provided by Xilinx Alveo cards for Data Center acceleration.

## The algorithm
We're implementing the algorithm proposed by [[Belloch, Gu, Shun, Sun]](https://arxiv.org/pdf/1810.05303.pdf) which is an incremental approach 
that lowers iteration dependency, improving the degree of **parallelization** reached, with respect to traditional methods.

## Status
General: **Work in Progress**
|                |Log                                   |
|----------------|--------------------------------------|
|28/02/20        |`Start           `                    |
|04/03/20        |`Main structures implemented`         |
|02/04/20        |`InCircle and Counterclockwise`       |
|04/04/20        |`Added merge encroaching points lists`|
|14/04/20        |`First (almost) working version`      |


## Contacts
- Alberto Giusti - BSc student, Politecnico di Milano - albertogiusti.alberto@gmail.com
- Saverio Ricci - PhD student, Politecnico di Milano - saverio.ricci95@hotmail.it
- NECSTLab 
  - [necst.it](www.necst.it) 
  - [Facebook](https://www.facebook.com/NECSTLab) 
  - [Youtube](https://www.youtube.com/channel/UCaovqRpUc7D_Uf2WJHL0rvA)
  
## Built with
- Vivado HLs toolchain
- uthash
