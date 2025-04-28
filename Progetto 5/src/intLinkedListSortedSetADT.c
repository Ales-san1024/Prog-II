#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#include "../include/intSortedSetADT.h"
#include "../include/intLinkedListSortedSetADT.h"

IntSortedSetADT mkSSet() {
  IntSortedSetADT s;
  s = (IntSortedSetADT)malloc(sizeof(struct intSortedSet));
  
  if (!s) return NULL;
  s->size = 0;
  s->first = NULL;
  s->last = NULL;
  return s;
}

_Bool dsSSet(IntSortedSetADT *ssptr) {
    if (!ssptr || !(*ssptr)) return false;
    ListNodePtr node = (*ssptr)->first;
    ListNodePtr tmp;
    while (node) {
      tmp = node;
      node = node->next;
      free(tmp);
    }
    free(*ssptr);
    *ssptr = NULL;
    return 1;
}

_Bool sset_add(IntSortedSetADT ss, const int elem) {
  if (!ss) return false;
  ListNodePtr node = ss->first;
  ListNodePtr prev = NULL;

  
  while (node && node->elem < elem) {
    prev = node;
    node = node->next;
  }
  if (node && node->elem == elem) return false;

  ListNodePtr new;
  new = (ListNodePtr)malloc(sizeof(ListNode));
  new->elem = elem;
  new->next = node;
  if (!prev) ss->first = new;
  else prev->next = new;

  if (new->next == NULL) ss->last = new;
  (ss->size)++;
  return true;
}

_Bool sset_remove(const IntSortedSetADT ss, const int elem) {
  if (!ss) return false;
  
  ListNodePtr curr = ss->first;
  ListNodePtr prev = NULL;

  while (curr && curr->elem < elem) {
    prev = curr;
    curr = curr->next;
  }

  if (!curr || curr->elem > elem) return false;
  
  if (prev) prev->next = curr->next;
  else ss->first = curr->next;
  
  if (!(curr->next)) ss->last = prev;
  
  free(curr);
  
  (ss->size)--;

  return true;
}

_Bool sset_member(const IntSortedSetADT ss, const int elem) {
  if (!ss) return false;

  ListNodePtr node = ss->first;

  while (node && node->elem < elem) node = node->next;
  if (!node || node->elem > elem) return false;
  return true;
}

_Bool isEmptySSet(const IntSortedSetADT ss) {
    return (ss && ss->size == 0);
}

int sset_size(const IntSortedSetADT ss) {
    return ss? ss->size : -1;
}

_Bool sset_extract(IntSortedSetADT ss, int *ptr) {
  //Toglie e restituisce un elemento a caso dell'insieme
  
  if (!ss || ss->size <= 0 || !ptr) return false;
  
  
  
  int index = rand() % ss->size; 
  ListNodePtr curr = ss->first;
  ListNodePtr prev = NULL;
  int i = 0;
  while (i < index) {
    prev = curr;  
    curr = curr->next;
    ++i;
  }

  if (curr == ss->first) ss->first = curr->next;
  else if (curr == ss->last) ss->last = prev;
  else prev->next = curr->next;

  *ptr = curr->elem;
  free(curr);
  (ss->size)--;
  
  return true;
}

_Bool sset_equals(const IntSortedSetADT s1, const IntSortedSetADT s2) {
    if (!s1 || !s2 || s1->size != s2->size) return false;

    ListNodePtr a = s1->first;
    ListNodePtr b = s2->first;

    while (a && b) {
      if ( a->elem != b->elem) return false;
      a = a->next;
      b = b->next;
    }
    
    return !a && !b;
}

_Bool sset_subseteq(const IntSortedSetADT s1, const IntSortedSetADT s2) {
  if (!s1 || !s2 || s1->size > s2->size) return false; //s2 non può essere incluso in s1 se s1->size < s2->size
  
  ListNodePtr curr1 = s1->first;
  ListNodePtr curr2 = s2->first;

  while (curr1 && curr2) {
    if (curr2->elem > curr1->elem) return false;
    if (curr2->elem == curr1->elem) curr1 = curr1->next;
    curr2 = curr2->next; 
  }

  return (!curr1);
}

_Bool sset_subset(const IntSortedSetADT s1, const IntSortedSetADT s2) {
  if (!s1 || !s2 || s1->size >= s2->size) return false; //s2 non può essere incluso in s1 se s1->size < s2->size
  
  ListNodePtr curr1 = s1->first;
  ListNodePtr curr2 = s2->first;

  while (curr1 && curr2) {
    if (curr2->elem > curr1->elem) return false;
    if (curr1->elem == curr2->elem) curr1 = curr1->next;
    curr2 = curr2->next; 
  }

  return (!curr1);
}

IntSortedSetADT sset_union(const IntSortedSetADT s1, const IntSortedSetADT s2) {
  if (!s1 || !s2) return NULL;
  
  IntSortedSetADT u = mkSSet();
  if (!u) return NULL;
  
  ListNodePtr curr1 = s1->first;
  ListNodePtr curr2 = s2->first;

  while (curr1) {
    sset_add(u, curr1->elem);
    curr1 = curr1->next;
  }
  while (curr2) {
    sset_add(u, curr2->elem);
    curr2 = curr2->next;
  }
  return u;
}

IntSortedSetADT sset_intersection(const IntSortedSetADT s1, const IntSortedSetADT s2) {
  if (!s1 || !s2) return NULL;
  
  IntSortedSetADT intersex = mkSSet();  
  if (!intersex) return NULL;

  ListNodePtr curr1 = s1->first;
  ListNodePtr curr2 = s2->first;

  while (curr1 && curr2) {
    if (curr1->elem == curr2->elem) sset_add(intersex, curr1->elem);
    if (curr1->elem < curr2->elem) curr1 = curr1->next;
    else curr2 = curr2->next;
  }
  return intersex;
  
}

IntSortedSetADT sset_subtraction(const IntSortedSetADT s1, const IntSortedSetADT s2) {
  if (!s1 || !s2)  return NULL;
  
  IntSortedSetADT sub = mkSSet();
  if (!sub) return NULL;

  ListNodePtr curr1 = s1->first;
  ListNodePtr curr2 = s2->first;

  while (curr1 && curr2) {
    if (curr1->elem < curr2->elem) sset_add(sub, curr1->elem);
    else curr2 = curr2->next;
    curr1 = curr1->next;
  }
  //aggiunge gli elementi rimanenti di s1, se ci sono
  while (curr1) {
    sset_add(sub, curr1->elem);
    curr1 = curr1->next;
  }

  return sub;
}

_Bool sset_min(const IntSortedSetADT ss, int *ptr) {
    if (!ss || !(ss->first)) return false;
    *ptr = ss->first->elem;
    return true;
}

_Bool sset_max(const IntSortedSetADT ss, int *ptr) {
  if (!ss || !(ss->first)) return false; //ss->first == NULL => ss->last == NULL
  *ptr = ss->last->elem;
  return true;
}

_Bool sset_extractMin(IntSortedSetADT ss, int *ptr) {
  if (!ss || !(ss->first)) return false;
  *ptr = ss->first->elem;
  return sset_remove(ss, *ptr);
    
}

_Bool sset_extractMax(IntSortedSetADT ss, int *ptr) {
  if (!ss || !(ss->first)) return false; //ss->first == NULL => ss->last == NULL
  *ptr = ss->last->elem;
  return sset_remove(ss, *ptr);       
}