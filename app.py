from fastapi import FastAPI
from pydantic import BaseModel
from cfiles.fibonacci import fibonacci
from cfiles.quadratic import quadratic

app = FastAPI()


class FibonacciRequest(BaseModel):
    num: int

class QuadraticRequest(BaseModel):
    a: float
    b: float
    c: float

@app.post("/fibonacci")
def get_fibonacci(request: FibonacciRequest):
    num = request.num
    if num > 93:
        return {"error": "숫자가 너무 큽니다. 93 이하로 입력하세요."}
    
    result = fibonacci.get_fibonacci_sequence(num)
    return {"sequence": result}

@app.post("/quadratic")
def get_quadratic(request: QuadraticRequest):
    a = request.a
    b = request.b
    c = request.c
    result= quadratic.getQuadraticAnswer(a, b, c)
    return {"ans" : result}