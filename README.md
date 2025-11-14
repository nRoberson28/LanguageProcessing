# LanguageProcessing
A Splay tree stores books by title; each node holds an AVL tree containing the book’s words. Users search the Splay tree for a title, then query the AVL tree for word info, e.g., word frequency in a book or whether a word is common across authors.

This is a shell data structure which consists of a Splay tree in which we can store the information about several books. The information stored is the title, the author, and the text. The text is stored in an AVL tree- every node in the Splay tree contains an AVL tree. The user is able to access the text by searching the Splay tree for a specific title. The text of every book is stored as words in the AVL tree. The user is able to search the AVL tree and collect some information about the text. Some examples of queries:

The number of occurrences of a word in a book.
Check whether a word is commonly used by multiple authors.
