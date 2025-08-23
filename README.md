# Juce 8 Audio Plugin Template including WebViews

Status: in work (August 2025)

## Prerequisites

- Installed cmake



## Installation

```
git clone https://github.com/kmueller/webview-plugin.git
cd webview-plugin
```

## Rename to your own Project

Replace/adjust all occurancies of "Juce8WebView..." by your own Plugin-Name:
- subfolder inside of "include/" folder
- in CMakeLists.txt files
- COMPANY_NAME
- PLUGIN_MANUFACTURER_CODE (4 chars)
- PLUGIN_CODE (4 chars)

## Build and Run

Execute this after changes of CMakeLists.txt files
```
cmake -S . -B build
```

Execute this to compile and build source code
```
cmake --build build
```

Test plugin on MacOS:
```
open /build/plugin/<your-plugin-name>_artefacts/Standalone/<your-plugin-name>Plugin.app
```

Test plugin on Windows:
```
/build/plugin/<your-plugin-name>_artefacts/Standalone/<your-plugin-name>Plugin.exe
```
