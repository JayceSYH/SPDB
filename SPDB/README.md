###In this project, we define a code practice
####use reference or pointer：
	1.when you use a variable's reference as a function's parameter, use reference(&) instead of pointer(*)
	>  eg :
	>    void func(A &a)  YES
	>    void func(A* a)  NO
	2.when the return value is one of the function parameter, use reference(&) as return value
	>  eg:
	>    A& func(A&) YES
	>    A* func(A&) NO
	3.when you return a variable create in heap in this function, return pointer(*) instead of reference(&)
	>  eg:
	>    A* func(B&) YES
	>    A& func(B&) NO
