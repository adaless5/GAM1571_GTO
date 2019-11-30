#version 120

attribute vec2 a_Position;
attribute vec2 a_UV;
attribute vec4 a_Color;

uniform vec2 u_ObjectTranslation;
uniform vec2 u_CameraTranslation;
uniform vec2 u_ProjectionScale;

varying vec2 v_UV;

void main()
{
    vec2 pos = a_Position;

    pos += u_ObjectTranslation;
    pos += u_CameraTranslation;
    pos *= u_ProjectionScale;

    // Hacked up projection for make building 3D.
    pos *= 1 + a_Color.r;

    gl_Position = vec4( pos, -0.1*a_Color.r, 1 );

	vec2 u_UVScale = vec2( 1, 1 ); //vec2( 16.0/256.0, 16.0/128.0 );
	vec2 u_UVTranslation = vec2( 0, 0 ); //vec2( 51.0/256.0, 61.0/128.0 );

    v_UV = a_UV * u_UVScale + u_UVTranslation;
}
