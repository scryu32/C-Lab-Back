import ctypes
import os

current_directory = os.path.dirname(os.path.abspath(__file__))
prime_dll_path = os.path.join(current_directory, "prime.dll")
prime_lib = ctypes.CDLL(prime_dll_path)

#구조체 정의
class PrimeFactors(ctypes.Structure):
    _fields_ = [('count', ctypes.c_int),
                ('factors', ctypes.POINTER(ctypes.c_int))]

prime_lib.getPrimeNumber.restype = PrimeFactors
prime_lib.getPrimeNumber.argtypes = [ctypes.c_int]

def getNicePrime(num: int):
    result = prime_lib.getPrimeNumber(num)
    factorsArray = []

    # C언어 배열은 파이썬으로 다시 바꿔줘야함
    for i in range(result.count):
        factorsArray.append(result.factors[i])
    
    prime_lib.freeArray(result.factors)
    return {"count": result.count, "factors": factorsArray}
