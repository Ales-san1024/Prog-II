#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../include/intSortedSetADT.h"
#include "../include/intLinkedListSortedSetADT.h"

IntSortedSetADT mkSSetv(int count, ...) {
    IntSortedSetADT set = mkSSet();

    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        int num = va_arg(args, int);
        sset_add(set,num);        
    }
    va_end(args);
    return set;
}

char *toString(IntSortedSetADT set) {
    char *sout = malloc(100*sizeof(char));

    ListNodePtr nptr = set->first;
    sprintf(sout, "{");
    while (nptr) {
        if (nptr == set->first)
            sprintf(sout+strlen(sout), "%d", nptr->elem);
        else
            sprintf(sout+strlen(sout), ",%d", nptr->elem);
        nptr = nptr->next;
    }

    sprintf(sout+strlen(sout), "}");

    return sout;
}

int check_mkSSet() {
    int passed = 1;
    printf("mkSet()\n");    
    IntSortedSetADT sptr = mkSSet();
    if (!sptr) {
        printf("FAILED");
        printf("EXPECTED: not %d\n", 0);   
    } else
        printf("OK\n");
    printf("RESULT:%p\n\n", (void *)sptr);  
    return passed;
}

int check_dsSSet() {
    int passed = 1;

    if (passed) {
        _Bool rv;
        IntSortedSetADT sptr = mkSSet();
        printf("dsSSet({})\n");    
        rv = dsSSet(&sptr);
        if (!rv || sptr) {
            printf("FAILED\n");
            printf("EXPECTED: NOT %d AND PTR %p\n", 0, (void *)NULL); 
            passed=0;  
        } else {
            printf("OK\n");
        }
        printf("RESULT:%d AND PTR %p\n\n", rv, (void *)sptr);
    }  

    if (passed) {
        _Bool rv;
        printf("dsSSet(NULL)\n");    
        rv = dsSSet(NULL);
        if (rv) {
            printf("FAILED\n");
            printf("EXPECTED: %d\n", 0);
            passed=0;   
        } else {
            printf("OK\n");
        }
        printf("RESULT:%d\n\n", rv);
    }

    return passed;
}

int check_sset_add() {
  int passed = 1;

  printf("sset_add()\n");

  IntSortedSetADT set = mkSSet();
  _Bool ok;

  ok = sset_add(set, 5);
  ok &= sset_add(set, 3);
  ok &= sset_add(set, 8);
  ok &= sset_add(set, 1);

  if (!ok) {
      printf("FAILED: errore nell'inserimento di nuovi elementi\n");
      passed = 0;
  }

  
  if (sset_add(set, 5)) {
      printf("FAILED: inserito un duplicato (5)\n");
      passed = 0;
  }

  char *str = toString(set);
  printf("Set risultante: %s\n", str);

  if (strcmp(str, "{1,3,5,8}") != 0) {
      printf("FAILED: atteso {1,3,5,8}\n");
      passed = 0;
  } else {
      printf("OK\n");
  }

  free(str);
  dsSSet(&set);
  printf("\n");
  return passed;
}

int check_sset_remove() {
  int passed = 1;
  IntSortedSetADT set = mkSSet();  // Creiamo un nuovo set vuoto

  printf("sset_remove()");
  // Aggiungiamo alcuni elementi al set
  sset_add(set, 10);
  sset_add(set, 20);
  sset_add(set, 30);

  // Verifica lo stato prima della rimozione
  printf("Before remove:\n");
  char *str = toString(set);
  printf("Set: %s\n", str);
  free(str);

  // Test rimozione di un elemento esistente
  if (!sset_remove(set, 20)) {
      printf("FAILED: Expected 20 to be removed\n");
      passed = 0;
  } else {
      printf("OK: 20 removed\n");
  }

  // Verifica lo stato dopo la rimozione
  printf("After remove 20:\n");
  str = toString(set);
  printf("Set: %s\n", str);
  free(str);

  // Test rimozione di un elemento che non esiste
  if (sset_remove(set, 100)) {
      printf("FAILED: Expected 100 not to be removed\n");
      passed = 0;
  } else {
      printf("OK: 100 not found\n");
  }

  // Verifica lo stato dopo aver tentato di rimuovere un elemento non presente
  printf("After remove 100 (non-existent):\n");
  str = toString(set);
  printf("Set: %s\n", str);
  free(str);

  // Rimuoviamo l'ultimo elemento (30)
  if (!sset_remove(set, 30)) {
      printf("FAILED: Expected 30 to be removed\n");
      passed = 0;
  } else {
      printf("OK: 30 removed\n");
  }

  // Verifica lo stato dopo aver rimosso l'ultimo elemento
  printf("After remove 30 (last element):\n");
  str = toString(set);
  printf("Set: %s\n", str);
  free(str);

  // Test rimozione del primo elemento (10)
  if (!sset_remove(set, 10)) {
      printf("FAILED: Expected 10 to be removed\n");
      passed = 0;
  } else {
      printf("OK: 10 removed\n");
  }

  // Verifica lo stato dopo aver rimosso l'ultimo elemento
  printf("After remove 10 (first element):\n");
  str = toString(set);
  printf("Set: %s\n", str);
  free(str);

  // Verifica che il set sia vuoto alla fine
  if (set->size != 0) {
      printf("FAILED: Expected set size to be 0, but got %d\n", set->size);
      passed = 0;
  } else {
      printf("OK: Set size is 0\n");
  }

  return passed;
}

