🌤️ Auto-Text-Corrector in C++

A real-time, interactive text assistant that **autocorrects** spelling errors and **suggests the next word** as you type. This project showcases classic **data structures** and **algorithms** implemented from scratch, with a real-time console interface.

---

 🚀 Project Overview

This system simulates a basic version of smart typing assistance (like seen in phones or editors) using only C++ and standard libraries. It supports:

* **Live autocorrection** of misspelled words
* **Next-word prediction** based on word pair frequencies
* **Interactive typing simulation** in the console

---

🧰 Tech Stack Used

* **Language**: C++
* **Data Structures**: Trie, Hash Maps
* **Algorithms**: Levenshtein Distance, Frequency-based Prediction
* **Console Handling**: `conio.h` for `_getch()` real-time input
* **File I/O**: `fstream` for loading dictionary and bigram data

---

 🔧 Algorithms & Purpose

| Algorithm / DS            | Purpose                                                |
| ------------------------- | ------------------------------------------------------ |
| **Trie**                  | Fast dictionary lookup to validate and correct words   |
| **Levenshtein Distance**  | To find the closest valid word when a typo is detected |
| **Bigram Language Model** | Predicts the most likely next word based on past usage |
| **Dynamic Programming**   | Used in computing the edit distance efficiently        |

---

 📂 Project Structure

```
├── main.cpp             // Main logic for correction and prediction
├── dictionary.txt       // List of valid English words (one per line)
├── bigrams.txt          // CSV of bigram frequencies: word1,word2,count
```

---

 ⚙️ How It Works

1. **Load Resources**:

   * `dictionary.txt` is loaded into a Trie and an unordered\_set.
   * `bigrams.txt` is parsed to build a nested hash map for word-pair frequencies.

2. **Typing Interaction**:

   * User types words in real-time (captured using `_getch()`).
   * On spacebar press, the last typed word is:

     * Validated using Trie
     * Autocorrected using Levenshtein if needed
     * Saved into a sentence vector

3. **Word Suggestion**:

   * Based on the last corrected word, a likely next word is suggested using the highest frequency bigram pair.

---

 🎓 Example Use Case

```
> i was got

Correction: [i] [was] [going]      
Next Suggestion: to
```

* "got" is replaced by "going" based on Levenshtein correction.
* "was going" bigram suggests the next word "to".

---

 🚤 Possible Extensions

* GUI interface with Qt or web frontend
* Use trigram or neural network language models
* Top-k next-word suggestions instead of single max
* Personal user profile to track word usage over time

---

📊 Impact & Skills Demonstrated

* Strong grasp of **algorithmic problem solving**
* Ability to implement **real-time user-facing systems**
* Applied **NLP concepts without any ML libraries**
* Demonstrated **data-driven prediction** with dynamic learning

---

 🌐 Author & Contact

**Hafeez Shaik**
Feel free to connect via [LinkedIn](https://www.linkedin.com/in/hafeez-shaik-2b3a26259/) 

---


