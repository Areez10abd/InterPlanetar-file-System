/*
#pragma once
#include <iostream>
#define MAX 4
#define MIN 2

using namespace std;

class BTreeNode {
public:
    int count;
    int value[MAX + 1];
     
    BTreeNode* child[MAX + 1];

    BTreeNode() {
        count = 0;
        for (int i = 0; i <= MAX; i++) {
            value[i] = 0;
            child[i] = nullptr;
        }
    }
};

BTreeNode* insert(BTreeNode*, int);
int setval(int, BTreeNode*, int*, BTreeNode**);
BTreeNode* search(int, BTreeNode*, int*);
int search_node(int, BTreeNode*, int*);
void fill_node(int, BTreeNode*, BTreeNode*, int);
void split(int, BTreeNode*, BTreeNode*, int, int*, BTreeNode**);
BTreeNode* Delete(BTreeNode*, int);
int delhelp(BTreeNode*, int);
void clear(BTreeNode*, int);
void copysucc(BTreeNode*, int);
void restore(BTreeNode*, int);
void rightshift(BTreeNode*, int);
void leftshift(BTreeNode*, int);
void merge(BTreeNode*, int);
void displayb(BTreeNode*);
void print_tree(BTreeNode* root, int prelen);

BTreeNode* insert(BTreeNode* root, int val) {
    int i;
    BTreeNode* c, * n;
    int flag;
    flag = setval(val, root, &i, &c);
    if (flag) {
        n = new BTreeNode();
        n->count = 1;
        n->value[1] = i;
        n->child[0] = root;
        n->child[1] = c;
        return n;
    }
    return root;
}

int setval(int val, BTreeNode* n, int* p, BTreeNode** c) {
    int k;
    if (n == NULL) {
        *p = val;
        *c = NULL;
        return 1;
    }
    else {
        if (search_node(val, n, &k))
            printf("\nKey value already exists.\n");
        if (setval(val, n->child[k], p, c)) {
            if (n->count < MAX) {
                fill_node(*p, *c, n, k);
                return 0;
            }
            else {
                split(*p, *c, n, k, p, c);
                return 1;
            }
        }
        return 0;
    }
}

BTreeNode* search(int val, BTreeNode* root, int* pos) {
    if (root == NULL)
        return NULL;
    else {
        if (search_node(val, root, pos))
            return root;
        else
            return search(val, root->child[*pos], pos);
    }
}

int search_node(int val, BTreeNode* root, int* pos) {
    if (val < root->value[1]) {
        *pos = 0;
        return 0;
    }
    else {
        *pos = root->count;
        while ((val < root->value[*pos]) && *pos > 1)
            (*pos)--;

        if (val == root->value[*pos]) //found
            return 1;
        else
            return 0;
    }
}

void fill_node(int val, BTreeNode* c, BTreeNode* root, int k) {
    int i;
    for (i = root->count; i > k; i--) {
        root->value[i + 1] = root->value[i];
        root->child[i + 1] = root->child[i];
    }
    root->value[k + 1] = val;
    root->child[k + 1] = c;
    root->count++;
}

void split(int val, BTreeNode* c, BTreeNode* n, int k, int* y, BTreeNode** newnode) {
    int i, mid;
    if (k <= MIN)
        mid = MIN;
    else
        mid = MIN + 1;
    *newnode = new BTreeNode();
    for (i = mid + 1; i <= MAX; i++) {
        (*newnode)->value[i - mid] = n->value[i];
        (*newnode)->child[i - mid] = n->child[i];
    }
    (*newnode)->count = MAX - mid;
    n->count = mid;
    if (k <= MIN)
        fill_node(val, c, n, k);
    else
        fill_node(val, c, *newnode, k - mid);
    *y = n->value[n->count];
    (*newnode)->child[0] = n->child[n->count];
    n->count--;
}

BTreeNode* Delete(BTreeNode* root, int val) {
    BTreeNode* temp;
    if (!delhelp(root, val))
        printf("\nValue %d not found.", val);
    else {
        if (root->count == 0) {
            temp = root;
            root = root->child[0];
            delete temp;
        }
    }
    return root;
}

int delhelp(BTreeNode* root, int val) {
    int i;
    int flag;
    if (root == NULL)
        return 0;
    else {
        flag = search_node(val, root, &i);
        if (flag) {
            if (root->child[i - 1]) {
                copysucc(root, i);
                flag = delhelp(root->child[i], root->value[i]);
                if (!flag)
                    printf("\nValue %d not found.", val);
            }
            else
                clear(root, i);
        }
        else
            flag = delhelp(root->child[i], val);
        if (root->child[i] != NULL) {
            if (root->child[i]->count < MIN)
                restore(root, i);
        }
        return flag;
    }
}

void clear(BTreeNode* node, int k) {
    int i;
    for (i = k + 1; i <= node->count; i++) {
        node->value[i - 1] = node->value[i];
        node->child[i - 1] = node->child[i];
    }
    node->count--;
}

void copysucc(BTreeNode* node, int i) {
    BTreeNode* temp;
    temp = node->child[i];
    while (temp->child[0])
        temp = temp->child[0];
    node->value[i] = temp->value[1];
}

void restore(BTreeNode* node, int i) {
    if (i == 0) {
        if (node->child[1]->count > MIN)
            leftshift(node, 1);
        else
            merge(node, 1);
    }
    else {
        if (i == node->count) {
            if (node->child[i - 1]->count > MIN)
                rightshift(node, i);
            else
                merge(node, i);
        }
        else {
            if (node->child[i - 1]->count > MIN)
                rightshift(node, i);
            else {
                if (node->child[i + 1]->count > MIN)
                    leftshift(node, i + 1);
                else
                    merge(node, i);
            }
        }
    }
}

void rightshift(BTreeNode* node, int k) {
    int i;
    BTreeNode* temp;
    temp = node->child[k];
    for (i = temp->count; i > 0; i--) {
        temp->value[i + 1] = temp->value[i];
        temp->child[i + 1] = temp->child[i];
    }
    temp->child[1] = temp->child[0];
    temp->count++;
    temp->value[1] = node->value[k];
    temp = node->child[k - 1];
    node->value[k] = temp->value[temp->count];
    node->child[k]->child[0] = temp->child[temp->count];
    temp->count--;
}

void leftshift(BTreeNode* node, int k) {
    int i;
    BTreeNode* temp;
    temp = node->child[k - 1];
    temp->count++;
    temp->value[temp->count] = node->value[k];
    temp->child[temp->count] = node->child[k]->child[0];
    temp = node->child[k];
    node->value[k] = temp->value[1];
    temp->child[0] = temp->child[1];
    temp->count--;
    for (i = 1; i <= temp->count; i++) {
        temp->value[i] = temp->value[i + 1];
        temp->child[i] = temp->child[i + 1];
    }
}

void merge(BTreeNode* node, int k) {
    int i;
    BTreeNode* temp1, * temp2;
    temp1 = node->child[k];
    temp2 = node->child[k - 1];
    temp2->count++;
    temp2->value[temp2->count] = node->value[k];
    temp2->child[temp2->count] = node->child[0];

    for (i = 1; i <= temp1->count; i++) {
        temp2->count++;
        temp2->value[temp2->count] = temp1->value[i];
        temp2->child[temp2->count] = temp1->child[i];
    }

    for (i = k; i < node->count; i++) {
        node->value[i] = node->value[i + 1];
        node->child[i] = node->child[i + 1];
    }
    node->count--;
    delete temp1;
}

void displayb(BTreeNode* root) {
    int i;
    if (root != NULL) {
        for (i = 0; i < root->count; i++) {
            displayb(root->child[i]);
            cout << root->value[i + 1] << "\t";
        }
        displayb(root->child[i]);
    }
}

void print_tree(BTreeNode* root, int prelen) {
    int i, j;
    if (root != NULL) {
        for (j = 0; j < prelen; j++)

            for (i = 1; i <= root->count; i++) {
                cout << root->value[i] << "\t";
            }

        for (i = root->count; i >= 0; i--) {
        }
    }
}

*/
/*
#pragma once
#include <iostream>
#define MAX 4
#define MIN 2

using namespace std;

class BTreeNode {
public:
    int count;
    int value[MAX + 1];
    string hash[MAX + 1];
    string path[MAX + 1];
    BTreeNode* child[MAX + 1];

    BTreeNode() {
        count = 0;
        for (int i = 0; i <= MAX; i++) {
            value[i] = 0;
            child[i] = nullptr;
        }
    }
};

BTreeNode* insert(BTreeNode*, int, string, string);
int setval(int, string, string, BTreeNode*, int*, BTreeNode**);
BTreeNode* search(int, string, string, BTreeNode*, int*);
int search_node(int, string, string, BTreeNode*, int*);
void fill_node(int, string, string, BTreeNode*, BTreeNode*, int);
void split(int, string, string, BTreeNode*, BTreeNode*, int, int*, BTreeNode**);
BTreeNode* Delete(BTreeNode*, int, string, string);
int delhelp(BTreeNode*, int, string, string);
void clear(BTreeNode*, int);
void copysucc(BTreeNode*, int);
void restore(BTreeNode*, int);
void rightshift(BTreeNode*, int);
void leftshift(BTreeNode*, int);
void merge(BTreeNode*, int);
void displayb(BTreeNode*);
void print_tree(BTreeNode* root, int prelen);

BTreeNode* insert(BTreeNode* root, int val, string hash, string path) {
    int i;
    BTreeNode* c, * n;
    int flag;
    flag = setval(val, hash, path, root, &i, &c);
    if (flag) {
        n = new BTreeNode();
        n->count = 1;
        n->hash[1] = hash;
        n->path[1] = path;
        n->value[1] = i;
        n->child[0] = root;
        n->child[1] = c;
        return n;
    }
    return root;
}

int setval(int val, string hash, string path, BTreeNode* n, int* p, BTreeNode** c) {
    int k;
    if (n == NULL) {
        *p = val;
        *c = NULL;
        return 1;
    }
    else {
        if (search_node(val, hash, path, n, &k))
            printf("\nKey value already exists.\n");
        if (setval(val, hash, path, n->child[k], p, c)) {
            if (n->count < MAX) {
                fill_node(*p, hash, path, *c, n, k);
                return 0;
            }
            else {
                split(*p, hash, path, *c, n, k, p, c);
                return 1;
            }
        }
        return 0;
    }
}

BTreeNode* search(int val, string hash, string path, BTreeNode* root, int* pos) {
    if (root == NULL)
        return NULL;
    else {
        if (search_node(val, hash, path, root, pos))
            return root;
        else
            return search(val, hash, path, root->child[*pos], pos);
    }
}

int search_node(int val, string hash, string path, BTreeNode* root, int* pos) {
    if (val < root->value[1]) {
        *pos = 0;
        return 0;
    }
    else {
        *pos = root->count;
        while ((val < root->value[*pos]) && *pos > 1)
            (*pos)--;

        if (val == root->value[*pos] && hash == root->hash[*pos]) //found
            return 1;
        else
            return 0;
    }
}

void fill_node(int val, string hash, string path, BTreeNode* c, BTreeNode* root, int k) {
    int i;
    for (i = root->count; i > k; i--) {
        root->value[i + 1] = root->value[i];
        root->hash[i + 1] = root->hash[i];
        root->path[i + 1] = root->path[i];
        root->child[i + 1] = root->child[i];
    }
    root->value[k + 1] = val;
    root->hash[k + 1] = hash;
    root->path[k + 1] = path;
    root->child[k + 1] = c;
    root->count++;
}

void split(int val, string hash, string path, BTreeNode* c, BTreeNode* n, int k, int* y, BTreeNode** newnode) {
    int i, mid;
    if (k <= MIN)
        mid = MIN;
    else
        mid = MIN + 1;
    *newnode = new BTreeNode();
    for (i = mid + 1; i <= MAX; i++) {
        (*newnode)->value[i - mid] = n->value[i];
        (*newnode)->hash[i - mid] = n->hash[i];
        (*newnode)->path[i - mid] = n->path[i];
        (*newnode)->child[i - mid] = n->child[i];
    }
    (*newnode)->count = MAX - mid;
    n->count = mid;
    if (k <= MIN)
        fill_node(val, hash, path, c, n, k);
    else
        fill_node(val, hash, path, c, *newnode, k - mid);
    *y = n->value[n->count];
    (*newnode)->child[0] = n->child[n->count];
    n->count--;
}

BTreeNode* Delete(BTreeNode* root, int val, string hash, string path) {
    BTreeNode* temp;
    if (!delhelp(root, val, hash, path))
        cout << "\nValue %d not found." << val;
    else {
        if (root->count == 0) {
            temp = root;
            root = root->child[0];
            delete temp;
        }
    }
    return root;
}

int delhelp(BTreeNode* root, int val, string hash, string path) {
    int i;
    int flag;
    if (root == NULL)
        return 0;
    else {
        flag = search_node(val, hash, path, root, &i);
        if (flag) {
            if (root->child[i - 1]) {
                copysucc(root, i);
                flag = delhelp(root->child[i], root->value[i], root->hash[i], root->path[i]);
                if (!flag)
                    printf("\nValue %d not found.", val);
            }
            else
                clear(root, i);
        }
        else
            flag = delhelp(root->child[i], val, hash, path);
        if (root->child[i] != NULL) {
            if (root->child[i]->count < MIN)
                restore(root, i);
        }
        return flag;
    }
}

void clear(BTreeNode* node, int k) {
    int i;
    for (i = k + 1; i <= node->count; i++) {
        node->value[i - 1] = node->value[i];
        node->hash[i - 1] = node->hash[i];
        node->path[i - 1] = node->path[i];
        node->child[i - 1] = node->child[i];
    }
    node->count--;
}

void copysucc(BTreeNode* node, int i) {
    BTreeNode* temp;
    temp = node->child[i];
    while (temp->child[0])
        temp = temp->child[0];
    node->value[i] = temp->value[1];
    node->hash[i] = temp->hash[1];
    node->path[i] = temp->path[1];
}

void restore(BTreeNode* node, int i) {
    if (i == 0) {
        if (node->child[1]->count > MIN)
            leftshift(node, 1);
        else
            merge(node, 1);
    }
    else {
        if (i == node->count) {
            if (node->child[i - 1]->count > MIN)
                rightshift(node, i);
            else
                merge(node, i);
        }
        else {
            if (node->child[i - 1]->count > MIN)
                rightshift(node, i);
            else {
                if (node->child[i + 1]->count > MIN)
                    leftshift(node, i + 1);
                else
                    merge(node, i);
            }
        }
    }
}

void rightshift(BTreeNode* node, int k) {
    int i;
    BTreeNode* temp;
    temp = node->child[k];
    for (i = temp->count; i > 0; i--) {
        temp->value[i + 1] = temp->value[i];
        temp->hash[i + 1] = temp->hash[i];
        temp->path[i + 1] = temp->path[i];
        temp->child[i + 1] = temp->child[i];
    }
    temp->child[1] = temp->child[0];
    temp->count++;
    temp->value[1] = node->value[k];
    temp->hash[1] = node->hash[k];
    temp->path[1] = node->path[k];
    temp = node->child[k - 1];
    node->value[k] = temp->value[temp->count];
    node->hash[k] = temp->hash[temp->count];
    node->path[k] = temp->path[temp->count];
    node->child[k]->child[0] = temp->child[temp->count];
    temp->count--;
}

void leftshift(BTreeNode* node, int k) {
    int i;
    BTreeNode* temp;
    temp = node->child[k - 1];
    temp->count++;
    temp->value[temp->count] = node->value[k];
    temp->hash[temp->count] = node->hash[k];
    temp->path[temp->count] = node->path[k];
    temp->child[temp->count] = node->child[k]->child[0];
    temp = node->child[k];
    node->value[k] = temp->value[1];
    node->hash[k] = temp->hash[1];
    node->path[k] = temp->path[1];

    temp->child[0] = temp->child[1];
    temp->count--;
    for (i = 1; i <= temp->count; i++) {
        temp->value[i] = temp->value[i + 1];
        temp->hash[i] = temp->hash[i + 1];
        temp->path[i] = temp->path[i + 1];
        temp->child[i] = temp->child[i + 1];
    }
}

void merge(BTreeNode* node, int k) {
    int i;
    BTreeNode* temp1, * temp2;
    temp1 = node->child[k];
    temp2 = node->child[k - 1];
    temp2->count++;
    temp2->value[temp2->count] = node->value[k];
    temp2->hash[temp2->count] = node->hash[k];
    temp2->path[temp2->count] = node->path[k];
    temp2->child[temp2->count] = node->child[0];

    for (i = 1; i <= temp1->count; i++) {
        temp2->count++;
        temp2->value[temp2->count] = temp1->value[i];
        temp2->hash[temp2->count] = temp1->hash[i];
        temp2->path[temp2->count] = temp1->path[i];
        temp2->child[temp2->count] = temp1->child[i];
    }

    for (i = k; i < node->count; i++) {
        node->value[i] = node->value[i + 1];
        node->hash[i] = node->hash[i + 1];
        node->path[i] = node->path[i + 1];
        node->child[i] = node->child[i + 1];
    }
    node->count--;
    delete temp1;
}

void displayb(BTreeNode* root) {
    int i;
    if (root != NULL) {
        for (i = 0; i < root->count; i++) {
            displayb(root->child[i]);
            cout << root->value[i + 1] << "\t";
            cout << root->hash[i + 1] << "\t";
            cout << root->path[i + 1] << "\n";
        }
        displayb(root->child[i]);
    }
}

void print_tree(BTreeNode* root, int prelen) {
    int i, j;
    if (root != NULL) {
        for (j = 0; j < prelen; j++)

            for (i = 1; i <= root->count; i++) {
                cout << root->value[i] << "\t";
                cout << root->hash[i] << "\t";
                cout << root->path[i] << "\n";
            }

        for (i = root->count; i >= 0; i--) {
        }
    }
}

*/


