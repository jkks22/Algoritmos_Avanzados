# Algoritmos_Avanzados

### Naive recursion

The naive recursive algorithm directly follows the Fibonacci definition:
F(n)=F(n−1)+F(n−2)
F(n)=F(n−1)+F(n−2)

However, it recalculates the same values many times. For example, calculating F(n−1)F(n−1) and F(n−2)F(n−2) may both calculate F(n−3)F(n−3). Therefore, its time complexity is O(2n)O(2n) as a simple upper bound, or more tightly O(φn)O(φn), where φφ is the golden ratio. Its recursive call stack requires O(n)O(n) space.

### Memoization

Memoization improves the recursive approach by storing each calculated Fibonacci value in a data structure, such as an array, map, or dictionary. When the same value is needed again, the algorithm retrieves it instead of recalculating it.

Each value from F(0)F(0) to F(n)F(n) is calculated only once, so the time complexity becomes O(n)O(n). Because the stored results and recursive call stack use additional memory, the space complexity is O(n)O(n).

### Tabulation

Tabulation uses a bottom-up dynamic programming approach. It starts with the base values F(0)=0F(0)=0 and F(1)=1F(1)=1, then fills a table by calculating each following value.

With a full array or table, tabulation has O(n)O(n) time complexity and O(n)O(n) space complexity. If only the previous two Fibonacci values are stored instead of the entire table, the time complexity remains O(n)O(n), but the auxiliary space complexity decreases to O(1)O(1).


### Comparison
|Aproach|Data Structure|Time Complexity|Space Complexity|


### Reference:
- Measuring Complexity of Fibonacci Algorithms (Memoization & Big O). (s. f.). https://velog.io/@devfish/Measuring-Complexity-of-Fibonacci-Algorithms-Memoization-Big-O

- Geeks for geeks. (2025, 27 agosto). Time complexity of recursive Fibonacci program. Geeks For Geeks. https://www.geeksforgeeks.org/dsa/time-complexity-recursive-fibonacci-program/

- Piwowarek, G., & Marshall, E. (s. f.). Computational complexity of Fibonacci sequence. Baeldung. https://www.baeldung.com/cs/fibonacci-computational-complexity