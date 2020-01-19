


#define NUM_LETTERS ((int)26)

typedef enum {FALSE=0, TRUE=1} boolean;
typedef struct node {
    char letter;
    long unsigned int count;
    struct node* children[NUM_LETTERS];
} node;


// malloc a new node struct and return a pointer to it
// char letter: input   used to reconstruct the path words counted
// return:              pointer to allocated node struct
// note: do not forget to 'free'
node* malloc_trie(char letter);


// Mr.PoopyButthole says: "always release your trie!"
void free_trie(node* trie);


// Update existing TRIE according to the input word
// node* root:  ouptput root node of trie structure
// char* word:  input   address of first character
// return:              frequency of 'word' in the trie 'root'
int update_trie(node* root, char* word);


// traverse the trie using DFS recursively
// while reconstructing counted words.
// note: each node with a positive 'count' means a word that we have encountered
void traverse_trie(node* root, boolean reversed, int limit);
