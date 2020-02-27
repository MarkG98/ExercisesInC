#include <stdio.h>
#include <string.h>
#include "util.h"
#include "minunit_util.h"

int tests_run = 0;

static char * test1()
{
  char *res = icmpcode_v4(0);
  mu_assert("error, code 0 should return \"network unreachable\"", strcmp(res, "network unreachable") == 0);
  return 0;
}

static char * test2()
{
  char *res = icmpcode_v4(1);
  mu_assert("error, code 1 should return \"host unreachable\"", strcmp(res, "host unreachable") == 0);
  return 0;
}

static char * test3()
{
  char *res = icmpcode_v4(2);
  mu_assert("error, code 2 should return \"protocol unreachable\"", strcmp(res, "protocol unreachable") == 0);
  return 0;
}

static char * test4()
{
  char *res = icmpcode_v4(3);
  mu_assert("error, code 3 should return \"port unreachable\"", strcmp(res, "port unreachable") == 0);
  return 0;
}

static char * test5()
{
  char *res = icmpcode_v4(4);
  mu_assert("error, code 4 should return \"fragmentation required but DF bit set\"", strcmp(res, "fragmentation required but DF bit set") == 0);
  return 0;
}

static char * test6()
{
  char *res = icmpcode_v4(5);
  mu_assert("error, code 5 should return \"source route failed\"", strcmp(res, "source route failed") == 0);
  return 0;
}

static char * test7()
{
  char *res = icmpcode_v4(6);
  mu_assert("error, code 6 should return \"destination network unknown\"", strcmp(res, "destination network unknown") == 0);
  return 0;
}

static char * test8()
{
  char *res = icmpcode_v4(7);
  mu_assert("error, code 7 should return \"destination host unknown\"", strcmp(res, "destination host unknown") == 0);
  return 0;
}

static char * test9()
{
  char *res = icmpcode_v4(8);
  mu_assert("error, code 8 should return \"source host isolated (obsolete)\"", strcmp(res, "source host isolated (obsolete)") == 0);
  return 0;
}

static char * test10()
{
  char *res = icmpcode_v4(9);
  mu_assert("error, code 9 should return \"destination network administratively prohibited\"", strcmp(res, "destination network administratively prohibited") == 0);
  return 0;
}

static char * test11()
{
  char *res = icmpcode_v4(10);
  mu_assert("error, code 10 should return \"destination host administratively prohibited\"", strcmp(res, "destination host administratively prohibited") == 0);
  return 0;
}

static char * test12()
{
  char *res = icmpcode_v4(11);
  mu_assert("error, code 11 should return \"network unreachable for TOS\"", strcmp(res, "network unreachable for TOS") == 0);
  return 0;
}

static char * test13()
{
  char *res = icmpcode_v4(12);
  mu_assert("error, code 12 should return \"host unreachable for TOS\"", strcmp(res, "host unreachable for TOS") == 0);
  return 0;
}

static char * test14()
{
  char *res = icmpcode_v4(13);
  mu_assert("error, code 13 should return \"communication administratively prohibited by filtering\"", strcmp(res, "communication administratively prohibited by filtering") == 0);
  return 0;
}

static char * test15()
{
  char *res = icmpcode_v4(14);
  mu_assert("error, code 14 should return \"host recedence violation\"", strcmp(res, "host recedence violation") == 0);
  return 0;
}

static char * test16()
{
  char *res = icmpcode_v4(15);
  mu_assert("error, code 15 should return \"precedence cutoff in effect\"", strcmp(res, "precedence cutoff in effect") == 0);
  return 0;
}

static char * test17()
{
  char *res = icmpcode_v4(23);
  mu_assert("error, code > 15 should return \"[unknown code]\"", strcmp(res, "[unknown code]") == 0);
  return 0;
}

static char * test18()
{
  char *res = icmpcode_v4(-6);
  mu_assert("error, code < 0 should return \"[unknown code]\"", strcmp(res, "[unknown code]") == 0);
  return 0;
}

static char * all_tests()
{
  mu_run_test(test1);
  mu_run_test(test2);
  mu_run_test(test3);
  mu_run_test(test4);
  mu_run_test(test5);
  mu_run_test(test6);
  mu_run_test(test7);
  mu_run_test(test8);
  mu_run_test(test9);
  mu_run_test(test10);
  mu_run_test(test11);
  mu_run_test(test12);
  mu_run_test(test13);
  mu_run_test(test14);
  mu_run_test(test15);
  mu_run_test(test16);
  mu_run_test(test17);
  mu_run_test(test18);
  return 0;
}

int main(int argc, char **argv)
{
  char *result = all_tests();
  if (result != 0)
  {
    printf("%s\n", result);
  }
  else
  {
    printf("ALL TESTS PASSED\n");
  }
  printf("Tests run: %d\n", tests_run);

  return result != 0;
}
