use std::fs;

const FILENAME: &str = "./day-2-input.txt";


struct Submarine {
    distance: i32,
    depth: i32,
}
pub trait SubmarineActions {
    fn move_forward(&mut self, n: i32) -> ();
    fn move_up(&mut self, n: i32) -> ();
    fn move_down(&mut self, n: i32) -> ();
    fn move_init(&mut self, data: &[Instruction]) -> () {
        for instruction in data {
            // println!("Instruction: {} \t current Position: {} - {}", line, self.distance, self.depth);
            match instruction.direction.as_str() {
                "forward" => self.move_forward(instruction.magnitude),
                "up" => self.move_up(instruction.magnitude),
                "down" => self.move_down(instruction.magnitude),
                _ => println!("Bad Instruction!!")
            }
        }
    }
}

impl SubmarineActions for Submarine {
    fn move_forward(&mut self, n: i32) -> () {
        self.distance += n
    }
    fn move_up(&mut self, n: i32) -> () {
        self.depth -= n
    }
    fn move_down(&mut self, n: i32) -> () {
        self.depth += n
    }
}


fn get_area(x: i32, y: i32) -> i32 {
    x * y
}
struct SubmarineWithAim {
    distance: i32,
    depth: i32,
    aim: i32
}


impl SubmarineActions for SubmarineWithAim {
    fn move_forward(&mut self, n: i32) -> () {
        self.distance += n;
        self.depth += n * self.aim;
    }
    fn move_up(&mut self, n: i32) -> () {
        self.aim -= n
    }
    fn move_down(&mut self, n: i32) -> () {
        self.aim += n
    }
}
pub struct Instruction {
    direction: String,
    magnitude: i32
}

impl Instruction {
    fn create(raw_string: &str) -> Self {
        let parts: Vec<&str> = raw_string.split_whitespace().collect();
        let direction: String  = String::from(parts[0]);
        let magnitude: i32 = parts[1].parse().unwrap();
       return Instruction {direction, magnitude};
    }
    fn read_instructions_from_data(data: String) -> Vec<Instruction> {
        let mut formatted_instruction: Vec<Instruction> = vec![];
        for line in data.lines() {
            let instruction: Instruction = Instruction::create(line);
            formatted_instruction.push(instruction);
        }
        return formatted_instruction
    }
}

fn main() {
    
    let mut sub = Submarine {
        distance: 0,
        depth: 0,

    };
    
    let mut aimed_sub = SubmarineWithAim {
        distance: 0,
        depth: 0,
        aim: 0
    };

    
    let raw_data: String = fs::read_to_string(FILENAME).expect("Unable to read file");
    let formatted_data: Vec<Instruction> = Instruction::read_instructions_from_data(raw_data);
    sub.move_init(&formatted_data);
    aimed_sub.move_init(&formatted_data);
    let p1_distance: i32 = get_area(sub.distance, sub.depth);
    let p2_distance: i32 = get_area(aimed_sub.distance, aimed_sub.depth);
    println!("Part one: {}", p1_distance);
    println!("Part one: {}", p2_distance);
}