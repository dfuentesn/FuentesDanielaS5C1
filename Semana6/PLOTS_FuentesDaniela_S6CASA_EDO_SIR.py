import numpy as np
import matplotlib.pyplot as plt

# Cargar datos
euler = np.genfromtxt("sir_euler.dat")
rk4   = np.genfromtxt("sir_rk4.dat")

t_e, S_e, I_e, R_e = euler[:,0], euler[:,1], euler[:,2], euler[:,3]
t_r, S_r, I_r, R_r = rk4[:,0],   rk4[:,1],   rk4[:,2],   rk4[:,3]

#Grafica 1 (S, I, R vs tiempo para cada metodo)
fig, axes = plt.subplots(1, 2, figsize=(12, 5), sharey=True)
fig.suptitle("Modelo SIR", fontsize=14)

for ax, t, S, I, R, titulo in zip(
        axes,
        [t_e, t_r], [S_e, S_r], [I_e, I_r], [R_e, R_r],
        ["Euler", "Runge-Kutta 4"]):
    ax.plot(t, S, label="S (Susceptibles)", color="steelblue")
    ax.plot(t, I, label="I (Infectados)",   color="tomato")
    ax.plot(t, R, label="R (Recuperados)",  color="mediumseagreen")
    ax.set_title(titulo)
    ax.set_xlabel("Tiempo")
    ax.set_ylabel("Población")
    ax.legend()
    ax.grid(alpha=0.3)

plt.tight_layout()
plt.savefig("sir_comparacion.png", dpi=150)
print("Guardado: sir_comparacion.png")

#Grafica 2 (comparacion Euler vs RK4 por compartimento) 
fig, axes = plt.subplots(1, 3, figsize=(14, 4))
fig.suptitle("Comparación Euler vs RK4 por compartimento", fontsize=14)

for ax, ye, yr, nombre, color in zip(
        axes,
        [S_e, I_e, R_e], [S_r, I_r, R_r],
        ["S", "I", "R"],
        ["steelblue", "tomato", "mediumseagreen"]):
    ax.plot(t_e, ye, label="Euler",  color=color, linestyle="--", linewidth=1.5)
    ax.plot(t_r, yr, label="RK4",    color=color, linestyle="-",  linewidth=1.5, alpha=0.7)
    ax.set_title(nombre)
    ax.set_xlabel("Tiempo")
    ax.set_ylabel("Población")
    ax.legend()
    ax.grid(alpha=0.3)

plt.tight_layout()
plt.savefig("sir_euler_vs_rk4.png", dpi=150)
print("Guardado: sir_euler_vs_rk4.png")

plt.show()