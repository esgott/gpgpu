/*
 *
 * Copyright © 2010-2011 Balázs Tóth <tbalazs@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include "camera.hpp"
#include <string>
#include <GL/glew.h>

Camera::Camera(void) :
        aspectRatio(1), pos(0, 0, -15), forward(0, 0, 1), right(-1, 0, 0), up(0, 1, 0), speed(10) {
    dragStartX = 0;
    dragStartY = 0;
}

void Camera::control(float deltaTime, bool* inputs) {
    // Camera controls
    if (inputs['w']) {
        pos += forward * speed * deltaTime;
    }
    if (inputs['s']) {
        pos -= forward * speed * deltaTime;
    }
    if (inputs['a']) {
        pos += right * speed * deltaTime;
    }
    if (inputs['d']) {
        pos -= right * speed * deltaTime;
    }
    if (inputs['e']) {
        pos += up * speed * deltaTime;
    }
    if (inputs['q']) {
        pos -= up * speed * deltaTime;
    }
}

void Camera::startDrag(int x, int y) {
    dragStartX = x;
    dragStartY = y;
}

void Camera::drag(int x, int y) {
    int dx = dragStartX - x;
    int dy = dragStartY - y;

    forward = forward.normalize();
    right = forward.cross(Vector(0, 1, 0));
    up = right.cross(forward);

    forward = forward.rotate(dx * 0.003, Vector(0, 1, 0));
    forward = forward.rotate(-dy * 0.003, right);

    dragStartX = x;
    dragStartY = y;
}

Matrix4x4 Camera::getViewDirMatrix() {
    Matrix4x4 viewRotationMatrix, projMatrix;
    viewRotationMatrix.makeViewRotation(forward);
    projMatrix.makeProj(1.5, aspectRatio, 0.1, 1000);
    return (projMatrix * viewRotationMatrix).invert();
}
