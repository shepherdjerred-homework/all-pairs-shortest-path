let numNodes = 500;
let numEdges = 30;
let minEdgeWeight = 0;
let maxEdgeWeight = 100;

let edges = [];

let genNum = (min, max) => {
  return Math.floor(Math.random() * (max - min + 1) + min);
}

let genRoute = () => {
  let source = -1;
  let dest = -1;
  do {
      source = genNum(0, numNodes - 1);
      dest = genNum(0, numNodes - 1);
  } while (source === dest);
  let weight = genNum(minEdgeWeight, maxEdgeWeight);
  return {
    source,
    dest,
    weight
  }
}

for (let i = 0; i < numEdges; i++) {
  edges[i] = genRoute();
}

let outputString = '';

outputString += numNodes + ' ' ;
outputString += '\n';
outputString += numEdges + ' ';
outputString += '\n';

for (let i = 0; i < numEdges; i++) {
  outputString += edges[i].source + ' ';
  outputString += edges[i].dest + ' ';
  outputString += edges[i].weight + ' ';
  outputString += '\n';
}

outputString += '\n';

console.log(outputString);
