# Juce 8 Audio Plugin Template including WebViews

This template is a remake based on the YouTube video by WolfSound: https://www.youtube.com/watch?v=0ALLRitFE34 resp. https://github.com/JanWilczek/juce-webview-tutorial

Status: August 2025

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

## Build the plugin

Execute this command in a Terminal after changes of CMakeLists.txt files

```
cmake -S . -B build
```

Execute this to compile and build source code

```
cmake --build build
```

## Usage of local development server

According to https://www.youtube.com/watch?v=Ub-v__G0IFQ this template uses a local development server in order to let the plugin run.

Open a separate Terminal in the subfolder plugin/ui/public and start the server (running on http://127.0.0.1:8080):

```
npx http-server
```

## Run the plugin

Test plugin as Standalone on MacOS:

```
open /build/plugin/<your-plugin-name>_artefacts/Standalone/<your-plugin-name>Plugin.app
```

Test plugin as Standalone on Windows:

```
/build/plugin/<your-plugin-name>_artefacts/Standalone/<your-plugin-name>Plugin.exe
```

## Test-Release (MacOS) of VST3 Plugin in Ableton Live

### Build Artefacts

```
cmake --preset Xcode
cmake --build --preset Xcode --config Release
```

### Copy VST3 Artefact into Ableton

Search for the \*.vst file.
`<your-project-folder>/xcode-build/plugin/<your-plugin-name>_artefacts/Release/VST3/<your-plugin-name>.vst3`

Copy the file and paste it in Ableton's plugin folder (see Ableton's preferences -> Plug-Ins).

Rescan plugins (click on button in Ableton's preferences)

If you are facing problems:

- Open the Terminal
- Listen to log stream:
  ```
  log stream --predicate 'eventMessage contains "vst3"' --info
  ```
