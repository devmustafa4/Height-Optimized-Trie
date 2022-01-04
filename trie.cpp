#include <iostream>
#include <list>
#include <map>
using namespace std;

template <class T>
class OptimizedTrie 
{
    class Node 
    {
        public:
            string identifier;
            T* data;
            map<char, Node*> children;
    };

    Node* root = NULL;

    public:

    OptimizedTrie()
    {
        // initialize the root node
        root = new Node();
        root->data = NULL;
        root->identifier = "";
    }

    void insert(string word, T data)
    {
        T* dataptr = new T(data); 
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

                    common_node->children[temp->identifier[0]] = temp;
                    // if the word has some non matching characters
                    if (word[i] != '\0')
                    {
                        // creating separate node to store the new data
                        Node* node2 = new Node();
                        node2->identifier = word.substr(i);
                        node2->data = dataptr;

                        // building the link between node with data and common node
                        common_node->children[word[i]] = node2;

                        // setting the parent of common node
                        prev->children[common_node->identifier[0]] = common_node;
                    }
                    // if the word only consists of matching characters
                    else
                    {
                        common_node->data = dataptr;
                    }
                    return;
                }
            }
            if (temp->children.find(word[i]) == temp->children.end())
            {
                Node* newNode = new Node();
                newNode->identifier = word.substr(i, word.length());
                newNode->data = dataptr;

                temp->children[word[i]] = newNode;
                break;
            }
            else
            {
                prev = temp;
                temp = temp->children[word[i]];
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
                cout<<"the data in the "<<word<<" is "<<*temp->data<<endl;
                return;
            }
            // if the word at i'th index is not the last character of word
            // then check if the node has a child at ith index
            if (temp->children.find(word[word_i]) == temp->children.end())
            {
                // if there is no node at ith index then the word does not exists
                cout<<word<<" does not exists"<<endl;          
                return;
            }
            else
                //if there is a node at ith index then search for the remaining word in the node
                temp = temp -> children[word[word_i]] -> second;
        }
    }

    // a function to print values of all nodes starting with a given string in the trie
    void printChildren(string prefix)
    {
        // temp is the node that contains the prefix
        Node* temp = root;
        int word_i =0;
       
        // find the node where prefix exists
        while(temp != NULL)
        {
            int temp_i = 0;
            
            // loop through every character in the current node 
            while (temp->identifier[temp_i] != '\0'&&prefix[word_i] != '\0')
            {
                if (temp->identifier[temp_i] == prefix[word_i])
                {
                    temp_i++;
                    word_i++;
                }
                else
                {
                    cout<<prefix<<" does not exists"<<endl;
                    return;
                }       
            }
            
            // if the word at i'th index is last character of word then the word is found
            if (prefix[word_i] == '\0')
            {
                // the node with the prefix has been found now 
                // now we have to print all children of that node
                printChildNodes(temp);
                return;
            }
            // if the word at i'th index is not the last character of word
            // then check if the node has a child at ith index
            if (temp->children.find(prefix[word_i]) == temp->children.end())
            {
                // if there is no node at ith index then the word does not exists
                cout<<prefix<<" does not exists"<<endl;          
                return;
            }
            else
                //if there is a node at ith index then search for the remaining word in the node
                temp = temp -> children[prefix[word_i]];
        }
    }

    void printChildNodes(Node* node)
    {
        // if the node is NULL return
        if (node == NULL)
        {
            cout<<"The given node is NULL"<<endl;
            return;
        }

        if (node->data != NULL)
            cout<<*node->data<<endl;
            //    iterating over all value of umap
    
        for (auto itr : node->children)
            printChildNodes(itr.second);
    }

};

int main ()
{
    OptimizedTrie<string> trie;
    
    trie.insert("he?:123llo", "1asdf");
    trie.insert("heloooo", "2asdf");
    trie.insert("hoooo", "3asdf");
    trie.insert("okayyyy","6asdf");
    trie.insert("okie", "11asdf");

    trie.printChildren("he?");
    return 0;
}