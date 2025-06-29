#include <bits/stdc++.h>
#include <conio.h>
using namespace std;

// ---------- TRIE ----------
class TrieNode {
public:
    bool isEnd;
    TrieNode* children[26];
    TrieNode() {
        isEnd = false;
        fill(begin(children), end(children), nullptr);
    }
};

class Trie {
    TrieNode* root;
public:
    Trie() { root = new TrieNode(); }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!isalpha(c)) continue;
            int idx = tolower(c) - 'a';
            if (!node->children[idx]) node->children[idx] = new TrieNode();
            node = node->children[idx];
        }
        node->isEnd = true;
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char c : word) {
            if (!isalpha(c)) return false;
            int idx = tolower(c) - 'a';
            if (!node->children[idx]) return false;
            node = node->children[idx];
        }
        return node->isEnd;
    }
};

// ---------- LEVENSHTEIN DISTANCE ----------
int editDistance(const string& a, const string& b) {
    int n = a.size(), m = b.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i-1] == b[j-1])
                dp[i][j] = dp[i-1][j-1];
            else
                dp[i][j] = 1 + min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
        }
    }
    return dp[n][m];
}

string correctWord(const string& word, const unordered_set<string>& dict) {
    string best = word;
    int minDist = INT_MAX;
    for (const string& w : dict) {
        int dist = editDistance(word, w);
        if (dist < minDist) {
            minDist = dist;
            best = w;
        }
    }
    return best;
}

// ---------- BIGRAM ----------
unordered_map<string, unordered_map<string, int>> bigram;

void loadBigramFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string w1, w2, countStr;
        if (!getline(ss, w1, ',')) continue;
        if (!getline(ss, w2, ',')) continue;
        if (!getline(ss, countStr)) continue;
        int count = stoi(countStr);
        transform(w1.begin(), w1.end(), w1.begin(), ::tolower);
        transform(w2.begin(), w2.end(), w2.begin(), ::tolower);
        bigram[w1][w2] = count;
    }
}

string suggestNextWord(const string& word) {
    string key = word;
    transform(key.begin(), key.end(), key.begin(), ::tolower);
    if (bigram.find(key) == bigram.end()) return "";
    auto& m = bigram[key];
    return max_element(m.begin(), m.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    })->first;
}

// ---------- MAIN ----------
int main() {
    Trie trie;
    unordered_set<string> dict;

    // Load dictionary
    ifstream df("dictionary.txt");
    string w;
    while (df >> w) {
        transform(w.begin(), w.end(), w.begin(), ::tolower);
        trie.insert(w);
        dict.insert(w);
    }

    // Load bigrams
    loadBigramFromFile("bigrams.txt");

    cout << "\n🔤 Real-Time Autocorrect + Suggestion (Press ESC to exit)\n\n> ";

    string typedWord = "", lastCorrected = "";
    vector<string> sentence;

    while (true) {
        char ch = _getch();

        if (ch == 27) break;  // ESC key

        if (ch == '\b') {
            if (!typedWord.empty()) {
                typedWord.pop_back();
                cout << "\b \b";
            }
            continue;
        }

        if (ch == ' ') {
            string word = typedWord;
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            word.erase(remove_if(word.begin(), word.end(), ::ispunct), word.end());

            string corrected = trie.search(word) ? word : correctWord(word, dict);
           if (!sentence.empty()) {
    string lastbefore = sentence.back();
    bigram[lastbefore][corrected]++;
}
            sentence.push_back(corrected);
            lastCorrected = corrected;

            typedWord.clear();

            // Refresh display
            system("cls");
            cout << "🔤 Real-Time Autocorrect + Suggestion (ESC to exit)\n\n> ";
            for (auto& w : sentence) cout << "[" << w << "] ";
            cout << "\n→ Suggest: " << suggestNextWord(lastCorrected) << "\n> ";
            for (auto& w : sentence) cout << w << " ";
        } else {
            typedWord += ch;
            cout << ch;

            string temp = typedWord;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            temp.erase(remove_if(temp.begin(), temp.end(), ::ispunct), temp.end());

            if (!temp.empty()) {
                string correction = trie.search(temp) ? temp : correctWord(temp, dict);
                string prediction = suggestNextWord(correction);

                // Refresh display
                system("cls");
                cout << "🔤 Real-Time Autocorrect + Suggestion (ESC to exit)\n\n> ";
                for (auto& w : sentence) cout << "[" << w << "] ";
                cout << "[" << correction << "]";  // current corrected word
                if (!prediction.empty())
                    cout << " → Suggest: " << prediction;

                cout << "\n> ";
                for (auto& w : sentence) cout << w << " ";
                cout << typedWord;
            }
        }
    }

    cout << "\n👋 Exiting...\n";
    return 0;
}
