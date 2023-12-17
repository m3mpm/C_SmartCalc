#include <check.h>

#include "calc_logic.h"

START_TEST(test1) {
  char *test1 = "1.23+2.23";
  double r1 = 0.0;
  double x1 = 0.0;
  get_result(test1, x1, &r1);
  double cp1 = 1.23 + 2.23;
  ck_assert_double_eq_tol(r1, cp1, EPS);
}
END_TEST

START_TEST(test2) {
  char *test2 = "1.4356789-2.245";
  double r2 = 0.0;
  double x2 = 0.0;
  get_result(test2, x2, &r2);
  double cp2 = 1.4356789 - 2.245;
  ck_assert_double_eq_tol(r2, cp2, EPS);
}
END_TEST

START_TEST(test3) {
  char *test3 = "100.456";
  double r3 = 0.0;
  double x3 = 0.0;
  get_result(test3, x3, &r3);
  double cp3 = 100.456;
  ck_assert_double_eq_tol(r3, cp3, EPS);
}
END_TEST

START_TEST(test4) {
  char *test4 = "(100.456)";
  double r4 = 0.0;
  double x4 = 0.0;
  get_result(test4, x4, &r4);
  double cp4 = 100.456;
  ck_assert_double_eq_tol(r4, cp4, EPS);
}
END_TEST

START_TEST(test5) {
  char *test5 = "2.1/(1.5+1.678)";
  double r5 = 0.0;
  double x5 = 0.0;
  get_result(test5, x5, &r5);
  double cp5 = 2.1 / (1.5 + 1.678);
  ck_assert_double_eq_tol(r5, cp5, EPS);
}
END_TEST

START_TEST(test6) {
  char *test6 = "2.7856*(5.345-2.345)";
  double r6 = 0.0;
  double x6 = 0.0;
  get_result(test6, x6, &r6);
  double cp6 = 2.7856 * (5.345 - 2.345);
  ck_assert_double_eq_tol(r6, cp6, EPS);
}
END_TEST

START_TEST(test7) {
  char *test7 = "2.25*(5.67-x)";
  double r7 = 0.0;
  double x7 = 2.543;
  get_result(test7, x7, &r7);
  double cp7 = 2.25 * (5.67 - 2.543);
  ck_assert_double_eq_tol(r7, cp7, EPS);
}
END_TEST

START_TEST(test8) {
  char *test8 = "(2^2)+(2^2)";
  double r8 = 0.0;
  double x8 = 0.0;
  get_result(test8, x8, &r8);
  double cp8 = pow(2, 2) + pow(2, 2);
  ck_assert_double_eq_tol(r8, cp8, EPS);
}
END_TEST

START_TEST(test9) {
  char *test9 = "2^2)+(2^2)";
  double r9 = 0.0;
  double x9 = 0.0;
  int error9 = get_result(test9, x9, &r9);
  int cp_error9 = 4;
  ck_assert_int_eq(error9, cp_error9);
}
END_TEST

START_TEST(test10) {
  char *test10 = "mod2";
  double r10 = 0.0;
  double x10 = 0.0;
  int error10 = get_result(test10, x10, &r10);
  int cp_error10 = 11;
  ck_assert_int_eq(error10, cp_error10);
}
END_TEST

START_TEST(test11) {
  char *test11 = "()";
  double r11 = 0.0;
  double x11 = 0.0;
  int error11 = get_result(test11, x11, &r11);
  int cp_error11 = 6;
  ck_assert_int_eq(error11, cp_error11);
}
END_TEST

START_TEST(test12) {
  char *test12 = "1/0";
  double r12 = 0.0;
  double x12 = 0.0;
  get_result(test12, x12, &r12);
  double cp_error12 = INFINITY;
  ck_assert_double_eq(r12, cp_error12);
}
END_TEST

START_TEST(test13) {
  char *test13 = "2mod0";
  double r13 = 0.0;
  double x13 = 0.0;
  get_result(test13, x13, &r13);
  ck_assert_double_nan(r13);
}
END_TEST

START_TEST(test14) {
  char *test14 = "((((10.987))))";
  double r14 = 0.0;
  double x14 = 0.0;
  get_result(test14, x14, &r14);
  double cp14 = 10.987;
  ck_assert_double_eq_tol(r14, cp14, EPS);
}
END_TEST

START_TEST(test15) {
  char *test15 = "sqrt9";
  double r15 = 0.0;
  double x15 = 0.0;
  get_result(test15, x15, &r15);
  double cp15 = 3;
  ck_assert_double_eq_tol(r15, cp15, EPS);
}
END_TEST

START_TEST(test16) {
  char *test16 = "10mod5";
  double r16 = 0.0;
  double x16 = 0.0;
  get_result(test16, x16, &r16);
  double cp16 = 0;
  ck_assert_double_eq_tol(r16, cp16, EPS);
}
END_TEST

START_TEST(test17) {
  char *test17 = "log10";
  double r17 = 0.0;
  double x17 = 0.0;
  get_result(test17, x17, &r17);
  double cp17 = 1;
  ck_assert_double_eq_tol(r17, cp17, EPS);
}
END_TEST

