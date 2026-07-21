import numpy as np
import matplotlib.pyplot as plt

# Separazione dei blocchi dal file
blocks = []
#devo per forza usare with open perche ho lasciato gli spazi,in scrittura, per non confondere
with open('buca.txt') as f:
    current = []
    
    for line in f:
        line = line.strip()
        
        if line == '':
            if current:
                blocks.append(np.array(current, dtype=float))
                current = []
        else:
            current.append([float(v) for v in line.split()])
    
    if current:
        blocks.append(np.array(current, dtype=float))

# Parametri della buca
N = 64
v0 = 10.0

# Coordinate del potenziale
x_pot = np.arange(N)

# Definizione della buca quadrata
V = np.where((x_pot >= N/4) & (x_pot < 3*N/4), -v0, 0.0)

# Colori diversi per gli autostati
colors = ['tab:blue', 'tab:orange', 'tab:green', 'tab:red']

plt.figure(figsize=(8,6))

# Plot del potenziale
plt.plot(x_pot,V,'k--',linewidth=2,label='V(x)')
# Plot delle autofunzioni traslate
for n, block in enumerate(blocks):
    
    x = block[:, 0]
    y = block[:, 3]   # E_n + mL*|psi_n|
    
    plt.plot(x,y,color=colors[n],linewidth=2,label=f'n={n}')

#plt.title('Buca di potenziale')
plt.xlabel('x/a')
plt.ylabel('potenziale/energia')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("buca.png")
plt.show()

# SECONDO GRAFICO
blocks = []

with open('muro.txt') as f:
    current = []
    
    for line in f:
        line = line.strip()
        
        if line == '':
            if current:
                blocks.append(np.array(current, dtype=float))
                current = []
        else:
            current.append([float(v) for v in line.split()])
    
    if current:
        blocks.append(np.array(current, dtype=float))

# Parametri del muro
N = 64
v0 = 10.0   # altezza del muro

# Coordinate del potenziale
x_pot = np.arange(N)

# Definizione del muro quadrato
V = np.where((x_pot >= N/4) & (x_pot < 3*N/4), v0, 0.0)
# Colori diversi per gli autostati
colors = ['tab:blue', 'tab:orange', 'tab:green', 'tab:red']

plt.figure(figsize=(8,6))

# Plot del muro
plt.plot(x_pot,V,'k--',linewidth=2,label='V(x)')
# Plot delle autofunzioni traslate
for n, block in enumerate(blocks):

    x = block[:, 0]
    y = block[:, 3]

    plt.plot(x,y,color=colors[n],linewidth=2,label=f'n={n}')
#plt.title('Muro di potenziale')
plt.xlabel('x/a')
plt.ylabel('potenziale/energia')
plt.grid(True)
plt.legend()
plt.tight_layout()
plt.savefig("muro.png")
plt.show()
