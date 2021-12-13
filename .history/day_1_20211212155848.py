

def is_deeper(old, new):
    if new > old:
        return True
    else:
        return False

def check_sonar(res):
    deeper = 0
    old = res[0]
    for val in res: 
        if is_deeper(old, val):
            deeper += 1
    print(deeper)
        
