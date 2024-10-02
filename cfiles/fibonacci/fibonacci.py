import ctypes
import os

#c언어로 짠 코드 여기서 불러오겠습니다~ 하는 코드
current_directory = os.path.dirname(os.path.abspath(__file__))
fibonacci_dll_path = os.path.join(current_directory, "fibonacci.dll")
fibonacci_lib = ctypes.CDLL(fibonacci_dll_path)
#포인터로 반환될거니까 너네가 주소에 저장된값 가져와주세요~ 하는 코드
fibonacci_lib.getFibonacci.argtypes = [ctypes.c_int] #인자는 정수로 받을게요
fibonacci_lib.getFibonacci.restype = ctypes.POINTER(ctypes.c_longlong) #리턴은 롱롱으로 받을게요
fibonacci_lib.freeArray.argtypes = [ctypes.POINTER(ctypes.c_longlong)] #메모리 해제할게요

def getNiceFibonacci(num: int):
    # C 함수 호출
    fib_array = fibonacci_lib.getFibonacci(num)
    
    # 배열 반환
    result = [fib_array[i] for i in range(num)]
    
    # 메모리 해제
    fibonacci_lib.freeArray(fib_array)
    
    return result
