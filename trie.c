
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "trie.h"


node* malloc_trie(char letter)
{
    // 'calloc' initializes the memory to zero
    node* trie = (node*)calloc(1, sizeof(node));
    trie->letter = letter;
    //trie->count = 0;
    //memset(trie->children, 0, sizeof(trie->children));
    return trie;
}


void free_trie(node* trie)
{
    // traverse children to call their 'free'
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        node* child = trie->children[i];
        if (NULL != child)
        {
            free_trie(child);
        }
    }
    free(trie);
}


int update_trie(node* root, char* word)
{
    // because we have no more letters to consume from 'word'.
    // the node 'root' is actually a leaf in the tree,
    // we update that we have seen the 'word' one more time
    if (*word == '\0')
    {
        return root->count++;
    }

    // this 'root' node does not know how many times we encountered the word so far
    // so the job is delegated to the appropriate child
    char letter = *word;
    char child_index = letter - 'a';
    node* child = root->children[child_index];
    // if a child node does not exist, we allocate a new one to complete the job
    if (NULL == child) {
        child = malloc_trie(letter);
        root->children[child_index] = child;
    }
    // ask the approptiate child about the rest of the word
    return update_trie(child, word+1);
}


static void _traverse_trie(node* trie, boolean reversed, char* visit, int length)
{
    visit[length++] = trie->letter;

    // print the reconstructed word
    if (trie->count)
    {
        visit[length] = '\0';
        printf("%s %ld\n", visit, trie->count);
    }

    // traverse children alphabetically (or 'reversed')
    for (int i = 0; i < NUM_LETTERS; i++)
    {
        int index = (!reversed) ? (i) : (NUM_LETTERS - i - 1);
        node* child = trie->children[index];
        if (NULL != child)
        {
            _traverse_trie(child, reversed, visit, length);
        }
    }
}


void traverse_trie(node* root, boolean reversed, int limit)
{
    char* buffer = malloc(limit);
    // the root node of the trie contains a null-terminator 'letter' and zero 'count'
    // the algorithm '_traverse_trie' assumes it is called since the first letter of the word
    // so we incerement the 'buffer' to allow the null-terminator to be written without access-violation
    _traverse_trie(root, reversed, buffer + 1, -1);
    // do not forget to release ;)
    free(buffer);
}
