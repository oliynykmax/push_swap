
![Score](score.jpg)

# push_swap – Stack Sorting with Minimal Operations

**push_swap** is a C algorithmic project focused on sorting a list of integers using two stacks (`a` and `b`) and a strict set of operations. The objective is to output the most efficient sequence of instructions to sort stack `a` in ascending order — with the **least number of moves possible**.

✅ **Implemented Strategy**: **Turk sort**

## 📦 Features

- 🌀 Sorts stack `a` using only allowed instructions: `sa`, `sb`, `pa`, `pb`, `ra`, `rra`, etc.
- 📉 Outputs the **shortest valid instruction sequence**
- 🧪 Complies with strict project benchmarks:
  - 100 elements sorted in < 700 operations
  - 500 elements sorted in < 6000 operations

## 🔧 Usage

```bash
make
./push_swap 2 1 3 6 5 8

