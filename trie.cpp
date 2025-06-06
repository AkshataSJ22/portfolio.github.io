#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

class TrieNode {
public:
    unordered_map<char, TrieNode*> children;
    bool isEndOfWord;

    TrieNode() {
        isEndOfWord = false;
    }
};

class Trie {
private:
    TrieNode* root;

    void dfs(TrieNode* node, string prefix, vector<string>& results) {
        if (node->isEndOfWord)
            results.push_back(prefix);

        for (auto& [ch, next] : node->children) {
            dfs(next, prefix + ch, results);
        }
    }

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* curr = root;
        for (char ch : word) {
            if (!curr->children.count(ch))
                curr->children[ch] = new TrieNode();
            curr = curr->children[ch];
        }
        curr->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* curr = root;
        for (char ch : word) {
            if (!curr->children.count(ch))
                return false;
            curr = curr->children[ch];
        }
        return curr->isEndOfWord;
    }

    vector<string> autocomplete(const string& prefix) {
        TrieNode* curr = root;
        for (char ch : prefix) {
            if (!curr->children.count(ch))
                return {}; // No matches
            curr = curr->children[ch];
        }

        vector<string> results;
        dfs(curr, prefix, results);
        return results;
    }
};
