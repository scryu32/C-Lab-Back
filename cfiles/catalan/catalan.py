import ctypes
import os

current_directory = os.path.dirname(os.path.abspath(__file__))
catalan_dll_path = os.path.join(current_directory, "catalan.dll")
catalan_lib = ctypes.CDLL(catalan_dll_path)
catalan_lib.getCatalanArr.restype = ctypes.c_longlong 
catalan_lib.getCatalanArr.argtypes = [ctypes.c_int]


def getNiceCatalan(num: int):
    #34 넘어가면 롱롱도 감당 못함
    if num > 34:
        return "error"
    cat_arr = []
    for i in range(num):
        cat_arr.append(catalan_lib.getCatalanArr(i+1))
    return cat_arr



