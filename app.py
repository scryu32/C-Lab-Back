from fastapi import FastAPI
from pydantic import BaseModel
from cfiles.fibonacci import fibonacci
from cfiles.quadratic import quadratic
from cfiles.catalan import catalan
from cfiles.collatz import collatz
from cfiles.prime import prime
from cfiles.genshinSimulator import genshinSimulator
from fastapi.middleware.cors import CORSMiddleware

#gcc --% -shared -o 이름.dll -Wl,--out-implib,lib이름.a 이름.c

app = FastAPI()

app.add_middleware(
    CORSMiddleware,
    allow_origins=["*"],
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

class intReq(BaseModel):
    num: int

class QuadraticRequest(BaseModel):
    a: float
    b: float
    c: float

class GenshinSim(BaseModel):
    character: str
    ticket: int
    constellation: int
    simTimes: int


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
    return {"result": result}

@app.post("/quadratic")
def get_quadratic(request: QuadraticRequest):
    a = request.a
    b = request.b
    c = request.c
    result= quadratic.getQuadraticAnswer(a, b, c)
    return {"result" : result}

@app.post("/catalan")
def get_catalan(request: intReq):
    num = request.num
    if num > 34:
        return {"error": "숫자가 너무 큽니다. 34 이하로 입력하세요."}
    result = catalan.getNiceCatalan(num)
    return {"result" : result}

@app.post("/collatz")
def get_collatz(request: intReq):
    num = request.num
    result = collatz.getNiceCollatz(num)
    return {"biggest" : result[1], "times" : result[0]}

@app.post("/prime")
def get_prime(request: intReq):
    num = request.num
    result = prime.getNicePrime(num)
    return {"count": result['count'], "factors": result['factors']}

@app.post("/genshin/character")
def get_genshinGatchaOfCharacter(requset: GenshinSim):
    character = requset.character
    ticket = requset.ticket
    constellation = requset.constellation
    simTimes = requset.simTimes
    if (simTimes > 1000000):
        return {"error": "숫자가 너무 큽니다"}
    if (constellation > 6):
        return {"error": "숫자가 너무 큽니다(별자리는 최대 6)"}
    if (ticket <= 0):
        return {"error": "티켓 숫자를 자연수로 입력하세요"}
    result = genshinSimulator.genshinSimulator(constellation, simTimes, ticket, character)
    return result
    