#pragma once
#include <iostream>
#define MAX 4
#define MIN 2

using namespace std;

class BTreeNode {
public:
    int count;
    int value[MAX + 1];
    string hash[MAX + 1];
    string path[MAX + 1];
    BTreeNode* child[MAX + 1];

    BTreeNode() {
        count = 0;
        for (int i = 0; i <= MAX; i++) {
            value[i] = 0;
            child[i] = nullptr;
        }
    }
};

BTreeNode* insert(BTreeNode*, int, string, string);
int setval(int, string, string, BTreeNode*, int*, BTreeNode**);
BTreeNode* searchTree(int, BTreeNode*, int*);
int search_node(int, BTreeNode*, int*);
void fill_node(int, string, string, BTreeNode*, BTreeNode*, int);
void split(int, string, string, BTreeNode*, BTreeNode*, int, int*, BTreeNode**);
BTreeNode* Delete(BTreeNode*, int, string, string);
int delhelp(BTreeNode*, int, string, string);
void clear(BTreeNode*, int);
void copysucc(BTreeNode*, int);
void restore(BTreeNode*, int);
void rightshift(BTreeNode*, int);
void leftshift(BTreeNode*, int);
void merge(BTreeNode*, int);
void displayb(BTreeNode*);
void print_tree(BTreeNode* root, int prelen);

