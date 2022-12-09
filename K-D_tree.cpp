#include <bits/stdc++.h>
#include <iostream>
using namespace std;

int k = 2;

struct node
{
    vector<double> point;
    node *left;
    node *right;
};

struct node *createNode(vector<double> p)
{
    struct node *temp = new node();
    for (int i = 0; i < k; i++)
    {
        temp->point.push_back(p[i]);
    }
    temp->left = temp->right = NULL;
    return temp;
}

node *insertNode(node *root, vector<double> p, int depth)
{
    if (root == NULL)
    {
        root = createNode(p);
        return root;
    }

    int cut_dimension = depth % k;

    if (p[cut_dimension] < root->point[cut_dimension])
    {
        root->left = insertNode(root->left, p, depth + 1);
    }
    else
    {
        root->right = insertNode(root->right, p, depth + 1);
    }

    return root;
}

int main(void)
{
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    struct node *root = NULL;
    vector<double> p;
    for (int i = 0; i < n; i++)
    {
        double x, y;
        cin >> x >> y;
        p.clear();
        p.push_back(x);
        p.push_back(y);
        root = insertNode(root, p, 0);
    }

    return 0;
}