from fastapi import FastAPI
from pydantic import BaseModel
from cfiles import fibonacci

app = FastAPI()


class FibonacciRequest(BaseModel):
    num: int

@app.post("/fibonacci")
def get_fibonacci(request: FibonacciRequest):
    num = request.num
    if num > 93:
        return {"error": "숫자가 너무 큽니다. 93 이하로 입력하세요."}
    
    result = fibonacci.get_fibonacci_sequence(num)
    return {"sequence": result}