int check_sset_member() {
  int passed = 1;

  // Creiamo un nuovo set
  IntSortedSetADT set = mkSSet();  
  
  printf("sseet_member()\n");

  if (sset_member(set, 20)) {
    printf("FAILED: Expected 20 not to be found in empty set\n");
    passed = 0;
  } else printf("OK: 20 not found\n");

  // Aggiungiamo alcuni elementi al set
  sset_add(set, 10);
  sset_add(set, 20);
  sset_add(set, 30);
  sset_add(set, 40);
  sset_add(set, 50);


  // Test per un elemento presente nel set
  if (!sset_member(set, 20)) {
      printf("FAILED: Expected 20 to be found\n");
      passed = 0;
  } else {
      printf("OK: 20 found\n");
  }

  // Test per un elemento non presente nel set
  if (sset_member(set, 25)) {
      printf("FAILED: Expected 25 not to be found\n");
      passed = 0;
  } else {
      printf("OK: 25 not found\n");
  }

  // Test per il primo elemento (10)
  if (!sset_member(set, 10)) {
      printf("FAILED: Expected 10 to be found\n");
      passed = 0;
  } else {
      printf("OK: 10 found\n");
  }

  // Test per l'ultimo elemento (50)
  if (!sset_member(set, 50)) {
      printf("FAILED: Expected 50 to be found\n");
      passed = 0;
  } else {
      printf("OK: 50 found\n");
  }

  // Test per un elemento che non esiste nel set
  if (sset_member(set, 100)) {
      printf("FAILED: Expected 100 not to be found\n");
      passed = 0;
  } else {
      printf("OK: 100 not found\n");
  }

  // Test per l'elemento massimo (30)
  if (!sset_member(set, 30)) {
      printf("FAILED: Expected 30 to be found\n");
      passed = 0;
  } else {
      printf("OK: 30 found\n");
  }

  return passed;
}


int check_isEmptySSet() {
  int passed = 1;

  printf("isEmptySSet()\n");

  // Test caso in cui l'insieme è vuoto
  IntSortedSetADT emptySet = mkSSet();
  if (isEmptySSet(emptySet) != 1) {
      printf("FAILED\n");
      printf("EXPECTED: 1 (True)\n");
      passed = 0;
  } else {
      printf("OK\n");
  }

  // Test caso in cui l'insieme ha un elemento
  IntSortedSetADT nonEmptySet = mkSSetv(1, 5);  // Aggiunge 5 all'insieme
  if (isEmptySSet(nonEmptySet) != 0) {
      printf("FAILED\n");
      printf("EXPECTED: 0 (False)\n");
      passed = 0;
  } else {
      printf("OK\n");
  }

  // Test caso in cui l'insieme è NULL
  IntSortedSetADT nullSet = NULL;
  if (isEmptySSet(nullSet) != 0) {
      printf("FAILED\n");
      printf("EXPECTED: 0 (False) for NULL set\n");
      passed = 0;
  } else {
      printf("OK\n");
  }

  printf("RESULT: %d\n\n", passed);
  return passed;
}


