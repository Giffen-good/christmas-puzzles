
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
            if is_deeper(int(old), int(val)):
                deeper += 1
            old = val
    print(deeper)

def get_data(fn):
     with open('day-1-input.txt') as f:
        return f.readlines()

def compare_decks(idx, decks, val):
    decks[idx] += val
    decks[idx-1] += val
    decks[idx-2] += val
    is_deeper = False
    if decks[idx-3] > decks[idx-2]:
        is_deeper = True
    decks[idx-3] = 0
    return is_deeper
def sonar_part_2(data):
    is_deeper = 0
    count = 2
    decks = [
        data[0] + data[1] + data[2],
        data[1] + data[2],
        data[2],
        0
    ]
    # skip the first 3 entries because special rules apply
    for val in data[2:]:
        compare_decks(count, decks, val)
        if count == 3: 
            count = 0
        else:
            count += 1
    print(is_deeper)

def main():
    list_data = get_data('day-1-input.txt')
    sonar_part_2(list_data)

if __name__ == "__main__":
    main()

    