BTreeNode* insert(BTreeNode* root, int val, string hash, string path) {
    int i;
    BTreeNode* c, * n;
    int flag;
    flag = setval(val, hash, path, root, &i, &c);
    if (flag) {
        n = new BTreeNode();
        n->count = 1;
        n->hash[1] = hash;
        n->path[1] = path;
        n->value[1] = i;
        n->child[0] = root;
        n->child[1] = c;
        return n;
    }
    return root;
}

int setval(int val, string hash, string path, BTreeNode* n, int* p, BTreeNode** c) {
    int k;
    if (n == NULL) {
        *p = val;
        *c = NULL;
        return 1;
    }
    else {
        if (search_node(val, n, &k))
            printf("\nKey value already exists.\n");
        if (setval(val, hash, path, n->child[k], p, c)) {
            if (n->count < MAX) {
                fill_node(*p, hash, path, *c, n, k);
                return 0;
            }
            else {
                split(*p, hash, path, *c, n, k, p, c);
                return 1;
            }
        }
        return 0;
    }
}

BTreeNode* searchTree(int val, BTreeNode* root, int* pos) {
    if (root == NULL)
        return NULL;
    else {
        if (search_node(val, root, pos))
            return root;
        else
            return searchTree(val, root->child[*pos], pos);
    }
}