int check_sset_size() {
  int passed = 1;

  printf("sset_size()\n");

  // Test caso in cui l'insieme è vuoto
  IntSortedSetADT emptySet = mkSSet();
  if (sset_size(emptySet) != 0) {
      printf("FAILED\n");
      printf("EXPECTED: 0 (size of empty set)\n");
      passed = 0;
  } else {
      printf("OK\n");
  }

  // Test caso in cui l'insieme ha un elemento
  IntSortedSetADT nonEmptySet = mkSSetv(1, 5);  // Aggiunge 5 all'insieme
  if (sset_size(nonEmptySet) != 1) {
      printf("FAILED\n");
      printf("EXPECTED: 1 (size of set with 1 element)\n");
      passed = 0;
  } else {
      printf("OK\n");
  }

  // Test caso in cui l'insieme ha più elementi
  IntSortedSetADT largerSet = mkSSetv(3, 1, 3, 5);  // Aggiunge 1, 3, 5 all'insieme
  if (sset_size(largerSet) != 3) {
      printf("FAILED\n");
      printf("EXPECTED: 3 (size of set with 3 elements)\n");
      passed = 0;
  } else {
      printf("OK\n");
  }

  // Test caso in cui l'insieme è NULL
  IntSortedSetADT nullSet = NULL;
  if (sset_size(nullSet) != -1) {
      printf("FAILED\n");
      printf("EXPECTED: -1 (size for NULL set)\n");
      passed = 0;
  } else {
      printf("OK\n");
  }

  printf("RESULT: %d\n\n", passed);
  return passed;
}



int check_sset_extract() {
  int passed = 1;
  int extractedValue;
  
  // Test 1: Estrazione su un insieme con un solo elemento
  {
      printf("sset_extract(single element)\n");
      IntSortedSetADT set = mkSSetv(1, 5);  // Crea un insieme con un solo elemento
      if (sset_extract(set, &extractedValue)) {
          if (extractedValue == 5 && set->size == 0) {
              printf("OK\n");
          } else {
              printf("FAILED\n");
              passed = 0;
          }
      } else {
          printf("FAILED\n");
          passed = 0;
      }
      printf("RESULT: Extracted %d, Set size %d\n\n", extractedValue, set->size);
  }

  // Test 2: Estrazione su un insieme con più elementi
  {
      printf("sset_extract(multiple elements)\n");
      IntSortedSetADT set = mkSSetv(3, 1, 2, 3);  // Crea un insieme con 3 elementi
      if (sset_extract(set, &extractedValue)) {
          if (extractedValue >= 1 && extractedValue <= 3 && set->size == 2) {
              printf("OK\n");
          } else {
              printf("FAILED\n");
              passed = 0;
          }
      } else {
          printf("FAILED\n");
          passed = 0;
      }
      printf("RESULT: Extracted %d, Set size %d\n\n", extractedValue, set->size);
  }

  // Test 3: Estrazione su un insieme vuoto
  {
      printf("sset_extract(empty set)\n");
      IntSortedSetADT set = mkSSet();  // Crea un insieme vuoto
      if (!sset_extract(set, &extractedValue)) {
          printf("OK\n");
      } else {
          printf("FAILED\n");
          passed = 0;
      }
      printf("RESULT: Set size %d\n\n", set->size);
  }

  // Test 4: Estrazione con il set che si svuota dopo l'estrazione
  {
      printf("sset_extract(set empties)\n");
      IntSortedSetADT set = mkSSetv(3, 10, 20, 30);  // Crea un insieme con 3 elementi
      while (set->size > 0) {
          if (sset_extract(set, &extractedValue)) {
              printf("Extracted %d, Set size %d\n", extractedValue, set->size);
          } else {
              printf("FAILED during extraction\n");
              passed = 0;
          }
      }
      if (set->size == 0) {
          printf("OK\n");
      } else {
          printf("FAILED\n");
          passed = 0;
      }
      printf("RESULT: Set size %d\n\n", set->size);
  }

  return passed;
}


