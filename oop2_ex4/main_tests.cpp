//#define NAHUM_TESTS
//#define MATANEL_TESTS
#define AKIVA_TESTS


//-------------- include section ---------------
#ifdef NAHUM_TESTS
#undef MATANEL_TESTS
#undef AKIVA_TESTS
#include "nahum_tests.cpp"
#endif // NAHUM_TESTS
#ifdef MATANEL_TESTS
#undef NAHUM_TESTS
#undef AKIVA_TESTS
#include "matanel_tests.cpp"
#endif // MATANEL_TESTS
#ifdef AKIVA_TESTS
#undef NAHUM_TESTS
#undef MATANEL_TESTS
#include "akiva_tests.cpp"
#endif // AKIVA_TESTS


//-------------- using section -----------------
void nahum_main();
void matanel_main();
void akiva_main();

//--------------- main -------------------------
int main() {

#ifdef NAHUM_TESTS
#undef MATANEL_TESTS
#undef AKIVA_TESTS
	nahum_main();
#endif // NAHUM_TESTS

#ifdef MATANEL_TESTS
	matanel_main();
#endif // MATANEL_TESTS

#ifdef AKIVA_TESTS
	akiva_main();
#endif // AKIVA_TESTS

	return 0;
}