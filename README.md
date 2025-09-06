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

## ***Prerequisites***

To get started, ensure you have the following installed:

- **Meson Build System**: If you don’t have Meson `1.8.0` or newer installed, follow the installation instructions on the official [Meson website](https://mesonbuild.com/Getting-meson.html).
- **Conan Package Manager**: If you prefer using Conan, ensure it is installed by following the instructions on the official [Conan website](https://docs.conan.io/en/latest/installation.html).

### Adding Dependency

#### Adding via Meson Git Wrap

To add a git-wrap, place a `.wrap` file in `subprojects` with the Git repo URL and revision, then use `dependency('fossil-math')` in `meson.build` so Meson can fetch and build it automatically.

#### Integrate the Dependency:

Add the `fossil-math.wrap` file in your `subprojects` directory and include the following content:

```ini
[wrap-git]
url = https://github.com/fossillogic/fossil-math.git
revision = v0.1.1

[provide]
dependency_names = fossil-math
```

**Note**: For the best experience, always use the latest releases. Visit the [releases](https://github.com/fossillogic/fossil-math/releases) page for the latest versions.

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
