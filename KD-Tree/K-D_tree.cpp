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

bool similarityCheck(vector<double> x, vector<double> y)
{
    if (x == y)
    {
        return true;
    }
    return false;
}

bool searchNode(node *root, vector<double> p, int depth)
{
    if (root == NULL)
    {
        return false;
    }

    if (similarityCheck(root->point, p))
    {
        return true;
    }

    int cut_dimension = depth % k;

    if (p[cut_dimension] < root->point[cut_dimension])
    {
        return searchNode(root->left, p, depth + 1);
    }
    else
    {
        return searchNode(root->right, p, depth + 1);
    }
}

double minimum(double a, double b, double c)
{
    return min(a, min(b, c));
}

double findMin(node *root, int d, int depth)
{
    if (root == NULL)
    {
        return 100000000.00;
    }

    int cut_dimension = depth % k;

    if (cut_dimension == d)
    {
        if (root->left == NULL)
        {
            return root->point[d];
        }
        else
        {
            return min(root->point[d], findMin(root->left, d, depth + 1));
        }
    }

    return minimum(root->point[d], findMin(root->left, d, depth + 1), findMin(root->right, d, depth + 1));
}

int main(void)
{
    // cout << "Enter the tree dimension: ";
    // cin >> k;

    cout << "\nEnter total number of nodes and edges: " << endl;
    freopen("input.txt", "r", stdin);
    int n;
    cin >> n;

    // tree creation
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

    // searching a node
    vector<double> p1;
    p1.push_back(7);
    p1.push_back(8.1);
    bool flag = searchNode(root, p1, 0);
    if (flag)
    {
        cout << "Found" << endl;
    }
    else
    {
        cout << "Not Found" << endl;
    }

    // finding minimum value in a dimension
    int d = 1; // input dimension
    cout << "Min value in dimension " << d << " is: " << findMin(root, d, 0);

    return 0;
}