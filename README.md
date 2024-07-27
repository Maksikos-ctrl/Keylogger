# Keylogger
## _The Ultimate Keylogger Tool_

[![Build Status](https://travis-ci.org/Maksikos-ctrl/Keylogger.svg?branch=master)](https://travis-ci.org/Maksikos-ctrl/Keylogger)


Keylogger is a sophisticated keylogging tool designed for security and monitoring purposes. It logs keystrokes and can be used to monitor user activity on a device.

- Record keystrokes efficiently
- Store logs locally
- ✨ Powerful and discreet ✨

## Table of Contents

- [Features](#features)
- [Tech](#tech)
- [Installation](#installation)
  - [Prerequisites](#prerequisites)
  - [Building](#building)
  - [Running](#running)
- [Usage](#usage)
- [Development](#development)
- [License](#license)

## Features

- Logs all keystrokes with timestamp and application context
- Stealth mode to run in the background without detection
- Logs stored in UTF-8 format to support various languages
- Easy configuration and setup

## Tech

Keylogger uses a number of open source projects and libraries to work properly:

- [Windows API](https://docs.microsoft.com/en-us/windows/win32/api/) - for intercepting input events
- [COM](https://docs.microsoft)


## Usage

1. Start the keylogger by running the executable.
2. The keylogger will run in stealth mode by hiding the console window.
3. Logs will be written to `log.txt` in the same directory as the executable.

## Development

Want to contribute? Great!

Keylogger uses standard C++ practices for development. Make a change in your file and instantly see your updates!

Open your favorite Terminal and run these commands.

First Tab:

```sh
Keylogger.exe
```
(optional) Second Tab:
```
sh
```

## Run your tests or other development tools

 - Building for source

  - For production release, use your C++ build system to compile the project with optimizations enabled.

  
## License

This project is licensed under the ANSYS License - see the [LICENSE](https://www.ansys.com/academic/students) file for details.


