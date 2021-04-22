#pragma once

struct Hit_Box {int left_edge, right_edge, top_edge, bottom_edge;};

bool Collision_check(Hit_Box A, Hit_Box B);