int check_sset_equals() {
  int passed = 1;

  // Test su set vuoti
  IntSortedSetADT s1 = mkSSet();
  IntSortedSetADT s2 = mkSSet();
  if (!sset_equals(s1, s2)) {
      printf("FAILED: Empty sets should be equal\n");
      passed = 0;
  } else {
      printf("OK: Empty sets are equal\n");
  }

  // Test su set uguali
  IntSortedSetADT s3 = mkSSetv(3, 1, 2, 3);
  IntSortedSetADT s4 = mkSSetv(3, 1, 2, 3);
  if (!sset_equals(s3, s4)) {
      printf("FAILED: Identical sets should be equal\n");
      passed = 0;
  } else {
      printf("OK: Identical sets are equal\n");
  }

  // Test su set con elementi diversi
  IntSortedSetADT s5 = mkSSetv(3, 1, 2, 3);
  IntSortedSetADT s6 = mkSSetv(3, 4, 5, 6);
  if (sset_equals(s5, s6)) {
      printf("FAILED: Different sets should not be equal\n");
      passed = 0;
  } else {
      printf("OK: Different sets are not equal\n");
  }

  // Test su set con dimensioni diverse
  IntSortedSetADT s7 = mkSSetv(3, 1, 2, 3);
  IntSortedSetADT s8 = mkSSetv(2, 1, 2);
  if (sset_equals(s7, s8)) {
      printf("FAILED: Sets with different sizes should not be equal\n");
      passed = 0;
  } else {
      printf("OK: Sets with different sizes are not equal\n");
  }

  return passed;
}


int check_sset_subseteq() {
  int passed = 1;

  // Test 1: Set vuoti
  {
      IntSortedSetADT s1 = mkSSet();
      IntSortedSetADT s2 = mkSSet();
      printf("sset_subseteq(s1, s2)\n");
      _Bool rv = sset_subseteq(s1, s2);
      if (!rv) {
          printf("FAILED\n");
          printf("EXPECTED: true\n");
          passed = 0;
      } else {
          printf("OK\n");
      }
      printf("RESULT: %d\n\n", rv);
  }

  // Test 2: s2 è un sottoinsieme di s1
  {
      IntSortedSetADT s1 = mkSSetv(3, 1, 2, 3);  // s1 = {1, 2, 3}
      IntSortedSetADT s2 = mkSSetv(2, 1, 2);      // s2 = {1, 2}
      printf("sset_subseteq(s1, s2)\n");
      _Bool rv = sset_subseteq(s1, s2);
      if (!rv) {
          printf("FAILED\n");
          printf("EXPECTED: true\n");
          passed = 0;
      } else {
          printf("OK\n");
      }
      printf("RESULT: %d\n\n", rv);
  }

  // Test 3: s2 non è un sottoinsieme di s1 (elemento in più in s2)
  {
      IntSortedSetADT s1 = mkSSetv(3, 1, 2, 3);  // s1 = {1, 2, 3}
      IntSortedSetADT s2 = mkSSetv(4, 1, 2, 3, 4);  // s2 = {1, 2, 3, 4}
      printf("sset_subseteq(s1, s2)\n");
      _Bool rv = sset_subseteq(s1, s2);
      if (rv) {
          printf("FAILED\n");
          printf("EXPECTED: false\n");
          passed = 0;
      } else {
          printf("OK\n");
      }
      printf("RESULT: %d\n\n", rv);
  }

  // Test 4: s2 non è un sottoinsieme di s1 (manca un elemento in s2)
  {
      IntSortedSetADT s1 = mkSSetv(3, 1, 2, 3);  // s1 = {1, 2, 3}
      IntSortedSetADT s2 = mkSSetv(2, 1, 4);      // s2 = {1, 4}
      printf("sset_subseteq(s1, s2)\n");
      _Bool rv = sset_subseteq(s1, s2);
      if (rv) {
          printf("FAILED\n");
          printf("EXPECTED: false\n");
          passed = 0;
      } else {
          printf("OK\n");
      }
      printf("RESULT: %d\n\n", rv);
  }

  // Test 5: s1 e s2 uguali
  {
      IntSortedSetADT s1 = mkSSetv(3, 1, 2, 3);  // s1 = {1, 2, 3}
      IntSortedSetADT s2 = mkSSetv(3, 1, 2, 3);  // s2 = {1, 2, 3}
      printf("sset_subseteq(s1, s2)\n");
      _Bool rv = sset_subseteq(s1, s2);
      if (!rv) {
          printf("FAILED\n");
          printf("EXPECTED: true\n");
          passed = 0;
      } else {
          printf("OK\n");
      }
      printf("RESULT: %d\n\n", rv);
  }

  return passed;
}

