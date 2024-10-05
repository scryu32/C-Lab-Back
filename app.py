from fastapi import FastAPI
from pydantic import BaseModel
from cfiles.fibonacci import fibonacci
from cfiles.quadratic import quadratic
from cfiles.catalan import catalan
from cfiles.collatz import collatz
from cfiles.prime import prime

app = FastAPI()

class intReq(BaseModel):
    num: int

class QuadraticRequest(BaseModel):
    a: float
    b: float
    c: float

from fastapi.responses import FileResponse

@app.get("/")
def mainpage():
    return FileResponse('templates/index.html')

@app.post("/fibonacci")
def get_fibonacci(request: intReq):
    num = request.num
    if num > 93:
        return {"error": "숫자가 너무 큽니다. 93 이하로 입력하세요."}
    
    result = fibonacci.getNiceFibonacci(num)
    return {"sequence": result}

@app.post("/quadratic")
def get_quadratic(request: QuadraticRequest):
    a = request.a
    b = request.b
    c = request.c
    result= quadratic.getQuadraticAnswer(a, b, c)
    return {"answer" : result}

@app.post("/catalan")
def get_catalan(request: intReq):
    num = request.num
    if num > 34:
        return {"error": "숫자가 너무 큽니다. 34 이하로 입력하세요."}
    result = catalan.getNiceCatalan(num)
    return {"answer" : result}

@app.post("/collatz")
def get_collatz(request: intReq):
    num = request.num
    result = collatz.getNiceCollatz(num)
    return {"biggest" : result[0], "times" : result[1]}

@app.post("/prime")
def get_prime(request: intReq):
    num = request.num
    result = prime.getNicePrime(num)
    return {"count": result['count'], "factors": result['factors']}