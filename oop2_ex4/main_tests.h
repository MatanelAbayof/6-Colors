#pragma once
//---------- define current test -----------------
//#define NAHUM_TESTS
//#define MATANEL_TESTS
#define AKIVA_TESTS




//----------- undefs ----------------------------
#pragma region Undefs
#ifdef NAHUM_TESTS
#undef MATANEL_TESTS
#undef AKIVA_TESTS
#endif // NAHUM_TESTS
#ifdef MATANEL_TESTS
#undef NAHUM_TESTS
#undef AKIVA_TESTS
#endif // MATANEL_TESTS
#ifdef AKIVA_TESTS
#undef NAHUM_TESTS
#undef MATANEL_TESTS
#endif // AKIVA_TESTS
#pragma endregion