int check_sset_subset() {
  int passed = 1;

  // Test 1: Set vuoti
  {
      IntSortedSetADT s1 = mkSSet();
      IntSortedSetADT s2 = mkSSet();
      printf("sset_subset(s1, s2)\n");
      _Bool rv = sset_subset(s1, s2);
      if (rv) {
          printf("FAILED\n");
          printf("EXPECTED: false (s2 non può essere un sottoinsieme stretto di s1)\n");
          passed = 0;
      } else {
          printf("OK\n");
      }
      printf("RESULT: %d\n\n", rv);
  }

  // Test 2: s2 è un sottoinsieme stretto di s1
  {
      IntSortedSetADT s1 = mkSSetv(3, 1, 2, 3);  // s1 = {1, 2, 3}
      IntSortedSetADT s2 = mkSSetv(2, 1, 2);      // s2 = {1, 2}
      printf("sset_subset(s1, s2)\n");
      _Bool rv = sset_subset(s1, s2);
      if (!rv) {
          printf("FAILED\n");
          printf("EXPECTED: true\n");
          passed = 0;
      } else {
          printf("OK\n");
      }
      printf("RESULT: %d\n\n", rv);
  }

  // Test 3: s2 non è un sottoinsieme di s1
  {
      IntSortedSetADT s1 = mkSSetv(3, 1, 2, 3);  // s1 = {1, 2, 3}
      IntSortedSetADT s2 = mkSSetv(4, 1, 2, 3, 4);  // s2 = {1, 2, 3, 4}
      printf("sset_subset(s1, s2)\n");
      _Bool rv = sset_subset(s1, s2);
      if (rv) {
          printf("FAILED\n");
          printf("EXPECTED: false (s2 ha un elemento in più)\n");
          passed = 0;
      } else {
          printf("OK\n");
      }
      printf("RESULT: %d\n\n", rv);
  }

  // Test 4: s1 è uguale a s2
  {
      IntSortedSetADT s1 = mkSSetv(3, 1, 2, 3);  // s1 = {1, 2, 3}
      IntSortedSetADT s2 = mkSSetv(3, 1, 2, 3);  // s2 = {1, 2, 3}
      printf("sset_subset(s1, s2)\n");
      _Bool rv = sset_subset(s1, s2);
      if (rv) {
          printf("FAILED\n");
          printf("EXPECTED: false (s2 non è un sottoinsieme stretto di s1)\n");
          passed = 0;
      } else {
          printf("OK\n");
      }
      printf("RESULT: %d\n\n", rv);
  }

  return passed;
}



int check_sset_union() {
  int passed = 1;

  // Test 1: Unione di due insiemi non vuoti
  printf("sset_union({1, 2, 3}, {3, 4, 5})\n");
  IntSortedSetADT set1 = mkSSetv(3, 1, 2, 3);
  IntSortedSetADT set2 = mkSSetv(3, 3, 4, 5);
  IntSortedSetADT result = sset_union(set1, set2);
  char *result_str = toString(result);
  if (strcmp(result_str, "{1,2,3,4,5}") != 0) {
      printf("FAILED\nEXPECTED: {1, 2, 3, 4, 5}\nACTUAL: %s\n", result_str);
      passed = 0;
  } else {
      printf("OK\n");
  }
  free(result_str);
  dsSSet(&result);

  // Test 2: Unione con un insieme vuoto
  printf("sset_union({1, 2, 3}, {})\n");
  set2 = mkSSet(); // Empty set
  result = sset_union(set1, set2);
  result_str = toString(result);
  if (strcmp(result_str, "{1,2,3}") != 0) {
      printf("FAILED\nEXPECTED: {1, 2, 3}\nACTUAL: %s\n", result_str);
      passed = 0;
  } else {
      printf("OK\n");
  }
  free(result_str);
  dsSSet(&result);

  // Test 3: Unione di due insiemi vuoti
  printf("sset_union({}, {})\n");
  set1 = mkSSet(); // Empty set
  set2 = mkSSet(); // Empty set
  result = sset_union(set1, set2);
  result_str = toString(result);
  if (strcmp(result_str, "{}") != 0) {
      printf("FAILED\nEXPECTED: {}\nACTUAL: %s\n", result_str);
      passed = 0;
  } else {
      printf("OK\n");
  }
  free(result_str);
  dsSSet(&result);

  // Test 4: Unione di un insieme vuoto con un altro insieme non vuoto
  printf("sset_union({}, {1, 2, 3})\n");
  set1 = mkSSet(); // Empty set
  set2 = mkSSetv(3, 1, 2, 3);
  result = sset_union(set1, set2);
  result_str = toString(result);
  if (strcmp(result_str, "{1,2,3}") != 0) {
      printf("FAILED\nEXPECTED: {1, 2, 3}\nACTUAL: %s\n", result_str);
      passed = 0;
  } else {
      printf("OK\n");
  }
  free(result_str);
  dsSSet(&result);

  return passed;
}

