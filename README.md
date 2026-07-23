# Stationary-Schrodinger-equation
A basic study of bound states and energy levels given the schrödinger's equation, using a static potential (time-indipendent)

## Theory
We analyse a static potential V(x) a very particular case in reality.
we seek a solution to the separable Schrodinger equation in x,t:

```math
\psi(x) = \phi(x) T(t)
```
Knowing that the Hamilton operator has the form:
```math
\hat H \psi(x,t) \equiv - \frac{\hbar^2}{2m}\nabla^2 + V(x)
```

Given the schrodinger's equation:
```math
i \hbar \frac{\partial}{\partial t} \psi(x,t)= \hat H \psi(x,t)
```
Putting all together we find 
```math
\phi(x)\cdot i \hbar \frac{\partial T}{\partial t} = T(t) \hat H \phi(x)
```
With some algebraic simplifications, it can be reduced to the form
```math
\hat H \phi(x) = E \phi(x)
```
This is an eigenvalue equation so we can use some eigenvalue solver to find the energy levels of the system.
E is the total energy of the system, it's a constant so therefore exist stationary states where :
```math
\psi(x,t) = \phi(x) e^{-\frac{iEt}{\hbar}}
```
These are considered stationary because 
```math
|\psi(x,t)|^2 = |\phi(x)|^2
```
is time indipendent.

## Discretization

## INSTALLATION
For this particular case we'll need only the most common libraries of C++ and Python.

The project include:
- main part (calculations and output) written in C++ 
- Data visualization written in Python using matplotlib

Installing Python dependences:
```bash
pip install -r libraries.txt
```
Installing GIT:
```bash
apt-get install git3
```
Clone the repo:
```bash
git clone https://github.com/michele2938/Stationary-Schrodinger-equation.git
cd Stationary-Schrodinger-equation
```
For the next steps, you need to be in the newly created folder, otherwise it won't work :)
### compile C++ files
using the makefile:
```bash
make
```
without makefile:
```bash
c++ main.cpp -o main.exe
```
### execute C++
```bash
./main
```

### compile Python
```bash
python3 plot.py
```

## Results
Using as physical parameters:
- mL = 8.0 (dimensionless)
- A = B = 0 (boundary condition)
```math
V(x)=\left\{
\substack{
0,\quad x<\frac{L}{4}\ \text{,}\ x\ge\frac{3L}{4}\\[4pt]
-V_0,\quad \frac{L}{4}\le x<\frac{3L}{4}
}
\right.
Follows

```
## References
Quantum Mechanics  - Cohen-Tannoudji