int search_node(int val, BTreeNode* root, int* pos) {
    if (val < root->value[1]) {
        *pos = 0;
        return 0;
    }
    else {
        *pos = root->count;
        while ((val < root->value[*pos]) && *pos > 1)
            (*pos)--;

        if (val == root->value[*pos]) //found
            return 1;
        else
            return 0;
    }
}

void fill_node(int val, string hash, string path, BTreeNode* c, BTreeNode* root, int k) {
    int i;
    for (i = root->count; i > k; i--) {
        root->value[i + 1] = root->value[i];
        root->hash[i + 1] = root->hash[i];
        root->path[i + 1] = root->path[i];
        root->child[i + 1] = root->child[i];
    }
    root->value[k + 1] = val;
    root->hash[k + 1] = hash;
    root->path[k + 1] = path;
    root->child[k + 1] = c;
    root->count++;
}

void split(int val, string hash, string path, BTreeNode* c, BTreeNode* n, int k, int* y, BTreeNode** newnode) {
    int i, mid;
    if (k <= MIN)
        mid = MIN;
    else
        mid = MIN + 1;
    *newnode = new BTreeNode();
    for (i = mid + 1; i <= MAX; i++) {
        (*newnode)->value[i - mid] = n->value[i];
        (*newnode)->hash[i - mid] = n->hash[i];
        (*newnode)->path[i - mid] = n->path[i];
        (*newnode)->child[i - mid] = n->child[i];
    }
    (*newnode)->count = MAX - mid;
    n->count = mid;
    if (k <= MIN)
        fill_node(val, hash, path, c, n, k);
    else
        fill_node(val, hash, path, c, *newnode, k - mid);
    *y = n->value[n->count];
    (*newnode)->child[0] = n->child[n->count];
    n->count--;
}

