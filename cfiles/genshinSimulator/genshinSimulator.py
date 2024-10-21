import ctypes
import os
import random

current_directory = os.path.dirname(os.path.abspath(__file__))
genshin_dll_path = os.path.join(current_directory, "genshin.dll")
genshin_lib = ctypes.CDLL(genshin_dll_path)
mostLowest = ctypes.c_int()
myRank = ctypes.c_int()
charlist = (ctypes.c_int * 24)()

notPickUp = ['다이루크', '각청', '치치', '타이나리', '진', '모나', '데히야']

def genshinSimulator(constellation: int, simTimes: int, ticket: int, wantCharacter: str):
    genshin_lib.get_simulation_result(ctypes.c_int(constellation), ctypes.c_int(simTimes), ctypes.c_int(ticket), ctypes.byref(mostLowest), charlist, ctypes.byref(myRank))
    result_dict = {}
    for i in range(12):
        pickup = charlist[2 * i]
        times = charlist[2 * i + 1]
        if pickup == 0 or pickup == 1:
            if pickup == 0:
                character = random.choice(notPickUp)
            else:
                character = wantCharacter
            if times != 0:
                result_dict[i + 1] = {"Character": character, "Times": times}
            else:
                return {"Sangwi": 0}
    sangwi = myRank.value
    return {"result": result_dict, "Sangwi": (sangwi/simTimes)*100}

print(genshinSimulator(6, 1000000, 200, '치오리'))

