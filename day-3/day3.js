
const fs = require('fs');
const readline = require('readline');
const filename = process.argv[2];

// Make sure we got a filename on the command line.
if (process.argv.length < 3) {
    console.log('Usage: node ' + process.argv[1] + ' FILENAME');
    process.exit(1);
}

const rl = readline.createInterface({
    input: fs.createReadStream(filename),
    output: process.stdout,
    terminal: false
});

let commonBits = [];
let lines = [];
rl.on('line', (line) => {
    lines.push(line);
    if (!commonBits.length) commonBits = new Array(line.length).fill(0);
    for (let i = 0; i < line.length; i++) {
        if (line[i] == 1) {
            commonBits[i] = commonBits[i]+1
        } else {
            commonBits[i] = commonBits[i]-1
        }
    }
});

const getGammaAndEpsilon = (bitOccurances) => {
    const rates = {gamma: '', epsilon: ''};
    for (let i = 0; i < bitOccurances.length; i++) {
        if (bitOccurances[i] > 0) {
            rates.gamma += "1";
            rates.epsilon += "0";

        } else {
            rates.gamma += "0";
            rates.epsilon += "1";
        }
    }
    return rates;
}
const getConsumptionRate = (gamma, epsilon) => {
    return parseInt(gamma, 2) * parseInt(epsilon, 2);
}

const getOxygenAndCO2Rates = (lines, idx, searchingForOxy) => {
    if (lines.length === 1) return lines
    let ones = [];
    let zeros = [];
    let count = 0;
    for (i = 0; i < lines.length;i++) {
        if (lines[i][idx] === "1") {
            ones.push(lines[i])
            count += 1
        } else {
            zeros.push(lines[i]);
            count -= 1
        }
    }
    let remaaining, rate;
    if (searchingForOxy)  {
        remaining = [ones, zeros]
    } else {
        remaining = [zeros, ones]
    }
    if (count >= 0) {
        rate = getOxygenAndCO2Rates(remaining[0], idx+1, searchingForOxy);
    } else {
        rate = getOxygenAndCO2Rates(remaining[1], idx+1, searchingForOxy);
    }
    return rate
}

const getLifeSupportRate = (oxy, co2) => (
    parseInt(oxy,2)*parseInt(co2,2)
)
rl.on('close', () => {
    let {gamma, epsilon} = getGammaAndEpsilon(commonBits);
    const consumptionRate = getConsumptionRate(gamma, epsilon)
    const oxygenRate = getOxygenAndCO2Rates(lines, 0, true)
    const co2 = getOxygenAndCO2Rates(lines, 0, false);
    const lifeSupportRate = getLifeSupportRate(oxygenRate, co2);
    
})