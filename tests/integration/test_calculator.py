import subprocess
import sys
import os

def test_addition_of_small_numbers():
    res = subprocess.run(["./build/app.exe"], input="3+5", text=True, capture_output=True)
    assert res.returncode == 0
    assert int(res.stdout) == 8

def test_multiplication_of_medium_numbers():
    res = subprocess.run(["./build/app.exe"], input="10*6", text=True, capture_output=True)
    assert res.returncode == 0
    assert int(res.stdout) == 60

def test_division_with_float_result():
    res = subprocess.run(["./build/app.exe", "--float"], input="7/3", text=True, capture_output=True)
    assert res.returncode == 0
    assert float(res.stdout) == 2.3333

def test_division_by_zero():
    res = subprocess.run(["./build/app.exe"], input="777/0", text=True, capture_output=True)
    assert res.returncode != 0

def test_invalid_expression_format():
    res = subprocess.run(["./build/app.exe"], input="15**3", text=True, capture_output=True)
    assert res.returncode != 0

def test_handling_large_positive_number():
    res = subprocess.run(["./build/app.exe"], input="2000000001", text=True, capture_output=True)
    assert res.returncode != 0

def test_handling_large_negative_number():
    res = subprocess.run(["./build/app.exe"], input="0-2000000001", text=True, capture_output=True)
    assert res.returncode != 0

def test_invalid_parentheses_structure():
    res = subprocess.run(["./build/app.exe"], input="5*((8-3)", text=True, capture_output=True)
    assert res.returncode != 0

def test_invalid_input_characters():
    res = subprocess.run(["./build/app.exe"], input="dick", text=True, capture_output=True)
    assert res.returncode != 0

def test_unary_minus_handling():
    res = subprocess.run(["./build/app.exe"], input="-666", text=True, capture_output=True)
    assert res.returncode != 0
