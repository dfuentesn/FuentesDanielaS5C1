import numpy as np
import matplotlib.pyplot as plt

# Cargo los datos
euler_h1 = np.loadtxt("euler_h1.dat")
euler_h2 = np.loadtxt("euler_h2.dat")
rk4_h1   = np.loadtxt("rk4_h1.dat")
rk4_h2   = np.loadtxt("rk4_h2.dat")

# columnas
t1 = euler_h1[:,0]
y_euler_h1 = euler_h1[:,1]
y_exact_h1 = euler_h1[:,2]
err_euler_h1 = euler_h1[:,3]

t2 = euler_h2[:,0]
y_euler_h2 = euler_h2[:,1]
y_exact_h2 = euler_h2[:,2]
err_euler_h2 = euler_h2[:,3]

t3 = rk4_h1[:,0]
y_rk4_h1 = rk4_h1[:,1]
err_rk4_h1 = rk4_h1[:,3]

t4 = rk4_h2[:,0]
y_rk4_h2 = rk4_h2[:,1]
err_rk4_h2 = rk4_h2[:,3]

# Grafica 1 (Todas las soluciones)
plt.figure()

plt.plot(t1, y_exact_h1,label="Exacta", linewidth=6)
plt.plot(t1, y_euler_h1, '--', color="green", label="Euler h1", linewidth=5)
plt.plot(t2, y_euler_h2, '--', color="red", label="Euler h2", linewidth=5)
plt.plot(t3, y_rk4_h1, color="yellow", label="RK4 h1", linewidth=3)
plt.plot(t4, y_rk4_h2, color="black", label="RK4 h2", linewidth=1)

plt.xlabel("t")
plt.ylabel("y(t)")
plt.title("Comparación de métodos")
plt.legend()
plt.grid()

plt.savefig("soluciones.png")

# Grafica 2 (los errores)
plt.figure()

plt.plot(t1, err_euler_h1, '--', label="Error Euler h1")
plt.plot(t2, err_euler_h2, '--', label="Error Euler h2")
plt.plot(t3, err_rk4_h1, label="Error RK4 h1", linewidth=4)
plt.plot(t4, err_rk4_h2, label="Error RK4 h2")

plt.xlabel("t")
plt.ylabel("Error")
plt.title("Error numérico")
plt.legend()
plt.grid()

plt.savefig("errores.png")

# Grafica 3 (Solo euler)
plt.figure()

plt.plot(t1, y_exact_h1,label="Exacta", linewidth=6)
plt.plot(t1, y_euler_h1, '--', label="Euler h1", linewidth=5)
plt.plot(t2, y_euler_h2, '--', label="Euler h2", linewidth=5)

plt.xlabel("t")
plt.ylabel("y(t)")
plt.title("Comparación de métodos con euler")
plt.legend()
plt.grid()

plt.savefig("euler.png")

# Grafica 4 (solo Runge)
plt.figure()

plt.plot(t1, y_exact_h1,label="Exacta", color="black", linewidth=6)
plt.plot(t3, y_rk4_h1, label="RK4 h1", linewidth=4)
plt.plot(t4, y_rk4_h2, label="RK4 h2", linewidth=2)

plt.xlabel("t")
plt.ylabel("y(t)")
plt.title("Comparación de métodos con Runge_Kutta")
plt.legend()
plt.grid()

plt.savefig("runge.png")

plt.show()