int check_sset_intersection() {
  int passed = 1;

  // Test 1: Intersezione di due insiemi non vuoti con elementi comuni
  printf("sset_intersection({1, 2, 3}, {2, 3, 4})\n");
  IntSortedSetADT set1 = mkSSetv(3, 1, 2, 3);
  IntSortedSetADT set2 = mkSSetv(3, 2, 3, 4);
  IntSortedSetADT result = sset_intersection(set1, set2);
  char *result_str = toString(result);
  if (strcmp(result_str, "{2,3}") != 0) {
      printf("FAILED\nEXPECTED: {2, 3}\nACTUAL: %s\n", result_str);
      passed = 0;
  } else {
      printf("OK\n");
  }
  free(result_str);
  dsSSet(&result);

  // Test 2: Intersezione di due insiemi senza elementi comuni
  printf("sset_intersection({1, 2, 3}, {4, 5, 6})\n");
  set1 = mkSSetv(3, 1, 2, 3);
  set2 = mkSSetv(3, 4, 5, 6);
  result = sset_intersection(set1, set2);
  result_str = toString(result);
  if (strcmp(result_str, "{}") != 0) {
      printf("FAILED\nEXPECTED: {}\nACTUAL: %s\n", result_str);
      passed = 0;
  } else {
      printf("OK\n");
  }
  free(result_str);
  dsSSet(&result);

  // Test 3: Intersezione con un insieme vuoto
  printf("sset_intersection({1, 2, 3}, {})\n");
  set2 = mkSSet(); // Empty set
  result = sset_intersection(set1, set2);
  result_str = toString(result);
  if (strcmp(result_str, "{}") != 0) {
      printf("FAILED\nEXPECTED: {}\nACTUAL: %s\n", result_str);
      passed = 0;
  } else {
      printf("OK\n");
  }
  free(result_str);
  dsSSet(&result);

  // Test 4: Intersezione di due insiemi vuoti
  printf("sset_intersection({}, {})\n");
  set1 = mkSSet(); // Empty set
  set2 = mkSSet(); // Empty set
  result = sset_intersection(set1, set2);
  result_str = toString(result);
  if (strcmp(result_str, "{}") != 0) {
      printf("FAILED\nEXPECTED: {}\nACTUAL: %s\n", result_str);
      passed = 0;
  } else {
      printf("OK\n");
  }
  free(result_str);
  dsSSet(&result);

  return passed;
}


int check_sset_subtraction() {
  int passed = 1;

  // Test 1: Sottrazione con elementi in comune
  printf("sset_subtraction({1, 2, 3}, {2, 4})\n");
  IntSortedSetADT set1 = mkSSetv(3, 1, 2, 3);
  IntSortedSetADT set2 = mkSSetv(2, 2, 4);
  IntSortedSetADT result = sset_subtraction(set1, set2);
  char *result_str = toString(result);
  if (strcmp(result_str, "{1,3}") != 0) {
      printf("FAILED\nEXPECTED: {1,3}\nACTUAL: %s\n", result_str);
      passed = 0;
  } else {
      printf("OK\n");
  }
  free(result_str);
  dsSSet(&result);

  // Test 2: Sottrazione con insieme vuoto
  printf("sset_subtraction({1, 2, 3}, {})\n");
  set2 = mkSSet();
  result = sset_subtraction(set1, set2);
  result_str = toString(result);
  if (strcmp(result_str, "{1,2,3}") != 0) {
      printf("FAILED\nEXPECTED: {1,2,3}\nACTUAL: %s\n", result_str);
      passed = 0;
  } else {
      printf("OK\n");
  }
  free(result_str);
  dsSSet(&result);
  dsSSet(&set2);

  // Test 3: Sottrazione con insieme uguale
  printf("sset_subtraction({1, 2, 3}, {1, 2, 3})\n");
  set2 = mkSSetv(3, 1, 2, 3);
  result = sset_subtraction(set1, set2);
  result_str = toString(result);
  if (strcmp(result_str, "{}") != 0) {
      printf("FAILED\nEXPECTED: {}\nACTUAL: %s\n", result_str);
      passed = 0;
  } else {
      printf("OK\n");
  }
  free(result_str);
  dsSSet(&result);
  dsSSet(&set1);
  dsSSet(&set2);

  // Test 4: Sottrazione con insieme A vuoto
  printf("sset_subtraction({}, {1, 2})\n");
  set1 = mkSSet();
  set2 = mkSSetv(2, 1, 2);
  result = sset_subtraction(set1, set2);
  result_str = toString(result);
  if (strcmp(result_str, "{}") != 0) {
      printf("FAILED\nEXPECTED: {}\nACTUAL: %s\n", result_str);
      passed = 0;
  } else {
      printf("OK\n");
  }
  free(result_str);
  dsSSet(&result);

  // Test 5: Sottrazione di due insiemi vuoti
  printf("sset_subtraction({}, {})\n");
  dsSSet(&set2); // Ricicliamo set1 (già vuoto)
  set2 = mkSSet();
  result = sset_subtraction(set1, set2);
  result_str = toString(result);
  if (strcmp(result_str, "{}") != 0) {
      printf("FAILED\nEXPECTED: {}\nACTUAL: %s\n", result_str);
      passed = 0;
  } else {
      printf("OK\n");
  }
  free(result_str);
  dsSSet(&result);
  dsSSet(&set1);
  dsSSet(&set2);

  return passed;
}