START_TEST(test18) {
  char *test18 = "ln2.718281828459045";
  double r18 = 0.0;
  double x18 = 0.0;
  get_result(test18, x18, &r18);
  double cp18 = 1;
  ck_assert_double_eq_tol(r18, cp18, EPS);
}
END_TEST

START_TEST(test19) {
  char *test19 = "log-10";
  double r19 = 0.0;
  double x19 = 0.0;
  get_result(test19, x19, &r19);
  ck_assert_double_nan(r19);
}
END_TEST

START_TEST(test20) {
  char *test20 = "ln-10";
  double r20 = 0.0;
  double x20 = 0.0;
  get_result(test20, x20, &r20);
  ck_assert_double_nan(r20);
}
END_TEST

START_TEST(test21) {
  char *test21 = "sqrt-10";
  double r21 = 0.0;
  double x21 = 0.0;
  get_result(test21, x21, &r21);
  ck_assert_double_nan(r21);
}
END_TEST

START_TEST(test22) {
  char *test22 = "---5";
  double r22 = 0.0;
  double x22 = 0.0;
  get_result(test22, x22, &r22);
  double cp22 = -5;
  ck_assert_double_eq_tol(r22, cp22, EPS);
}
END_TEST

START_TEST(test23) {
  char *test23 = "--++5";
  double r23 = 0.0;
  double x23 = 0.0;
  get_result(test23, x23, &r23);
  double cp23 = 5;
  ck_assert_double_eq_tol(r23, cp23, EPS);
}
END_TEST

START_TEST(test24) {
  char *test24 = "5.25-10.01";
  double r24 = 0.0;
  double x24 = 0.0;
  get_result(test24, x24, &r24);
  double cp24 = 5.25 - 10.01;
  ck_assert_double_eq_tol(r24, cp24, EPS);
}
END_TEST

START_TEST(test25) {
  char *test25 = "3.01*3.02";
  double r25 = 0.0;
  double x25 = 0.0;
  get_result(test25, x25, &r25);
  double cp25 = 3.01 * 3.02;
  ck_assert_double_eq_tol(r25, cp25, EPS);
}
END_TEST

START_TEST(test26) {
  char *test26 = "9.45/3.26";
  double r26 = 0.0;
  double x26 = 0.0;
  get_result(test26, x26, &r26);
  double cp26 = 9.45 / 3.26;
  ck_assert_double_eq_tol(r26, cp26, EPS);
}
END_TEST

START_TEST(test27) {
  char *test27 = "0*3";
  double r27 = 0.0;
  double x27 = 0.0;
  get_result(test27, x27, &r27);
  double cp27 = 0 * 3;
  ck_assert_double_eq_tol(r27, cp27, EPS);
}
END_TEST

START_TEST(test28) {
  char *test28 = "0^(-1)";
  double r28 = 0.0;
  double x28 = 0.0;
  get_result(test28, x28, &r28);
  double cp28 = INFINITY;
  ck_assert_double_eq(r28, cp28);
}
END_TEST

START_TEST(test29) {
  char *test29 = "ln0";
  double r29 = 0.0;
  double x29 = 0.0;
  get_result(test29, x29, &r29);
  double cp29 = -INFINITY;
  ck_assert_double_eq(r29, cp29);
}
END_TEST

START_TEST(test30) {
  char *test30 = "-0";
  double r30 = 0.0;
  double x30 = 0.0;
  get_result(test30, x30, &r30);
  double cp30 = 0;
  ck_assert_double_eq_tol(r30, cp30, EPS);
}
END_TEST

START_TEST(test31) {
  char *test31 = "sin(2.14/2.1)";
  double r31 = 0.0;
  double x31 = 0.0;
  get_result(test31, x31, &r31);
  double cp31 = sin(2.14 / 2.1);
  ck_assert_double_eq_tol(r31, cp31, EPS);
}
END_TEST

START_TEST(test32) {
  char *test32 = "sin(0)";
  double r32 = 0.0;
  double x32 = 0.0;
  get_result(test32, x32, &r32);
  double cp32 = sin(0);
  ck_assert_double_eq_tol(r32, cp32, EPS);
}
END_TEST

START_TEST(test33) {
  char *test33 = "-sin(2.14/2.1)";
  double r33 = 0.0;
  double x33 = 0.0;
  get_result(test33, x33, &r33);
  double cp33 = -sin(2.14 / 2.1);
  ck_assert_double_eq_tol(r33, cp33, EPS);
}
END_TEST

START_TEST(test34) {
  char *test34 = "cos(2.14)";
  double r34 = 0.0;
  double x34 = 0.0;
  get_result(test34, x34, &r34);
  double cp34 = cos(2.14);
  ck_assert_double_eq_tol(r34, cp34, EPS);
}
END_TEST

START_TEST(test35) {
  char *test35 = "cos(0)";
  double r35 = 0.0;
  double x35 = 0.0;
  get_result(test35, x35, &r35);
  double cp35 = cos(0);
  ck_assert_double_eq_tol(r35, cp35, EPS);
}
END_TEST

