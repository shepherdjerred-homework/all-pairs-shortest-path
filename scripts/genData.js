let numNodes = 5;
let numEdges = 13;
let numRoutes = 3;
let minEdgeWeight = 0;
let maxEdgeWeight = 50;
let minRouteLength = 4;
let maxRouteLength = numEdges;

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

let routes = [];
for (let i = 0; i < numRoutes; i++) {
  let numNodesInRoute = genNum(minRouteLength, maxRouteLength);
  routes[i] = [];
  for (let j = 0; j < numNodesInRoute; j++) {
    routes[i][j] = genNum(0, numNodes - 1);
  }
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

outputString += numRoutes;
outputString += '\n';

for (let i = 0; i < numRoutes; i++) {
  let numNodesInRoute = routes[i].length;
  outputString += numNodesInRoute + ' ';
  for (let j = 0; j < numNodesInRoute; j++) {
    outputString += routes[i][j] + ' ';
  }
  outputString += '\n'
}

outputString += '\n';

console.log(outputString);
