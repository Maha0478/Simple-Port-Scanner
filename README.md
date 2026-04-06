# Simple Port Scanner

A high-performance TCP port scanner written in C++ using Boost ASIO library for concurrent scanning.

## Features

- **Fast scanning**: Scan multiple ports concurrently using configurable thread pools
- **Flexible port ranges**: Scan single ports or ranges (e.g., 80-443)
- **Custom timeout**: Configure connection timeout per port
- **Verbose mode**: Detailed output for debugging and monitoring
- **Cross-platform**: Built with CMake for Windows, Linux, and macOS support

## Prerequisites

- **C++17 or later**
- **Boost 1.90.0** library (with ASIO, Thread, Chrono, Atomic, and Program Options)
- **CMake 3.16+**
- **Visual Studio 2019+** (for Windows) or GCC/Clang (for Linux/macOS)

## Installation

### Windows (Visual Studio)

1. Clone the repository:
```bash
git clone https://github.com/Maha0478/Simple-Port-Scanner.git
cd Simple-Port-Scanner
```

2. Create build directory:
```bash
mkdir build
cd build
```

3. Configure with CMake:
```bash
cmake .. -G "Visual Studio 16 2019" -A x64
```

4. Build the project:
```bash
msbuild port_scanner.vcxproj /p:Configuration=Release /p:Platform=x64
```

The executable will be in `Release\port_scanner.exe`

### Linux/macOS

1. Clone the repository:
```bash
git clone https://github.com/Maha0478/Simple-Port-Scanner.git
cd Simple-Port-Scanner
```

2. Create build directory:
```bash
mkdir build
cd build
```

3. Configure and build:
```bash
cmake ..
make
```

The executable will be in `./port_scanner`

## Usage

### Basic Usage

Scan common ports on localhost:
```bash
./port_scanner.exe -i 127.0.0.1 -p 1-1024
```

### Command Line Options

```
-h, --help                Show this help message
-i, --dname ADDR          Set domain name or IP address (default: 127.0.0.1)
-p, --ports RANGE         Set port range (e.g., 1-1024 or just 80) (default: 1-1024)
-t, --threads NUM         Max concurrent threads (default: 100)
-e, --expiry_time SEC     Timeout in seconds (default: 2)
-v, --verbose             Enable verbose output
```

### Examples

Scan specific ports on a remote host:
```bash
./port_scanner.exe -i 192.168.1.1 -p 80-443
```

Full TCP port scan with custom settings:
```bash
./port_scanner.exe -i example.com -p 65535 -t 200 -e 5
```

Scan a single port with verbose output:
```bash
./port_scanner.exe -i 10.0.0.1 -p 22 -v
```

## Architecture

- **main.cpp**: Entry point with command-line argument parsing using Boost.Program_Options
- **src/PortScanner.hpp**: Header file with PortScanner class definition
- **src/PortScanner.cpp**: Implementation of port scanning logic using Boost.ASIO
- **CMakeLists.txt**: CMake build configuration

## How It Works

1. **Port Queue**: All ports in the specified range are added to a queue
2. **Async Connections**: For each port, an async connection attempt is made using Boost.ASIO
3. **Thread Pool**: Multiple threads handle connections concurrently (configurable)
4. **Timeout**: Each connection has a configurable timeout value
5. **Results**: Open ports are displayed in green, statistics are shown at completion

## Building Details

The project is configured to use:
- **C++ Standard**: C++17
- **Runtime Library**: Static (/MT) for compatibility with Boost static libraries
- **Optimization**: O2 level for Release builds
- **Boost Libraries Used**:
  - libboost_program_options (CLI parsing)
  - libboost_thread (Threading)
  - libboost_chrono (Timing)
  - libboost_atomic (Atomic operations)
  - libboost_asio (Non-blocking I/O)

## Security Considerations

⚠️ **Important**: Only scan networks and systems you own or have explicit permission to test. Unauthorized port scanning may be illegal in your jurisdiction.

## License

This project is provided as-is for educational purposes.

## Contributing

Contributions are welcome! Feel free to submit issues or pull requests.

## Author

Ghassat Maha

---

**Note**: This scanner performs TCP connection scanning. For advanced features like UDP scanning, SYN scanning, or OS fingerprinting, consider using specialized tools like Nmap.
