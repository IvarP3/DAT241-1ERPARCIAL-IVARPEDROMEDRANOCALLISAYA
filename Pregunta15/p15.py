import multiprocessing as mp

def hola_mundo():
    print("Hola mundo")

if __name__ == "__main__":
    proceso = mp.Process(target=hola_mundo)
    proceso.start()
    proceso.join()
