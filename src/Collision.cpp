#include "../include/Collision.h"

/*
* checks for a collision between the Hit boxes
*/
bool Collision_check(Hit_Box A, Hit_Box B) {
	bool Collision = true;

	if (A.RE < B.LE && A.LE < B.RE) {
		Collision = false;
	}
	else if (A.LE > B.RE && A.RE > B.LE) {
		Collision = false;
	}
	else if (A.BE < B.TE && A.TE < B.BE) {
		Collision = false;
	}
	else if (A.TE > B.BE && A.BE > B.TE) {
		Collision = false;
	}

	return Collision;
}