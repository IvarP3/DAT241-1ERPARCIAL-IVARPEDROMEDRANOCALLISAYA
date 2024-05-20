import multiprocessing

def calcular_pi_parcial(rango, tamaño):
    pi_local = 0.0
    for n in range(rango, 100000, tamanio):
        signo = 1 if n % 2 == 0 else -1
        denominador = 2 * n + 1
        pi_local += signo * 1.0 / denominador
    return pi_local

if __name__ == "__main__":
    tamanio = multiprocessing.cpu_count()
    pool = multiprocessing.Pool(processes=tamanio)

    resultados = pool.starmap(calcular_pi_parcial, [(rango, tamanio) for rango in range(tamanio)])
    pi = sum(resultados)

    pi *= 4 
    print("Valor aproximado de pi:", pi)
