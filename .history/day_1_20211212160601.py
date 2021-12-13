

def is_deeper(old, new):
    print(old, new)
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
            if is_deeper(int(old), int(val)):
                deeper += 1
            old = val
        
check_sonar()