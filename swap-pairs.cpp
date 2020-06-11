#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <fstream>

using namespace std;

struct ListNode
{
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
  friend ostream &operator<<(ostream &os, ListNode *node)
  {
    while (node != nullptr)
    {
      os << node->val << ' ';
      node = node->next;
    }
    os << endl;
    return os;
  }
};

auto compare = [](const ListNode *a, const ListNode *b) {
  if (!a || !b)
  {
    return false;
  }
  return a->val > b->val;
};

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        bool isEven = true;
        ListNode* curr = head;
        ListNode* prev = nullptr;
        while (curr != nullptr)
        {
          if (isEven && curr->next) {
              auto next = curr->next;
              curr->next = next->next;
              next->next = curr;
              if (head == curr)  {
                  head = next;
              }
              if (prev) {
                  prev->next = next;
              }
          } else {
              prev = curr;
              curr = curr->next;
              cout << (curr ? curr->val : -1) << curr << endl;
          }
          isEven = !isEven;
        }
    }
};

ListNode *reverseList(ListNode *lst)
{
  if (lst == nullptr)
  {
    return nullptr;
  }
  ListNode *head = lst;
  ListNode *curr = head->next;
  head->next = nullptr;
  ListNode *moving = head;
  while (curr != nullptr)
  {
    ListNode *temp = curr->next;
    curr->next = moving;
    moving = curr;
    curr = temp;
  }
  return moving;
}

struct deletePtr
{
  template <typename P>
  void operator()(P p)
  {
    while (p != nullptr)
    {
      auto t = p->next;
      delete p;
      p = t;
    }
  }
};

int main()
{
  int tc;
  stringstream ss;
  string line;
  ifstream fin("swap-pairs.txt");

  getline(fin, line);
  ss << line;
  ss >> tc;
  ss.clear();

  for (int i = 0; i < tc; ++i)
  {
      ListNode* nList;

      getline(fin, line);
      ss << line;
      if (line.size() == 0)
      {
        nList = nullptr;
      }
      int k = 0;
      int num;
      while (ss >> num)
      {
        if (k == 0)
        {
          ListNode *first = new ListNode(num);
          nList = first;
        }
        else
        {
          ListNode *next = new ListNode(num, nList);
          nList = next;
        }
        k++;
      }
      cout << nList << endl;
      nList = reverseList(nList);
      cout << "rev: " << nList << endl;
      Solution().swapPairs(nList);
      deletePtr()(nList);
  }
}
