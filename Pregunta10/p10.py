import multiprocessing

def generar_series(rank, size, M, N, series):
    chunk = M // size
    inicio = rank * chunk
    fin = M if rank == size - 1 else inicio + chunk

    for i in range(inicio, fin):
        valor_inicio = (i * N + 1) * 2
        for j in range(N):
            series[i * N + j] = valor_inicio + j * 2

if __name__ == "__main__":
    num_procesadores = multiprocessing.cpu_count()
    print("Numero de procesadores: ", num_procesadores)
    M = int(input("Ingrese el número de vectores (M): "))
    N = int(input("Ingrese el número de términos (N): "))

    serie_compartida = multiprocessing.Array('i', M * N)

    procesos = []
    for i in range(num_procesadores):
        proceso = multiprocessing.Process(target=generar_series, args=(i, num_procesadores, M, N, serie_compartida))
        procesos.append(proceso)
        proceso.start()

    for proceso in procesos:
        proceso.join()

    print("Serie generada:")
    for i in range(M):
        vector = [serie_compartida[i * N + j] for j in range(N)]
        print(f"Vector {i + 1}: {' '.join(map(str, vector))}")
