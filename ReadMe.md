# Zone - Neural Network Library

Zone is my experimental C-based neural network library—a naive attempt to build a complete neural network framework from scratch. This project emerged after I struggled to get TensorFlow 2 and Keras working on my Android device. While projects like llamacpp, TensorFlow for embedded systems, and TinyML have set the bar high, my goal is to craft a beginner-friendly ML library for Android and embedded systems.

**Highlights:**
- Part of a six-module ML stack.
- Focused solely on the neural network component.
- Built with CMake.

## ML Stack Modules
1. **memalloc:** Memory allocator/manager.
2. **zot:** A dummy interface for memalloc.
3. **zobject:** Object-oriented programming emulator.
4. **zor:** Tensor library.
5. **zode:** Autodiff library.
6. **zone:** Neural network library (this project).

## Getting Started

Clone the repository and build with CMake:
```bash
git clone https://github.com/iudah/zone.git
cd zone
cmake .
make
```

## Examples

Check the examples folder for sample projects demonstrating Zone in action.

## Feedback

If you have suggestions or run into issues, please open an issue. Contributions are welcome as I continue refining this project.
