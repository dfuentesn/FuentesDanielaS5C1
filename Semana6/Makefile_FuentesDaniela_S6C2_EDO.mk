all: plots_edo plots_sir

# primero

plots_edo: soluciones.png errores.png euler.png runge.png

soluciones.png errores.png euler.png runge.png: euler_h1.dat euler_h2.dat rk4_h1.dat rk4_h2.dat PLOTS_FuentesDaniela_S6C2_EDO.py
	python PLOTS_FuentesDaniela_S6C2_EDO.py

euler_h1.dat euler_h2.dat rk4_h1.dat rk4_h2.dat: edo
	./edo

edo: FuentesDaniela_S6C2_EDO.cpp
	g++ FuentesDaniela_S6C2_EDO.cpp -o edo

# segundo

plots_sir: sir_comparacion.png sir_euler_vs_rk4.png

sir_comparacion.png sir_euler_vs_rk4.png: sir_euler.dat sir_rk4.dat PLOTS_FuentesDaniela_S6CASA_EDO_SIR.py
	python PLOTS_FuentesDaniela_S6CASA_EDO_SIR.py

sir_euler.dat sir_rk4.dat: edo_sir
	./edo_sir

edo_sir: FuentesDaniela_S6CASA_EDO_SIR.cpp
	g++ FuentesDaniela_S6CASA_EDO_SIR.cpp -o edo_sir

clean:
	del /Q *.dat *.png edo.exe edo_sir.exe 2>nul