BTreeNode* Delete(BTreeNode* root, int val, string hash, string path) {
    BTreeNode* temp;
    if (!delhelp(root, val, hash, path))
        cout << "\nValue %d not found." << val;
    else {
        if (root->count == 0) {
            temp = root;
            root = root->child[0];
            delete temp;
        }
    }
    return root;
}

int delhelp(BTreeNode* root, int val, string hash, string path) {
    int i;
    int flag;
    if (root == NULL)
        return 0;
    else {
        flag = search_node(val, root, &i);
        if (flag) {
            if (root->child[i - 1]) {
                copysucc(root, i);
                flag = delhelp(root->child[i], root->value[i], root->hash[i], root->path[i]);
                if (!flag)
                    printf("\nValue %d not found.", val);
            }
            else
                clear(root, i);
        }
        else
            flag = delhelp(root->child[i], val, hash, path);
        if (root->child[i] != NULL) {
            if (root->child[i]->count < MIN)
                restore(root, i);
        }
        return flag;
    }
}

void clear(BTreeNode* node, int k) {
    int i;
    for (i = k + 1; i <= node->count; i++) {
        node->value[i - 1] = node->value[i];
        node->hash[i - 1] = node->hash[i];
        node->path[i - 1] = node->path[i];
        node->child[i - 1] = node->child[i];
    }
    node->count--;
}

