<div align="center">
  <h1>🧬 C++ Genetic Algorithm Optimization</h1>
  <p>A comprehensive console-based application built in C++ to demonstrate Evolutionary Computing principles by optimizing quadratic functions.</p>

  ![C++](https://img.shields.io/badge/C++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
  ![Algorithms](https://img.shields.io/badge/Algoritmi-Avansati-orange.svg?style=for-the-badge)
</div>

---

## 📌 Short Description
Developed for the **Algoritmi Avansati** course, this project implements a fully functional Genetic Algorithm from scratch. It is designed to find the maximum value of a quadratic mathematical function over a specific domain. The system models a biological evolution process over multiple generations, utilizing concepts like elitism, roulette wheel selection, crossover, and mutation.

## 💻 Tech Stack & Concepts
The project utilizes the standard C++ library and focuses on efficient algorithmic implementations:

* **🧬 Genetic Representation:** Continuous domain variables encoded into binary strings based on required precision.
* **🎯 Proportional Selection:** Implementation of Roulette Wheel Selection using cumulative probabilities and binary search.
* **🔀 Genetic Operators:** Customizable mutation rates and a modified uniform crossover mechanism.
* **🏆 Elitism:** Ensures the strict survival of the fittest individual across generations.

## ✨ Key Features

* **⚙️ Dynamic Configuration:** Reads population size, domain boundaries, function coefficients, and genetic rates from `date.in`.
* **📊 Automatic Precision:** Adapts bit string length automatically based on the desired decimal precision.
* **📝 Detailed Logging:** Generates `Evolutie.txt` documenting step-by-step selection, crossover, and mutation for the first generation.
* **📈 Evolution Tracking:** Monitors maximum and average fitness across all generations to visualize convergence.

## 🚀 Setup & Execution

**1. Clone the repository:**
```bash
git clone [https://github.com/MihneaG17/Genetic-Algorithm-Optimization.git](https://github.com/MihneaG17/Genetic-Algorithm-Optimization.git)
cd Genetic-Algorithm-Optimization
```

**2. Prepare the input file (date.in)**
Ensure the file contains the parameters in the following order:
[Pop_Size] [a] [b] [A] [B] [C] [Precision] [Cross_Prob] [Mut_Prob] [Stages]
Example:
```bash
20 -1.5 2 -1 1 2 6 0.25 0.01 50
```

**3. Compile the source code:**
```bash
g++ main.cpp -o genetic_optimizer
```

**4. Run the application:**
```bash
./genetic_optimizer```
