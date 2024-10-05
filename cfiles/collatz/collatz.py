import ctypes
import os

current_directory = os.path.dirname(os.path.abspath(__file__))
collatz_dll_path = os.path.join(current_directory, "collatz.dll")
collatz_lib = ctypes.CDLL(collatz_dll_path)
collatz_lib.getCollatz.argtypes = [ctypes.c_longlong]
collatz_lib.getCollatz.restype = ctypes.POINTER(ctypes.c_longlong)
collatz_lib.freeArray.argtypes = [ctypes.POINTER(ctypes.c_longlong)]

def getNiceCollatz(num: int):
    try:
        col_array = collatz_lib.getCollatz(num)
        result = [col_array[0], col_array[1]]
        collatz_lib.freeArray(col_array)
    except Exception as e:
        result = ["error", "숫자너무큼"] 
    return result