void copysucc(BTreeNode* node, int i) {
    BTreeNode* temp;
    temp = node->child[i];
    while (temp->child[0])
        temp = temp->child[0];
    node->value[i] = temp->value[1];
    node->hash[i] = temp->hash[1];
    node->path[i] = temp->path[1];
}

void restore(BTreeNode* node, int i) {
    if (i == 0) {
        if (node->child[1]->count > MIN)
            leftshift(node, 1);
        else
            merge(node, 1);
    }
    else {
        if (i == node->count) {
            if (node->child[i - 1]->count > MIN)
                rightshift(node, i);
            else
                merge(node, i);
        }
        else {
            if (node->child[i - 1]->count > MIN)
                rightshift(node, i);
            else {
                if (node->child[i + 1]->count > MIN)
                    leftshift(node, i + 1);
                else
                    merge(node, i);
            }
        }
    }
}

void rightshift(BTreeNode* node, int k) {
    int i;
    BTreeNode* temp;
    temp = node->child[k];
    for (i = temp->count; i > 0; i--) {
        temp->value[i + 1] = temp->value[i];
        temp->hash[i + 1] = temp->hash[i];
        temp->path[i + 1] = temp->path[i];
        temp->child[i + 1] = temp->child[i];
    }
    temp->child[1] = temp->child[0];
    temp->count++;
    temp->value[1] = node->value[k];
    temp->hash[1] = node->hash[k];
    temp->path[1] = node->path[k];
    temp = node->child[k - 1];
    node->value[k] = temp->value[temp->count];
    node->hash[k] = temp->hash[temp->count];
    node->path[k] = temp->path[temp->count];
    node->child[k]->child[0] = temp->child[temp->count];
    temp->count--;
}

