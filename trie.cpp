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

    Node* getNode(string word)
    {
        // returns the node with the identifier

        int word_i = 0;
        Node* temp = root;
        
        // temp variable to traverse the nodes in trie
        while(temp != NULL)
        {
            int temp_i = 0;
            // compare corresponding characters of word and identifier
            while (temp->identifier[temp_i] != '\0')
            {
                // if the current character is same then increment variable to compare next character
                if (temp->identifier[temp_i] == word[word_i])
                {
                    temp_i++;
                    word_i++;
                }
                // if at any point the corresponding characters do not match then the word is not present in the trie
                else
                {
                    return NULL;
                }       
            }

            // if the word at i'th index is last character of word then the word is found
            if (word[word_i] == '\0')
            {
                if (temp->data != NULL)
                    return temp;
                else
                    return NULL;
            }
            // if the word at i'th index is not the last character of word
            // then find the node that begins with the character in the children of the current node
            if (temp->children.find(word[word_i]) == temp->children.end())
            {
                // if there is no node at ith index then the word does not exists
                return NULL;
            }
            else
                //if there is a node at ith index then search for the remaining word in the child node
                temp = temp -> children[word[word_i]];
        
        }
        return NULL;
    }

    void search(string word)
    {
        Node* node = getNode(word);
        if (node != NULL)
        {
            // if the node exists but does not contain any data then 
            cout<<"The data stored in node with key "<<word<<" is "<<*node->data<<endl;
        }   
    }

    void Delete(string word)
    {
        // returns the node with the identifier

        int word_i = 0;
        Node* prev = NULL;
        Node* temp = root;
        
        // temp variable to traverse the nodes in trie
        while(temp != NULL)
        {
            int temp_i = 0;
            // compare corresponding characters of word and identifier
            while (temp->identifier[temp_i] != '\0')
            {
                // if the current character is same then increment variable to compare next character
                if (temp->identifier[temp_i] == word[word_i])
                {
                    temp_i++;
                    word_i++;
                }
                // if at any point the corresponding characters do not match then the word is not present in the trie
                else
                {
                    return;
                }       
            }

            // if the word at i'th index is last character of word then the word is found
            if (word[word_i] == '\0')
            {
                if (temp->data != NULL)
                    break;
                else
                    return;
            }
            // if the word at i'th index is not the last character of word
            // then find the node that begins with the character in the children of the current node
            if (temp->children.find(word[word_i]) == temp->children.end())
            {
                // if there is no node at ith index then the word does not exists
                return;
            }
            else
            {
                prev = temp;
                //if there is a node at that begins with character at word_i then search for the remaining word in that child node
                temp = temp -> children[word[word_i]];
            }
        }
    
        cout<<"deleting the node with key "<<word<<endl;
        
        // if the node has children then delete its data
        if (temp->children.size() > 0)
        {
            temp->data = NULL;
        }
        // if the node has no child then delete the node
        else
        {
            prev->children.erase(temp->identifier[0]);
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
    
    trie.insert("helo", "helo");
    trie.insert("heloooo", "heloo");
    trie.insert("hi", "hi");
    // trie.insert("hel", "hel");
    trie.insert("hello", "hello");
    trie.insert("hey", "hey");

    // trie.search("he"); // prints nothing
    // trie.search("hey"); // prints that the node has 5 stored in it
    cout<<"\nbefore deleting: "<<endl;
    trie.printChildren("h");

    trie.Delete("hello");

    cout<<"\nafter deleting: "<<endl;
    trie.printChildren("h");

    return 0;
}