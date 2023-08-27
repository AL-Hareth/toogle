function add(a: number, b: number): number {
    return a + b;
}

function capitalize(str: string): string {
    return str.toUpperCase();
}

function getLength(str: string): number {
    return str.length;
}

function subtract(a: number, b: number): number {
    return a - b;
}

function divide(a: number, b: number): number {
    if (b === 0) {
        return 0;
    }
    return a / b;
}

function multiply(a: number, b: number): number {
    return a * b;
}

function addMultiple(...arr: number[]): number {
    return arr.reduce((a, b) => a + b, 0);
}
