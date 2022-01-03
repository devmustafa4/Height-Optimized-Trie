#include <iostream>

using std::string;
using std::cout;
using std::endl;

class Optimized_Trie 
{
    class Node 
    {
        public:
            string identifier;
            int data;
            Node* children[26];

            Node() {       
                for (int i=0; i<26;i++)
                {
                    children[i] = NULL;
                }
            }
    };

    Node* root = NULL;

    public:

    Optimized_Trie()
    {
        // initialize the root node
        root = new Node();
        root->data = 0;
        root->identifier = "";
    }

    void insert(string word, int data)
    {
        int i =0;
        // find common substring split, if found 
        // else if identifier length < word then go to next child 
        Node* prev = NULL;
        Node* temp = root;
        while (i<word.length())
        {
            int temp_i = 0;
            while (temp->identifier[temp_i] != '\0')
            {
                if (temp->identifier[temp_i] == word[i])
                {
                    temp_i++;
                    i++;
                }
                else 
                {
                    // non common letter exists at ith index on the word
                    // in this case create a new node and add two childs one to store the previous chain
                    // and one to store the new word

                    // node where common identifier exists exists
                    
                    // a new common node to insert before
                    Node* common_node = new Node();
                    common_node->identifier = temp->identifier.substr(0,temp_i);
                    //changing the identifier of prev node
                    temp->identifier = temp->identifier.substr( temp_i );

                    common_node->children[ temp->identifier[0] - 'a'] = temp;
                    // if the word has some non matching characters
                    if (word[i] != '\0')
                    {
                        // creating separate node to store the new data
                        Node* node2 = new Node();
                        node2->identifier = word.substr(i);
                        node2->data = data;

                        // building the link between node with data and common node
                        common_node->children[word[i]-'a'] = node2;

                        // setting the parent of common node
                        prev->children[common_node->identifier[0]-'a'] = common_node;
                    }
                    // if the word only consists of matching characters
                    else
                    {
                          common_node->data = data;
                    }
                    return;
                }
            }
            if (temp->children[word[i]- 'a'] == NULL)
            {
                Node* newNode = new Node();
                newNode->identifier = word.substr(i, word.length());
                newNode->data = data;

                temp->children[word[i]-'a'] = newNode;
                break;
            }
            else
            {
                prev = temp;
                temp = temp->children[word[i]-'a'];
            }
        }
    }



    void search(string word)
    {
        int word_i = 0;
        Node* temp = root;
        
        // if temp is NULL then don't continue
        while(temp != NULL)
        {
            int temp_i = 0;
            // loop through every character in the current node 
            while (temp->identifier[temp_i] != '\0')
            {
                if (temp->identifier[temp_i] == word[word_i])
                {
                    temp_i++;
                    word_i++;
                }
                else
                {
                    cout<<word<<" does not exists"<<endl;
                    return;
                }       
            }

            // if the word at i'th index is last character of word then the word is found
            if (word[word_i] == '\0')
            {
                cout<<"the data in the "<<word<<" is "<<temp->data<<endl;
                return;
            }
            // if the word at i'th index is not the last character of word
            // then check if the node has a child at ith index
            if (temp->children[word[word_i] - 'a'] == NULL)
            {
                // if there is no node at ith index then the word does not exists
                cout<<word<<" does not exists"<<endl;          
                return;
            }
            else
                //if there is a node at ith index then search for the remaining word in the node
                temp = temp -> children[word[word_i]-'a'];
        }
    }

};

int main ()
{
    Optimized_Trie trie;
    
    trie.insert("kesy", 1);
    trie.insert("acha", 2);
    trie.insert("acha git", 3);
    trie.insert("achjjj",6);

    trie.search("kesy");
    trie.search("acha");
    trie.search("acha git");
    trie.search("achjjj");
    trie.search("bye");
    return 0;
}