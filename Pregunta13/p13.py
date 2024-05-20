import multiprocessing as mp
import math

def fibo_term(n):
    if n == 2:
        return 1
    else:
        p1 = (1 / math.sqrt(5)) * ((1 + math.sqrt(5)) / 2) ** n
        p2 = (1 / math.sqrt(5)) * ((1 - math.sqrt(5)) / 2) ** n
        return int(p1 - p2)

def fibo_worker(inicio, fin):
    return [fibo_term(i) for i in range(inicio, fin)]

if __name__ == "__main__":
    num_procesadores = mp.cpu_count()
    num_terminos = 1000
    terminos_por_procesador = num_terminos // num_procesadores

    # Rangos para cada procesador
    rangos = [(i * terminos_por_procesador, (i + 1) * terminos_por_procesador) for i in range(num_procesadores)]
    rangos[-1] = (rangos[-1][0], num_terminos)  # Ajustar el último rango

    pool = mp.Pool(processes=num_procesadores)
    resultados = pool.starmap(fibo_worker, rangos)

    for idx, resultado in enumerate(resultados):
        print(f"Procesador {idx + 1}: {resultado}")
