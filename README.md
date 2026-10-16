# openMSL

![openMSL logo](documentation/openMSL_logo.jfif)

**openMSL** is a C++ library that provides tools for numerical methods, engineering statics, number systems, and control. The repository also includes a small PowerShell utility for displaying project information, license details, and documentation.

> **Status:** Beta release (`beta 0.0.3`). The library API and some of its dependencies are still under development.

## Contents

- [Modules](#modules)
- [Requirements and dependencies](#requirements-and-dependencies)
- [Usage](#usage)
- [PowerShell utility](#powershell-utility)
- [Repository structure](#repository-structure)
- [License](#license)

## Modules

The headers are located in `include/msl/`. The names below are in the `msl` namespace:

| Header | Functionality |
| --- | --- |
| `numerical.hpp` | Root-finding methods such as bisection, secant, and Newton–Raphson; numerical integration; interpolation; and error calculations. |
| `statics.hpp` | Cartesian vector and force operations, sine and cosine laws, angle conversions, and moment calculation. |
| `logic.hpp` | Conversions between binary, octal, and hexadecimal number systems, and data-size unit conversions. |
| `control.hpp` | Proportional, integral, and derivative controllers, with support for computing outputs over time. |
| `statistics.hpp` | A header that currently contains no statistical interfaces. |

`include/msl.hpp` provides a combined include for the control, logic, numerical, and statics modules. It does not include `statistics.hpp`.

## Requirements and dependencies

- A modern C++ compiler. The included VS Code configuration is set to C++20.
- The repository currently has no build system or dependency manager.
- Some headers depend on external projects: `control.hpp` depends on openUDT and openCF, `logic.hpp` on openCF, and `numerical.hpp` on openETL. Add the corresponding header search paths to your compiler configuration when using these modules.
- The example below uses only `statics.hpp` and standard library headers.

## Usage

Add the `include` directory to your compiler's include paths, then include the header you need. This example uses the moment calculation function from `statics.hpp`:

```cpp
#include <iostream>
#include <msl/statics.hpp>

int main()
{
    const double moment = msl::Moment(2.0, 3.0);
    std::cout << "Moment: " << moment << '\n';
}
```

With `g++`, build the example from the repository root:

```powershell
g++ -std=c++20 -I .\include .\main.cpp -o .\main.exe
```

To use the combined header, replace the include in the example with:

```cpp
#include <msl.hpp>
```

This combined include also requires the external dependencies listed above. There are currently no example or test files in the `examples/` and `tests/` directories.

## PowerShell utility

Run the following commands from the repository root:

```powershell
.\msl.ps1 --help
.\msl.ps1 --version
.\msl.ps1 --author
.\msl.ps1 --license
.\msl.ps1 --brief
```

To display documentation for a specific header, pass its path to `--help`. The utility looks for a corresponding documentation file under `help/`:

```powershell
.\msl.ps1 --help msl\numerical.hpp
```

## Repository structure

```text
include/
  msl.hpp              # Combined header
  msl/                 # Library module headers
documentation/         # Logo and project/license information
help/                  # Documentation used by the PowerShell utility
examples/              # Reserved for examples
tests/                 # Reserved for tests
msl.ps1                # PowerShell information and documentation utility
LICENSE
```

## License

This project is licensed under the **GNU Lesser General Public License, version 2.1 (LGPL-2.1)**. See [LICENSE](LICENSE) for the full text.