START_TEST(test36) {
  char *test36 = "cos(2.14/2.1)+(10.01)*(-1.1)";
  double r36 = 0.0;
  double x36 = 0.0;
  get_result(test36, x36, &r36);
  double cp36 = cos(2.14 / 2.1) + (10.01) * (-1.1);
  ck_assert_double_eq_tol(r36, cp36, EPS);
}
END_TEST

START_TEST(test37) {
  char *test37 = "tan(0)";
  double r37 = 0.0;
  double x37 = 0.0;
  get_result(test37, x37, &r37);
  double cp37 = tan(0);
  ck_assert_double_eq_tol(r37, cp37, EPS);
}
END_TEST

START_TEST(test38) {
  char *test38 = "tan(2.14/4.01)";
  double r38 = 0.0;
  double x38 = 0.0;
  get_result(test38, x38, &r38);
  double cp38 = tan(2.14 / 4.01);
  ck_assert_double_eq_tol(r38, cp38, EPS);
}
END_TEST

START_TEST(test39) {
  char *test39 = "-tan(2.14/4.01)";
  double r39 = 0.0;
  double x39 = 0.0;
  get_result(test39, x39, &r39);
  double cp39 = -tan(2.14 / 4.01);
  ck_assert_double_eq_tol(r39, cp39, EPS);
}
END_TEST

START_TEST(test40) {
  char *test40 = "asin(-0.91)";
  double r40 = 0.0;
  double x40 = 0.0;
  get_result(test40, x40, &r40);
  double cp40 = asin(-0.91);
  ck_assert_double_eq_tol(r40, cp40, EPS);
}
END_TEST

START_TEST(test41) {
  char *test41 = "acos(0)";
  double r41 = 0.0;
  double x41 = 0.0;
  get_result(test41, x41, &r41);
  double cp41 = acos(0);
  ck_assert_double_eq_tol(r41, cp41, EPS);
}
END_TEST

START_TEST(test42) {
  char *test42 = "atan(-1.01)";
  double r42 = 0.0;
  double x42 = 0.0;
  get_result(test42, x42, &r42);
  double cp42 = atan(-1.01);
  ck_assert_double_eq_tol(r42, cp42, EPS);
}
END_TEST

START_TEST(test43) {
  char *test43 = "2^2^2^2";
  double r43 = 0.0;
  double x43 = 0.0;
  get_result(test43, x43, &r43);
  double cp43 = pow(2, pow(2, pow(2, 2)));
  ck_assert_double_eq_tol(r43, cp43, EPS);
}
END_TEST

Suite *calc_math(void) {
  Suite *s;
  TCase *tc_math;
  s = suite_create("calc_math");
  tc_math = tcase_create("math");
  tcase_add_test(tc_math, test1);
  tcase_add_test(tc_math, test2);
  tcase_add_test(tc_math, test3);
  tcase_add_test(tc_math, test4);
  tcase_add_test(tc_math, test5);
  tcase_add_test(tc_math, test6);
  tcase_add_test(tc_math, test7);
  tcase_add_test(tc_math, test8);
  tcase_add_test(tc_math, test9);
  tcase_add_test(tc_math, test10);
  tcase_add_test(tc_math, test11);
  tcase_add_test(tc_math, test12);
  tcase_add_test(tc_math, test13);
  tcase_add_test(tc_math, test14);
  tcase_add_test(tc_math, test15);
  tcase_add_test(tc_math, test16);
  tcase_add_test(tc_math, test17);
  tcase_add_test(tc_math, test18);
  tcase_add_test(tc_math, test19);
  tcase_add_test(tc_math, test20);
  tcase_add_test(tc_math, test21);
  tcase_add_test(tc_math, test22);
  tcase_add_test(tc_math, test23);
  tcase_add_test(tc_math, test24);
  tcase_add_test(tc_math, test25);
  tcase_add_test(tc_math, test26);
  tcase_add_test(tc_math, test27);
  tcase_add_test(tc_math, test28);
  tcase_add_test(tc_math, test29);
  tcase_add_test(tc_math, test30);

  tcase_add_test(tc_math, test31);
  tcase_add_test(tc_math, test32);
  tcase_add_test(tc_math, test33);
  tcase_add_test(tc_math, test34);
  tcase_add_test(tc_math, test35);
  tcase_add_test(tc_math, test36);
  tcase_add_test(tc_math, test37);
  tcase_add_test(tc_math, test38);
  tcase_add_test(tc_math, test39);
  tcase_add_test(tc_math, test40);
  tcase_add_test(tc_math, test41);
  tcase_add_test(tc_math, test42);
  tcase_add_test(tc_math, test43);
  suite_add_tcase(s, tc_math);
  return s;
}

void calc_test(SRunner **sr) { *sr = srunner_create(calc_math()); }

int main(void) {
  int number_failed;
  SRunner *sr = NULL;
  calc_test(&sr);
  srunner_run_all(sr, CK_ENV);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
