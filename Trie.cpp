struct TrieNode
{
    TrieNode* child[26]={};
    bool f=false;
};

class Trie {
public:
TrieNode*root;
    Trie() {
        root=new TrieNode();
    }
    
    void insert(string word) {
        
        TrieNode*node=root;
        
             for (char ch : word) {
            int idx = ch - 'a';
            if (!node->child[idx])
                node->child[idx] = new TrieNode();
            node = node->child[idx];
        }
        node->f = true;
        
    }
    
    bool search(string word) {
       TrieNode*node=root;
       
             for (char ch : word) {
            int idx = ch - 'a';
            if (!node->child[idx])
                return false;
            node = node->child[idx];
        }
        return node->f;
          
    }
    
};
