# **Fossil Math by Fossil Logic**

**Fossil Math** is a lightweight, cross-platform mathematics library written in pure C with zero external dependencies. Designed for high-performance computation, embedded systems, and cross-platform applications, Fossil Math provides a robust set of functions for linear algebra, geometry, trigonometry, and numerical analysis, all optimized for efficiency and portability.

### Key Features

- **Cross-Platform Support**  
  Runs reliably on Windows, macOS, Linux, and embedded platforms.

- **Zero External Dependencies**  
  Pure C implementation ensures maximum portability, auditability, and ease of integration.

- **Comprehensive Math Functions**  
  Includes linear algebra, vectors, matrices, quaternions, trigonometry, and other numerical utilities.

- **Lightweight and Efficient**  
  Optimized for performance with minimal resource usage, suitable for embedded and low-power devices.

- **Precision and Reliability**  
  Provides stable and accurate numerical results for high-precision calculations.

- **Modular Design**  
  Easily integrated into projects, with optional modules for advanced math features.

## Getting Started

### Prerequisites

- **Meson Build System**  
  Fossil Math uses Meson for build configuration. If you don’t have Meson installed, follow the instructions on the official [Meson website](https://mesonbuild.com/Getting-meson.html).

### Adding Fossil Math as a Dependency

#### Using Meson

### **Install or Upgrade Meson** (version 1.3 or newer recommended):

```sh
   python -m pip install meson           # Install Meson
   python -m pip install --upgrade meson # Upgrade Meson
```
###	Add the .wrap File
Place a file named fossil-math.wrap in your subprojects directory with the following content:

```ini
# ======================
# Git Wrap package definition
# ======================
[wrap-git]
url = https://github.com/fossillogic/fossil-math.git
revision = v0.1.0

[provide]
fossil-math = fossil_math_dep
```

###	Integrate in Your meson.build
Add the dependency by including this line:

```meson
math_dep = dependency('fossil-math')
```


## Build Configuration Options

Customize your build with the following Meson options:
	•	Enable Tests
To run the built-in test suite, configure Meson with:

```sh
meson setup builddir -Dwith_test=enabled
```

### Tests Double as Samples

The project is designed so that **test cases serve two purposes**:

- ✅ **Unit Tests** – validate the framework’s correctness.  
- 📖 **Usage Samples** – demonstrate how to use these libraries through test cases.  

This approach keeps the codebase compact and avoids redundant “hello world” style examples.  
Instead, the same code that proves correctness also teaches usage.  

This mirrors the **Meson build system** itself, which tests its own functionality by using Meson to test Meson.  
In the same way, Fossil Logic validates itself by demonstrating real-world usage in its own tests via Fossil Test.  

```bash
meson test -C builddir -v
```

Running the test suite gives you both verification and practical examples you can learn from.

## Contributing and Support

For those interested in contributing, reporting issues, or seeking support, please open an issue on the project repository or visit the [Fossil Logic Docs](https://fossillogic.com/docs) for more information. Your feedback and contributions are always welcome.
