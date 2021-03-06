## tychoBCGEN - the Boundary Condition GENerator for TYCHO (TYrolian Computational HydrOdynamics)

This is tychoBCGEN - the Boundary Condition GENerator for TYCHO (TYrolian Computational HydrOdynamics). Goal of this program is the generation of boundary conditions from pixel images (i.e. jpeg or png files). This is done by selecting pixels in the same color-range and exporting this masks as solid boundaries. This is version 0.3 of tychoBCGEN, which is freely available to everyone. You are welcome to download it and do whatever you want with it. I would appreciate, however, if you would acknowledge the package in your publications/work and if you send me information for what purpose you use the code.

tychoBCGEN requires QT. QT is licensed under the terms of the GNU Lesser General Public License (LGPL) version 2.1 (see http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html).
More about the QT license can be found at http://qt.nokia.com/products/licensing/


To generate tychoBCGEN you need to execute the following steps:

qmake-qt4
make

After compilation you should find the tychoBCGEN executable within the sources directory. Additional help is provided within tychoBCGEN or the webpage http://www.tycho-cfd.at

----------------------------------------

TYCHO is a multidimensional (1D/2D and 3D) compressible hydrodynamics code written in C and parallelized with OpenMP. A Lagrangian remap version of the Piecewise Parabolic Method developed by Paul Woodward and Phil Colella (1984) is applied. The code is based on the freely available VH-1 package.


The simulation package is focused on wind-tunnel experiments and has special routines for obstacles in wind-stream and advection of marker fields for investigating obstacle-gas interactions. In addition momenta and their direction on obstacle surfaces and thermal diffusion can be studied within your simulation. Gravity is included as a constant background-field and a stratified atmosphere can be set up if needed. 
TYCHO is freely available to everyone. You are welcome to download it and do whatever you want with it. I would appreciate, however, if you would acknowledge the package in your publications/work and if you would send me information for what purpose you use the code. Keep in mind that this code does not come with any guarantee. 

TYCHO's home is http://www.tycho-cfd.at/
