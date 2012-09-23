#ifndef H_ARGS_MACROS_H
	#define H_ARGS_MACROS_H


	/* Theses macros are used to make key_value pairs from function arguments names and values */

	#define OTOS(S) Utils::otos(S).c_str()


	#define TO_STR_1(A) OTOS(A)
	#define TO_STR_2(A,B) OTOS(A),OTOS(B)
	#define TO_STR_3(A,B,C) OTOS(A),OTOS(B),OTOS(C)
	#define TO_STR_4(A,B,C,D) OTOS(A),OTOS(B),OTOS(C),OTOS(D)
	#define TO_STR_5(A,B,C,D,E) OTOS(A),OTOS(B),OTOS(C),OTOS(D),OTOS(E)
	#define TO_STR_6(A,B,C,D,E,F) OTOS(A),OTOS(B),OTOS(C),OTOS(D),OTOS(E),OTOS(F)


	#define REC_ARGS(...) Utils::index_variables_key_value(ARG_LIST_STR(__VA_ARGS__), ##__VA_ARGS__ )

	#define REC_ARGS_1( A ) Utils::index_variables_key_value(Utils::get_variable_names(1,#A), TO_STR_1( A ) )
	#define REC_ARGS_2( A, B ) Utils::index_variables_key_value(Utils::get_variable_names(2, #A, #B ), TO_STR_2( A, B ) )
	#define REC_ARGS_3( A, B, C ) Utils::index_variables_key_value(Utils::get_variable_names(3, #A, #B, #C ), TO_STR_3( A, B, C) )
	#define REC_ARGS_4( A, B, C, D ) Utils::index_variables_key_value(Utils::get_variable_names(4, #A, #B, #C, #D ), TO_STR_4( A, B, C, D ) )
	#define REC_ARGS_5( A, B, C, D, E ) Utils::index_variables_key_value(Utils::get_variable_names(5, #A, #B, #C, #D, #E ), TO_STR_5( A, B, C, D, E ) )
	#define REC_ARGS_6( A, B, C, D, E, F ) Utils::index_variables_key_value(Utils::get_variable_names(6, #A, #B, #C, #D, #E, #F ), TO_STR_6(  A, B, C, D, E, F ) )
	#define REC_ARGS_7( A, B, C, D, E, F, G ) Utils::index_variables_key_value(Utils::get_variable_names(7, #A, #B, #C, #D, #E, #F,#G ), TO_STR_7(  A, B, C, D, E, F, G ) )


	#define PUT_VAR_IN_URL(URL,var) Utils::put_variable_in_url( URL, #var, OTOS(var) )


	/* That was an experimental arg counter */
	// #define VA_NUM_ARGS(...) VA_NUM_ARGS_IMPL(__VA_ARGS__, 9,8,7,6,5,4,3,2,1)
	// #define VA_NUM_ARGS_IMPL(_1,_2,_3,_4,_5,_6,_7,_8,_9,N,...) N

#endif