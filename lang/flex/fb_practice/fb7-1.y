/**************************************
 * 
 * fb7-1.y
 * 
 *************************************/

%{
%}

	/* %token A */

%%
start: x 'D' 'B'
	| y 'D' 'C'
	;

x: 'A';
y: 'A';
%%