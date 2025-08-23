import * as Juce from "./juce/index.js";

console.log("Hello, welcome to the Frontend!");

//console.log(window.__JUCE__.backend);

const data = window.__JUCE__.initialisationData;

document.getElementById("vendor").innerText = data.vendor;
document.getElementById("pluginName").innerText = data.pluginName;
document.getElementById("pluginVersion").innerText = "v" + data.pluginVersion;
