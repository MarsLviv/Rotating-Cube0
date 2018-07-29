#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;// input data - matrix after transformations

attribute vec4 a_position; // input data - coordinates of vertices
attribute vec3 a_color; // input data - my color

varying vec3 v_color;// need to send data to fragment shader

void main(){
    gl_Position = mvp_matrix * a_position;// Calculate vertex position in screen space

    v_color = a_color;// send data to fragment shader
}

