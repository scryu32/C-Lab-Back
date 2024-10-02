import ctypes
import os

# DLL 로드
current_directory = os.path.dirname(os.path.abspath(__file__))
quadratic_dll_path = os.path.join(current_directory, "quadratic.dll")
quadratic_lib = ctypes.CDLL(quadratic_dll_path)
# 함수의 인자 및 반환 타입 설정
quadratic_lib.getquadraticEquationAnswer.argtypes = [ctypes.c_float, ctypes.c_float, ctypes.c_float]
quadratic_lib.getquadraticEquationAnswer.restype = ctypes.POINTER(ctypes.c_char)
quadratic_lib.freeArray.argtypes = [ctypes.POINTER(ctypes.c_char)]

def getQuadraticAnswer(a: float, b: float, c: float):
    result_ptr = quadratic_lib.getquadraticEquationAnswer(a, b, c)
    #문자열로 받을거니까 인코딩 해야함
    result = ctypes.string_at(result_ptr).decode("utf-8")
    quadratic_lib.freeArray(result_ptr)
    print(result)
    return result

# 테스트 호출
getQuadraticAnswer(1, 2, 1)
