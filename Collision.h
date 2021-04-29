#pragma once

struct Hit_Box {int LE, RE, TE, BE;};

bool Collision_check(Hit_Box A, Hit_Box B);
