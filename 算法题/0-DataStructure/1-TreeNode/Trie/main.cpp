#include<bits/stdc++.h>

using namespace std;

struct Trie{
	vector<Trie*> children = vector<Trie*>(26);
    bool isEnd;
    Trie(){
    	isEnd = false;
    	for(auto &child : children){
    		child = nullptr;
    	}
    }
};

class TrieOper{
private:
    Trie* root;
public:
    TrieOper(){
        root = new Trie();
    }

    void insert(string wordString){
        if(!wordString.size())
            return;
        Trie *cur = root;
        for(auto c : wordString){
            
            if(!cur->children[c-'a'])
                cur->children[c-'a'] = new Trie();
            cur = cur->children[c-'a'];
        }
        cur->isEnd = true;
        return;
    }

    bool search(string wordString){
        if(!wordString.size())
            return false;
        Trie *cur = root;
        for(auto c : wordString){
            if(!cur->children[c-'a'])
                return false;
            cur = cur->children[c-'a'];
        }
        if(cur->isEnd) return true;
        return false;
    }
};

int main(){
    TrieOper tp{};
    tp.insert("abc");
    cout<<boolalpha<<tp.search("ab")<<endl;
    return 0;
}