void leftshift(BTreeNode* node, int k) {
    int i;
    BTreeNode* temp;
    temp = node->child[k - 1];
    temp->count++;
    temp->value[temp->count] = node->value[k];
    temp->hash[temp->count] = node->hash[k];
    temp->path[temp->count] = node->path[k];
    temp->child[temp->count] = node->child[k]->child[0];
    temp = node->child[k];
    node->value[k] = temp->value[1];
    node->hash[k] = temp->hash[1];
    node->path[k] = temp->path[1];

    temp->child[0] = temp->child[1];
    temp->count--;
    for (i = 1; i <= temp->count; i++) {
        temp->value[i] = temp->value[i + 1];
        temp->hash[i] = temp->hash[i + 1];
        temp->path[i] = temp->path[i + 1];
        temp->child[i] = temp->child[i + 1];
    }
}

void merge(BTreeNode* node, int k) {
    int i;
    BTreeNode* temp1, * temp2;
    temp1 = node->child[k];
    temp2 = node->child[k - 1];
    temp2->count++;
    temp2->value[temp2->count] = node->value[k];
    temp2->hash[temp2->count] = node->hash[k];
    temp2->path[temp2->count] = node->path[k];
    temp2->child[temp2->count] = node->child[0];

    for (i = 1; i <= temp1->count; i++) {
        temp2->count++;
        temp2->value[temp2->count] = temp1->value[i];
        temp2->hash[temp2->count] = temp1->hash[i];
        temp2->path[temp2->count] = temp1->path[i];
        temp2->child[temp2->count] = temp1->child[i];
    }

    for (i = k; i < node->count; i++) {
        node->value[i] = node->value[i + 1];
        node->hash[i] = node->hash[i + 1];
        node->path[i] = node->path[i + 1];
        node->child[i] = node->child[i + 1];
    }
    node->count--;
    delete temp1;
}

void displayb(BTreeNode* root) {
    int i;
    if (root != NULL) {
        for (i = 0; i < root->count; i++) {
            displayb(root->child[i]);
            cout << root->value[i + 1] << "\t";
            cout << root->hash[i + 1] << "\t";
            cout << root->path[i + 1] << "\n";
        }
        displayb(root->child[i]);
    }
}

void print_tree(BTreeNode* root, int prelen) {
    int i, j;
    if (root != NULL) {
        for (j = 0; j < prelen; j++)

            for (i = 1; i <= root->count; i++) {
                cout << root->value[i] << "\t";
                cout << root->hash[i] << "\t";
                cout << root->path[i] << "\n";
            }

        for (i = root->count; i >= 0; i--) {
        }
    }
}