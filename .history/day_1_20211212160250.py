

def is_deeper(old, new):
    if new > old:
        return True
    else:
        return False

def check_sonar():
    deeper = 0
    with open('day-1-input.txt') as f:
        lines = f.readlines()
        old = lines[0]
        for val in lines: 
            if is_deeper(old, val):
                deeper += 1
    print(deeper)
        
check_sonar()