int check_sset_min() {
  int passed = 1;

  // Test 1: Minimo di un insieme con più di un elemento
  printf("sset_min({1, 2, 3})\n");
  IntSortedSetADT set1 = mkSSetv(3, 1, 2, 3);
  int min_val;
  if (sset_min(set1, &min_val) && min_val == 1) {
      printf("OK\n");
  } else {
      printf("FAILED\nEXPECTED: 1\nACTUAL: %d\n", min_val);
      passed = 0;
  }
  dsSSet(&set1);

  // Test 2: Minimo di un insieme con un solo elemento
  printf("sset_min({5})\n");
  set1 = mkSSetv(1, 5);
  if (sset_min(set1, &min_val) && min_val == 5) {
      printf("OK\n");
  } else {
      printf("FAILED\nEXPECTED: 5\nACTUAL: %d\n", min_val);
      passed = 0;
  }
  dsSSet(&set1);

  // Test 3: Minimo di un insieme vuoto
  printf("sset_min({})\n");
  set1 = mkSSet(); // Empty set
  if (!sset_min(set1, &min_val)) {
      printf("OK\n");
  } else {
      printf("FAILED\nEXPECTED: false\nACTUAL: %d\n", min_val);
      passed = 0;
  }
  dsSSet(&set1);

  return passed;
}

int check_sset_max() {
  int passed = 1;

  // Test 1: Massimo di un insieme con più di un elemento
  printf("sset_max({1, 2, 3})\n");
  IntSortedSetADT set1 = mkSSetv(3, 1, 2, 3);
  int max_val;
  if (sset_max(set1, &max_val) && max_val == 3) {
      printf("OK\n");
  } else {
      printf("FAILED\nEXPECTED: 3\nACTUAL: %d\n", max_val);
      passed = 0;
  }
  dsSSet(&set1);

  // Test 2: Massimo di un insieme con un solo elemento
  printf("sset_max({5})\n");
  set1 = mkSSetv(1, 5);
  if (sset_max(set1, &max_val) && max_val == 5) {
      printf("OK\n");
  } else {
      printf("FAILED\nEXPECTED: 5\nACTUAL: %d\n", max_val);
      passed = 0;
  }
  dsSSet(&set1);

  // Test 3: Massimo di un insieme vuoto
  printf("sset_max({})\n");
  set1 = mkSSet(); // Empty set
  if (!sset_max(set1, &max_val)) {
      printf("OK\n");
  } else {
      printf("FAILED\nEXPECTED: false\nACTUAL: %d\n", max_val);
      passed = 0;
  }
  dsSSet(&set1);

  return passed;
}


