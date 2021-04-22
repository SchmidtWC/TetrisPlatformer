#include "Collision.h"

/*
* checks for a collision between the Hit boxes
*/
bool Collision_check(Hit_Box A, Hit_Box B) {
	bool Collision = true;

	if (A.right_edge < B.left_edge && A.left_edge < B.right_edge) {
		Collision = false;
	}
	else if (A.left_edge > B.right_edge && A.right_edge > B.left_edge) {
		Collision = false;
	}

	else if (A.bottom_edge < B.top_edge && A.top_edge < B.bottom_edge) {
		Collision = false;
	}
	else if (A.top_edge > B.bottom_edge && A.bottom_edge > B.top_edge) {
		Collision = false;
	}

	return Collision;
}