int check_sset_extractMin() {
  int passed = 1;

  // Test 1: Estrazione del minimo in un insieme con più di un elemento
  printf("sset_extractMin({1, 2, 3})\n");
  IntSortedSetADT set1 = mkSSetv(3, 1, 2, 3);
  int min_val;
  if (sset_extractMin(set1, &min_val) && min_val == 1) {
      printf("OK\n");
  } else {
      printf("FAILED\nEXPECTED: 1\nACTUAL: %d\n", min_val);
      passed = 0;
  }
  dsSSet(&set1);

  // Test 2: Estrazione del minimo in un insieme con un solo elemento
  printf("sset_extractMin({5})\n");
  set1 = mkSSetv(1, 5);
  if (sset_extractMin(set1, &min_val) && min_val == 5) {
      printf("OK\n");
  } else {
      printf("FAILED\nEXPECTED: 5\nACTUAL: %d\n", min_val);
      passed = 0;
  }
  dsSSet(&set1);

  // Test 3: Estrazione del minimo in un insieme vuoto
  printf("sset_extractMin({})\n");
  set1 = mkSSet(); // Empty set
  if (!sset_extractMin(set1, &min_val)) {
      printf("OK\n");
  } else {
      printf("FAILED\nEXPECTED: false\nACTUAL: %d\n", min_val);
      passed = 0;
  }
  dsSSet(&set1);

  return passed;
}

int check_sset_extractMax() {
  int passed = 1;

  // Test 1: Estrazione del massimo in un insieme con più di un elemento
  printf("sset_extractMax({1, 2, 3})\n");
  IntSortedSetADT set1 = mkSSetv(3, 1, 2, 3);
  int max_val;
  if (sset_extractMax(set1, &max_val) && max_val == 3) {
      printf("OK\n");
  } else {
      printf("FAILED\nEXPECTED: 3\nACTUAL: %d\n", max_val);
      passed = 0;
  }
  dsSSet(&set1);

  // Test 2: Estrazione del massimo in un insieme con un solo elemento
  printf("sset_extractMax({5})\n");
  set1 = mkSSetv(1, 5);
  if (sset_extractMax(set1, &max_val) && max_val == 5) {
      printf("OK\n");
  } else {
      printf("FAILED\nEXPECTED: 5\nACTUAL: %d\n", max_val);
      passed = 0;
  }
  dsSSet(&set1);

  // Test 3: Estrazione del massimo in un insieme vuoto
  printf("sset_extractMax({})\n");
  set1 = mkSSet(); // Empty set
  if (!sset_extractMax(set1, &max_val)) {
      printf("OK\n");
  } else {
      printf("FAILED\nEXPECTED: false\nACTUAL: %d\n", max_val);
      passed = 0;
  }
  dsSSet(&set1);

  return passed;
}


int main(int argc, char *argv[]) {
  puts("BEGIN TEST intLinkedListSortedSetADT"); 

  {
    printf("TEST mkSSet\n");
    check_mkSSet();
    printf("\n");
  }

  {
    printf("TEST dsSSet\n");
    check_dsSSet();
    printf("\n");
  }

  {
    printf("TEST sset_add\n");
    check_sset_add();
    printf("\n");
  }

  {
    printf("TEST sset_remove\n");    
    check_sset_remove();
    printf("\n");
  }

  {
    printf("TEST sset_member\n");    
    check_sset_member();
    printf("\n");
  }

  {
    printf("TEST isEmptySSet\n");    
    check_isEmptySSet();
    printf("\n");
  }

  {
    printf("TEST sset_size\n");    
    check_sset_size();
    printf("\n");
  }

  {
    printf("TEST sset_extract\n");    
    check_sset_extract();
    printf("\n");
  }

  {
    printf("TEST sset_equals\n");    
    check_sset_equals();
    printf("\n");
  }

  {
    printf("TEST sset_subseteq\n");    
    check_sset_subseteq();
    printf("\n");
  }

  {
    printf("TEST sset_subset\n");    
    check_sset_subset();
    printf("\n");
  }

  {
    printf("TEST sset_union\n");    
    check_sset_union();
    printf("\n");
  }

  {
    printf("TEST sset_intersection\n");    
    check_sset_intersection();
    printf("\n");
  }

  {
    printf("TEST sset_subtraction\n");    
    check_sset_subtraction();
    printf("\n");
  }

  {
    printf("TEST sset_min\n");    
    check_sset_min();
    printf("\n");
  }

  {
    printf("TEST sset_max\n");    
    check_sset_max();
    printf("\n");
  }

  {
    printf("TEST sset_extractMin\n");    
    check_sset_extractMin();
    printf("\n");
  }

  {
    printf("TEST sset_extractMax\n");    
    check_sset_extractMax();
    printf("\n");
  }
}